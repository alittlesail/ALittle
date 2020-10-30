#ifndef DEEPLEARNING_XOR_INCLUDED
#define DEEPLEARNING_XOR_INCLUDED

#include "dynet/training.h"
#include "dynet/expr.h"
#include "dynet/io.h"
#include "dynet/model.h"

#include "deeplearning_model.hpp"

class DeeplearningXorModel : public DeeplearningModel
{
public:
	DeeplearningXorModel() : m_trainer(m_collection)
	{
		const unsigned int hidden_size = 8;
		m_pW = m_collection.add_parameters({ hidden_size, 2 });
		m_pb = m_collection.add_parameters({ hidden_size });
		m_pV = m_collection.add_parameters({ 1, hidden_size });
		m_pa = m_collection.add_parameters({ 1 });
	}

public:
	void Init(const char* model_path)
	{
		if (model_path != nullptr)
		{
			dynet::TextFileLoader loader(model_path);
			loader.populate(m_collection);
		}

		// 重置
		m_trainer.restart();
	}

	size_t TrainInit() override
	{
		m_x_values.push_back({ 1.0f, 1.0f });
		m_y_value.push_back(-1.0f);

		m_x_values.push_back({ -1.0f, -1.0f });
		m_y_value.push_back(-1.0f);

		m_x_values.push_back({ -1.0f, 1.0f });
		m_y_value.push_back(1.0f);

		m_x_values.push_back({ 1.0f, -1.0f });
		m_y_value.push_back(1.0f);

		return m_y_value.size();
	}

	void TrainRelease() override
	{
		m_x_values.clear();
		m_y_value.clear();
	}
	
	double Training(size_t index, size_t& right_count) override
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		auto x_values = m_x_values[index];
		float y_value = m_y_value[index];

		dynet::ComputationGraph cg;
		
		// 获得参数表达式
		const auto W = parameter(cg, m_pW);
		const auto b = parameter(cg, m_pb);
		const auto V = parameter(cg, m_pV);
		const auto a = parameter(cg, m_pa);

		// 设置输入表达式
		const auto x = input(cg, { 2 }, &x_values);
		// 设置输出表达式
		const auto y = input(cg, &y_value);
		// 获得预测表达式
		const auto y_pred = V * tanh(W * x + b) + a;
		// 获得损失表达式
		const auto loss_expr = squared_distance(y_pred, y);

		// 获取损失		
		const double loss = as_scalar(cg.forward(loss_expr));

		// 计算反向传播
		cg.backward(loss_expr);
		// 更新训练
		m_trainer.update();

		return loss;
	}

	double Output(double x1, double x2)
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		std::vector<float> x_values;		
		x_values[0] = static_cast<float>(x1);
		x_values[1] = static_cast<float>(x2);

		dynet::ComputationGraph cg;

		// 获得参数表达式
		const auto W = parameter(cg, m_pW);
		const auto b = parameter(cg, m_pb);
		const auto V = parameter(cg, m_pV);
		const auto a = parameter(cg, m_pa);

		// 设置输入表达式
		const auto x = input(cg, { 2 }, &x_values);
		// 获得预测表达式
		const auto y_pred = V * tanh(W * x + b) + a;
		
		return as_scalar(cg.forward(y_pred));
	}

private:
	dynet::SimpleSGDTrainer m_trainer;

private:
	dynet::Parameter m_pW;
	dynet::Parameter m_pb;
	dynet::Parameter m_pV;
	dynet::Parameter m_pa;

private:
	std::vector<std::vector<float>> m_x_values;
	std::vector<float> m_y_value;
};

#endif