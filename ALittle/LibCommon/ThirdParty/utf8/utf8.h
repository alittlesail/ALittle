
#ifndef _ALITTLE_UTF8_H_
#define _ALITTLE_UTF8_H_

int utf8_GetByteCountOfOneWord(unsigned char first_char);
int utf8_CalcWordCount(const char* str);
int utf8_CalcByteCountByWordCount(const char* str, int offset, int word_count);

const char* utf8_UTF82ANSI(const char* content);
const char* utf8_ANSI2UTF8(const char* content);

#endif // _ALITTLE_UTF8_H_