
#ifndef _ALITTLE_ROBOT_NLPVOICEPHONEME_H_
#define _ALITTLE_ROBOT_NLPVOICEPHONEME_H_

#include "../../Graph/Expression.h"
#include "../Base/Dictionary.h"
#include "../Base/MLP.h"
#include "../Base/WordEmbeding.h"

namespace ALittle
{
namespace Robot
{

class ParameterCollection;
class ComputationGraph;
class ModelSerializer;
class ModelDeserializer;
class ParameterInit;

class NLPVoicePhonemeData
{
public:
	std::vector<real> data;
	std::vector<std::string> label;
};

class NLPVoicePhonemeDataManager
{
public:
	static NLPVoicePhonemeDataManager& Instance();

public:
	void Clear();
	bool SetData(const char* key, const char* json);
	NLPVoicePhonemeData* GetData(const char* key);


private:
	std::map<std::string, NLPVoicePhonemeData> m_map;

private:
	NLPVoicePhonemeDataManager() {}
	~NLPVoicePhonemeDataManager();
};

#define g_NLPVoicePhonemeDataManager NLPVoicePhonemeDataManager::Instance()

class NLPVoicePhoneme
{
public:
	NLPVoicePhoneme(ParameterCollection* model, int lstm_dim, int lstm_layer, const char* json_info);
	~NLPVoicePhoneme();

public:
	void Build(ComputationGraph* graph);
	const char* Output(const char* file_path);
	int Loss(const char* key);
	int GetCount() { return m_count; }
	int GetCorrect() { return m_correct; }
	const char* GetTmp() { return m_tmp.c_str(); }
	const char* GetLabel() { return m_label.c_str(); }

public:
	void AddInput(std::vector<Expression>& input_list, std::vector<Expression>& out);

public:
	void Serialize(ModelSerializer* file, const char* name);
	void Deserialize(ModelDeserializer* file, const char* name);

private:
	ComputationGraph* m_graph;

private:
	int m_input_dim;
	int m_hidden_dim;
	int m_hidden_layer;
	std::string m_data_path;
	std::string m_name;

private:
	Dictionary m_tag_dict;
	int m_tag_size;
	int m_tag_BLANK;

private:
	MLP* m_mlp;
	BiLSTM* m_bilstm;

private:
	std::string m_label;
	std::string m_tmp;
	int m_count;
	int m_correct;
};

} // Robot
} // ALittle

#endif // _ALITTLE_ROBOT_NLPVOICEPHONEME_H_
