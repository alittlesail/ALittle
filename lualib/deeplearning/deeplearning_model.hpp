#ifndef DEEPLEARNING_MODEL_INCLUDED
#define DEEPLEARNING_MODEL_INCLUDED

#include "carp_task_consumer.hpp"

class DeeplearningModel
{
public:
	virtual ~DeeplearningModel() { StopTraining(); }

public:
	static int ReverseInt(int i)
	{
		unsigned char ch1, ch2, ch3, ch4;
		ch1 = i & 255;
		ch2 = (i >> 8) & 255;
		ch3 = (i >> 16) & 255;
		ch4 = (i >> 24) & 255;
		return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
	}

	// 读取图像数据
	// Code from https://compvisionlab.wordpress.com/2014/01/01/c-code-for-reading-mnist-data-set/ to read MNIST
	static bool ReadMnist(const std::string& data_file, std::vector<std::vector<float>>& arr)
	{
		std::ifstream file(data_file, std::ios::binary);
		if (!file.is_open()) return false;

		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);
		arr.resize(number_of_images);
		for (int i = 0; i < number_of_images; ++i)
		{
			arr[i].reserve(n_rows * n_cols);
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					arr[i].push_back((float)temp);
				}
			}
		}

		return true;
	}

	// 读取标记数据
	static bool ReadMnistLabels(const std::string& label_file, std::vector<unsigned>& labels)
	{
		std::ifstream file(label_file, std::ios::binary);
		if (!file.is_open()) return false;

		int magic_number = 0;
		int number_of_images = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		labels.reserve(number_of_images);
		for (int i = 0; i < number_of_images; ++i)
		{
			unsigned char temp = 0;
			file.read((char*)&temp, sizeof(temp));
			labels.push_back((unsigned)temp);
		}
		return true;
	}

public:
	bool StartTraining()
	{
		StopTraining();

		if (dynet::get_number_of_active_graphs() > 0) return false;

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
		TrainInit();
		while (m_run)
		{
			auto loss = Training();
			m_consumer.PushEvent(std::bind(&DeeplearningModel::HandleTrainResult, this, loss));
		}
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

	virtual void TrainInit() {}
	virtual void TrainRelease() {}
	virtual double Training() { return 0.0; }

	virtual int GetTotalTrainCount() { return m_total_train_count; }
	virtual int GetCurTrainCount() { return m_cur_train_count; }
	virtual int GetTrainRound() { return m_train_round; }
	virtual int GetCurRightCount() { return m_cur_right_count; }
	
protected:
	dynet::ParameterCollection m_collection;

protected:
	int m_total_train_count = 0;
	int m_cur_train_count = 0;
	int m_cur_right_count = 0;	// 正确数量
	int m_train_round = 0;
	std::list<double> m_loss_list;

private:
	std::thread* m_thread = nullptr;
	volatile bool m_run = false;	// 支线程是否正在执行
	CarpTaskConsumer m_consumer;
};

#endif