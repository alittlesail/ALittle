
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "alanguage.h"
}

#include "Model/ABnf.h"
#include "Index/ABnfProject.h"
#include "Index/ABnfFile.h"

void* create_abnf()
{
	return new ABnf();
}

const char* abnf_load(void* abnf, const char* buffer, void* factory)
{
	static std::string error;
	error.clear();
	if (((ABnf*)abnf)->Load(buffer, (ABnfFactory*)factory, error)) return nullptr;
	return error.c_str();
}

void delete_abnf(void* abnf)
{
	delete ((ABnf*)abnf);
}

void abnffile_settext(void* abnf_file, const char* text, size_t len)
{
	((ABnfFile*)abnf_file)->SetText(text, len);
}

void abnffile_inserttext(void* abnf_file, const char* text, size_t len, int it_line, int it_char)
{
	((ABnfFile*)abnf_file)->InsertText(text, len, it_line, it_char);
}

void abnffile_deletetext(void* abnf_file, int it_line_start, int it_char_start, int it_line_end, int it_char_end)
{
	((ABnfFile*)abnf_file)->DeleteText(it_line_start, it_char_start, it_line_end, it_char_end);
}

const struct ABnfQueryColor** abnffile_querycolor(void* abnf_file, int version, int line, int* count)
{
	static std::vector<const struct ABnfQueryColor*> temp;
	temp.resize(0);

	auto* list = ((ABnfFile*)abnf_file)->QueryColor(version, line);
	if (list != nullptr)
	{
		for (auto& color : *list)
			temp.push_back(&color);
	}

	*count = static_cast<int>(temp.size());
	return temp.data();
}

int abnffile_queryinfo(void* abnf_file, int version, int it_line, int it_char, struct ABnfQueryInfo* info)
{
	static std::string temp;
	temp.resize(0);
	bool result = ((ABnfFile*)abnf_file)->QueryInfo(version, it_line, it_char, temp, info->line_start, info->char_start, info->line_end, info->char_end);
	if (!result) return 0;
	info->info = temp.c_str();
	return 1;
}

int abnffile_querygoto(void* abnf_file, int version, int it_line, int it_char, struct ABnfQueryGoto* info)
{
	static std::string temp;
	temp.resize(0);
	bool result = ((ABnfFile*)abnf_file)->QueryGoto(version, it_line, it_char, temp, info->line_start, info->char_start, info->line_end, info->char_end);
	if (!result) return 0;
	info->file_path = temp.c_str();
	return 1;
}

const struct ABnfQueryComplete* abnffile_querycomplete(void* abnf_file, int version, int it_line, int it_char
	, int* count, int* line_start, int* char_start, int* line_end, int* char_end)
{
	static std::vector<ALanguageCompletionInfo> completion_temp;
	completion_temp.resize(0);
	bool result = ((ABnfFile*)abnf_file)->QueryComplete(version, it_line, it_char, completion_temp, *line_start, *char_start, *line_end, *char_end);
	if (!result) return nullptr;

	static std::vector<struct ABnfQueryComplete> query_temp;
	query_temp.resize(0);
	for (auto& temp : completion_temp)
	{
		struct ABnfQueryComplete info;
		info.insert = temp.insert.empty() ? 0 : temp.insert.c_str();
		info.display = temp.display.c_str();
		info.descriptor = temp.descriptor.empty() ? 0 : temp.descriptor.c_str();
		info.tag = temp.tag;
		query_temp.push_back(info);
	}
	*count = static_cast<int>(query_temp.size());
	return query_temp.data();
}

const struct ABnfQueryError* abnffile_queryerror(void* abnf_file, int version, int* count)
{
	static std::vector<ALanguageErrorInfo> error_temp;
	error_temp.resize(0);
	bool result = ((ABnfFile*)abnf_file)->QueryError(version, error_temp);
	if (!result) return nullptr;

	static std::vector<struct ABnfQueryError> query_temp;
	query_temp.resize(0);
	for (auto& temp : error_temp)
	{
		struct ABnfQueryError info;
		info.line_start = temp.line_start;
		info.char_start = temp.char_start;
		info.line_end = temp.line_end;
		info.char_end = temp.char_end;
		info.error = temp.error.c_str();
		query_temp.push_back(info);
	}
	*count = static_cast<int>(query_temp.size());
	return query_temp.data();
}
