
#include "ALittleScriptAccessData.h"

#include "../../alanguage/Model/ABnfElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptUsingNameDecElement.h"

// 添加新元素
void ALittleScriptAccessData::AddNameDec(std::shared_ptr<ABnfElement> dec)
{
    // 获取名称
    const std::string& name = dec->GetElementText();

    // 计算类型
    ABnfElementType type;
    if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(dec))
        type = ABnfElementType::CLASS_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(dec))
        type = ABnfElementType::ENUM_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(dec))
        type = ABnfElementType::STRUCT_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(dec))
        type = ABnfElementType::INSTANCE_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(dec))
        type = ABnfElementType::GLOBAL_METHOD;
    else if (std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(dec))
        type = ABnfElementType::USING_NAME;
    else
        return;

    // 添加到映射表
    m_element_map[type][name].insert(dec);
}

// 查找元素
void ALittleScriptAccessData::FindNameDecList(ABnfElementType type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result)
{
    auto it = m_element_map.find(type);
    if (it == m_element_map.end()) return;

    if (name.empty())
    {
        for (auto& pair : it->second)
        {
            for (auto& e : pair.second)
                result.push_back(e);
        }
        return;
    }

    auto sub_it = it->second.find(name);
    if (sub_it == it->second.end()) return;

    for (auto& e : sub_it->second)
        result.push_back(e);
}

// 移除元素
void ALittleScriptAccessData::RemoveNameDec(std::shared_ptr<ABnfElement> dec)
{
    // 获取名称
    const auto& name = dec->GetElementText();

    // 计算类型
    ABnfElementType type;
    if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(dec))
        type = ABnfElementType::CLASS_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(dec))
        type = ABnfElementType::ENUM_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(dec))
        type = ABnfElementType::STRUCT_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(dec))
        type = ABnfElementType::INSTANCE_NAME;
    else if (std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(dec))
        type = ABnfElementType::GLOBAL_METHOD;
    else if (std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(dec))
        type = ABnfElementType::USING_NAME;
    else
        return;

    auto it = m_element_map.find(type);
    if (it == m_element_map.end()) return;
    auto sub_it = it->second.find(name);
    if (sub_it == it->second.end()) return;

    sub_it->second.erase(dec);
    if (sub_it->second.empty()) it->second.erase(sub_it);
}
