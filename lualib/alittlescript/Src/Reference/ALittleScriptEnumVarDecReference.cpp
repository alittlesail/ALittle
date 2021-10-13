#include "ALittleScriptEnumVarDecReference.h"

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"

#include "../Generate/ALittleScriptNumberElement.h"

ABnfGuessError ALittleScriptEnumVarDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    if (element->GetText() != nullptr)
    {
        const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("string");
        if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else
    {
        const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("int");
        if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
        
    return nullptr;
}

ABnfGuessError ALittleScriptEnumVarDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetNumber() == nullptr) return nullptr;

    if (!ALittleScriptUtility::IsInt(element->GetNumber()))
        return ABnfGuessError(element->GetNumber(), u8"ö��ֵ����������");
    return nullptr;
}
