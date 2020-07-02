
#ifndef _ALITTLE_ALITTLESCRIPT_H_
#define _ALITTLE_ALITTLESCRIPT_H_

void* create_alittlescript_project(const char* full_path, const char* abnf_buffer);
void delete_alittlescript_project(void* project);

void* create_alittlescript_file(void* project, const char* full_path, const char* text, size_t len);
void delete_alittlescript_file(void* file);

#endif // _ALITTLE_ALITTLESCRIPT_H_
