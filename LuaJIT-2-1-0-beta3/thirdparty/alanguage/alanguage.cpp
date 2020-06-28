
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "alanguage.h"
}

#include "Model/ABnf.h"
#include "Index/ABnfProject.h"
#include "Index/ABnfFile.h"

void* create_abnf()
{
	return new ABnf();
}

const char* abnf_load(void* abnf, const char* buffer, void* factory)
{
	static std::string error;
	error.clear();
	if (((ABnf*)abnf)->Load(buffer, (ABnfFactory*)factory, error))
		return nullptr;
	return error.c_str();
}

void delete_abnf(void* abnf)
{
	delete ((ABnf*)abnf);
}

void abnffile_settext(void* abnf_file, const char* text, size_t len)
{
	((ABnfFile*)abnf_file)->SetText(text, len);
}

void abnffile_inserttext(void* abnf_file, const char* text, size_t len, int it_line, int it_char)
{
	((ABnfFile*)abnf_file)->InsertText(text, len, it_line, it_char);
}

void abnffile_deletetext(void* abnf_file, int it_line_start, int it_char_start, int it_line_end, int it_char_end)
{
	((ABnfFile*)abnf_file)->DeleteText(it_line_start, it_char_start, it_line_end, it_char_end);
}

const struct ABnfQueryColor** abnffile_querycolor(void* abnf_file, int version, int line, int* count)
{
	static std::vector<const struct ABnfQueryColor*> temp;
	temp.resize(0);

	auto* list = ((ABnfFile*)abnf_file)->QueryColor(version, line);
	if (list != nullptr)
	{
		for (auto& color : *list)
			temp.push_back(&color);
	}

	*count = static_cast<int>(temp.size());
	return temp.data();
}
