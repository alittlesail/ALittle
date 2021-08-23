#ifndef DEEPLEARNING_DQN_DNN_INCLUDED
#define DEEPLEARNING_DQN_DNN_INCLUDED

extern "C"
{
#include "lua.h"
}

#include "Carp/carp_robot_model.hpp"
#include "deeplearning_model.hpp"

struct DeeplearningDqnDnn
{
	DeeplearningDqnDnn(CarpRobotParameterCollection& model, int state_count, int action_count, int hide_dim)
		: fc1(model, state_count, hide_dim)
		, fc2(model, hide_dim, action_count)
	{
	}

	void Build(CarpRobotComputationGraph& graph)
	{
		fc1.Build(graph);
		fc2.Build(graph);
	}

	CarpRobotExpression Forward(CarpRobotExpression& input)
	{
		auto x = fc1.Forward(input);
		x = x.Rectify();
		return fc2.Forward(x);
	}

	void Copy(DeeplearningDqnDnn& value)
	{
		fc1.Copy(value.fc1);
		fc2.Copy(value.fc2);
	}

	CarpRobotLinear fc1;
	CarpRobotLinear fc2;
};

class DeeplearningDqnDnnModel : public DeeplearningModel
{
public:
	DeeplearningDqnDnnModel(int state_count, int action_count, int hide_dim, int memory_capacity)
		: m_eval(m_model, state_count, action_count, hide_dim)
		, m_target(m_model, state_count, action_count, hide_dim)
		, m_trainer(m_model)
	{
		m_memory_capacity = memory_capacity;
		if (m_memory_capacity < 100) m_memory_capacity = 100;
		m_memory.reserve(m_memory_capacity);

		m_state_count = state_count;
		m_action_count = action_count;
	}

public:	
	int TrainInit() override
	{
		return 0;
	}

	void TrainRelease() override
	{
	}
	
	double Training(size_t index, bool& right) override
	{
		return TrainingImpl(index, right);
	}

	double TrainingImpl(size_t index, bool& right)
	{
		if (m_memory.empty()) return 0;

		CarpRobotComputationGraph graph;

		m_eval.Build(graph);
		m_target.Build(graph);

		// target net 参数更新
		if (m_learn_step_counter % TARGET_REPLACE_ITER == 0)
			m_target.Copy(m_eval);

		m_learn_step_counter += 1;

		if (index == (size_t)-1) index = rand();
		const auto position = index % m_memory.size();

		// 设置输入
		auto& memory = m_memory[position];

		auto state = graph.AddInput(CarpRobotDim({ m_state_count }), &memory.state);
		auto reward = graph.AddInput(&memory.reward);
		auto next_state = graph.AddInput(CarpRobotDim({ m_state_count }), &memory.next_state);

		// 针对做过的动作action, 来选 q_eval 的值, (q_eval 原本有所有动作的值)
		auto x = m_eval.Forward(state);
		auto q_eval = x.PickElement(memory.action, 0);

		auto q_next = m_target.Forward(next_state);
		auto q_target = reward + GAMMA * q_next.GetValue().AsVectorAndMaxValue();

		// 获得损失表达式
		auto loss_expr = (q_eval - q_target).Square();
		auto loss = loss_expr.GetValue().AsScalar();

		// 计算反向传播
		graph.Backward();
		// 更新训练
		m_trainer.Update();

		return loss;
	}

	double Learn()
	{
		bool right = false;
		return TrainingImpl((size_t)-1, right);
	}

	double LearnLastTransition(int count)
	{
		double loss = 0;
		int index = (int)m_last_memory;
		int total_count = count;
		while (count > 0)
		{
			bool right = false;
			loss += TrainingImpl(index, right);

			--count;
			--index;
			if (index < 0) index = (int)m_memory.size() - 1;
		}

		return loss / total_count;
	}

