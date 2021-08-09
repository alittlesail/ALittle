#ifndef DEEPLEARNING_DQN_DNN_INCLUDED
#define DEEPLEARNING_DQN_DNN_INCLUDED

extern "C"
{
#include "lua.h"
}

#include "torch/torch.h"
#include "deeplearning_model.hpp"

#ifdef max
#undef max
#endif

struct DeeplearningDqnDnn
{
	DeeplearningDqnDnn(int state_count, int action_count, int hide_dim)
		: fc1(state_count, hide_dim)
		, fc2(hide_dim, action_count)
	{
		fc1->weight.data().normal_(0, 0.1);
		fc2->weight.data().normal_(0, 0.1);
	}

	torch::Tensor Forward(torch::Tensor input)
	{
		return fc2(torch::relu(fc1(input)));
	}

	void Copy(DeeplearningDqnDnn& value)
	{
		*fc1 = *value.fc1;
		*fc2 = *value.fc2;
	}

	torch::nn::Linear fc1;
	torch::nn::Linear fc2;
};

class DeeplearningDqnDnnModel : public DeeplearningModel
{
public:
	DeeplearningDqnDnnModel(int state_count, int action_count, int hide_dim, int memory_capacity)
		: m_eval(state_count, action_count, hide_dim)
		, m_target(state_count, action_count, hide_dim)
	{
		register_module("eval_fc1", m_eval.fc1);
		register_module("eval_fc2", m_eval.fc2);

		register_module("target_fc1", m_target.fc1);
		register_module("target_fc2", m_target.fc2);

		m_memory_capacity = memory_capacity;
		if (m_memory_capacity < 100) m_memory_capacity = 100;
		m_memory.reserve(m_memory_capacity);

		m_state_count = state_count;
		m_action_count = action_count;

		m_trainer = std::make_shared<torch::optim::Adam>(parameters(), torch::optim::AdamOptions(LR));
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
		if (m_memory.empty()) return 0;

		// 重置误差项
		m_trainer->zero_grad();

		// target net 参数更新
		if (m_learn_step_counter % TARGET_REPLACE_ITER == 0)
			m_target.Copy(m_eval);

		m_learn_step_counter += 1;

		if (index == (size_t)-1) index = rand();
		const auto position = index % m_memory.size();
		// 设置输入
		auto& memory = m_memory[position];

		const auto state = torch::from_blob(memory.state.data(), { 1, m_state_count });
		const auto action = torch::from_blob(&memory.action, { 1, 1 }, torch::TensorOptions(torch::kLong));
		const auto reward = torch::from_blob(&memory.reward, { 1 });
		const auto next_state = torch::from_blob(memory.next_state.data(), { 1, m_state_count });

		// 针对做过的动作action, 来选 q_eval 的值, (q_eval 原本有所有动作的值)
		auto q_eval = torch::gather(m_eval.Forward(state), 1, action);	// shape(batch, 1)

		auto q_next = m_target.Forward(next_state).detach();			// q_next 不进行反向传递误差, 所以 detach
		auto q_target = reward + GAMMA * std::get<0>(q_next.max(1));	// shape(batch, 1)
		
		// 获得损失表达式
		auto loss_expr = torch::mse_loss(q_eval, q_target);
		auto loss = loss_expr.item().toDouble();
		
		// 计算反向传播
		loss_expr.backward();
		// 更新训练
		m_trainer->step();

		return loss;
	}

	double Learn()
	{
		bool right = false;
		return Training((size_t)-1, right);
	}

	double LearnLastTransition()
	{
		bool right = false;
		return Training(m_memory.size() - 1, right);
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

		const auto x = torch::from_blob(state.data(), { 1, m_state_count });
		const auto actions_value = m_eval.Forward(x);
		const auto action = std::get<1>(torch::max(actions_value, 1));
		lua_pushinteger(l_state, action.item().toInt());
		return 1;
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

		info.action = luaL_checkinteger(l_state, 3);
		info.reward = luaL_checknumber(l_state, 4);

		if (m_memory.size() < m_memory_capacity)
		{
			m_memory.emplace_back(info);
		}
		else
		{
			m_memory[m_memory_counter % m_memory_capacity]= std::move(info);
			m_memory_counter++;
		}

		return 0;
	}

private:
	std::shared_ptr<torch::optim::Adam> m_trainer;

private:
	DeeplearningDqnDnn m_eval;
	DeeplearningDqnDnn m_target;

	int m_state_count = 0;
	int m_action_count = 0;

private:
	struct MemoryInfo
	{
		std::vector<float> state;
		int64_t action = 0;
		float reward = 0.0;
		std::vector<float> next_state;
	};
	int m_learn_step_counter = 0;
	int m_memory_counter = 0;
	int m_memory_capacity = 0;
	std::vector<MemoryInfo> m_memory;

private:
	const float LR = 0.01f;
	const float EPSILON = 0.9f;
	const float GAMMA = 0.9f;
	const int TARGET_REPLACE_ITER = 100;
	const int MEMORY_CAPACITY = 2000;
};

#endif