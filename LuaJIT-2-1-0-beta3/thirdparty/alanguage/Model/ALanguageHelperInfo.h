
#ifndef _ALITTLE_ALANGUAGEHELPERINFO_H_
#define _ALITTLE_ALANGUAGEHELPERINFO_H_

#include <string>
#include <vector>

struct ALanguageCompletionInfo
{
    std::string insert;
    std::string display;
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
    int start = 0;
    int end = 0;
};

#endif // _ALITTLE_ALANGUAGEHELPERINFO_H_
