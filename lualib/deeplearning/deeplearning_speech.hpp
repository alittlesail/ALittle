#ifndef DEEPLEARNING_SPEECH_INCLUDED
#define DEEPLEARNING_SPEECH_INCLUDED

#include "torch/torch.h"
#include "deeplearning_model.hpp"
#include "Carp/carp_message.hpp"
#include "Carp/carp_string.hpp"
#include "other/mfcc.h"

CARP_MESSAGE_MACRO(MFCCData, 0, std::vector<float>, mfccs, size_t, count, std::string, sentence, std::string, phoneme_word, std::string, phoneme_vowel);
CARP_MESSAGE_MACRO(SpeechData, 0, std::vector<MFCCData>, data_list);
CARP_MESSAGE_MACRO(SpeechWordData, 0, std::vector<std::string>, word_list);

class DeeplearningSpeechModel : public DeeplearningModel
{
public:
	DeeplearningSpeechModel(const char* word_data_path)
	{
		m_tag_BLANK = Convert("<BLANK>");

		std::vector<char> out;
		if (word_data_path != nullptr && CarpMessageReadFactory::LoadStdFile(word_data_path, out))
		{
			SpeechWordData data;
			const int result = data.Deserialize(out.data(), static_cast<int>(out.size()));
			if (result >= CARP_MESSAGE_DR_NO_DATA)
			{
				for (auto& word : data.word_list)
					Convert(word);
			}
		}

		m_conv1 = register_module("conv1", torch::nn::Conv1d(torch::nn::Conv1dOptions(MFCC_SIZE, 50, {5})));
		m_pool1 = register_module("pool1", torch::nn::MaxPool1d(torch::nn::MaxPool1dOptions(4)));
		m_lstm = register_module("lstm", torch::nn::LSTM(torch::nn::LSTMOptions(50, 128).bidirectional(true)));
		m_fc = register_module("fc", torch::nn::Linear(256, m_word_map_tag.size()));

		m_trainer = std::make_shared<torch::optim::Adam>(parameters(), torch::optim::AdamOptions(0.01));
	}
	
	bool Wav2MFCC(const char* desc_path, const char* wav_base_path, int max_count, const char* word_out_path, const char* speech_out_path)
	{
		std::ifstream desc_file(desc_path);
		if (!desc_file.is_open()) return false;

		SpeechData speech_data;

		std::set<std::string> word_set;

		int cur_count = 0;
		while (true)
		{
			std::string file;
			if (!std::getline(desc_file, file)) break;
			std::string sentence;
			if (!std::getline(desc_file, sentence)) break;
			std::string phoneme_word;
			if (!std::getline(desc_file, phoneme_word)) break;
			std::string phoneme_vowel;
			if (!std::getline(desc_file, phoneme_vowel)) break;

			std::string wav_path = wav_base_path;
			wav_path += file;
			std::ifstream wav_file(wav_path, std::ios::binary);
			if (!wav_file.is_open()) break;

			MFCC mfcc;
			std::vector<std::vector<double>> mfcc_list;
			std::string error;
			if (!mfcc.process(wav_file, mfcc_list, error)) return false;

			speech_data.data_list.emplace_back(MFCCData());
			auto& back = speech_data.data_list.back();

			back.sentence = sentence;
			back.phoneme_word = phoneme_word;
			back.phoneme_vowel = phoneme_vowel;

			back.count = mfcc_list.size();
			for (size_t i = 0; i < mfcc_list.size(); ++i)
				for (auto& value : mfcc_list[i])
					back.mfccs.push_back(static_cast<float>(value));

			std::vector<std::string> phoneme_list;
			CarpString::Split(back.phoneme_word, " ", true, phoneme_list);
			for (auto& value : phoneme_list) word_set.insert(value);

			++cur_count;
			std::cout << cur_count << std::endl;
			if (max_count > 0)
			{
				--max_count;
				if (max_count == 0) break;
			}
		}

		{
			SpeechWordData word_data;
			for (auto& value : word_set)
				word_data.word_list.push_back(value);
			std::sort(word_data.word_list.begin(), word_data.word_list.end());

			std::vector<char> out;
			out.resize(word_data.GetTotalSize());
			word_data.Serialize(out.data());
			if (!CarpMessageWriteFactory::WriteMemoryToStdFile(word_out_path, out.data(), out.size())) return false;
		}

		std::vector<char> out;
		out.resize(speech_data.GetTotalSize());
		speech_data.Serialize(out.data());
		return CarpMessageWriteFactory::WriteMemoryToStdFile(speech_out_path, out.data(), out.size());
	}

public:
	void SetSpeechDataPath(const char* mfcc_path)
	{
		// 保存训练数据路径
		m_train_mfcc_path.clear();
		if (mfcc_path) m_train_mfcc_path = mfcc_path;
	}
	
	size_t TrainInit() override
	{
		m_data.data_list.clear();

		std::vector<char> out;
		if (!CarpMessageReadFactory::LoadStdFile(m_train_mfcc_path, out)) return 0;

		const int result = m_data.Deserialize(out.data(), static_cast<int>(out.size()));
		if (result < CARP_MESSAGE_DR_NO_DATA) return 0;

		return m_data.data_list.size();
	}

	void TrainRelease() override
	{
		m_data.data_list.clear();
	}
	
	double Training(size_t index, bool& right) override
	{
		// 重置误差项
		m_trainer->zero_grad();
		
		// 设置输入
		auto& data = m_data.data_list[index];

		auto input = torch::from_blob(data.mfccs.data(), { (long long)data.count, 1, MFCC_SIZE });
		
		// 执行运算
		auto output = forward(input, true);

		auto labels = output.argmax(2);

		// 判断预测是否正确
		const auto pred = Label2String(labels, labels.size(0));
		// std::cout << pred << std::endl;
		right = m_data.data_list[index].phoneme_word == pred;

		std::vector<std::string> word_list;
		CarpString::Split(m_data.data_list[index].phoneme_word, " ", true, word_list);
		std::vector<int> phoneme_list;
		for (auto& word : word_list)
		{
			auto it = m_word_map_tag.find(word);
			if (it != m_word_map_tag.end())
				phoneme_list.push_back(it->second);
			else
				phoneme_list.push_back((int)m_word_map_tag.size());
		}
		torch::Tensor target = torch::from_blob(phoneme_list.data(), { (long long)phoneme_list.size() }, at::TensorOptions(torch::ScalarType::Int));

		auto input_lengths = torch::full({ 1 }, output.size(0), at::TensorOptions(torch::ScalarType::Int));
		auto target_lengths = torch::full({ 1 }, target.size(0), at::TensorOptions(torch::ScalarType::Int));

		// 获得损失表达式
		auto loss_expr = torch::ctc_loss(output, target, input_lengths, target_lengths, m_tag_BLANK);
		auto loss = loss_expr.item().toDouble();
		
		// 计算反向传播
		loss_expr.backward();
		// 更新训练
		m_trainer->step();

		return loss;
	}

	torch::Tensor forward(torch::Tensor x, bool training)
	{
		x = x.transpose(0, 1).transpose(1, 2);
		x = m_conv1->forward(x);
		x = m_pool1->forward(x);
		x = torch::relu(x);
		x = x.transpose(1, 2).transpose(0, 1);
		// 双向lstm
		x = std::get<0>(m_lstm->forward(x));
		
		// 全连接
		x = m_fc->forward(x);
		return torch::log_softmax(x, 2);
	}

	const char* Output(const char* file_path)
	{
		m_output.clear();

		std::string wav_path = file_path;
		std::ifstream wav_file(wav_path, std::ios::binary);
		if (!wav_file.is_open()) return m_output.c_str();

		std::vector<std::vector<double>> mfcc_list;
		std::string error;
		MFCC mfcc;
		if (!mfcc.process(wav_file, mfcc_list, error)) return m_output.c_str();

		std::vector<float> data;
		for (size_t i = 0; i < mfcc_list.size(); ++i)
			for (auto& value : mfcc_list[i])
				data.push_back(static_cast<float>(value));

		torch::Tensor input = torch::from_blob(data.data(), { (long long)mfcc_list.size(), 1, MFCC_SIZE });

		// 执行运算
		auto output = forward(input, false);
		auto labels = output.argmax(2);

		m_output = Label2String(labels, data.size());
		return m_output.c_str();
	}

	std::string Label2String(const torch::Tensor& labels, size_t count)
	{
		std::string out;
		for (size_t i = 0; i < count; ++i)
		{
			const auto label = labels[i][0].item().toInt();
			if (label == m_tag_BLANK) continue;
			
			auto it = m_tag_map_word.find(label);
			if (it != m_tag_map_word.end())
				out += it->second;
			else
				out += "?";
			if (i + 1 < count)
				out += " ";
		}

		return out;
	}

	int Convert(const std::string& word)
	{
		auto it = m_word_map_tag.find(word);
		if (it != m_word_map_tag.end()) return it->second;

		const int id = m_max_id;
		++m_max_id;
		m_word_map_tag[word] = id;
		m_tag_map_word[id] = word;
		return id;
	}

private:
	std::shared_ptr<torch::optim::Adam> m_trainer;

private:
	torch::nn::Conv1d m_conv1{nullptr};
	torch::nn::MaxPool1d m_pool1{ nullptr };
	torch::nn::LSTM m_lstm{nullptr};
	torch::nn::Linear m_fc{nullptr};
	
private:
	std::string m_train_mfcc_path;
	SpeechData m_data;
	std::string m_output;

private:
	std::map<int, std::string> m_tag_map_word;
	std::map<std::string, int> m_word_map_tag;
	int m_max_id = 0;
	int m_tag_BLANK = 0;

	static const unsigned MFCC_SIZE = 13;
};

#endif