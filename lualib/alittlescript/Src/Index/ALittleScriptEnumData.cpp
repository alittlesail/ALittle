
#include "ALittleScriptEnumData.h"

#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptEnumVarNameDecElement.h"
#include "../Generate/ALittleScriptLineCommentElement.h"

// �����Ԫ��
void ALittleScriptEnumData::AddVarDec(const std::shared_ptr<ABnfElement>& dec, const std::shared_ptr<ABnfElement>& next_dec)
{
    auto var_dec = std::dynamic_pointer_cast<ALittleScriptEnumVarDecElement>(dec);
    if (var_dec == nullptr) return;

    auto name_dec = var_dec->GetEnumVarNameDec();
    if (name_dec == nullptr) return;
    const auto& name = name_dec->GetElementText();

    auto comment = std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(next_dec);
    if (comment && comment->GetStartLine() == name_dec->GetStartLine()) var_dec->SetDescriptor(comment->GetElementText());

    m_element_map[name] = var_dec;
}

// ����Ԫ��
void ALittleScriptEnumData::FindVarDecList(const std::string& name, std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& result) const
{
    if (name.empty())
    {
        for (const auto& pair : m_element_map)
            result.push_back(pair.second);
    }
    else
    {
        const auto it = m_element_map.find(name);
        if (it != m_element_map.end())
            result.push_back(it->second);
    }
}
