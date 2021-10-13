
#ifndef _ALITTLE_ALITTLESCRIPTGUESSENUM_H_
#define _ALITTLE_ALITTLESCRIPTGUESSENUM_H_

#include "ALittleScriptGuess.h"

class ALittleScriptEnumDecElement;

class ALittleScriptGuessEnum : public ALittleScriptGuess
{
public:
    // 命名域和枚举名
    std::string namespace_name;
    std::string enum_name;

    // 元素对象
    std::weak_ptr<ALittleScriptEnumDecElement> enum_dec;

public:
    ALittleScriptGuessEnum(const std::string& p_namespace_name, const std::string& p_enum_name
        , const std::shared_ptr<ALittleScriptEnumDecElement>& p_enum_dec);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSENUM_H_
