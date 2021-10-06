
#ifndef _ALITTLE_ABNFPROJECTEXPORT_H_
#define _ALITTLE_ABNFPROJECTEXPORT_H_

#include <string>
#include <vector>
#include <thread>
#include <list>
#include <functional>
#include <mutex>
#include <unordered_map>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "../Model/ABnf.h"
#include "../Index/ABnfProject.h"

class ABnfProjectExport : public ABnfProject
{
	// 支线程逻辑
protected:
	volatile bool m_run = false;
	std::condition_variable m_cv;       // 条件变量
	std::thread* m_thread = nullptr;
	std::mutex m_input_lock;
	std::list<std::function<void()>> m_inputs;
	std::mutex m_output_lock;
	std::list<std::function<int(lua_State*)>> m_outputs;

	static int Run(ABnfProjectExport* self);

	virtual void ClearImpl() {}

public:
	virtual ~ABnfProjectExport() { Stop(); }

public:
	void Start(const std::string& abnf_buffer);
	void Stop();
	inline bool IsStopped() const { return m_run == false; }
	int PollOne(lua_State* L);
	void Add(const std::function<void()>& fun);

public:
	int QueryRuleColor(lua_State* L) const;

public:
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

#endif