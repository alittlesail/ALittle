
#ifndef _ALITTLE_ABNF_C_H_
#define _ALITTLE_ABNF_C_H_

void* create_abnf_factory();
void delete_abnf_factory(void* abnf);

void* create_abnf_file(const char* full_path, void* abnf, const char* text, size_t len);
void delete_abnf_file(void* abnf);

#endif // _ALITTLE_ABNF_C_H_
