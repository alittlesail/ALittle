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

class Deeplearning2048Model : public DeeplearningDqnCnnModel
{
public:
	Deeplearning2048Model(int input_len, int action_count, int memory_capacity)
		: DeeplearningDqnCnnModel(4, 4, 4, memory_capacity)
	{
        srand(static_cast<unsigned int>(time(0)));
	}

public:	
	int TrainInit() override
	{
        Init2048();
        Born2048();
        Born2048();

		return -1;
	}

	void TrainRelease() override
	{
	}

    double TrainingDeep()
    {
        // ������Ϣ
        int old_value_map[G2048_ROW_COUNT][G2048_COL_COUNT];
        GetValueMap(old_value_map);
        int old_score = m_score;

        // ����״̬
        std::vector<float> old_state;
        CalcState(old_value_map, old_state);

        int max_action = -1;
        double max_reward = -1;
        std::map<int, double> action_map;
        // �������
        for (int action = 0; action <= 3; ++action)
        {
            // ָ������
            if (action == 0)
                CalcDown();
            else if (action == 1)
                CalcRight();
            else if (action == 2)
                CalcLeft();
            else if (action == 3)
                CalcUp();

            // ��ȡ������
            int new_value_map[G2048_ROW_COUNT][G2048_COL_COUNT];
            GetValueMap(new_value_map);

            // ��ȡ��״̬
            std::vector<float> new_state;
            CalcState(new_value_map, new_state);

            // ��ȡ����
            auto new_score = m_score;

            // �ж��Ƿ����
            bool over = IsGameOver();

            float reward = -50;
            if (!over)
            {
                // ����ƶ��ˣ���1��
                if (!m_item_moved)
                {
                    reward = -5;
                }
                else
                {
                    reward = 1;
                    reward += new_score - old_score;
                }

                // �жϾ���
                // score += CalcSmooth(new_value_map);
                // if (CalcSmooth(new_value_map) > CalcSmooth(old_value_map))
                //     score += 1;
                // score += CalcSmooth(new_value_map); // -CalcSmooth(old_value_map);
                // score += CalcGradient(new_value_map); // -CalcGradient(old_value_map);

                // score += CalcMax(new_value_map);

                // ��ǰ����
            }

            if (reward > 0)
                reward = (float)std::log2(reward + 1) / 16.0f;
            else if (reward < 0)
                reward = -(float)std::log2(-reward + 1) / 16.0f;

            if (max_reward < reward)
            {
                max_reward = reward;
                max_action = action;
            }
            action_map[action] = reward;
            // ���澭��
            auto index = SaveTransitionByState(old_state, action, reward, new_state);

            // ��������
            ResetData(old_value_map, old_score);
        }

        // ����aiִ�в���
        // if (max_action < 0)
        int action = ChooseActionByState(old_state);

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
            if (max_action == 0)
                CalcDown();
            else if (max_action == 1)
                CalcRight();
            else if (max_action == 2)
                CalcLeft();
            else if (max_action == 3)
                CalcUp();

            // if (m_item_moved)
            //    printf("step action %d, reward %lf, force_action %d, force_reward %lf\n", action, action_map[action], max_action, action_map[max_action]);
        }
        else
        {
            /*
            if (action_map[max_action] > action_map[action])
                printf("action %d, reward %lf, max_action %d, max_reward %lf\n", action, action_map[action], max_action, action_map[max_action]);
            else
                printf("action %d\n", action);
            */
        }

        ++m_step;
        // if (m_score > old_score) printf("step:%d\tscore:%d\n", m_step, m_score);

        if (m_item_moved)
        {
            Born2048();
            Born2048();
        }

        if (IsGameOver())
        {
            for (int row = 0; row < G2048_ROW_COUNT; ++row)
            {
                for (int col = 0; col < G2048_COL_COUNT; ++col)
                {
                    printf("%d\t", m_2048[row][col]);
                }
                printf("\n");
            }
         
            Restart2048();
        }

