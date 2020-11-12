
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUETHISTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUETHISTYPEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueThisTypeElement.h"

class ALittleScriptClassDecElement;
class ALittleScriptClassCtorDecElement;
class ALittleScriptClassGetterDecElement;
class ALittleScriptClassSetterDecElement;
class ALittleScriptClassMethodDecElement;
class ALittleScriptClassStaticDecElement;
class ALittleScriptGlobalMethodDecElement;

class ALittleScriptPropertyValueThisTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueThisTypeElement>
{
private:
    std::weak_ptr<ALittleScriptClassDecElement> m_class_dec;
    std::weak_ptr<ALittleScriptClassCtorDecElement> m_class_ctor_dec;
    std::weak_ptr<ALittleScriptClassGetterDecElement> m_class_getter_dec;
    std::weak_ptr<ALittleScriptClassSetterDecElement> m_class_setter_dec;
    std::weak_ptr<ALittleScriptClassMethodDecElement> m_class_method_dec;
    std::weak_ptr<ALittleScriptClassStaticDecElement> m_class_static_dec;
    std::weak_ptr<ALittleScriptGlobalMethodDecElement> m_global_method_dec;
    bool m_is_const = false;

public:
    ALittleScriptPropertyValueThisTypeReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueThisTypeReference(element); }

private:
    void ReloadInfo();

    void CalcResolve(std::vector<ABnfElementPtr>& result_list) const;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUETHISTYPEREFERENCE_H_