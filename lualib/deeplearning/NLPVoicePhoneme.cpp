
#include "NLPVoicePhoneme.h"
#include "../../Parameter/ParameterInit.h"
#include "../../Parameter/Parameter.h"
#include "../../Parameter/ParameterCollection.h"
#include "../../Graph/ComputationGraph.h"
#include "../../Common/ModelFile.h"
#include "../../Common/MFCC.h"

#include <rapidjson/document.h>

namespace ALittle
{
namespace Robot
{
	
NLPVoicePhonemeDataManager& NLPVoicePhonemeDataManager::Instance()
{
	static NLPVoicePhonemeDataManager instance;
	return instance;
}

bool NLPVoicePhonemeDataManager::SetData(const char* key, const char* json)
{
	rapidjson::Document doc;
	doc.Parse<0>(json);

	if (doc.HasParseError()) return false;
	if (doc.IsObject() == false) return false;

	NLPVoicePhonemeData& data = m_map[key] = NLPVoicePhonemeData();

	rapidjson::Value::ConstMemberIterator label_it = doc.FindMember("label");
	if (label_it == doc.MemberEnd() || label_it->value.IsArray() == false)
	{
		ALITTLE_ERROR("label not found or not a array");
		return false;
	}

	data.label.clear(); data.label.reserve(label_it->value.Capacity());
	for (unsigned int i = 0; i < label_it->value.Capacity(); ++i)
	{
		if (label_it->value[i].IsString() == false) return false;
		data.label.push_back(label_it->value[i].GetString());
	}

	rapidjson::Value::ConstMemberIterator data_it = doc.FindMember("data");
	if (data_it == doc.MemberEnd() || data_it->value.IsObject() == false)
	{
		ALITTLE_ERROR("data not found or not a object");
		return false;
	}

	rapidjson::Value::ConstMemberIterator v_it = data_it->value.FindMember("v");
	if (v_it == data_it->value.MemberEnd() || v_it->value.IsArray() == false)
	{
		ALITTLE_ERROR("v not found or not a array");
		return false;
	}

	data.data.clear(); data.data.reserve(v_it->value.Capacity());
	for (unsigned int i = 0; i < v_it->value.Capacity(); ++i)
	{
		if (v_it->value[i].IsNumber() == false) return false;
		data.data.push_back((real)v_it->value[i].GetDouble());
	}
	return true;
}

NLPVoicePhonemeData* NLPVoicePhonemeDataManager::GetData( const char* file_path )
{
	std::map<std::string, NLPVoicePhonemeData>::iterator it = m_map.find(file_path);
	if (it != m_map.end()) return &(it->second);

	return 0;
}

NLPVoicePhonemeDataManager::~NLPVoicePhonemeDataManager()
{
	Clear();
}

void NLPVoicePhonemeDataManager::Clear()
{
	m_map.clear();
}

NLPVoicePhoneme::NLPVoicePhoneme( ParameterCollection* model, int lstm_dim, int lstm_layer, const char* json_info )
{
	m_input_dim = 13;
	m_hidden_dim = lstm_dim;
	m_hidden_layer = lstm_layer;

	std::vector<std::string> json_list;
	Utility::SplitJsonArray(json_info, json_list);

	m_name = "NLPVoicePhoneme";
	if (json_list.size() >= 1)
		m_name = json_list[0];

	if (json_list.size() >= 2)
		m_data_path = json_list[1];

	std::vector<std::string> tag_list;
	if (json_list.size() >= 3)
		Utility::SplitJsonArray(json_list[2], tag_list);

	m_tag_BLANK = m_tag_dict.Convert("<BLANK>");
	for (unsigned int i = 0; i < tag_list.size(); ++i)
		m_tag_dict.Convert(tag_list[i]);

	m_tag_size = m_tag_dict.GetCount();

	m_bilstm = new BiLSTM(model, m_hidden_layer, m_input_dim, m_hidden_dim, false);
	m_mlp = new MLP(model, m_hidden_dim, m_tag_size);
}

NLPVoicePhoneme::~NLPVoicePhoneme()
{
	if (m_bilstm) delete m_bilstm;
	if (m_mlp) delete m_mlp;
}

void NLPVoicePhoneme::Build( ComputationGraph* graph )
{
	m_graph = graph;
	m_bilstm->Build(graph);
	m_mlp->Build(graph);
}

void NLPVoicePhoneme::AddInput( std::vector<Expression>& input_list, std::vector<Expression>& out )
{
	// 双向LSTM
	m_bilstm->FullLSTM(input_list, out);

	// mlp
	for (unsigned int i = 0; i < out.size(); ++i)
		out[i] = m_mlp->Calc(out[i]);
}

const char* NLPVoicePhoneme::Output( const char* file_path )
{
	VectorRealForLua data;
	Dim dim;
	if (MFCC::OutputFromFile(file_path, &data, &dim) == false)
	{
		m_tmp = "[]";
		return m_tmp.c_str();
	}

	// 新建网络节点
	Expression sample_expr = Expression(m_graph, m_graph->AddInput(Dim(data.m_data.size()), &(data.m_data)));
	int size = (int)data.m_data.size();
	int count = size / m_input_dim;
	std::vector<Expression> mel_list(count);
	for (int i = 0; i < count; ++i)
		mel_list[i] = pick_range(sample_expr, m_input_dim * i, m_input_dim * (i + 1), 0);


	// 添加到神经网络计算
	std::vector<Expression> observations;
	AddInput(mel_list, observations);

	// 对观察序列进行预测
	std::vector<int> best_path;
	for (unsigned int i = 0; i < observations.size(); ++i)
		best_path.push_back(observations[i].GetValue().AsVectorAndArgmax());

	SimpleJsonArray json_array(8);
	for (unsigned int i = 0; i < best_path.size(); ++i)
	{
		// ignore blanks and repeats
		if ((! (best_path[i] == m_tag_BLANK)) && (! (i != 0 && best_path[i] == best_path[i-1])))
			json_array.Push(m_tag_dict.GetWord(best_path[i]));
	}

	m_tmp = "";
	json_array.GetResult(m_tmp);
	return m_tmp.c_str();
}

int NLPVoicePhoneme::Loss( const char* key )
{
	NLPVoicePhonemeData* data = g_NLPVoicePhonemeDataManager.GetData(key);
	if (data == 0)
	{
		ALITTLE_INFO(STRING_2_UTF8("文件加载失败:") << key);
		m_count = 0;
		m_correct = 0;
		return m_graph->AddInput(0.0f);
	}

	// 转换成枚举
	std::vector<int> new_tags;
	for (unsigned int i = 0; i < data->label.size(); ++i)
	{
		int tag = m_tag_dict.GetIndex(data->label[i]);
		if (tag < 0)
		{
			ALITTLE_ERROR("标签不存在:" << data->label[i] << ", tag_dict:" << m_tag_dict.GetString());
			m_count = 0;
			m_correct = 0;
			return m_graph->AddInput(0.0f);
		}
		new_tags.push_back(tag);
	}

	// 新建网络节点
	Expression sample_expr = Expression(m_graph, m_graph->AddInput(Dim(data->data.size()), &(data->data)));
	int size = (int)data->data.size();
	int count = size / m_input_dim;
	std::vector<Expression> mel_list(count);
	for (int i = 0; i < count; ++i)
		mel_list[i] = pick_range(sample_expr, m_input_dim * i, m_input_dim * (i + 1), 0);


	// 添加到神经网络计算
	std::vector<Expression> observations;
	AddInput(mel_list, observations);

	// 对观察序列进行预测
	std::vector<int> best_path;
	for (unsigned int i = 0; i < observations.size(); ++i)
		best_path.push_back(observations[i].GetValue().AsVectorAndArgmax());

	std::vector<int> hyp;
	for (unsigned int i = 0; i < best_path.size(); ++i)
	{
		// ignore blanks and repeats
		if ((! (best_path[i] == m_tag_BLANK)) && (! (i != 0 && best_path[i] == best_path[i-1])))
			hyp.push_back(best_path[i]);
	}

	Expression loss = ctc_loss(concatenate(observations), m_tag_size, new_tags, m_tag_BLANK);

	// 计算总数和正确数
	m_correct = 0;
	m_count = new_tags.size();
	int index = -1;
	while (true)
	{
		++ index;
		if (index >= (int)new_tags.size()) break;
		if (index >= (int)hyp.size()) break;

		if (new_tags[index] == hyp[index])
			++ m_correct;
	}

	{
		SimpleJsonArray json_array(8);
		for (unsigned int i = 0; i < hyp.size(); ++i)
			json_array.Push(m_tag_dict.GetWord(hyp[i]));

		m_tmp = "";
		json_array.GetResult(m_tmp);
	}

	{
		SimpleJsonArray json_array(8);
		for (unsigned int i = 0; i < new_tags.size(); ++i)
			json_array.Push(m_tag_dict.GetWord(new_tags[i]));

		m_label = "";
		json_array.GetResult(m_label);
	}

	return loss.i;
}

void NLPVoicePhoneme::Serialize( ModelSerializer* file, const char* name )
{
	if (name)
		file->WriteString(name);
	else
		file->WriteString("NLPVoicePhoneme");

	m_bilstm->Serialize(file, "bilstm");
	m_mlp->Serialize(file, "mlp");
}

void NLPVoicePhoneme::Deserialize( ModelDeserializer* file, const char* name )
{
	std::string name_copy = "NLPVoicePhoneme";
	if (name) name_copy = name;
	std::string read_name = file->ReadString();
	if (read_name != name_copy)	ThrowImpl(STRING_2_UTF8("反序列化名称错误, 当前是:") + read_name + STRING_2_UTF8("应当是:") + name_copy);

	m_bilstm->Deserialize(file, "bilstm");
	m_mlp->Deserialize(file, "mlp");
}

} // Robot
} // ALittle