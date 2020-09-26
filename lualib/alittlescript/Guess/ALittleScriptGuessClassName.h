
#ifndef _ALITTLE_ALITTLESCRIPTGUESSCLASSNAME_H_
#define _ALITTLE_ALITTLESCRIPTGUESSCLASSNAME_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptClassNameDecElement;

class ALittleScriptGuessClassName : public ALittleScriptGuess
{
public:
    // 命名域和类名
    std::string namespace_name;
    std::string class_name;

    std::weak_ptr<ALittleScriptClassNameDecElement> class_name_dec;

    ALittleScriptGuessClassName(const std::string& p_namespace_name, const std::string& p_class_name
        , std::shared_ptr<ALittleScriptClassNameDecElement> p_class_name_dec);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSCLASSNAME_H_
