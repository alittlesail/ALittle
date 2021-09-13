#ifndef DEEPLEARNING_DUELING_DQN_INCLUDED
#define DEEPLEARNING_DUELING_DQN_INCLUDED

extern "C"
{
#include "lua.h"
}

#include "Carp/carp_robot_model.hpp"
#include "deeplearning_model.hpp"

class DeeplearningDuelingDqnDnn
{
public:
	DeeplearningDuelingDqnDnn(CarpRobotParameterCollection* model, int state_count, int action_count, int hide_dim)
		: m_linear(model, state_count, hide_dim)
		, m_value(model, hide_dim, 1)
		, m_advantage(model, hide_dim, action_count)
	{
		m_state_count = state_count;
	}

	void Build(CarpRobotComputationGraph* graph)
	{
		m_linear.Build(graph);
		m_value.Build(graph);
		m_advantage.Build(graph);
	}

	virtual CarpRobotExpression Forward(CarpRobotComputationGraph& graph, const std::vector<cr_real>& state)
	{
		// ��ȡ����
		auto input = graph.AddInput(CarpRobotDim({ m_state_count }), &state);

		return ForwardImpl(input);
	}

	CarpRobotExpression ForwardImpl(CarpRobotExpression& input)
	{
		// ȫ�������ز�
		auto x = m_linear.Forward(input);
		x = x.Rectify();

		// ���� state �� value
		auto value = m_value.Forward(x);

		// ר�ŷ���ÿ�ֶ����� Advantage
		auto advantage = m_advantage.Forward(x);

		// �ϲ� V �� A, Ϊ�˲��� A ֱ��ѧ���� Q, ���Ǽ����� A �ľ�ֵ
		return advantage - advantage.MeanElements(0) + value;
	}

	void Copy(DeeplearningDuelingDqnDnn* value)
	{
		m_linear.Copy(&value->m_linear);
		m_value.Copy(&value->m_value);
		m_advantage.Copy(&value->m_advantage);
	}

protected:
	CarpRobotLinear m_linear;
	CarpRobotLinear m_value;
	CarpRobotLinear m_advantage;

	int m_state_count = 0;
};

class DeeplearningDuelingDqnCnn : public DeeplearningDuelingDqnDnn
{
public:
	DeeplearningDuelingDqnCnn(CarpRobotParameterCollection* model, int input_width, int input_height, int action_count, int hide_dim)
		: conv1(model, 1, 16, 2, 2, 1, 1, false)
		, DeeplearningDuelingDqnDnn(model, 16 * input_width * input_height, action_count, hide_dim)
	{
		m_input_width = input_width;
		m_input_height = input_height;
	}

	void Build(CarpRobotComputationGraph* graph)
	{
		conv1.Build(graph);
		DeeplearningDuelingDqnDnn::Build(graph);
	}

	CarpRobotExpression Forward(CarpRobotComputationGraph* graph, const std::vector<cr_real>& state)
	{
		auto input = graph->AddInput(CarpRobotDim({ m_input_width, m_input_height, 1 }), &state);
		auto x = conv1.Forward(input).Rectify();
		x = x.Reshape(CarpRobotDim({ m_conv_out * m_input_width * m_input_height }));

		return DeeplearningDuelingDqnDnn::ForwardImpl(x);
	}

	void Copy(DeeplearningDuelingDqnCnn* value)
	{
		conv1.Copy(&value->conv1);
		DeeplearningDuelingDqnDnn::Copy(value);
	}

private:
	CarpRobotConv2D conv1;
	int m_input_width = 0;
	int m_input_height = 0;
	int m_conv_out = 16;
};

class DeeplearningSumTree
{
public:
	struct MemoryInfo
	{
		std::vector<cr_real> state;
		int action = 0;
		cr_real reward = 0.0f;
		std::vector<cr_real> next_state;
	};

public:
	DeeplearningSumTree(int memory_capacity)
	{
		// ��������
		m_memory_capacity = memory_capacity;

		// ���������2�ݴη�
		m_memory_capacity = CeilToPowerOf2(m_memory_capacity);

		// ����һ�·�Χ
		if (m_memory_capacity < 1024) m_memory_capacity = 1024;

		// ����ؼ�
		m_memory.reserve(m_memory_capacity);

		// ����������Ĳ�
		auto level = (int)(std::log(m_memory_capacity) / std::log(2) + 1);

		// ������������нڵ�ĸ���
		auto count = (1 << level) - 1;
		m_tree.resize(count, 0);
	}

	uint32_t CeilToPowerOf2(uint32_t value)
	{
		value += value == 0 ? 1 : 0;
		value--;

		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;

		value++;

		return value;
	}

