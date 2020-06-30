
#ifndef _ALITTLE_ALANGUAGEHELPERINFO_H_
#define _ALITTLE_ALANGUAGEHELPERINFO_H_

#include <string>
#include <vector>

const int s_indent_size = 4;

struct ALanguageCompletionInfo
{
    std::string display;
    std::string descriptor;
    int tag;
};

struct ALanguageParameterInfo
{
    std::string documentation;
    std::string name;
};

struct ALanguageSignatureInfo
{
    std::vector<ALanguageParameterInfo> param_list;
};

struct ALanguageHighlightWordInfo
{
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
};

#endif // _ALITTLE_ALANGUAGEHELPERINFO_H_
