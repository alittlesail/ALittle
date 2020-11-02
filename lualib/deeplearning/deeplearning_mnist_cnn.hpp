#ifndef DEEPLEARNING_MNIST_CNN_INCLUDED
#define DEEPLEARNING_MNIST_CNN_INCLUDED

#include "deeplearning_model.hpp"
#include "carp_surface.hpp"

class DeeplearningMnistCNNModel : public DeeplearningModel
{
public:
	DeeplearningMnistCNNModel() : m_trainer(m_collection)
	{
		m_pConv1 = m_collection.add_parameters({ 5, 5, 1, 32 });
		m_pB1 = m_collection.add_parameters({ 32, });
		m_pConv2 = m_collection.add_parameters({ 5, 5, 32, 64 });
		m_pB2 = m_collection.add_parameters({ 64, });
		m_pW1 = m_collection.add_parameters({ HIDDEN_DIM, 7 * 7 * 64 });
		m_pB3 = m_collection.add_parameters({ HIDDEN_DIM, });
		m_pW2 = m_collection.add_parameters({ 10, HIDDEN_DIM });
	}

public:
	void SetTrainDataPath(const char* train_image, const char* train_labels)
	{
		// 保存训练数据路径
		m_train_image_path.clear();
		m_train_labels_path.clear();
		if (train_image) m_train_image_path = train_image;
		if (train_labels) m_train_labels_path = train_labels;
	}

	dynet::Expression Build(dynet::ComputationGraph& cg, dynet::Expression x, bool dropout) const
	{
		// 卷积参数
		const auto conv1 = dynet::parameter(cg, m_pConv1);
		// 偏置参数
		const auto b1 = dynet::parameter(cg, m_pB1);
		// 卷积
		const auto conv1_x = dynet::conv2d(x, conv1, b1, { 1, 1 }, false);
		// 激活
		const auto relu1_x = dynet::rectify(dynet::maxpooling2d(conv1_x, { 2, 2 }, { 2, 2 }));

		// 卷积参数
		const auto conv2 = dynet::parameter(cg, m_pConv2);
		// 偏置参数
		const auto b2 = dynet::parameter(cg, m_pB2);
		// 卷积
		const auto conv2_x = dynet::conv2d(relu1_x, conv2, b2, { 1, 1 }, false);
		// 激活
		const auto relu2_x = dynet::rectify(dynet::maxpooling2d(conv2_x, { 2, 2 }, { 2, 2 }));

		// 调整维度
		const auto reshape_x = dynet::reshape(relu2_x, { 7 * 7 * 64, 1 });

		// 线性变换
		const auto w1 = dynet::parameter(cg, m_pW1);
		const auto b3 = dynet::parameter(cg, m_pB3);
		auto h = dynet::rectify(w1 * reshape_x + b3);

		if (dropout) h = dynet::dropout(h, DROPOUT_RATE);
		const auto w2 = dynet::parameter(cg, m_pW2);

		return w2 * h;
	}

	size_t TrainInit() override
	{
		m_image_list.clear();
		ReadImage(m_train_image_path, m_image_list);
		for (auto& trains : m_image_list)
		{
			for (auto& value : trains)
				value /= 255.0f;
		}
		m_label_list.clear();
		ReadLabel(m_train_labels_path, m_label_list);

		// 重置
		m_trainer.restart();
		return m_image_list.size();
	}

	void TrainRelease() override
	{
		m_image_list.clear();
		m_label_list.clear();
	}

	double Training(size_t index, bool& right) override
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		// 构建动态图
		dynet::ComputationGraph cg;
		// 设置输入
		const auto x = input(cg, { IMAGE_SIZE, IMAGE_SIZE }, m_image_list[index]);
		// 获得隐藏层
		const auto output = Build(cg, x, true);

		// 预测
		const auto label = Prediction(cg, output);
		right = label == static_cast<int>(m_label_list[index]);
		
		// 构建 负对数似然 模型
		const auto loss_expr = dynet::pickneglogsoftmax(output, m_label_list[index]);
		// 累计损失值
		const double loss = as_scalar(cg.forward(loss_expr));
		// 反向传播
		cg.backward(loss_expr);
		// 更新参数
		m_trainer.update();

		return loss;
	}

	static int Prediction(dynet::ComputationGraph& cg, dynet::Expression output)
	{
		// 预测
		const auto out = dynet::softmax(output);
		// Get values
		const auto probs = dynet::as_vector(cg.forward(out));
		// Get argmax
		size_t argmax = 0;
		for (size_t i = 1; i < probs.size(); ++i) {
			if (probs[i] > probs[argmax])
				argmax = i;
		}

		return static_cast<int>(argmax);
	}

	int Output(size_t address)
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;
		
		CarpSurface* surface = nullptr;
		memcpy(&surface, &address, sizeof(size_t));
		
		if (surface == nullptr) return -1;
		if (surface->GetWidth() == 0 || surface->GetHeight() == 0) return -1;
		
		std::vector<float> data;

		// 如果图片不是指定大小那么就进行缩放
		if (surface->GetWidth() == IMAGE_SIZE && surface->GetHeight() == IMAGE_SIZE)
		{
			data.resize(IMAGE_SIZE * IMAGE_SIZE, 0.0f);
			for (unsigned i = 0; i < IMAGE_SIZE * IMAGE_SIZE; ++i)
				data[i] = static_cast<float>(surface->GetGray(i)) / 255.0f;
		}
		else
		{
			CarpSurface new_surface(IMAGE_SIZE, IMAGE_SIZE);
			new_surface.ScaleFrom(surface, nullptr, nullptr);

			data.resize(IMAGE_SIZE * IMAGE_SIZE, 0.0f);
			for (unsigned i = 0; i < IMAGE_SIZE * IMAGE_SIZE; ++i)
				data[i] = static_cast<float>(new_surface.GetGray(i)) / 255.0f;
		}

		// 构建动态图
		dynet::ComputationGraph cg;
		// 设置当前输入
		const auto x = input(cg, { IMAGE_SIZE, IMAGE_SIZE }, data);
		// 获得隐藏层
		const auto output = Build(cg, x, false);

		return Prediction(cg, output);
	}

private:
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
	static bool ReadImage(const std::string& data_file, std::vector<std::vector<float>>& arr)
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
	static bool ReadLabel(const std::string& label_file, std::vector<unsigned>& labels)
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

private:
	dynet::SimpleSGDTrainer m_trainer;

private:
	dynet::Parameter m_pConv1;
	dynet::Parameter m_pB1;
	dynet::Parameter m_pConv2;
	dynet::Parameter m_pB2;
	dynet::Parameter m_pW1;
	dynet::Parameter m_pB3;
	dynet::Parameter m_pW2;
	
private:
	std::string m_train_image_path;
	std::string m_train_labels_path;
	
	std::vector<std::vector<float>> m_image_list;
	std::vector<unsigned> m_label_list;

private:
	static const unsigned HIDDEN_DIM = 1024;
	static const unsigned IMAGE_SIZE = 28;
	static constexpr float DROPOUT_RATE = 0.4f;
};

#endif