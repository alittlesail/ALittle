#ifndef DEEPLEARNING_MNIST_INCLUDED
#define DEEPLEARNING_MNIST_INCLUDED

#include "Carp/carp_surface.hpp"

#include "Carp/carp_robot_model.hpp"
#include "deeplearning_model.hpp"

class DeeplearningMnistModel : public DeeplearningModel
{
public:
	DeeplearningMnistModel()
		: m_conv1(m_model, 1, 64, { 5, 5 })
		, m_conv2(m_model, 64, 128, { 5, 5 })
		, m_fc1(m_model, 4 * 4 * 128, 1024), m_fc2(m_model, 1024, 10)
		, m_trainer(m_model)
	{
	}

public:
	void SetMnistRoot(const char* path)
	{
		if (path) m_mnist_path = path;
	}

	static unsigned int CarpRtpReadUint32(unsigned int value)
	{
		char* ptr = (char*)&value;
		std::swap(ptr[0], ptr[3]);
		std::swap(ptr[1], ptr[2]);
		return value;
	}
	
	int TrainInit() override
	{
		m_images.clear();
		m_labels.clear();

		// 读取图片
		{
			std::string file_path = m_mnist_path + "/train-images-idx3-ubyte";

			FILE* file = nullptr;
#ifdef _WIN32
			fopen_s(&file, file_path.c_str(), "rb");
#else
			file = fopen(file_path.c_str(), "rb");
#endif
			if (file == nullptr)
			{
				printf("file open failed:%s\n", file_path.c_str());
				return 0;
			}

			struct ImageHead
			{
				unsigned int desc = 0;
				unsigned int count = 0;
				unsigned int width = 0;
				unsigned int height = 0;
			};
				
			// 读取头信息
			ImageHead head;
			size_t read = fread(&head, 1, sizeof(head), file);
			if (read != sizeof(head))
			{
				printf("head read failed:%s\n", file_path.c_str());
				fclose(file);
				return 0;
			}

			head.desc = CarpRtpReadUint32(head.desc);
			head.width = CarpRtpReadUint32(head.width);
			head.height = CarpRtpReadUint32(head.height);
			head.count = CarpRtpReadUint32(head.count);

			// 图片像素数量
			auto pixel_count = head.width * head.height;
				
			m_images.resize(head.count);
			std::vector<unsigned char> buffer;
			buffer.resize(pixel_count);
			for (size_t i = 0; i < m_images.size(); ++i)
			{
				auto& image = m_images[i];
				image.resize(pixel_count);
				read = fread(buffer.data(), 1, pixel_count, file);
				if (read != pixel_count)
				{
					printf("buffer read failed:%s\n", file_path.c_str());
					fclose(file);
					return 0;
				}
				for (size_t j = 0; j < buffer.size(); ++j)
					image[j] = buffer[j] / 255.0f;
			}

			fclose(file);
		}

		// 读取标签
		{
			std::string file_path = m_mnist_path + "/train-labels-idx1-ubyte";

			FILE* file = nullptr;
#ifdef _WIN32
			fopen_s(&file, file_path.c_str(), "rb");
#else
			file = fopen(file_path.c_str(), "rb");
#endif
			if (file == nullptr)
			{
				printf("file open failed:%s\n", file_path.c_str());
				return 0;
			}

			struct LabelHead
			{
				unsigned int desc = 0;
				unsigned int count = 0;
			};

			// 读取头信息
			LabelHead head;
			size_t read = fread(&head, 1, sizeof(head), file);
			if (read != sizeof(head))
			{
				printf("head read failed:%s\n", file_path.c_str());
				fclose(file);
				return 0;
			}

			head.desc = CarpRtpReadUint32(head.desc);
			head.count = CarpRtpReadUint32(head.count);

			m_labels.resize(head.count);
			std::vector<unsigned char> buffer;
			buffer.resize(head.count);
			read = fread(buffer.data(), 1, head.count, file);
			if (read != head.count)
			{
				printf("buffer read failed:%s\n", file_path.c_str());
				fclose(file);
				return 0;
			}

			for (size_t j = 0; j < m_labels.size(); ++j)
				m_labels[j] = buffer[j];
			
			fclose(file);
		}

		return static_cast<int>(m_images.size());
	}

	void TrainRelease() override
	{	
		m_images.clear();
		m_labels.clear();
	}
	
	double Training(size_t index, bool& right) override
	{
		CarpRobotComputationGraph graph;

		m_conv1.Build(graph);
		m_conv2.Build(graph);
		m_fc1.Build(graph);
		m_fc2.Build(graph);

		auto input = graph.AddInput(CarpRobotDim({ IMAGE_SIZE, IMAGE_SIZE, 1 }), &m_images[index]);
		
		// 执行运算
		auto output = Forward(input, true);

		// 判断预测是否正确
		right = output.GetValue().AsVectorAndArgmax() == m_labels[index];

		// 设置输出表达式
		auto target = m_labels[index];

		// 获得损失表达式
		auto loss_expr = output.PickNegLogSoftmax(m_labels[index]);
		auto loss = loss_expr.GetValue().AsScalar();
		
		graph.Backward();
		// 更新训练
		m_trainer.Update();

		return loss;
	}

	CarpRobotExpression Forward(CarpRobotExpression& input, bool training)
	{
		// 第一层卷积
		auto x = m_conv1.Forward(input);
		x = x.MaxPooling2D({ 2, 2 }, { 2, 2 });
		x = x.Rectify();

		// 第二层卷积
		x = m_conv2.Forward(x);
		x = x.MaxPooling2D({ 2, 2 }, { 2, 2 });
		x = x.Rectify();

		// 将矩阵转为
		x = x.Reshape(CarpRobotDim({ 4 * 4 * 128 }));

		// 第一层全连接
		x = m_fc1.Forward(x);
		x = x.Rectify();

		// dropout
		if (training) x = x.Dropout(0.5);

		// 第二层全连接
		x = m_fc2.Forward(x);

		return x.LogSoftmax();
	}

	int Output(size_t address)
	{
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

		CarpRobotComputationGraph graph;

		m_conv1.Build(graph);
		m_conv2.Build(graph);
		m_fc1.Build(graph);
		m_fc2.Build(graph);

		auto input = graph.AddInput(CarpRobotDim({ IMAGE_SIZE, IMAGE_SIZE, 1 }), &data);

		// 执行运算
		auto output = Forward(input, false);

		return output.GetValue().AsVectorAndArgmax();
	}

private:
	CarpRobotAdamTrainer m_trainer;

private:
	CarpRobotConv2D m_conv1;
	CarpRobotConv2D m_conv2;
	CarpRobotLinear m_fc1;
	CarpRobotLinear m_fc2;

private:
	std::vector<std::vector<float>> m_images;
	std::vector<int> m_labels;
	std::string m_mnist_path;

	static const unsigned IMAGE_SIZE = 28;
};

#endif