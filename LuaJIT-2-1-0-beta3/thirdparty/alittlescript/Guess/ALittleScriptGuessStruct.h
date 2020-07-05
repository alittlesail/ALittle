
#ifndef _ALITTLE_ALITTLESCRIPTGUESSSTRUCT_H_
#define _ALITTLE_ALITTLESCRIPTGUESSSTRUCT_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptStructDecElement;

class ALittleScriptGuessStruct : public ALittleScriptGuess
{
public:
    // 命名域和枚举名
    std::string namespace_name;
    std::string struct_name;

    // 元素对象
    std::weak_ptr<ALittleScriptStructDecElement> struct_dec;

public:
    ALittleScriptGuessStruct(const std::string& p_namespace_name, const std::string& p_struct_name
        , std::shared_ptr<ALittleScriptStructDecElement> p_struct_dec, bool p_is_const);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSSTRUCT_H_
