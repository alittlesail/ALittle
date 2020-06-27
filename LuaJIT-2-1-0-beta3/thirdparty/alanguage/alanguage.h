
#ifndef _ALITTLE_ALANGUAGE_H_
#define _ALITTLE_ALANGUAGE_H_

void* create_abnf();
const char* abnf_load(void* abnf, const char* buffer, void* factory);
void delete_abnf(void* abnf);

#endif // _ALITTLE_ALANGUAGE_H_
