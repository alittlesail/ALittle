#ifndef DEEPLEARNING_XOR_INCLUDED
#define DEEPLEARNING_XOR_INCLUDED

#include "Carp/carp_robot_model.hpp"
#include "deeplearning_model.hpp"

class DeeplearningXorModel : public DeeplearningModel
{
public:
	DeeplearningXorModel()
		: m_fc1(m_model, 2, 8), m_fc2(m_model, 8, 1)
		, m_trainer(m_model)
	{
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
		// 这里故意阻塞10毫秒，因为担心速度太快卡到界面
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		CarpRobotComputationGraph graph;

		m_fc1.Build(graph);
		m_fc2.Build(graph);
		auto input = graph.AddInput(CarpRobotDim({ 2 }), &m_x_values[index]);
		auto target = graph.AddInput(&m_y_value[index]);

		auto sigmod = m_fc1.Forward(input).Sigmoid();
		auto out_expr = m_fc2.Forward(sigmod);
		auto out = out_expr.GetValue().AsScalar();

		auto loss_expr = (out_expr - target).Square();
		auto loss = loss_expr.GetValue().AsScalar();

		right = std::abs(out - m_y_value[index]) < 0.0001;

		graph.Backward();
		m_trainer.Update();
		
		return loss;
	}

	float Output(float x1, float x2)
	{
		CarpRobotComputationGraph graph;

		m_fc1.Build(graph);
		m_fc2.Build(graph);

		std::vector<float> x_values;
		x_values.push_back(x1);
		x_values.push_back(x2);
		auto x = graph.AddInput(CarpRobotDim({ 2 }), &x_values);
		auto out_1 = m_fc1.Forward(x);
		out_1 = out_1.Sigmoid();
		auto out_2 = m_fc2.Forward(out_1);

		return out_2.GetValue().AsScalar();
	}

	void Load(const char* file_path) override
	{
		CarpRobotModelDeserializer file;
		if (!file.Open(file_path)) return;
		m_model.Deserialize(file);
	}

	void Save(const char* file_path) override
	{
		CarpRobotModelSerializer file;
		if (!file.Open(file_path)) return;
		m_model.Serialize(file);
	}

private:
	CarpRobotParameterCollection m_model;
	CarpRobotAdamTrainer m_trainer;

private:
	CarpRobotLinear m_fc1;
	CarpRobotLinear m_fc2;

private:
	std::vector<std::vector<float>> m_x_values;
	std::vector<float> m_y_value;
};

#endif