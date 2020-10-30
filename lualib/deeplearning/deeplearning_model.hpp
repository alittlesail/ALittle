#ifndef DEEPLEARNING_MODEL_INCLUDED
#define DEEPLEARNING_MODEL_INCLUDED

#include <random>


#include "carp_task_consumer.hpp"

class DeeplearningModel
{
public:
	virtual ~DeeplearningModel() { StopTraining(); }

public:
	bool StartTraining()
	{
		StopTraining();

		if (dynet::get_number_of_active_graphs() > 0) return false;

		m_total_train_count = 0;
		m_cur_train_count = 0;
		m_train_round = 0;
		m_cur_right_count = 0;
		
		m_train_order.clear();
		m_train_index = 0;

		m_run = true;
		m_thread = new std::thread(&DeeplearningModel::Run, this);

		return true;
	}

	void StopTraining()
	{
		if (m_thread == nullptr) return;

		m_run = false;
		m_thread->join();
		delete m_thread;
		m_thread = nullptr;

		m_consumer.HandleEvent();
		m_loss_list.clear();
	}

	void Run()
	{
		m_total_train_count = TrainInit();
		if (m_total_train_count <= 0) return;

		// 计算批次数量
		m_train_order.resize(m_total_train_count);
		for (size_t i = 0; i < m_train_order.size(); ++i) m_train_order[i] = i;
		std::shuffle(m_train_order.begin(), m_train_order.end(), std::mt19937(std::random_device()()));

		while (m_run)
		{
			// 计算下一轮
			if (m_train_index >= m_train_order.size())
			{
				m_train_round += 1;
				m_cur_train_count = 0;
				m_cur_right_count = 0;
				m_train_index = 0;
			}

			// 训练获得结果
			size_t right_count = 0;
			auto loss = Training(m_train_order[m_train_index], right_count);

			// 训练下标
			m_train_index += 1;
			m_cur_train_count += 1;
			m_cur_right_count += right_count;
			
			m_consumer.PushEvent(std::bind(&DeeplearningModel::HandleTrainResult, this, loss));
		}

		m_train_order.clear();
		TrainRelease();
	}

	void HandleEvent() { m_consumer.HandleEvent(); }

private:
	void HandleTrainResult(double loss)
	{
		m_loss_list.push_back(loss);
	}

public:
	bool HasLoss() const { return !m_loss_list.empty(); }
	
	double GetLoss()
	{
		if (m_loss_list.empty()) return 0;
		const double value = m_loss_list.front();
		m_loss_list.pop_front();
		return value;
	}
	
public:
	virtual void Save(const char* file_path)
	{
		dynet::TextFileSaver saver(file_path);
		saver.save(m_collection);
	}

	virtual size_t TrainInit() { return 0; }
	virtual void TrainRelease() {}
	virtual double Training(size_t index, size_t& right_count) { return 0.0; }

	virtual size_t GetTotalTrainCount() { return m_total_train_count; }
	virtual size_t GetCurTrainCount() { return m_cur_train_count; }
	virtual size_t GetTrainRound() { return m_train_round; }
	virtual size_t GetCurRightCount() { return m_cur_right_count; }
	
protected:
	dynet::ParameterCollection m_collection;

private:
	size_t m_total_train_count = 0;
	size_t m_cur_train_count = 0;
	size_t m_cur_right_count = 0;	// 正确数量
	size_t m_train_round = 0;
	std::list<double> m_loss_list;

private:
	std::vector<size_t> m_train_order;
	size_t m_train_index = 0;

private:
	std::thread* m_thread = nullptr;
	volatile bool m_run = false;	// 支线程是否正在执行
	CarpTaskConsumer m_consumer;
};

#endif