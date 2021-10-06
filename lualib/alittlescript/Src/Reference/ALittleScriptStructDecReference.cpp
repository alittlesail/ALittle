#include "ALittleScriptStructDecReference.h"

#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptStructBodyDecElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"
#include "../Generate/ALittleScriptStructVarNameDecElement.h"
#include "../Generate/ALittleScriptStructOptionDecElement.h"
#include "../Generate/ALittleScriptStructOptionNameDecElement.h"

#include "../Generate/ALittleScriptTextElement.h"
#include "../Guess/ALittleScriptGuessStruct.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptFactoryClass.h"

#include <set>

ALittleScriptStructDecReference::ALittleScriptStructDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptStructDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

ABnfGuessError ALittleScriptStructDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);
    auto struct_name_dec = element->GetStructNameDec();
    if (struct_name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���ṹ����");

    auto info = std::static_pointer_cast<ABnfGuess>(
	    std::make_shared<ALittleScriptGuessStruct>(m_namespace_name, struct_name_dec->GetElementText(), element,
	                                               false));
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

ABnfGuessError ALittleScriptStructDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto struct_name_dec = element->GetStructNameDec();
    if (struct_name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���ṹ����");

    auto body_dec = element->GetStructBodyDec();
    if (body_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���ṹ������");

    const auto& var_dec_list = body_dec->GetStructVarDecList();
    std::set<std::string> name_set;
    for (auto& var_dec : var_dec_list)
    {
        auto var_name_dec = var_dec->GetStructVarNameDec();
        if (var_name_dec == nullptr) return ABnfGuessError(var_dec, u8"û�ж����Ա������");

        const auto& text = var_name_dec->GetElementText();
        if (name_set.find(text) != name_set.end())
            return ABnfGuessError(var_name_dec, u8"�ṹ���ֶ����ظ�");
        name_set.insert(text);
    }

    const auto& option_dec_list = body_dec->GetStructOptionDecList();
    std::set<std::string> option_set;
    for (auto& option_dec : option_dec_list)
    {
        auto option_name_dec = option_dec->GetStructOptionNameDec();
        if (option_name_dec == nullptr) return ABnfGuessError(option_dec, u8"û�ж��帽����Ϣ��");

        const auto& text = option_name_dec->GetElementText();
        if (option_set.find(text) != option_set.end())
            return ABnfGuessError(option_name_dec, u8"������Ϣ���ظ�");
        option_set.insert(text);

        auto option_value = option_dec->GetText();
        if (option_value == nullptr) return ABnfGuessError(option_dec, text + u8"û�����ö�Ӧ��ֵ");

        if (text == "primary")
        {
            auto element_string = option_value->GetElementString();
            ALittleScriptUtility::TrimLeft(element_string);
            ALittleScriptUtility::TrimRight(element_string);
            if (name_set.find(element_string) == name_set.end())
                return ABnfGuessError(option_value, u8"û���ҵ���Ӧ���ֶ���:" + element_string);
            continue;
        }

        if (text == "unique" || text == "index")
        {
            std::vector<std::string> list;
            ABnfFactory::Split(option_value->GetElementString(), ",", list);
            for (auto& name : list)
            {
                ALittleScriptUtility::TrimLeft(name);
                ALittleScriptUtility::TrimRight(name);
                if (name_set.find(name) == name_set.end())
                    return ABnfGuessError(option_value, u8"û���ҵ���Ӧ���ֶ���:" + name);
            }
            continue;
        }
    }

    return nullptr;
}
