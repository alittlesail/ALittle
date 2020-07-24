
#ifndef _ALITTLE_ALANGUAGE_H_
#define _ALITTLE_ALANGUAGE_H_

#include "lua.h"

int alanguage_project_pollone(void* project, lua_State* L);

void* create_abnfproject(const char* abnf_buffer);
void delete_abnfproject(void* project);
int abnfproject_queryrulecolor(void* project, lua_State* L);

void* create_abnffile(void* project, const char* full_path, const char* text, size_t len);
void delete_abnffile(void* file);

void alanguage_project_updatefile(void* project, const char* module_path, const char* full_path, int version);
void alanguage_project_tempfile(void* project, const char* module_path, const char* full_path, const char* text, size_t len, int version);
void alanguage_project_removefile(void* project, const char* full_path);
void alanguage_project_clear(void* project);

void abnffile_settext(void* abnf_file, int version, const char* text, size_t len);
void abnffile_inserttext(void* abnf_file, int version, const char* text, size_t len, int it_line, int it_char);
void abnffile_deletetext(void* abnf_file, int version, int it_line_start, int it_char_start, int it_line_end, int it_char_end);
void abnffile_querycolor(void* abnf_file, int query_id, int version, int line);
void abnffile_queryinfo(void* abnf_file, int query_id, int version, int it_line, int it_char);
void abnffile_querygoto(void* abnf_file, int query_id, int version, int it_line, int it_char);
void abnffile_querycomplete(void* abnf_file, int query_id, int version, int it_line, int it_char);
void abnffile_queryparamlist(void* abnf_file, int query_id, int version, int it_line, int it_char);
int abnffile_queryparamindex(void* abnf_file, int version, int it_line, int it_char);
void abnffile_queryerror(void* abnf_file, int query_id, int version, int force);

int abnffile_querydesiredindent(void* abnf_file, int version, int it_line, int it_char);
int abnffile_queryformateindent(void* abnf_file, int version, int it_line, int it_char);
int abnffile_queryautopair(void* abnf_file, int version, int it_line, int it_char, const char* left_pair, const char* right_pair);

#endif // _ALITTLE_ALANGUAGE_H_
