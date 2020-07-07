#include "ALittleScriptCustomTypeReference.h"

#include "../Index/ALittleScriptUtility.h"

#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptCustomTypeNameElement.h"
#include "../Generate/ALittleScriptCustomTypeDotIdElement.h"

ALittleScriptCustomTypeReference::ALittleScriptCustomTypeReference(ABnfElementPtr p_element) : ALittleScriptCustomTypeCommonReference(std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(p_element), p_element)
{
    auto element = std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(p_element);
    if (element == nullptr) return;

    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
    auto name_dec = element->GetCustomTypeName();
    if (name_dec != nullptr) m_key = name_dec->GetElementText();

    auto dot_id = element->GetCustomTypeDotId();
    if (dot_id != nullptr)
    {
        auto dot_id_name = dot_id->GetCustomTypeDotIdName();
        if (dot_id_name != nullptr)
        {
            m_namespace_name = m_key;
            m_key = dot_id_name->GetElementText();
        }
    }
}

ABnfGuessError ALittleScriptCustomTypeReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");
    return nullptr;
}
