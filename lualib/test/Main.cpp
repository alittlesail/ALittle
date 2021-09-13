
#include <eigen/Eigen/Eigen>
#include <eigen/unsupported/Eigen/CXX11/Tensor>
#include <eigen_third_party/eigen_spatial_convolutions.h>
#include <eigen_third_party/eigen_backward_spatial_convolutions.h>
#include <eigen_third_party/eigen_pooling.h>

#include <iostream>

using cr_real = float;

class DeeplearningSumTree
{
public:
	struct MemoryInfo
	{
		int value = 0;
	};

public:
	DeeplearningSumTree(int memory_capacity)
	{
		// 保存容量
		m_memory_capacity = memory_capacity;

		// 计算最近的2幂次方
		m_memory_capacity = CeilToPowerOf2(m_memory_capacity);

		// 控制一下范围
		// if (m_memory_capacity < 1024) m_memory_capacity = 1024;

		// 申请控件
		m_memory.reserve(m_memory_capacity);

		// 计算二叉树的层
		auto level = (int)(std::log(m_memory_capacity) / std::log(2) + 1);

		// 计算二叉树所有节点的个数
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

	// 返回是否存满
	bool SaveMemory(int value, cr_real loss)
	{
		MemoryInfo info;
		info.value = value;

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

		// 设置loss
		m_tree[index] = loss;

		// 从最底层不断更新上去
		int level_offset = 0;				// 当前层在m_tree中的偏移
		int level_count = m_memory_capacity; // 当前层的节点数量
		int level_index = index;			// 当前层的节点偏移
		while (true)
		{
			// 获取左右节点的下标
			auto left = level_index;
			auto right = level_index + 1;
			if (level_index % 2 == 1)
			{
				left = level_index - 1;
				right = level_index;
			}
			left += level_offset;
			right += level_offset;

			// 获取父节点下标
			auto parent = level_index / 2 + level_offset + level_count;
			// 如果超出范围，那么就跳出
			if (parent >= m_tree.size()) break;
			// 更新父节点
			m_tree[parent] = m_tree[left] + m_tree[right];

			// 更新
			level_index = level_index / 2;
			level_offset += level_count;
			level_count = level_count >> 1;
		}

		return (int)m_memory.size() >= m_memory_capacity;
	}

	// 选择记忆
	bool SelectMemory(int count, std::vector<const MemoryInfo*>& out)
	{
		if (m_memory.empty()) return false;

		// 取最大的那个数
		auto max = m_tree.back();

		// 根据数量分段
		auto split = max / count;

		auto cur_max = split;
		for (int i = 0; i < count; ++i)
		{
			auto score = GetRandFloat(cur_max - split, cur_max);

			// 开始选择
			int level_count = 1;
			int level_offset = (int)m_tree.size() - level_count;
			int level_index = 0;
			while (true)
			{
				// 这里说明已经到叶子节点了
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

				// 如果比左边比当前分数大，那么就选左边
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

int main(int argc, char* argv[])
{
	/*
	std::vector<float> m_value(4 * 3 * 2);
	m_value = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100
	, -0, -100, -200, -300, -400, -500, -600, -700, -800, -900, -1000, -1100 };
	Eigen::TensorMap<Eigen::Tensor<float, 3>> a(m_value.data(), 4, 3, 2);

	Eigen::array<int, 1> red_axis; red_axis[0] = 0;
	Eigen::array<int, 2> red_axis2 = { 1, 0};

	std::cout << "a" << std::endl << a << std::endl;
	std::cout << "b" << std::endl << a.chip<2>(0).chip(0, 1) << std::endl;
	std::cout << "c" << std::endl << a.maximum(red_axis) << std::endl;
	std::cout << "c" << std::endl << a.sum(red_axis) << std::endl;
	std::cout << "c" << std::endl << a.sum(red_axis2) << std::endl;
	*/
	DeeplearningSumTree tree(16);
	for (int i = 0; i < 16; ++i)
		tree.SaveMemory(i, i);

	std::vector<const DeeplearningSumTree::MemoryInfo*> list;
	tree.SelectMemory(10, list);

	return 0;
}
