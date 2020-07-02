
#ifndef _ALITTLE_ABNF_C_H_
#define _ALITTLE_ABNF_C_H_

void* create_abnf_project(const char* full_path, const char* abnf_buffer);
void delete_abnf_project(void* project);

void* create_abnf_file(void* project, const char* full_path, const char* text, size_t len);
void delete_abnf_file(void* file);

#endif // _ALITTLE_ABNF_C_H_
