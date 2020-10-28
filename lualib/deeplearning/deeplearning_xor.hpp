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

		m_total_train_count = 4;
		m_cur_train_count = 0;
		m_train_round = 0;

		// 重置
		m_trainer.restart();
	}

	double Training() override
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		std::vector<dynet::real> x_values;
		dynet::real y_value = 0.0;

		dynet::ComputationGraph cg;
		
		// 获得参数表达式
		auto W = parameter(cg, m_pW);
		auto b = parameter(cg, m_pb);
		auto V = parameter(cg, m_pV);
		auto a = parameter(cg, m_pa);

		// 设置输入表达式
		x_values.resize(2, 0.0);
		dynet::Expression x = input(cg, { 2 }, &x_values);
		// 设置输出表达式
		y_value = 0.0;
		dynet::Expression y = input(cg, &y_value);
		// 获得预测表达式
		auto y_pred = V * tanh(W * x + b) + a;
		// 获得损失表达式
		auto loss_expr = squared_distance(y_pred, y);
		
		double loss = 0;

		for (unsigned mi = 0; mi < 4; ++mi) {
			bool x1 = mi % 2;
			bool x2 = (mi / 2) % 2;
			// 设置输入值
			x_values[0] = x1 ? 1.0f : -1.0f;
			x_values[1] = x2 ? 1.0f : -1.0f;
			// 设置输出值
			y_value = (x1 != x2) ? 1.0f : -1.0f;

			// 获取损失
			loss += as_scalar(cg.forward(loss_expr));
			// 计算反向传播
			cg.backward(loss_expr);
			// 更新训练
			m_trainer.update();
		}

		++m_train_round;

		return loss / 4;
	}

	double Output(double x1, double x2)
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		std::vector<dynet::real> x_values;
		dynet::real y_value = 0.0;
		
		x_values[0] = (dynet::real)x1;
		x_values[1] = (dynet::real)x2;

		dynet::ComputationGraph cg;

		// 获得参数表达式
		auto W = parameter(cg, m_pW);
		auto b = parameter(cg, m_pb);
		auto V = parameter(cg, m_pV);
		auto a = parameter(cg, m_pa);

		// 设置输入表达式
		x_values.resize(2, 0.0);
		dynet::Expression x = input(cg, { 2 }, &x_values);
		// 设置输出表达式
		y_value = 0.0;
		dynet::Expression y = input(cg, &y_value);
		// 获得预测表达式
		auto y_pred = V * tanh(W * x + b) + a;
		
		return as_scalar(cg.forward(y_pred));
	}

private:
	dynet::SimpleSGDTrainer m_trainer;

private:
	dynet::Parameter m_pW;
	dynet::Parameter m_pb;
	dynet::Parameter m_pV;
	dynet::Parameter m_pa;
};

#endif