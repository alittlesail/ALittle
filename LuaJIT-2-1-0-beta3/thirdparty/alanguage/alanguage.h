
#ifndef _ALITTLE_ALANGUAGE_H_
#define _ALITTLE_ALANGUAGE_H_

void* create_abnf();
const char* abnf_load(void* abnf, const char* buffer, void* factory);
void delete_abnf(void* abnf);

void abnffile_settext(void* abnf_file, const char* text, size_t len);
void abnffile_inserttext(void* abnf_file, const char* text, size_t len, int it_line, int it_char);
void abnffile_deletetext(void* abnf_file, int it_line_start, int it_char_start, int it_line_end, int it_char_end);

struct ABnfQueryColor
{
	int line_start;
	int char_start;
	int line_end;
	int char_end;
	int tag;
	int blur;
};
const struct ABnfQueryColor** abnffile_querycolor(void* abnf_file, int version, int line, int* count);

struct ABnfQueryInfo
{
	int line_start;
	int char_start;
	int line_end;
	int char_end;
	const char* info;
};
int abnffile_queryinfo(void* abnf_file, int version, int it_line, int it_char, struct ABnfQueryInfo* info);

struct ABnfQueryGoto
{
	int line_start;
	int char_start;
	int line_end;
	int char_end;
	const char* file_path;
};
int abnffile_querygoto(void* abnf_file, int version, int it_line, int it_char, struct ABnfQueryGoto* info);

#endif // _ALITTLE_ALANGUAGE_H_
