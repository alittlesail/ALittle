#ifndef DEEPLEARNING_MNIST_INCLUDED
#define DEEPLEARNING_MNIST_INCLUDED

#include "torch/torch.h"
#include "deeplearning_model.hpp"
#include "Carp/carp_surface.hpp"

class DeeplearningMnistModel : public DeeplearningModel
{
public:
	DeeplearningMnistModel()
		: m_conv1(torch::nn::Conv2dOptions(1, 64, 5))
		, m_conv2(torch::nn::Conv2dOptions(64, 128, 5))
		, m_fc1(4 * 4 * 128, 1024)
		, m_fc2(1024, 10)
	{
		register_module("conv1", m_conv1);
		register_module("conv2", m_conv2);
		register_module("conv2_drop", m_conv2_drop);
		register_module("fc1", m_fc1);
		register_module("fc2", m_fc2);

		m_trainer = std::make_shared<torch::optim::SGD>(parameters(), torch::optim::SGDOptions(0.01));
	}

public:
	void SetMnistRoot(const char* path)
	{
		if (path) m_mnist_path = path;
	}
	
	size_t TrainInit() override
	{
		auto data_loader = torch::data::make_data_loader(
			torch::data::datasets::MNIST(m_mnist_path).map(
				torch::data::transforms::Stack<>()), 1);

		m_images.clear();
		m_labels.clear();

		for (auto& example : *data_loader)
		{
			m_images.push_back(example.data);
			m_labels.push_back(example.target);
		}

		return m_images.size();
	}

	void TrainRelease() override
	{	
		m_images.clear();
		m_labels.clear();
	}
	
	double Training(size_t index, bool& right) override
	{
		// 重置误差项
		m_trainer->zero_grad();
		
		// 设置输入
		torch::Tensor input = m_images[index];
		
		// 执行运算
		auto output = forward(input, true);

		// 判断预测是否正确
		right = output.argmax().item().toInt() == m_labels[index].item().toInt();

		// 设置输出表达式
		auto target = m_labels[index];

		// 获得损失表达式
		auto loss_expr = torch::nll_loss(output, target);
		auto loss = loss_expr.item().toDouble();
		
		// 计算反向传播
		loss_expr.backward();
		// 更新训练
		m_trainer->step();

		return loss;
	}

	torch::Tensor forward(torch::Tensor x, bool training)
	{
		// 第一层卷积
		x = m_conv1->forward(x);
		x = torch::max_pool2d(x, 2);
		x = torch::relu(x);

		// 第二层卷积
		x = m_conv2->forward(x);
		x = m_conv2_drop->forward(x);
		x = torch::max_pool2d(x, 2);
		x = torch::relu(x);

		// 将矩阵转为
		x = x.view({ -1, 4 * 4 * 128 });

		// 第一层全连接
		x = m_fc1->forward(x);
		x = torch::relu(x);

		// dropout
		x = torch::dropout(x, /*p=*/0.5, training);

		// 第二层全连接
		x = m_fc2->forward(x);
		return torch::log_softmax(x, /*dim=*/1);
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
				data[i] = static_cast<float>(surface->GetGray(i)) / 255.0f;
		}
		else
		{
			CarpSurface new_surface(IMAGE_SIZE, IMAGE_SIZE);
			new_surface.ScaleFrom(surface, nullptr, nullptr);

			data.resize(IMAGE_SIZE * IMAGE_SIZE, 0.0f);
			for (unsigned i = 0; i < IMAGE_SIZE * IMAGE_SIZE; ++i)
				data[i] = static_cast<float>(new_surface.GetGray(i)) / 255.0f;
		}

		torch::Tensor input = torch::from_blob(data.data(), { 1 /*批次数量*/, 1 /*通道数*/, IMAGE_SIZE /*宽*/, IMAGE_SIZE /*高*/ });

		// 执行运算
		auto output = forward(input, false);

		return output.argmax().item().toInt();
	}

private:
	std::shared_ptr<torch::optim::SGD> m_trainer;

private:
	torch::nn::Conv2d m_conv1;
	torch::nn::Conv2d m_conv2;
	torch::nn::Dropout2d m_conv2_drop;
	torch::nn::Linear m_fc1;
	torch::nn::Linear m_fc2;

private:
	std::vector<torch::Tensor> m_images;
	std::vector<torch::Tensor> m_labels;
	std::string m_mnist_path;

	static const unsigned IMAGE_SIZE = 28;
};

#endif