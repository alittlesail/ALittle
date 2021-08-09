#ifndef DEEPLEARNING_XOR_INCLUDED
#define DEEPLEARNING_XOR_INCLUDED

#include "torch/torch.h"
#include "deeplearning_model.hpp"

class DeeplearningXorModel : public DeeplearningModel
{
public:
	DeeplearningXorModel()
	{
		const unsigned int hidden_size = 8;
		m_fc1 = register_module("fc1", torch::nn::Linear(2, hidden_size));
		m_fc2 = register_module("fc2", torch::nn::Linear(hidden_size, 1));

		m_trainer = std::make_shared<torch::optim::SGD>(parameters(), torch::optim::SGDOptions(0.02));
	}

public:
	int TrainInit() override
	{
		m_x_values.push_back({ 0.0f, 0.0f });
		m_y_value.push_back(0.0f);

		m_x_values.push_back({ 0.0f, 1.0f });
		m_y_value.push_back(1.0f);

		m_x_values.push_back({ 1.0f, 0.0f });
		m_y_value.push_back(1.0f);

		m_x_values.push_back({ 1.0f, 1.0f });
		m_y_value.push_back(0.0f);

		return static_cast<int>(m_y_value.size());
	}

	void TrainRelease() override
	{
		m_x_values.clear();
		m_y_value.clear();
	}
	
	double Training(size_t index, bool& right) override
	{
		// 重置误差项
		m_trainer->zero_grad();
		
		// 设置输入
		torch::Tensor input = torch::from_blob(m_x_values[index].data(), { 2 });

		// 执行运算
		auto t = m_fc1->forward(input);
		t = torch::sigmoid(t);
		auto output = m_fc2->forward(t);

		// 判断预测是否正确
		right = std::fabs(output.item().toFloat() - m_y_value[index]) < 0.00001f;

		// 设置输出表达式
		auto target = torch::from_blob(&m_y_value[index], {1});

		torch::nn::MSELoss loss_func;
		// 获得损失表达式
		auto loss_expr = loss_func->forward(output, target);
		auto loss = loss_expr.item().toDouble();
		
		// 计算反向传播
		loss_expr.backward();
		// 更新训练
		m_trainer->step();

		return loss;
	}

	float Output(float x1, float x2)
	{
		std::vector<float> x_values;
		x_values.push_back(x1);
		x_values.push_back(x2);
		torch::Tensor input = torch::from_blob(x_values.data(), { 2 });

		auto t = m_fc1->forward(input);
		t = torch::sigmoid(t);
		auto output = m_fc2->forward(t);

		return output.item().toFloat();
	}

private:
	std::shared_ptr<torch::optim::SGD> m_trainer;

private:
	torch::nn::Linear m_fc1{nullptr};
	torch::nn::Linear m_fc2{nullptr};

private:
	std::vector<std::vector<float>> m_x_values;
	std::vector<float> m_y_value;
};

#endif