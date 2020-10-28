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
		m_graph.clear();

		// 获得参数表达式
		m_W = parameter(m_graph, m_pW);
		m_b = parameter(m_graph, m_pb);
		m_V = parameter(m_graph, m_pV);
		m_a = parameter(m_graph, m_pa);

		// 设置输入表达式
		m_x_values.resize(2, 0.0);
		dynet::Expression x = input(m_graph, { 2 }, &m_x_values);
		// 设置输出表达式
		m_y_value = 0.0;  
		dynet::Expression y = input(m_graph, &m_y_value);
		// 获得预测表达式
		m_y_pred = m_V * tanh(m_W * x + m_b) + m_a;
		// 获得损失表达式
		m_loss_expr = squared_distance(m_y_pred, y);
	}

	double Training()
	{
		double loss = 0;

		for (unsigned mi = 0; mi < 4; ++mi) {
			bool x1 = mi % 2;
			bool x2 = (mi / 2) % 2;
			// 设置输入值
			m_x_values[0] = x1 ? 1.0f : -1.0f;
			m_x_values[1] = x2 ? 1.0f : -1.0f;
			// 设置输出值
			m_y_value = (x1 != x2) ? 1.0f : -1.0f;
			// 获取损失
			loss += as_scalar(m_graph.forward(m_loss_expr));
			// 计算反向传播
			m_graph.backward(m_loss_expr);
			// 更新训练
			m_trainer.update();
		}

		++m_train_round;

		return loss / 4;
	}

	double Output(double x1, double x2)
	{
		m_x_values[0] = (dynet::real)x1;
		m_x_values[1] = (dynet::real)x2;
		return as_scalar(m_graph.forward(m_y_pred));
	}

private:
	dynet::SimpleSGDTrainer m_trainer;
	dynet::ComputationGraph m_graph;

private:
	dynet::Parameter m_pW;
	dynet::Parameter m_pb;
	dynet::Parameter m_pV;
	dynet::Parameter m_pa;

private:
	dynet::Expression m_W;
	dynet::Expression m_b;
	dynet::Expression m_V;
	dynet::Expression m_a;
	dynet::Expression m_loss_expr;
	dynet::Expression m_y_pred;

private:
	std::vector<dynet::real> m_x_values;
	dynet::real m_y_value = 0.0;
};

#endif