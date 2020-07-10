
#ifndef _ALITTLE_ALITTLESCRIPT_H_
#define _ALITTLE_ALITTLESCRIPT_H_

void* create_alittlescript_project(const char* abnf_buffer);
void delete_alittlescript_project(void* project);
void alittlescriptproject_settargetlanguage(void* project, const char* target_language);
void alittlescriptproject_generate(void* project, int query_id, const char* full_path);

void* create_alittlescript_file(void* project, const char* module_path, const char* full_path, const char* text, size_t len);
void delete_alittlescript_file(void* file);

#endif // _ALITTLE_ALITTLESCRIPT_H_
