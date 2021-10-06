
#ifndef _ALITTLE_ALITTLESCRIPTGUESSNAMESPACE_H_
#define _ALITTLE_ALITTLESCRIPTGUESSNAMESPACE_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptNamespaceDecElement;

class ALittleScriptGuessNamespace : public ALittleScriptGuess
{
public:
    // �������ö����
    std::string namespace_name;

    // Ԫ�ض���
    std::weak_ptr<ALittleScriptNamespaceDecElement> namespace_dec;

public:
    ALittleScriptGuessNamespace(const std::string& p_namespace_name, const std::shared_ptr<ALittleScriptNamespaceDecElement>& p_namespace_dec);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSNAMESPACE_H_
