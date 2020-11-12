
#ifndef _ALITTLE_ALANGUAGEHELPERINFO_H_
#define _ALITTLE_ALANGUAGEHELPERINFO_H_

#include <string>

const int s_indent_size = 4;

struct ALanguageColorInfo
{
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
    int tag = 0;
    bool blur = false;
};

struct ALanguageQuickInfo
{
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
    std::string info;
};

struct ALanguageGotoInfo
{
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
    std::string file_path;
};

struct ALanguageCompletionInfo
{
    ALanguageCompletionInfo() = default;
    ALanguageCompletionInfo(const std::string& p_display, int p_tag, const std::string& p_descriptor) : display(p_display), descriptor(p_descriptor), tag(p_tag) {}
    ALanguageCompletionInfo(const std::string& p_display, const std::string& p_insert, int p_tag, const std::string& p_descriptor) : display(p_display), insert(p_insert), descriptor(p_descriptor), tag(p_tag) {}
    std::string display;
    std::string insert;
    std::string descriptor;
    int tag = 0;
};

struct ALanguageErrorInfo
{
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
    std::string error;
};

struct ALanguageParameterInfo
{
    std::string descriptor;
    std::string name;
};

struct ALanguageHighlightWordInfo
{
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
};

#endif // _ALITTLE_ALANGUAGEHELPERINFO_H_
