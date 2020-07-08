#include "ALittleScriptTemplatePairDecReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptTemplateExtendsClassDecElement.h"
#include "../Generate/ALittleScriptTemplateExtendsStructDecElement.h"
#include "../Generate/ALittleScriptTemplateExtendsDecElement.h"
#include "../Generate/ALittleScriptTemplateNameDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"

#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessClassTemplate.h"
#include "../Guess/ALittleScriptGuessMethodTemplate.h"

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"

ABnfGuessError ALittleScriptTemplatePairDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);

    std::shared_ptr<ALittleScriptAllTypeElement> all_type;
    std::shared_ptr<ALittleScriptTemplateExtendsClassDecElement> extends_class_dec;
    std::shared_ptr<ALittleScriptTemplateExtendsStructDecElement> extends_struct_dec;

    auto extends = element->GetTemplateExtendsDec();
    if (extends != nullptr)
    {
        all_type = extends->GetAllType();
        extends_class_dec = extends->GetTemplateExtendsClassDec();
        extends_struct_dec = extends->GetTemplateExtendsStructDec();
    }

    ABnfGuessPtr template_extends;
    bool is_class = false;
    bool is_struct = false;
    if (all_type != nullptr)
    {
        ABnfGuessPtr guess;
        auto error = all_type->GuessType(guess);
        if (error) return error;
        if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess) && !std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess)) {
            return ABnfGuessError(all_type, u8"继承的对象必须是一个类或者结构体");
        }
        template_extends = guess;
    }
    else if (extends_class_dec != nullptr)
    {
        is_class = true;
    }
    else if (extends_struct_dec != nullptr)
    {
        is_struct = true;
    }

    if (element->GetParent() == nullptr) return ABnfGuessError(element, u8"没有父节点");
    auto parent = element->GetParent();
    if (parent->GetParent() == nullptr) return ABnfGuessError(parent, u8"没有父节点");
    parent = parent->GetParent();

    // 根据定义区分类模板还是函数模板
    if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent))
    {
        auto info = ABnfGuessPtr(new ALittleScriptGuessClassTemplate(element, template_extends, is_class, is_struct));
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    else
    {
        auto info = ABnfGuessPtr(new ALittleScriptGuessMethodTemplate(element, template_extends, is_class, is_struct));
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    return nullptr;
}

ABnfGuessError ALittleScriptTemplatePairDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto name_dec = element->GetTemplateNameDec();
    if (name_dec == nullptr) return nullptr;

    if (name_dec->GetElementText().find("___") == 0)
        return ABnfGuessError(name_dec, u8"模板名不能以3个下划线开头");
    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(name_dec, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(name_dec, u8"重复定义");

    return nullptr;
}
