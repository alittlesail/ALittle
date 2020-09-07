
#ifndef _ALITTLE_ABNFPROJECT_H_
#define _ALITTLE_ABNFPROJECT_H_

#include <string>
#include <vector>
#include <thread>
#include <list>
#include <functional>
#include <mutex>
#include <unordered_map>

#include <lua.hpp>
#include "../Model/ABnf.h"
#include "ABnfFactory.h"

class ABnfProject
{
	// 提供UI部分
private:
	ABnf m_abnf_ui;

	// 提供支线程部分
protected:
	ABnf m_abnf;
	ABnfFactory m_default_factory;
	std::unordered_map<std::string, ABnfFile*> m_file_map;

	// 支线程逻辑
protected:
	volatile bool m_run = false;
	std::condition_variable m_cv;       // 条件变量
	std::thread* m_thread = nullptr;
	std::mutex m_input_lock;
	std::list<std::function<void()>> m_inputs;
	std::mutex m_output_lock;
	std::list<std::function<int(lua_State*)>> m_outputs;

	static int Run(ABnfProject* self);

	virtual void ClearImpl() {}

public:
	ABnfProject();
	virtual ~ABnfProject();

public:
	void Start(const std::string& abnf_buffer);
	void Stop();
	inline bool IsStoped() const { return m_run == false; }
	int PollOne(lua_State* L);
	void Add(std::function<void()> fun);

public:
	virtual ABnfFactory& RefFactory() { return m_default_factory; };
	virtual ABnf& RefABnf() { return m_abnf; }
	virtual ABnf& RefABnfUI() { return m_abnf_ui; }

	int QueryRuleColor(lua_State* L);

	virtual void FindDefineImpl(const std::string& pre_input, const std::string& input, std::vector<ALanguageCompletionInfo>& info_list) {}
	virtual void FindGotoImpl(const std::string& text, ALanguageGotoInfo& info) { }

public:
	ABnfFile* GetFile(const std::string& full_path);
	void UpdateFile(const std::string& module_path, const std::string& full_path, int version);
	void TempFile(const std::string& module_path, const std::string& full_path, const std::string& text, int version);
	void RemoveFile(const std::string& full_path);
	void FindFile(int query_id, const std::string& text);
	void FindDefine(int query_id, const std::string& pre_input, const std::string& input);
	void FindGoto(int query_id, const std::string& text);
	void UpdateText(const std::string& full_path, int version, const std::string& text);
	void InsertText(const std::string& full_path, int version, const std::string& text, int it_line, int it_char);
	void DeleteText(const std::string& full_path, int version, int it_line_start, int it_char_start, int it_line_end, int it_char_end);

public:
	void QueryColor(const std::string& full_path, int query_id, int version, int line);
	void QueryInfo(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryGoto(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryComplete(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryParamList(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryError(const std::string& full_path, int query_id, int version, bool force);
};

#endif // _ALITTLE_ABNFPROJECT_H_