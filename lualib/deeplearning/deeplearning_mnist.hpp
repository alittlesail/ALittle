#ifndef DEEPLEARNING_MNIST_INCLUDED
#define DEEPLEARNING_MNIST_INCLUDED

#include "dynet/training.h"
#include "dynet/expr.h"
#include "dynet/io.h"
#include "dynet/model.h"
#include "other/mlp.h"

#include "deeplearning_model.hpp"
#include "carp_surface.hpp"
#include "carp_surface_bind.hpp"

class DeeplearningMnistModel : public DeeplearningModel
{
public:
	DeeplearningMnistModel() : m_trainer(m_collection)
		, m_mlp(m_collection, std::vector<dynet::Layer>({
		        dynet::Layer(/* input_dim */ IMAGE_SIZE* IMAGE_SIZE, /* output_dim */ 512, /* activation */ dynet::RELU, /* dropout_rate */ 0.2f),
		        dynet::Layer(/* input_dim */ 512, /* output_dim */ 512, /* activation */ dynet::RELU, /* dropout_rate */ 0.2f),
		        dynet::Layer(/* input_dim */ 512, /* output_dim */ 10, /* activation */ dynet::LINEAR, /* dropout_rate */ 0.0f)
			}))
	{
		m_trainer.clip_threshold *= BATCH_SIZE;
	}

private:
	static int ReverseInt(int i)
	{
		unsigned char ch1, ch2, ch3, ch4;
		ch1 = i & 255;
		ch2 = (i >> 8) & 255;
		ch3 = (i >> 16) & 255;
		ch4 = (i >> 24) & 255;
		return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
	}

	// 读取图像数据
	// Code from https://compvisionlab.wordpress.com/2014/01/01/c-code-for-reading-mnist-data-set/ to read MNIST
	static bool ReadMnist(const std::string& data_file, std::vector<std::vector<float>>& arr)
	{
		std::ifstream file(data_file, std::ios::binary);
		if (!file.is_open()) return false;
			
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);
		arr.resize(number_of_images);
		for (int i = 0; i < number_of_images; ++i)
		{
			arr[i].reserve(n_rows * n_cols);
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					arr[i].push_back((float)temp);
				}
			}
		}

		return true;
	}

	// 读取标记数据
	static bool ReadMnistLabels(const std::string& label_file, std::vector<unsigned>& labels)
	{
		std::ifstream file(label_file, std::ios::binary);
		if (!file.is_open()) return false;
		
		int magic_number = 0;
		int number_of_images = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		labels.reserve(number_of_images);
		for (int i = 0; i < number_of_images; ++i)
		{
			unsigned char temp = 0;
			file.read((char*)&temp, sizeof(temp));
			labels.push_back((unsigned)temp);
		}
		return true;
	}

public:
	void Init(const char* model_path, const char* train_image, const char* train_labels)
	{
		if (model_path != nullptr)
		{
			dynet::TextFileLoader loader(model_path);
			loader.populate(m_collection);
		}
		
		m_mnist_train.clear();
		m_mnist_train_labels.clear();
		m_train_order.clear();

		// 如果有填充
		if (train_image && train_labels)
		{
			ReadMnist(train_image, m_mnist_train);
			ReadMnistLabels(train_labels, m_mnist_train_labels);
			
			// 计算批次数量
			auto num_batches = m_mnist_train.size() / BATCH_SIZE - 1;
			m_train_order.resize(num_batches);
			for (int i = 0; i < (int)num_batches; ++i) m_train_order[i] = i;
			std::random_shuffle(m_train_order.begin(), m_train_order.end());
		}
		m_train_index = 0;

		// 重置
		m_trainer.restart();

	}

	double Training()
	{
		// 启用dropout
		m_mlp.enable_dropout();
		
		// 构建动态图
		dynet::ComputationGraph cg;
		// 计算当前批次的下标和大小
		int id = m_train_order[m_train_index] * BATCH_SIZE;
		unsigned bsize = std::min((unsigned)m_mnist_train.size() - id, BATCH_SIZE);
		// 设置当前批次的输入
		std::vector<dynet::Expression> cur_batch(bsize);
		std::vector<unsigned> cur_labels(bsize);
		for (unsigned idx = 0; idx < bsize; ++idx)
		{
			cur_batch[idx] = input(cg, { IMAGE_SIZE * IMAGE_SIZE }, m_mnist_train[id + idx]);
			cur_labels[idx] = m_mnist_train_labels[id + idx];
		}
		// 把所有输入合并为一个矩阵
		dynet::Expression x_batch = reshape(concatenate_cols(cur_batch), dynet::Dim({ IMAGE_SIZE * IMAGE_SIZE }, bsize));
		// 构建 负对数似然 模型
		dynet::Expression loss_expr = m_mlp.get_nll(x_batch, cur_labels, cg);
		// 累计损失值
		double loss = as_scalar(cg.forward(loss_expr));
		// 反向传播
		cg.backward(loss_expr);
		// 更新参数
		m_trainer.update();

		++m_train_index;
		if (m_train_index >= (int)m_train_order.size())
			m_train_index = 0;
		return loss / bsize;
	}

	int Output(size_t address)
	{
		CarpSurface* surface = nullptr;
		memcpy(&surface, &address, sizeof(size_t));
		
		if (surface == nullptr) return -1;
		if (surface->GetWidth() == 0 || surface->GetHeight() == 0) return -1;
		
		std::vector<float> data;

		// 如果图片不是指定大小那么就进行缩放
		if (surface->GetWidth() == IMAGE_SIZE && surface->GetHeight() == IMAGE_SIZE)
		{
			data.resize(IMAGE_SIZE * IMAGE_SIZE, 0.0f);
			for (unsigned i = 0; i < IMAGE_SIZE * IMAGE_SIZE; ++i)
				data[i] = (float)surface->GetGray(i);
		}
		else
		{
			CarpSurface new_surface(IMAGE_SIZE, IMAGE_SIZE);
			new_surface.ScaleFrom(surface, nullptr, nullptr);

			data.resize(IMAGE_SIZE * IMAGE_SIZE, 0.0f);
			for (unsigned i = 0; i < IMAGE_SIZE * IMAGE_SIZE; ++i)
				data[i] = (float)new_surface.GetGray(i);
		}

		m_mlp.disable_dropout();

		// 构建动态图
		dynet::ComputationGraph cg;
		// 设置当前输入
		dynet::Expression x = input(cg, { IMAGE_SIZE* IMAGE_SIZE }, data);
		// 构建 负对数似然 模型，并进行预测
		return (int)m_mlp.predict(x, cg);
	}

	void Save(const char* file_path)
	{
		dynet::TextFileSaver saver(file_path);
		saver.save(m_collection);
	}

private:
	dynet::AdamTrainer m_trainer;
	dynet::ParameterCollection m_collection;
	
private:
	dynet::MLP m_mlp;

	std::vector<std::vector<float>> m_mnist_train;
	std::vector<unsigned> m_mnist_train_labels;
	std::vector<int> m_train_order;
	unsigned int m_train_index = 0;

private:
	static const unsigned BATCH_SIZE = 128;
	static const unsigned IMAGE_SIZE = 28;
};

#endif