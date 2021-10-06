
#ifndef _ALITTLE_ALITTLESCRIPTGUESSENUMNAME_H_
#define _ALITTLE_ALITTLESCRIPTGUESSENUMNAME_H_

#include "ALittleScriptGuess.h"

class ALittleScriptEnumNameDecElement;

class ALittleScriptGuessEnumName : public ALittleScriptGuess
{
public:
    // �������ö����
    std::string namespace_name;
    std::string enum_name;

    // Ԫ�ض���
    std::weak_ptr<ALittleScriptEnumNameDecElement> enum_name_dec;

public:
    ALittleScriptGuessEnumName(const std::string& p_namespace_name, const std::string& p_enum_name
        , const std::shared_ptr<ALittleScriptEnumNameDecElement>& p_enum_name_dec);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSENUMNAME_H_
