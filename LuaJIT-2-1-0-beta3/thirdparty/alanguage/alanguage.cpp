
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "alanguage.h"
}

#include "Model/ABnf.h"
#include "Index/ABnfProject.h"
#include "Index/ABnfFile.h"

int alanguage_project_pollone(void* project, lua_State* L)
{
	auto* project_c = (ABnfProject*)project;
	return project_c->PollOne(L);
}

void* create_abnfproject(const char* abnf_buffer)
{
	auto* project = new ABnfProject();
	project->Start(abnf_buffer);
	return project;
}

void delete_abnfproject(void* file)
{
	delete ((ABnfProject*)file);
}

int abnfproject_queryrulecolor(void* project, lua_State* L)
{
	auto* project_c = (ABnfProject*)project;
	return project_c->QueryRuleColor(L);
}

void* create_abnffile(void* project, const char* full_path, const char* text, size_t len)
{
	return new ABnfFile((ABnfProject*)project, "", full_path, text, len, true);
}

void delete_abnffile(void* file)
{
	delete ((ABnfFile*)file);
}

void alanguage_project_updatefile(void* project, const char* module_path, const char* full_path, int version)
{
	auto* project_c = (ABnfProject*)project;
	project_c->Add(std::bind(&ABnfProject::UpdateFile, project_c, std::string(module_path), std::string(full_path), version));
}

void alanguage_project_tempfile(void* project, const char* module_path, const char* full_path, const char* text, size_t len, int version)
{
	auto* project_c = (ABnfProject*)project;
	project_c->Add(std::bind(&ABnfProject::TempFile, project_c, std::string(module_path), std::string(full_path), std::string(text, len), version));
}

void alanguage_project_removefile(void* project, const char* full_path)
{
	auto* project_c = (ABnfProject*)project;
	project_c->Add(std::bind(&ABnfProject::RemoveFile, project_c, std::string(full_path)));
}

void alanguage_project_clear(void* project)
{
	auto* project_c = (ABnfProject*)project;
	project_c->Stop();
}

void abnffile_settext(void* abnf_file, int version, const char* text, size_t len)
{
	((ABnfFile*)abnf_file)->SetText(text, len);

	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::UpdateText, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), version, std::string(text, len)));
}

void abnffile_inserttext(void* abnf_file, int version, const char* text, size_t len, int it_line, int it_char)
{
	((ABnfFile*)abnf_file)->InsertText(text, len, it_line, it_char);

	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::InsertText, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), version, std::string(text, len), it_line, it_char));
}

void abnffile_deletetext(void* abnf_file, int version, int it_line_start, int it_char_start, int it_line_end, int it_char_end)
{
	((ABnfFile*)abnf_file)->DeleteText(it_line_start, it_char_start, it_line_end, it_char_end);

	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::DeleteText, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), version, it_line_start, it_char_start, it_line_end, it_char_end));
}

void abnffile_querycolor(void* abnf_file, int query_id, int version, int line)
{
	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::QueryColor, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), query_id, version, line));
}

void abnffile_queryinfo(void* abnf_file, int query_id, int version, int it_line, int it_char)
{
	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::QueryInfo, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), query_id, version, it_line, it_char));
}

void abnffile_querygoto(void* abnf_file, int query_id, int version, int it_line, int it_char)
{
	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::QueryGoto, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), query_id, version, it_line, it_char));
}

void abnffile_querycomplete(void* abnf_file, int query_id, int version, int it_line, int it_char)
{
	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::QueryComplete, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), query_id, version, it_line, it_char));
}

void abnffile_queryparamlist(void* abnf_file, int query_id, int version, int it_line, int it_char)
{
	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::QueryParamList, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), query_id, version, it_line, it_char));
}

int abnffile_queryparamindex(void* abnf_file, int version, int it_line, int it_char)
{
	return ((ABnfFile*)abnf_file)->QueryParamIndex(version, it_line, it_char);
}

void abnffile_queryerror(void* abnf_file, int query_id, int version, int force)
{
	auto* project_c = ((ABnfFile*)abnf_file)->GetProject();
	project_c->Add(std::bind(&ABnfProject::QueryError, project_c, ((ABnfFile*)abnf_file)->GetFullPath(), query_id, version, force != 0));
}

int abnffile_querydesiredindent(void* abnf_file, int version, int it_line, int it_char)
{
	return ((ABnfFile*)abnf_file)->QueryDesiredIndent(version, it_line, it_char);
}

int abnffile_queryformateindent(void* abnf_file, int version, int it_line, int it_char)
{
	return ((ABnfFile*)abnf_file)->QueryFormateIndent(version, it_line, it_char);
}

int abnffile_queryautopair(void* abnf_file, int version, int it_line, int it_char, const char* left_pair, const char* right_pair)
{
	return ((ABnfFile*)abnf_file)->QueryAutoPair(version, it_line, it_char, left_pair, right_pair) ? 1 : 0;
}
