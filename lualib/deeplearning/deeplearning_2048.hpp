#ifndef DEEPLEARNING_2048_INCLUDED
#define DEEPLEARNING_2048_INCLUDED

extern "C"
{
#include "lua.h"
}

#include "deeplearning_dqn_cnn.hpp"

const int G2048_ROW_COUNT = 4;
const int G2048_COL_COUNT = 4;
const int G2048_ACTION_COUNT = 4;

class Deeplearning2048Model : public DeeplearningDqnDnnModel
{
public:
	Deeplearning2048Model(int input_len, int action_count, int memory_capacity)
		: DeeplearningDqnDnnModel(4, 4, 128, memory_capacity)
	{
        srand(static_cast<unsigned int>(time(0)));
	}

public:	
	int TrainInit() override
	{
        Restart2048();
		return -1;
	}

	void TrainRelease() override
	{
	}
	
	double Training(size_t index, bool& right) override
	{
        auto old_score = m_score;

        int old_value_map[G2048_ROW_COUNT][G2048_COL_COUNT];
        GetValueMap(old_value_map);

        std::vector<float> state;
        CalcState(old_value_map, state);
        
        int action = ChooseActionByState(state);

        m_item_moved = false;

        if (action == 0)
            CalcDown();
        else if (action == 1)
            CalcRight();
        else if (action == 2)
            CalcLeft();
        else if (action == 3)
            CalcUp();

        if (m_item_moved == false)
        {
            action = rand() % 4;

            if (action == 0)
                CalcDown();
            else if (action == 1)
                CalcRight();
            else if (action == 2)
                CalcLeft();
            else if (action == 3)
                CalcUp();
        }

        bool item_moved = m_item_moved;

        int new_value_map[G2048_ROW_COUNT][G2048_COL_COUNT];
        GetValueMap(new_value_map);

        std::vector<float> new_state;
        CalcState(new_value_map, new_state);

        auto new_score = m_score;

        if (m_item_moved)
        {
            Born2048();
            Born2048();
        }

        bool over = IsGameOver();
        if (over) Restart2048();

        int score = 1;
        if (!over)
        {
            // 如果移动了，加1分
            if (item_moved) score += 1;

            // 判断局面
            score += CalcSmooth(new_value_map); // -CalcSmooth(old_value_map);
            score += CalcGradient(new_value_map); // -CalcGradient(old_value_map);

            // 有新分数
            score += new_score; // -old_score;
        }

        if (score <= 0) score = 1;

        double reward = (float)std::log2(score);
        index = SaveTransitionByState(state, action, reward, new_state);

        auto loss = DeeplearningDqnDnnModel::Training(index, right);

        int rand_learn = 100;
        for (int i = 0; i < rand_learn; ++i)
            loss += DeeplearningDqnDnnModel::Training((size_t)-1, right);

        return loss / (rand_learn + 1);
	}

    int CalcSmooth(int value_map[G2048_ROW_COUNT][G2048_COL_COUNT])
    {
        int score = 0;
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                auto cur_value = value_map[row][col];
                if (cur_value == 0) continue;

                for (int next_col = col + 1; next_col < G2048_COL_COUNT; ++next_col)
                {
                    auto next_value = value_map[row][next_col];
                    if (next_value != 0)
                    {
                        if (cur_value == next_value)
                            score += 1;
                        break;
                    }
                }
                for (int next_row = row + 1; next_row < G2048_ROW_COUNT; ++next_row)
                {
                    auto next_value = value_map[next_row][col];
                    if (next_value != 0)
                    {
                        if (cur_value == next_value)
                            score += 1;
                        break;
                    }
                }
            }
        }

        return score;
    }

    int CalcGradient(int value_map[G2048_ROW_COUNT][G2048_COL_COUNT])
    {
        int score = 0;
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                auto cur_value = value_map[row][col];
                if (cur_value == 0) continue;

                for (int next_col = col + 1; next_col < G2048_COL_COUNT; ++next_col)
                {
                    auto next_value = value_map[row][next_col];
                    if (next_value != 0)
                    {
                        if (cur_value <= next_value)
                            score += 1;
                        break;
                    }
                }
                for (int next_row = row + 1; next_row < G2048_ROW_COUNT; ++next_row)
                {
                    auto next_value = value_map[next_row][col];
                    if (next_value != 0)
                    {
                        if (cur_value <= next_value)
                            score += 1;
                        break;
                    }
                }
            }
        }

        return score;
    }

