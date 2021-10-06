
#ifndef _ALITTLE_ABNFPROJECT_H_
#define _ALITTLE_ABNFPROJECT_H_

#include <string>
#include <vector>
#include <thread>
#include <list>
#include <functional>
#include <mutex>
#include <unordered_map>

#include "alanguage/Src/Model/ABnf.h"
#include "ABnfFactory.h"

class ABnfProject
{
	// 提供UI部分
protected:
	ABnf m_abnf_ui;

	// 提供支线程部分
protected:
	ABnf m_abnf;
	ABnfFactory m_default_factory;
	std::unordered_map<std::string, ABnfFile*> m_file_map;

public:
	virtual ~ABnfProject() { }

public:
	virtual std::string LoadABnf(const std::string& abnf_buffer);
	virtual ABnfFactory& RefFactory() { return m_default_factory; };
	virtual ABnf& RefABnf() { return m_abnf; }
	virtual ABnf& RefABnfUI() { return m_abnf_ui; }

public:
	virtual bool IsStopped() const { return false; }
	virtual void FindDefineImpl(const std::string& pre_input, const std::string& input, std::vector<ALanguageCompletionInfo>& info_list) {}
	virtual void FindGotoImpl(const std::string& text, ALanguageGotoInfo& info) { }

public:
	virtual ABnfFile* GetFile(const std::string& full_path);
	virtual void UpdateFile(const std::string& module_path, const std::string& full_path, int version);
	virtual void TempFile(const std::string& module_path, const std::string& full_path, const std::string& text, int version);
	virtual void RemoveFile(const std::string& full_path);

public:
	virtual void FindFile(int query_id, const std::string& text) { }
	virtual void FindDefine(int query_id, const std::string& pre_input, const std::string& input) { }
	virtual void FindGoto(int query_id, const std::string& text) { }
	virtual void UpdateText(const std::string& full_path, int version, const std::string& text) { }
	virtual void InsertText(const std::string& full_path, int version, const std::string& text, int it_line, int it_char) { }
	virtual void DeleteText(const std::string& full_path, int version, int it_line_start, int it_char_start, int it_line_end, int it_char_end) { }

public:
	virtual void QueryColor(const std::string& full_path, int query_id, int version, int line) { }
	virtual void QueryInfo(const std::string& full_path, int query_id, int version, int it_line, int it_char) { }
	virtual void QueryGoto(const std::string& full_path, int query_id, int version, int it_line, int it_char) { }
	virtual void QueryComplete(const std::string& full_path, int query_id, int version, int it_line, int it_char) { }
	virtual void QueryParamList(const std::string& full_path, int query_id, int version, int it_line, int it_char) { }
	virtual void QueryError(const std::string& full_path, int query_id, int version, bool force) { }
};

#endif