        // ѧϰ����
        double loss = 0;
        int learn_count = GetMemorySize() / 2;
        if (learn_count <= 0) learn_count = 1;
        else if (learn_count >= 10) learn_count = 10;
        for (int i = 0; i < learn_count; ++i)
            loss += Learn();
        return loss / learn_count;
    }
	
	double Training(size_t index, bool& right) override
	{
        return TrainingDeep();
	}

    int CalcMax(int value_map[G2048_ROW_COUNT][G2048_COL_COUNT])
    {
        int score = 0;
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                auto cur_value = value_map[row][col];
                if (score < cur_value) score = cur_value;
            }
        }

        return score;
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
                            score += cur_value;
                        break;
                    }
                }
                for (int next_row = row + 1; next_row < G2048_ROW_COUNT; ++next_row)
                {
                    auto next_value = value_map[next_row][col];
                    if (next_value != 0)
                    {
                        if (cur_value == next_value)
                            score += cur_value;
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
        m_play_count++;
        m_total_score += m_score;
        if (m_max_score < m_score) m_max_score = m_score;
        printf("restart, score:%d, max_score:%d, average_score:%d\n", m_score,  m_max_score, m_total_score / m_play_count);
        Init2048();
        Born2048();
        Born2048();

        m_item_moved = false;
        m_score = 0;
        m_step = 0;
    }

	void Init2048()
	{
		for (int row = 0; row < G2048_ROW_COUNT; ++row)
			for (int col = 0; col < G2048_COL_COUNT; ++col)
				m_2048[row][col] = 0;
	}

    bool IsGameOver()
    {
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                if (m_2048[row][col] == 0) return false;
            }
        }

        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                auto value = m_2048[row][col];

                // ������
                if (col > 0 && m_2048[row][col - 1] == value)
                    return false;

                // ����ұ�
                if (col < G2048_COL_COUNT - 1 && m_2048[row][col + 1] == value)
                    return false;

                // ����ϱ�
                if (row > 0 && m_2048[row - 1][col] == value)
                    return false;

                // ����±�
                if (row < G2048_ROW_COUNT - 1 && m_2048[row + 1][col] == value)
                    return false;
            }
        }

        return true;
    }

	bool Born2048()
	{
        // �ѿ��еĸ��ӱ�������
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

		// ������ӵı�ţ�2 ���� 4
		int rand1 = rand() % 10;
		int number = 4;
		if (rand1 < 9) number = 2;

		// ������ӵ�λ��
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
        for (int col = 0; col < G2048_COL_COUNT; ++col)
        {
            // �ռ������
            std::vector<Cell> list;
            for (int row = G2048_ROW_COUNT - 1; row >= 0; --row)
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

            // ����ϲ�
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
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            // �ռ������
            std::vector<Cell> list;
            for (int col = G2048_COL_COUNT - 1; col >= 0; --col)
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

            // ����ϲ�
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
        for (int col = 0; col < G2048_COL_COUNT; ++col)
        {
            // �ռ������
            std::vector<Cell> list;
            for (int row = 0; row < G2048_ROW_COUNT; ++row)
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

            // ����ϲ�
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
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
        {
            // �ռ������
            std::vector<Cell> list;
            for (int col = 0; col < G2048_COL_COUNT; ++col)
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

            // ����ϲ�
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
        // �ж��ƶ�
        m_item_moved = true;
        // ��ԭ����λ������Ϊ0
        RemoveCell(cell);
        // �����µ�λ��
        BornCell(cell.value, to_row, to_col);
    }

    void CombineCells(Cell cell_1, Cell cell_2, int to_row, int to_col)
    {
        // �Ƴ�����λ��
        RemoveCell(cell_1);
        RemoveCell(cell_2);
        // �����µ�λ��
        BornCell(cell_1.value * 2, to_row, to_col);
        // ��һ�·���
        m_score += cell_1.value * 2;
        // ���Ϊ���ƶ�
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
                state.push_back((float)std::log2(value_map[row][col] + 1) / 16.0f);
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

    void ResetData(int value_map[G2048_ROW_COUNT][G2048_COL_COUNT], int score)
    {
        m_score = score;
        m_item_moved = false;
        for (int row = 0; row < G2048_ROW_COUNT; ++row)
            for (int col = 0; col < G2048_COL_COUNT; ++col)
            {
                m_2048[row][col] = value_map[row][col];
            }
    }

private:
	int m_2048[G2048_ROW_COUNT][G2048_COL_COUNT];
    bool m_item_moved = false;
    int m_score = 0;
    int m_step = 0;

    int m_play_count = 0;
    int m_total_score = 0;
    int m_max_score = 0;
};

#endif