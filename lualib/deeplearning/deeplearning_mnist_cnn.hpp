#ifndef DEEPLEARNING_MNIST_CNN_INCLUDED
#define DEEPLEARNING_MNIST_CNN_INCLUDED

#include "dynet/training.h"
#include "dynet/expr.h"
#include "dynet/io.h"
#include "dynet/model.h"

#include "deeplearning_model.hpp"
#include "carp_surface.hpp"

class DeeplearningMnistCNNModel : public DeeplearningModel
{
public:
	DeeplearningMnistCNNModel() : m_trainer(m_collection)
	{
		m_pConv1 = m_collection.add_parameters({ 5, 5, 1, 32 });
		m_pB1 = m_collection.add_parameters({ 32, });
		m_pConv2 = m_collection.add_parameters({ 5, 5, 32, 64 });
		m_pB2 = m_collection.add_parameters({ 64, });
		m_pW1 = m_collection.add_parameters({ HIDDEN_DIM, 7 * 7 * 64 });
		m_pB3 = m_collection.add_parameters({ HIDDEN_DIM, });
		m_pW2 = m_collection.add_parameters({ 10, HIDDEN_DIM });
	}

public:
	void Init(const char* model_path, const char* train_image, const char* train_labels)
	{
		StopTraining();
		
		if (model_path != nullptr)
		{
			dynet::TextFileLoader loader(model_path);
			loader.populate(m_collection);
		}

		m_train_image_path.clear();
		m_train_labels_path.clear();
		if (train_image) m_train_image_path = train_image;
		if (train_labels) m_train_labels_path = train_labels;
		
		m_mnist_train.clear();
		m_mnist_train_labels.clear();
		m_train_order.clear();

		// 如果有填充
		m_train_index = 0;

		m_total_train_count = 0;
		m_cur_train_count = 0;
		m_train_round = 0;
		m_cur_right_count = 0;

		// 重置
		m_trainer.restart();
	}

	dynet::Expression Build(dynet::ComputationGraph& cg, dynet::Expression x, bool dropout)
	{
		// 卷积参数
		dynet::Expression conv1 = dynet::parameter(cg, m_pConv1);
		// 偏置参数
		dynet::Expression b1 = dynet::parameter(cg, m_pB1);
		// 卷积
		dynet::Expression conv1_x = dynet::conv2d(x, conv1, b1, { 1, 1 }, false);
		// 激活
		dynet::Expression relu1_x = dynet::rectify(dynet::maxpooling2d(conv1_x, { 2, 2 }, { 2, 2 }));

		// 卷积参数
		dynet::Expression conv2 = dynet::parameter(cg, m_pConv2);
		// 偏置参数
		dynet::Expression b2 = dynet::parameter(cg, m_pB2);
		// 卷积
		dynet::Expression conv2_x = dynet::conv2d(relu1_x, conv2, b2, { 1, 1 }, false);
		// 激活
		dynet::Expression relu2_x = dynet::rectify(dynet::maxpooling2d(conv2_x, { 2, 2 }, { 2, 2 }));

		// 调整维度
		dynet::Expression reshape_x = dynet::reshape(relu2_x, { 7 * 7 * 64, 1 });

		// 线性变换
		dynet::Expression w1 = dynet::parameter(cg, m_pW1);
		dynet::Expression b3 = dynet::parameter(cg, m_pB3);
		dynet::Expression h = dynet::rectify(w1 * reshape_x + b3);

		if (dropout) h = dynet::dropout(h, DROPOUT_RATE);
		dynet::Expression w2 = dynet::parameter(cg, m_pW2);

		return w2 * h;
	}

