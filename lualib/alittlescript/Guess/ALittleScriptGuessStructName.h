
#ifndef _ALITTLE_ALITTLESCRIPTGUESSSTRUCTNAME_H_
#define _ALITTLE_ALITTLESCRIPTGUESSSTRUCTNAME_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptStructNameDecElement;

class ALittleScriptGuessStructName : public ALittleScriptGuess
{
public:
    // 命名域和枚举名
    std::string namespace_name;
    std::string struct_name;

    // 元素对象
    std::weak_ptr<ALittleScriptStructNameDecElement> struct_name_dec;

public:
    ALittleScriptGuessStructName(const std::string& p_namespace_name, const std::string& p_struct_name
        , std::shared_ptr<ALittleScriptStructNameDecElement> p_struct_name_dec);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSSTRUCTNAME_H_