	static std::default_random_engine& GetGen()
	{
		static thread_local std::unique_ptr<std::default_random_engine> gen;
		if (gen != nullptr) return *gen;
		std::random_device rd;
		gen = std::make_unique<std::default_random_engine>(rd());
		return *gen;
	}

	static cr_real GetRandFloat(cr_real min, cr_real max)
	{
		max -= std::numeric_limits<cr_real>::epsilon();
		if (min == max) return min;
		if (min > max) std::swap(min, max);
		std::uniform_real_distribution<cr_real> dis(min, max);  // [a, b)
		return dis(GetGen());
	}

	// �����Ƿ����
	bool SaveMemory(const std::vector<cr_real>& state, const std::vector<cr_real>& next_state, int action, cr_real reward, cr_real loss)
	{
		MemoryInfo info;
		info.state = state;
		info.next_state = next_state;
		info.action = action;
		info.reward = reward;

		size_t index = 0;
		if ((int)m_memory.size() < m_memory_capacity)
		{
			m_memory.emplace_back(info);
			index = m_memory.size() - 1;
		}
		else
		{
			index = m_memory_counter % m_memory_capacity;
			m_memory[index] = std::move(info);
			m_memory_counter++;
		}

		// ����loss
		m_tree[index] = loss;

		// ����ײ㲻�ϸ�����ȥ
		int level_offset = 0;				// ��ǰ����m_tree�е�ƫ��
		int level_count = m_memory_capacity; // ��ǰ��Ľڵ�����
		int level_index = (int)index;			// ��ǰ��Ľڵ�ƫ��
		while (true)
		{
			// ��ȡ���ҽڵ���±�
			auto left = level_index;
			auto right = level_index + 1;
			if (level_index % 2 == 1)
			{
				left = level_index - 1;
				right = level_index;
			}
			left += level_offset;
			right += level_offset;

			// ��ȡ���ڵ��±�
			auto parent = level_index / 2 + level_offset + level_count;
			// ���������Χ����ô������
			if (parent >= m_tree.size()) break;
			// ���¸��ڵ�
			m_tree[parent] = m_tree[left] + m_tree[right];

			// ����
			level_index = level_index / 2;
			level_offset += level_count;
			level_count = level_count >> 1;
		}

		return (int)m_memory.size() >= m_memory_capacity;
	}

	// ѡ�����
	void SelectMemory(int count, std::vector<const MemoryInfo*>& out)
	{
		if (m_memory.empty()) return;

		// ȡ�����Ǹ���
		auto max = m_tree.back();

		// ���������ֶ�
		auto split = max / count;

		auto cur_max = split;
		for (int i = 0; i < count; ++i)
		{
			auto score = GetRandFloat(cur_max - split, cur_max);

			// ��ʼѡ��
			int level_count = 1;
			int level_offset = (int)m_tree.size() - level_count;
			int level_index = 0;
			while (true)
			{
				// ����˵���Ѿ���Ҷ�ӽڵ���
				if (level_offset <= 0)
				{
					if (level_index < m_memory.size())
						out.push_back(&m_memory[level_index]);
					break;
				}

				auto parent_score = m_tree[level_index + level_offset];

				int left = level_index * 2;
				int right = left + 1;
				level_count = level_count << 1;
				level_offset -= level_count;

				auto left_score = m_tree[left + level_offset];
				auto right_score = m_tree[right + level_offset];

				// �������߱ȵ�ǰ��������ô��ѡ���
				if (left_score >= score)
				{
					level_index = left;
				}
				else
				{
					score -= left_score;
					level_index = right;
				}
			}

			cur_max += split;
		}
	}

private:
	std::vector<MemoryInfo> m_memory;
	int m_memory_capacity = 0;
	int m_memory_counter = 0;

private:
	std::vector<cr_real> m_tree;
};