	void TrainInit() override
	{
		if (m_train_image_path.size() && m_train_labels_path.size())
		{
			ReadMnist(m_train_image_path, m_mnist_train);
			for (auto& trains : m_mnist_train)
			{
				for (auto& value : trains)
					value /= 255.0f;
			}
			ReadMnistLabels(m_train_labels_path, m_mnist_train_labels);

			// 计算批次数量
			m_train_order.resize(m_mnist_train.size());
			for (int i = 0; i < (int)m_train_order.size(); ++i) m_train_order[i] = i;
			std::random_shuffle(m_train_order.begin(), m_train_order.end());

			m_total_train_count = (int)m_mnist_train.size();
		}
	}

	void TrainRelease() override
	{
		m_mnist_train.clear();
		m_mnist_train_labels.clear();
		m_train_order.clear();
	}

	double Training() override
	{
		if (m_train_order.empty()) return 0;
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		// 构建动态图
		dynet::ComputationGraph cg;
		// 计算当前批次的下标和大小
		int id = m_train_order[m_train_index];
		// 把所有输入合并为一个矩阵
		dynet::Expression x = input(cg, { IMAGE_SIZE, IMAGE_SIZE }, m_mnist_train[id]);
		// 获得隐藏层
		dynet::Expression output = Build(cg, x, true);

		// 预测
		auto label = Prediction(cg, output);
		if (label == m_mnist_train_labels[id])
			++m_cur_right_count;
		
		// 构建 负对数似然 模型
		dynet::Expression loss_expr = dynet::pickneglogsoftmax(output, m_mnist_train_labels[id]);
		// 累计损失值
		double loss = as_scalar(cg.forward(loss_expr));
		// 反向传播
		cg.backward(loss_expr);
		// 更新参数
		m_trainer.update();

		++m_train_index;
		m_cur_train_count += 1;
		if (m_train_index >= (int)m_train_order.size())
		{
			++m_train_round;
			m_cur_train_count = 0;
			m_cur_right_count = 0;
			m_train_index = 0;
		}
		return loss;
	}

	int Prediction(dynet::ComputationGraph& cg, dynet::Expression output)
	{
		// 预测
		dynet::Expression out = dynet::softmax(output);
		// Get values
		std::vector<float> probs = dynet::as_vector(cg.forward(out));
		// Get argmax
		int argmax = 0;
		for (int i = 1; i < (int)probs.size(); ++i) {
			if (probs[i] > probs[argmax])
				argmax = i;
		}

		return argmax;
	}

	int Output(size_t address)
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
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
				data[i] = (float)surface->GetGray(i) / 255.0f;
		}
		else
		{
			CarpSurface new_surface(IMAGE_SIZE, IMAGE_SIZE);
			new_surface.ScaleFrom(surface, nullptr, nullptr);

			data.resize(IMAGE_SIZE * IMAGE_SIZE, 0.0f);
			for (unsigned i = 0; i < IMAGE_SIZE * IMAGE_SIZE; ++i)
				data[i] = (float)new_surface.GetGray(i) / 255.0f;
		}

		// 构建动态图
		dynet::ComputationGraph cg;
		// 设置当前输入
		dynet::Expression x = input(cg, { IMAGE_SIZE, IMAGE_SIZE }, data);
		// 获得隐藏层
		dynet::Expression output = Build(cg, x, false);

		return Prediction(cg, output);
	}

private:
	dynet::SimpleSGDTrainer m_trainer;

private:
	dynet::Parameter m_pConv1;
	dynet::Parameter m_pB1;
	dynet::Parameter m_pConv2;
	dynet::Parameter m_pB2;
	dynet::Parameter m_pW1;
	dynet::Parameter m_pB3;
	dynet::Parameter m_pW2;
	
private:
	std::vector<std::vector<float>> m_mnist_train;
	std::vector<unsigned> m_mnist_train_labels;
	std::vector<int> m_train_order;
	unsigned int m_train_index = 0;

	std::string m_train_image_path;
	std::string m_train_labels_path;

private:
	static const unsigned HIDDEN_DIM = 1024;
	static const unsigned IMAGE_SIZE = 28;
	static constexpr float DROPOUT_RATE = 0.4f;
};

#endif