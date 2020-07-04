
#include "ALittleScriptEnumData.h"

#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptEnumVarNameDecElement.h"

// 添加新元素
void ALittleScriptEnumData::AddVarDec(std::shared_ptr<ALittleScriptEnumVarDecElement> dec)
{
    auto name_dec = dec->GetEnumVarNameDec();
    if (name_dec == nullptr) return;
    const auto& name = name_dec->GetElementText();
    m_element_map[name] = dec;
}

// 查找元素
void ALittleScriptEnumData::FindVarDecList(const std::string& name, std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& result) const
{
    if (name.empty())
    {
        for (auto& pair : m_element_map)
            result.push_back(pair.second);
    }
    else
    {
        auto it = m_element_map.find(name);
        if (it != m_element_map.end())
            result.push_back(it->second);
    }
}
