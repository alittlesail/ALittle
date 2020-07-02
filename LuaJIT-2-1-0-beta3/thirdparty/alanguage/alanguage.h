
#ifndef _ALITTLE_ALANGUAGE_H_
#define _ALITTLE_ALANGUAGE_H_

#include "lua.h"

int alanguage_project_pollone(void* project, lua_State* L);
void alanguage_project_updatefile(void* project, const char* full_path);
void alanguage_project_removefile(void* project, const char* full_path);

void abnffile_settext(void* abnf_file, const char* text, size_t len);
void abnffile_inserttext(void* abnf_file, const char* text, size_t len, int it_line, int it_char);
void abnffile_deletetext(void* abnf_file, int it_line_start, int it_char_start, int it_line_end, int it_char_end);
void abnffile_querycolor(void* abnf_file, int query_id, int version, int line);
void abnffile_queryinfo(void* abnf_file, int query_id, int version, int it_line, int it_char);
void abnffile_querygoto(void* abnf_file, int query_id, int version, int it_line, int it_char);
void abnffile_querycomplete(void* abnf_file, int query_id, int version, int it_line, int it_char);
void abnffile_queryerror(void* abnf_file, int query_id, int version);

int abnffile_querydesiredindent(void* abnf_file, int version, int it_line, int it_char);
int abnffile_queryformateindent(void* abnf_file, int version, int it_line, int it_char);

#endif // _ALITTLE_ALANGUAGE_H_
