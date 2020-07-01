
#ifndef _ALITTLE_ALITTLESCRIPT_H_
#define _ALITTLE_ALITTLESCRIPT_H_

void* create_alittlescript_factory();
void delete_alittlescript_factory(void* alittlescript);

void* create_alittlescript_file(void* project, const char* full_path, void* abnf, const char* text, size_t len);
void delete_alittlescript_file(void* alittlescript);

void* create_alittlescript_project(const char* full_path);
void delete_alittlescript_project(void* alittlescript);

#endif // _ALITTLE_ALITTLESCRIPT_H_
