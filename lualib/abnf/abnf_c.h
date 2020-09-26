
#ifndef _ALITTLE_ABNF_C_H_
#define _ALITTLE_ABNF_C_H_

void* create_abnf_project(const char* abnf_buffer);
void delete_abnf_project(void* project);

void* create_abnf_file(void* project, const char* full_path, const char* text, size_t len);
void delete_abnf_file(void* file);

void abnffile_generate(void* file, int query_id, int version, const char* target_path, const char* language_name);

#endif // _ALITTLE_ABNF_C_H_
