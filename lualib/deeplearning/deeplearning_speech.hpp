#ifndef DEEPLEARNING_SPEECH_INCLUDED
#define DEEPLEARNING_SPEECH_INCLUDED

#include "other/mfcc.h"
#include "deeplearning_model.hpp"
#include "dynet/lstm.h"
#include "dynet/dict.h"
#include "other/mlp.h"
#include "carp_string.hpp"
#include <fstream>
#include "other/ctc/CTCLossNode.h"

#define _MFCCData 0
#define _SpeechData 0
#define _SpeechWordData 0

CARP_MESSAGE_MACRO(MFCCData, std::vector<std::vector<float>>, mfcc, std::string, sentence, std::string, phoneme_word, std::string, phoneme_vowel);
CARP_MESSAGE_MACRO(SpeechData, std::vector<MFCCData>, data_list);
CARP_MESSAGE_MACRO(SpeechWordData, std::vector<std::string>, word_list);

class DeeplearningSpeechModel : public DeeplearningModel
{
public:
	DeeplearningSpeechModel(const char* word_data_path) : m_trainer(m_collection)
		, m_l2rbuilder(1, MFCC_SIZE, HIDDEN_DIM, m_collection)
		, m_r2lbuilder(1, MFCC_SIZE, HIDDEN_DIM, m_collection)
		, m_mlp(m_collection)
	{
		size_t label_size = 1;
		m_tag_BLANK = m_dict.convert("<BLANK>");

		std::vector<char> out;
		if (word_data_path != nullptr && CarpMessageReadFactory::LoadStdFile(word_data_path, out))
		{
			SpeechWordData data;
			int result = data.Deserialize(out.data(), static_cast<int>(out.size()));
			if (result >= CARP_MESSAGE_DR_NO_DATA)
			{
				for (auto& word : data.word_list)
					m_dict.convert(word);
				label_size = m_dict.get_words().size();
			}
		}
		
		m_mlp.append(m_collection, dynet::Layer(/* input_dim */ HIDDEN_DIM * 2, /* output_dim */ label_size, /* activation */ dynet::Activation::LINEAR, /* dropout_rate */ DROPOUT_RATE));
	}

public:
	bool Wav2MFCC(const char* desc_path, const char* wav_base_path, const char* word_out_path, const char* speech_out_path)
	{
		std::ifstream desc_file(desc_path);
		if (!desc_file.is_open()) return false;

		SpeechData speech_data;

		std::set<std::string> word_set;
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

			back.mfcc.resize(mfcc_list.size());
			for (size_t i = 0; i < mfcc_list.size(); ++i)
				for (auto& value : mfcc_list[i])
					back.mfcc[i].push_back(static_cast<float>(value));

			std::vector<std::string> phoneme_list;
			CarpString::Split(back.phoneme_word, " ", phoneme_list);
			for (auto& value : phoneme_list) word_set.insert(value);
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
	void SetTrainDataPath(const char* mfcc_path)
	{
		// 保存训练数据路径
		m_train_mfcc_path.clear();
		if (mfcc_path) m_train_mfcc_path = mfcc_path;
	}

	void Build(dynet::ComputationGraph& cg, const std::vector<dynet::Expression>& input_list, bool dropout, std::vector<dynet::Expression>& out_list)
	{
		// 双向lstm
		m_l2rbuilder.new_graph(cg);  // reset RNN builder for new graph
		m_l2rbuilder.start_new_sequence();
		m_r2lbuilder.new_graph(cg);  // reset RNN builder for new graph
		m_r2lbuilder.start_new_sequence();

		// read sequence from left to right
		std::vector<dynet::Expression> l2r;
		for (int i = 0; i < (int)input_list.size(); ++i)
			l2r.push_back(m_l2rbuilder.add_input(input_list[i]));
		// read sequence from right to left
		std::vector<dynet::Expression> r2l;
		for (int i = (int)input_list.size() - 1; i >= 0; --i)
			r2l.push_back(m_r2lbuilder.add_input(input_list[i]));
	
		// 合并
		for (int i = 0; i < (int)input_list.size(); ++i)
			out_list.push_back(dynet::concatenate({ l2r[i], r2l[i] }));

		// MLP
		if (dropout) m_mlp.enable_dropout();
		else m_mlp.disable_dropout();

		for (int i = 0; i < (int)out_list.size(); ++i)
			out_list[i] = m_mlp.run(out_list[i], cg);
	}

	size_t TrainInit() override
	{
		m_data.data_list.clear();

		std::vector<char> out;
		if (!CarpMessageReadFactory::LoadStdFile(m_train_mfcc_path, out)) return 0;

		int result = m_data.Deserialize(out.data(), static_cast<int>(out.size()));
		if (result < CARP_MESSAGE_DR_NO_DATA) return 0;

		return m_data.data_list.size();
	}

	void TrainRelease() override
	{
		m_data.data_list.clear();
	}

	double Training(size_t index, bool& right) override
	{
		if (dynet::get_number_of_active_graphs() > 0) return 0;

		// 构建动态图
		dynet::ComputationGraph cg;
		// 设置输入
		std::vector<dynet::Expression> input_list;
		for (auto& data : m_data.data_list[index].mfcc)
			input_list.push_back(input(cg, { MFCC_SIZE }, data));

		// 获得隐藏层
		std::vector<dynet::Expression> out_list;
		Build(cg, input_list, true, out_list);

		// 预测
		std::vector<int> label_list;
		Prediction(cg, out_list, label_list);

		right = Label2String(label_list) == m_data.data_list[index].phoneme_word;

		dynet::Expression loss_expr = ctc_loss(dynet::concatenate(out_list), m_dict.get_words().size(), label_list, m_tag_BLANK);

		// 累计损失值
		const double loss = as_scalar(cg.incremental_forward(loss_expr));
		// 反向传播
		cg.backward(loss_expr);
		// 更新参数
		m_trainer.update();

		return loss;
	}

	static void Prediction(dynet::ComputationGraph& cg, const std::vector<dynet::Expression>& softmax_list, std::vector<int>& label_list)
	{
		// 预测
		int index = 0;
	    for (auto& out : softmax_list)
	    {
			++index;
			// Get values
			const auto probs = dynet::as_vector(cg.incremental_forward(out));
			// Get argmax
			size_t argmax = 0;
			for (size_t i = 1; i < probs.size(); ++i) {
				if (probs[i] > probs[argmax])
					argmax = i;
			}
			label_list.push_back(argmax);
	    }
	}

	const char* Output(const char* file_path)
	{
		m_output.clear();
		if (dynet::get_number_of_active_graphs() > 0) return m_output.c_str();

		std::string wav_path = file_path;
		std::ifstream wav_file(wav_path, std::ios::binary);
		if (!wav_file.is_open()) return m_output.c_str();

		std::vector<std::vector<double>> mfcc_list;
		std::string error;
		MFCC mfcc;
		if (!mfcc.process(wav_file, mfcc_list, error)) return m_output.c_str();

		std::vector<std::vector<float>> data_list;
		data_list.resize(mfcc_list.size());
		for (size_t i = 0; i < mfcc_list.size(); ++i)
			for (auto& value : mfcc_list[i])
				data_list[i].push_back(static_cast<float>(value));

		// 构建动态图
		dynet::ComputationGraph cg;
		// 设置输入
		std::vector<dynet::Expression> input_list;
		for (auto& data : data_list)
			input_list.push_back(input(cg, { MFCC_SIZE }, data));

		// 获得隐藏层
		std::vector<dynet::Expression> out_list;
		Build(cg, input_list, false, out_list);

		// 预测
		std::vector<int> label_list;
		Prediction(cg, out_list, label_list);

		m_output = Label2String(label_list);
		return m_output.c_str();
	}

	std::string Label2String(const std::vector<int>& label_list)
	{
		std::string out;
		for (size_t i = 0; i < label_list.size(); ++i)
		{
			out += m_dict.convert(label_list[i]);
			if (i + 1 < label_list.size())
				out += " ";
		}

		return out;
	}

private:
	dynet::SimpleSGDTrainer m_trainer;

private:
	dynet::LSTMBuilder m_l2rbuilder;
	dynet::LSTMBuilder m_r2lbuilder;
	dynet::MLP m_mlp;

private:
	std::string m_train_mfcc_path;
	SpeechData m_data;

	dynet::Dict m_dict;
	int m_tag_BLANK = 0;

	std::string m_output;

private:
	static const unsigned HIDDEN_DIM = 1024;
	static const unsigned MFCC_SIZE = 13;
	static constexpr float DROPOUT_RATE = 0.4f;
};

#endif