	int ChooseAction(lua_State* l_state)
	{
		if (!lua_istable(l_state, 2))
			return 0;

		std::vector<float> state;
		lua_pushnil(l_state);
		while (lua_next(l_state, 2) != 0)
		{
			const auto index = static_cast<int>(lua_tointeger(l_state, -2));
			const auto value = static_cast<float>(lua_tonumber(l_state, -1));
			state.push_back(value);
			lua_pop(l_state, 1);
		}

		if (static_cast<int>(state.size()) != m_state_count) return 0;

		CarpRobotComputationGraph graph;
		m_eval.Build(graph);

		auto x = graph.AddInput(CarpRobotDim({ m_state_count }), &state);
		auto actions_value = m_eval.Forward(x);
		auto action = actions_value.GetValue().AsVectorAndArgmax();
		lua_pushinteger(l_state, action);
		return 1;
	}

	int ChooseActionByState(std::vector<float> state)
	{
		if (static_cast<int>(state.size()) != m_state_count) return 0;

		CarpRobotComputationGraph graph;
		m_eval.Build(graph);

		auto x = graph.AddInput(CarpRobotDim({ m_state_count }), &state);
		auto actions_value = m_eval.Forward(x);
		auto action = actions_value.GetValue().AsVectorAndArgmax();
		return action;
	}

	int SaveTransition(lua_State* l_state)
	{
		if (!lua_istable(l_state, 2))
			return 0;

		if (!lua_istable(l_state, 5))
			return 0;

		MemoryInfo info;
		info.state.reserve(m_state_count);
		info.next_state.reserve(m_state_count);

		lua_pushnil(l_state);
		while (lua_next(l_state, 2) != 0)
		{
			const auto index = static_cast<int>(lua_tointeger(l_state, -2));
			const auto value = static_cast<float>(lua_tonumber(l_state, -1));
			info.state.emplace_back(value);
			lua_pop(l_state, 1);
		}

		std::vector<float> new_state;
		lua_pushnil(l_state);
		while (lua_next(l_state, 5) != 0)
		{
			const auto index = static_cast<int>(lua_tointeger(l_state, -2));
			const auto value = static_cast<float>(lua_tonumber(l_state, -1));
			info.next_state.emplace_back(value);
			lua_pop(l_state, 1);
		}

		info.action = static_cast<int>(luaL_checkinteger(l_state, 3));
		info.reward = static_cast<float>(luaL_checknumber(l_state, 4));

		if (m_memory.size() < m_memory_capacity)
		{
			m_memory.emplace_back(info);
			m_last_memory = m_memory.size() - 1;
		}
		else
		{
			m_last_memory = m_memory_counter % m_memory_capacity;
			m_memory[m_last_memory]= std::move(info);
			m_memory_counter++;
		}

		return 0;
	}

	size_t SaveTransitionByState(const std::vector<float>& state, int action, float reward, const std::vector<float>& new_state)
	{
		MemoryInfo info;
		info.state = state;
		info.next_state = new_state;
		info.action = action;
		info.reward = reward;

		if (m_memory.size() < m_memory_capacity)
		{
			m_memory.emplace_back(info);
			m_last_memory = m_memory.size() - 1;
		}
		else
		{
			m_last_memory = m_memory_counter % m_memory_capacity;
			m_memory[m_last_memory] = std::move(info);
			m_memory_counter++;
		}

		return m_last_memory;
	}

private:
	CarpRobotAdamTrainer m_trainer;

private:
	DeeplearningDqnDnn m_eval;
	DeeplearningDqnDnn m_target;

	int m_state_count = 0;
	int m_action_count = 0;

private:
	struct MemoryInfo
	{
		std::vector<float> state;
		int action = 0;
		float reward = 0.0;
		std::vector<float> next_state;
	};
	int m_learn_step_counter = 0;
	int m_memory_counter = 0;
	int m_memory_capacity = 0;
	size_t m_last_memory = 0;
	std::vector<MemoryInfo> m_memory;

private:
	const float LR = 0.01f;
	const float EPSILON = 0.9f;
	const float GAMMA = 0.9f;
	const int TARGET_REPLACE_ITER = 100;
	const int MEMORY_CAPACITY = 2000;
};

#endif