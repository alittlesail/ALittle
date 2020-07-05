
#ifndef _ALITTLE_ALITTLESCRIPTGUESSNAMESPACENAME_H_
#define _ALITTLE_ALITTLESCRIPTGUESSNAMESPACENAME_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptNamespaceNameDecElement;

class ALittleScriptGuessNamespaceName : public ALittleScriptGuess
{
public:
    // 命名域和枚举名
    std::string namespace_name;

    // 元素对象
    std::weak_ptr<ALittleScriptNamespaceNameDecElement> namespace_name_dec;

public:
    ALittleScriptGuessNamespaceName(const std::string& p_namespace_name, std::shared_ptr<ALittleScriptNamespaceNameDecElement> p_namespace_name_dec);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSNAMESPACENAME_H_
