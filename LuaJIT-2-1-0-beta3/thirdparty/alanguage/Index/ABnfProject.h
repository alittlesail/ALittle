
#ifndef _ALITTLE_ABNFPROJECT_H_
#define _ALITTLE_ABNFPROJECT_H_

#include <string>
#include <vector>
#include <thread>
#include <list>
#include <functional>
#include <mutex>
#include <unordered_map>

#include "lua.hpp"
#include "../Model/ABnf.h"
class ABnfFactory;

class ABnfProject
{
	// 提供UI部分
private:
	ABnf m_abnf_ui;

	// 提供支线程部分
private:
	std::string m_project_path;
	ABnf m_abnf;
	std::unordered_map<std::string, ABnfFile*> m_file_map;

	// 支线程逻辑
private:
	volatile bool m_run = false;
	std::condition_variable m_cv;       // 条件变量
	std::thread* m_thread = nullptr;
	std::mutex m_input_lock;
	std::list<std::function<void()>> m_inputs;
	std::mutex m_output_lock;
	std::list<std::function<int(lua_State*)>> m_outputs;

	static int Run(ABnfProject* self);

public:
	ABnfProject(const std::string& full_path);
	virtual ~ABnfProject();

public:
	void Start(const std::string& abnf_buffer);
	void Stop();
	int PollOne(lua_State* L);
	void Add(std::function<void()> fun);

public:
	const std::string& GetProjectPath() const { return m_project_path; }
	virtual ABnfFactory& RefFactory() = 0;
	virtual ABnf& RefABnf() { return m_abnf; }
	virtual ABnf& RefABnfUI() { return m_abnf_ui; }

public:
	void UpdateFile(const std::string& full_path);
	void RemoveFile(const std::string& full_path);
	void UpdateText(const std::string& full_path, const std::string& text);
	void InsertText(const std::string& full_path, const std::string& text, int it_line, int it_char);
	void DeleteText(const std::string& full_path, int it_line_start, int it_char_start, int it_line_end, int it_char_end);

public:
	void QueryColor(const std::string& full_path, int query_id, int version, int line);
	void QueryInfo(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryGoto(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryComplete(const std::string& full_path, int query_id, int version, int it_line, int it_char);
	void QueryError(const std::string& full_path, int query_id, int version);
};

#endif // _ALITTLE_ABNFPROJECT_H_