class DeeplearningDuelingDqnModel : public DeeplearningModel
{
public:
	DeeplearningDuelingDqnModel(int state_count, int action_count, int hide_dim, int memory_capacity)
		: m_eval(&m_model, state_count, state_count, action_count, hide_dim)
		, m_target(&m_model, state_count, state_count, action_count, hide_dim)
		, m_trainer(&m_model), m_sum_tree(memory_capacity)
	{
		m_state_count = state_count * state_count;
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
		// ɸѡ����
		std::vector<const DeeplearningSumTree::MemoryInfo*> memory_list;
		m_sum_tree.SelectMemory(10, memory_list);
		if (memory_list.empty()) return 0;

		// target net ��������
		if (m_learn_step_counter % TARGET_REPLACE_ITER == 0)
			m_target.Copy(&m_eval);
		m_learn_step_counter += 1;

		double total_loss = 0;
		for (auto& memory : memory_list)
		{
			CarpRobotComputationGraph graph;

			m_eval.Build(&graph);
			m_target.Build(&graph);

			auto reward = graph.AddInput(&memory->reward);

			// ��������Ķ���action, ��ѡ q_eval ��ֵ, (q_eval ԭ�������ж�����ֵ)
			auto x = m_eval.Forward(&graph, memory->state);
			auto q_eval = x.PickElement(memory->action, 0);

			auto q_next = m_target.Forward(&graph, memory->next_state);
			auto q_target = reward + GAMMA * q_next.GetValue().AsVectorAndMaxValue();

			// �����ʧ���ʽ
			auto loss_expr = (q_eval - q_target).Square();
			auto loss = loss_expr.GetValue().AsScalar();

			// ���㷴�򴫲�
			graph.Backward();
			// ����ѵ��
			m_trainer.Update();

			total_loss += loss;
		}
		
		return total_loss / memory_list.size();
	}

	double Learn()
	{
		bool right = false;
		return TrainingImpl((size_t)-1, right);
	}

	double LearnLastTransition(int count)
	{
		bool right = false;
		return TrainingImpl((size_t)-1, right);
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
		m_eval.Build(&graph);

		auto actions_value = m_eval.Forward(&graph, state);
		auto action = actions_value.GetValue().AsVectorAndArgmax();
		lua_pushinteger(l_state, action);
		return 1;
	}

	int ChooseActionByState(std::vector<cr_real> state)
	{
		if (static_cast<int>(state.size()) != m_state_count) return 0;

		CarpRobotComputationGraph graph;
		m_eval.Build(&graph);

		auto actions_value = m_eval.Forward(&graph, state);
		auto action = actions_value.GetValue().AsVectorAndArgmax();
		return action;
	}

	int SaveTransition(lua_State* l_state)
	{
		if (!lua_istable(l_state, 2))
			return 0;

		if (!lua_istable(l_state, 5))
			return 0;

		std::vector<cr_real> state;
		state.reserve(m_state_count);
		std::vector<cr_real> next_state;
		next_state.reserve(m_state_count);

		lua_pushnil(l_state);
		while (lua_next(l_state, 2) != 0)
		{
			const auto index = static_cast<int>(lua_tointeger(l_state, -2));
			const auto value = static_cast<cr_real>(lua_tonumber(l_state, -1));
			state.emplace_back(value);
			lua_pop(l_state, 1);
		}

		lua_pushnil(l_state);
		while (lua_next(l_state, 5) != 0)
		{
			const auto index = static_cast<int>(lua_tointeger(l_state, -2));
			const auto value = static_cast<cr_real>(lua_tonumber(l_state, -1));
			next_state.emplace_back(value);
			lua_pop(l_state, 1);
		}

		int action = static_cast<int>(luaL_checkinteger(l_state, 3));
		cr_real reward = static_cast<cr_real>(luaL_checknumber(l_state, 4));

		SaveTransitionByState(state, action, reward, next_state);

		return 0;
	}

	void SaveTransitionByState(const std::vector<cr_real>& state, int action, cr_real reward, const std::vector<cr_real>& next_state)
	{
		CarpRobotComputationGraph graph;

		m_eval.Build(&graph);
		m_target.Build(&graph);

		auto reward_expr = graph.AddInput(&reward);

		// ��������Ķ���action, ��ѡ q_eval ��ֵ, (q_eval ԭ�������ж�����ֵ)
		auto x = m_eval.Forward(&graph, state);
		auto q_eval = x.PickElement(action, 0);

		auto q_next = m_target.Forward(&graph, next_state);
		auto q_target = reward + GAMMA * q_next.GetValue().AsVectorAndMaxValue();

		// �����ʧ���ʽ
		auto loss_expr = (q_eval - q_target).Square();
		auto loss = loss_expr.GetValue().AsScalar();

		m_sum_tree.SaveMemory(state, next_state, action, reward, loss);
	}

private:
	CarpRobotAdamTrainer m_trainer;

private:
	DeeplearningDuelingDqnCnn m_eval;
	DeeplearningDuelingDqnCnn m_target;
	int m_learn_step_counter = 0;

	int m_state_count = 0;
	int m_action_count = 0;

private:
	DeeplearningSumTree m_sum_tree;

private:
	const float LR = 0.01f;
	const float EPSILON = 0.9f;
	const float GAMMA = 0.9f;
	const int TARGET_REPLACE_ITER = 100;
	const int MEMORY_CAPACITY = 2000;
};

#endif