public:
    struct Cell
    {
        int row = 0;
        int col = 0;
        int value = 0;
    };

    void Restart2048()
    {
        printf("restart :%d\n", m_score);
        Init2048();
        Born2048();
        Born2048();

        m_item_moved = false;
        m_score = 0;
    }

	void Init2048()
	{
		for (int row = 0; row < G2048_ROW_COUNT; ++row)
			for (int col = 0; col < G2048_COL_COUNT; ++col)
				m_2048[row][col] = 0;
	}

    bool IsGameOver()
    {
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                if (m_2048[row][col] == 0) return false;
            }
        }

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                auto value = m_2048[row][col];

                // 检查左边
                if (col >= 1 && m_2048[row][col - 1] == value)
                    return false;

                // 检查右边
                if (col <= 2 && m_2048[row][col + 1] == value)
                    return false;

                // 检查上边
                if (row >= 1 && m_2048[row - 1][col] == value)
                    return false;

                // 检查下边
                if (row <= 2 && m_2048[row + 1][col] == value)
                    return false;
            }
        }

        return true;
    }

	bool Born2048()
	{
        // 把空闲的格子遍历出来
		std::vector<Cell> list;
		for (int row = 0; row < G2048_ROW_COUNT; ++row)
		{
			for (int col = 0; col < G2048_ROW_COUNT; ++col)
			{
				if (m_2048[row][col] == 0)
				{
					Cell cell;
					cell.row = row;
					cell.col = col;
                    cell.value = 0;
					list.push_back(cell);
				}
			}
		}
		if (list.empty()) return false;

		// 随机格子的编号，2 或者 4
		int rand1 = rand() % 10;
		int number = 4;
		if (rand1 < 9) number = 2;

		// 随机格子的位置
		int rand2 = rand() % list.size();

		m_2048[list[rand2].row][list[rand2].col] = number;
		return true;
	}

	bool Play2048(int action)
	{
        m_item_moved = false;

		// down
		if (action == 0)
		{
            CalcDown();
		}
		// right
		else if (action == 1)
		{
            CalcRight();
		}
		// left
		else if (action == 2)
		{
            CalcLeft();
		}
		// up
		else if (action == 3)
		{
            CalcUp();
		}

        if (m_item_moved)
        {
            Born2048();
            Born2048();
        }

        return m_item_moved;
	}

    int PlayAI()
    {
        int value_map[G2048_ROW_COUNT][G2048_COL_COUNT];
        GetValueMap(value_map);

        std::vector<float> state;
        CalcState(value_map, state);

        return ChooseActionByState(state);
    }

	void CalcDown()
	{
        for (int col = 0; col < 4; ++col)
        {
            // 收集横向的
            std::vector<Cell> list;
            for (int row = 3; row >= 0; --row)
            {
                if (m_2048[row][col] != 0)
                {
                    Cell info;
                    info.row = row;
                    info.col = col;
                    info.value = m_2048[row][col];
                    list.push_back(info);
                }
            }

            // 计算合并
            if (list.size() == 1)
            {
                TransCell(list[0], 3, col);
            }
            else if(list.size() == 2)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], 3, col);
                }
                else
                {
                    TransCell(list[0], 3, col);
                    TransCell(list[1], 2, col);
                }
            }
            else if(list.size() == 3)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], 3, col);
                    TransCell(list[2], 2, col);
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], 3, col);
                    CombineCells(list[1], list[2], 2, col);
                }
                else
                {
                    TransCell(list[0], 3, col);
                    TransCell(list[1], 2, col);
                    TransCell(list[2], 1, col);
                }
            }
            else if(list.size() == 4)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], 3, col);
                    if (list[2].value == list[3].value)
                    {
                        CombineCells(list[2], list[3], 2, col);
                    }
                    else
                    {
                        TransCell(list[2], 2, col);
                        TransCell(list[3], 1, col);
                    }
                }
                else if(list[1].value == list[2].value)
                {
                    TransCell(list[0], 3, col);
                    CombineCells(list[1], list[2], 2, col);
                    TransCell(list[3], 1, col);
                }
                else if(list[2].value == list[3].value)
                {
                    TransCell(list[0], 3, col);
                    TransCell(list[1], 2, col);
                    CombineCells(list[2], list[3], 1, col);
                }
            }
        }
	}

    void CalcRight()
    {
        for (int row = 0; row < 4; ++row)
        {
            // 收集横向的
            std::vector<Cell> list;
            for (int col = 3; col >= 0; --col)
            {
                if (m_2048[row][col] != 0)
                {
                    Cell info;
                    info.row = row;
                    info.col = col;
                    info.value = m_2048[row][col];
                    list.push_back(info);
                }
            }

            // 计算合并
            if (list.size() == 1)
            {
                TransCell(list[0], row, 3);
            }
            else if (list.size() == 2)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], row, 3);
                }
                else
                {
                    TransCell(list[0], row, 3);
                    TransCell(list[1], row, 2);
                }
            }
            else if (list.size() == 3)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], row, 3);
                    TransCell(list[2], row, 2);
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], row, 3);
                    CombineCells(list[1], list[2], row, 2);
                }
                else
                {
                    TransCell(list[0], row, 3);
                    TransCell(list[1], row, 2);
                    TransCell(list[2], row, 1);
                }
            }
            else if (list.size() == 4)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], row, 3);
                    if (list[2].value == list[3].value)
                    {
                        CombineCells(list[2], list[3], row, 2);
                    }
                    else
                    {
                        TransCell(list[2], row, 2);
                        TransCell(list[3], row, 1);
                    }
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], row, 3);
                    CombineCells(list[1], list[2], row, 2);
                    TransCell(list[3], row, 1);
                }
                else if (list[2].value == list[3].value)
                {
                    TransCell(list[0], row, 3);
                    TransCell(list[1], row, 2);
                    CombineCells(list[2], list[3], row, 1);
                }
            }
        }
    }

    void CalcUp()
    {
        for (int col = 0; col < 4; ++col)
        {
            // 收集横向的
            std::vector<Cell> list;
            for (int row = 0; row <= 3; ++row)
            {
                if (m_2048[row][col] != 0)
                {
                    Cell info;
                    info.row = row;
                    info.col = col;
                    info.value = m_2048[row][col];
                    list.push_back(info);
                }
            }

            // 计算合并
            if (list.size() == 1)
            {
                TransCell(list[0], 0, col);
            }
            else if (list.size() == 2)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], 0, col);
                }
                else
                {
                    TransCell(list[0], 0, col);
                    TransCell(list[1], 1, col);
                }
            }
            else if (list.size() == 3)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], 0, col);
                    TransCell(list[2], 1, col);
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], 0, col);
                    CombineCells(list[1], list[2], 1, col);
                }
                else
                {
                    TransCell(list[0], 0, col);
                    TransCell(list[1], 1, col);
                    TransCell(list[2], 2, col);
                }
            }
            else if (list.size() == 4)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], 0, col);
                    if (list[2].value == list[3].value)
                    {
                        CombineCells(list[2], list[3], 1, col);
                    }
                    else
                    {
                        TransCell(list[2], 1, col);
                        TransCell(list[3], 2, col);
                    }
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], 0, col);
                    CombineCells(list[1], list[2], 1, col);
                    TransCell(list[3], 2, col);
                }
                else if (list[2].value == list[3].value)
                {
                    TransCell(list[0], 0, col);
                    TransCell(list[1], 1, col);
                    CombineCells(list[2], list[3], 2, col);
                }
            }
        }
    }

    void CalcLeft()
    {
        for (int row = 0; row < 4; ++row)
        {
            // 收集横向的
            std::vector<Cell> list;
            for (int col = 0; col <= 3; ++col)
            {
                if (m_2048[row][col] != 0)
                {
                    Cell info;
                    info.row = row;
                    info.col = col;
                    info.value = m_2048[row][col];
                    list.push_back(info);
                }
            }

            // 计算合并
            if (list.size() == 1)
            {
                TransCell(list[0], row, 0);
            }
            else if (list.size() == 2)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], row, 0);
                }
                else
                {
                    TransCell(list[0], row, 0);
                    TransCell(list[1], row, 1);
                }
            }
            else if (list.size() == 3)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], row, 0);
                    TransCell(list[2], row, 1);
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], row, 0);
                    CombineCells(list[1], list[2], row, 1);
                }
                else
                {
                    TransCell(list[0], row, 0);
                    TransCell(list[1], row, 1);
                    TransCell(list[2], row, 2);
                }
            }
            else if (list.size() == 4)
            {
                if (list[0].value == list[1].value)
                {
                    CombineCells(list[0], list[1], row, 0);
                    if (list[2].value == list[3].value)
                    {
                        CombineCells(list[2], list[3], row, 1);
                    }
                    else
                    {
                        TransCell(list[2], row, 1);
                        TransCell(list[3], row, 2);
                    }
                }
                else if (list[1].value == list[2].value)
                {
                    TransCell(list[0], row, 0);
                    CombineCells(list[1], list[2], row, 1);
                    TransCell(list[3], row, 2);
                }
                else if (list[2].value == list[3].value)
                {
                    TransCell(list[0], row, 0);
                    TransCell(list[1], row, 1);
                    CombineCells(list[2], list[3], row, 2);
                }
            }
        }
    }

    void TransCell(Cell cell, int to_row, int to_col)
    {
        if (cell.row == to_row && cell.col == to_col) return;
        // 判定移动
        m_item_moved = true;
        // 把原来的位置设置为0
        RemoveCell(cell);
        // 设置新的位置
        BornCell(cell.value, to_row, to_col);
    }

    void CombineCells(Cell cell_1, Cell cell_2, int to_row, int to_col)
    {
        // 移除两个位置
        RemoveCell(cell_1);
        RemoveCell(cell_2);
        // 生长新的位置
        BornCell(cell_1.value * 2, to_row, to_col);
        // 加一下分数
        m_score += cell_1.value * 2;
        // 标记为已移动
        m_item_moved = true;
    }

    void RemoveCell(Cell cell)
    {
        m_2048[cell.row][cell.col] = 0;
    }

    void BornCell(int number, int row, int col)
    {
        m_2048[row][col] = number;
    }

    int Get2048(int row, int col)
    {
        return m_2048[row][col];
    }

    int GetScore()
    {
        return m_score;
    }

    void CalcState(int value_map[G2048_ROW_COUNT][G2048_COL_COUNT], std::vector<float>& state)
    {
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                float value = (float)std::log2(value_map[row][col] + 1) / 16.0f;
                state.push_back(value);
            }
    }

    void GetValueMap(int value_map[G2048_ROW_COUNT][G2048_COL_COUNT])
    {
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                value_map[row][col] = m_2048[row][col];
            }
    }

private:
	int m_2048[G2048_ROW_COUNT][G2048_COL_COUNT];
    bool m_item_moved = false;
    int m_score = 0;
};

#endif