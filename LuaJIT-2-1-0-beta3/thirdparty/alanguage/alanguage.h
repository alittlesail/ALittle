
#ifndef _ALITTLE_ALANGUAGE_H_
#define _ALITTLE_ALANGUAGE_H_

void* create_abnf();
const char* abnf_load(void* abnf, const char* buffer, void* factory);
void delete_abnf(void* abnf);

void abnffile_settext(void* abnf_file, const char* text, size_t len);
void abnffile_inserttext(void* abnf_file, const char* text, size_t len, int it_line, int it_char);
void abnffile_deletetext(void* abnf_file, int it_line_start, int it_char_start, int it_line_end, int it_char_end);

#endif // _ALITTLE_ALANGUAGE_H_
