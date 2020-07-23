
#include "ALittleScriptClassData.h"
#include "ALittleScriptUtility.h"

#include "../../alanguage/Model/ABnfElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptTemplatePairDecElement.h"
#include "../Generate/ALittleScriptTemplateNameDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptClassVarDecElement.h"
#include "../Generate/ALittleScriptClassVarNameDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptLineCommentElement.h"
#include "../Generate/ALittleScriptBlockCommentElement.h"

// 添加新元素
void ALittleScriptClassData::AddClassChildDec(std::shared_ptr<ABnfElement> dec, std::shared_ptr<ABnfElement> pre_dec, std::shared_ptr<ABnfElement> next_dec)
{
    // 模板定义特殊处理
    auto template_dec = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(dec);
    if (template_dec)
    {
        const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
        for (auto& pair_dec : pair_dec_list)
            AddClassChildDec(pair_dec, nullptr, nullptr);
        return;
    }

    ClassAccessType access_type = ClassAccessType::PRIVATE;
    ClassAttrType attr_type;
    std::string name;
    
    // 处理模板参数
    if (std::dynamic_pointer_cast<ALittleScriptTemplatePairDecElement>(dec))
    {
        auto pair_dec = std::dynamic_pointer_cast<ALittleScriptTemplatePairDecElement>(dec);
        name = pair_dec->GetTemplateNameDec()->GetElementText();
        access_type = ClassAccessType::PUBLIC;
        attr_type = ClassAttrType::TEMPLATE;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(dec))
    {
        auto element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(dec);
        access_type = ALittleScriptUtility::CalcAccessType(element_dec->GetModifierList());
        // 处理成员变量
        if (element_dec->GetClassVarDec() != nullptr)
        {
            auto var_dec = element_dec->GetClassVarDec();
            auto name_dec = var_dec->GetClassVarNameDec();
            if (name_dec == nullptr) return;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::VAR;
            dec = element_dec->GetClassVarDec();

            // 如果next_dec是行注释，并且同行，那么就是注释
            if (std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(next_dec) && next_dec->GetStartLine() == name_dec->GetEndLine())
                dec->SetDescriptor(next_dec->GetElementText());
        }
        // 处理成员函数
        else if (element_dec->GetClassMethodDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassMethodDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::FUN;

            // 如果pre_dec是注释，那么就去描述
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        // 处理getter函数
        else if (element_dec->GetClassGetterDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassGetterDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::GETTER;

            // 如果pre_dec是注释，那么就去描述
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        // 处理setter函数
        else if (element_dec->GetClassSetterDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassSetterDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::SETTER;

            // 如果pre_dec是注释，那么就去描述
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        // 处理静态函数
        else if (element_dec->GetClassStaticDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassStaticDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::STATIC;

            // 如果pre_dec是注释，那么就去描述
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }

    m_element_map[access_type][attr_type][name] = dec;
}

// 查找元素
void ALittleScriptClassData::FindClassAttrList(int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result) const
{
    if (access_level >= ALittleScriptUtility::sAccessOnlyPublic)
    {
        const auto* map = GetElementMap(attr_type, ClassAccessType::PUBLIC);
        if (map != nullptr)
        {
            if (name.empty())
            {
                for (auto& pair : *map)
                    result.push_back(pair.second);
            }   
            else
            {
                auto it = map->find(name);
                if (it != map->end())
                    result.push_back(it->second);
            }
        }
    }

    if (access_level >= ALittleScriptUtility::sAccessProtectedAndPublic)
    {
        const auto* map = GetElementMap(attr_type, ClassAccessType::PROTECTED);
        if (map != nullptr)
        {
            if (name.empty())
            {
                for (auto& pair : *map)
                    result.push_back(pair.second);
            }   
            else
            {
                auto it = map->find(name);
                if (it != map->end())
                    result.push_back(it->second);
            }
        }
    }

    if (access_level >= ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic)
    {
        const auto* map = GetElementMap(attr_type, ClassAccessType::PRIVATE);
        if (map != nullptr)
        {
            if (name.empty())
            {
                for (auto& pair : *map)
                    result.push_back(pair.second);
            }
            else
            {
                auto it = map->find(name);
                if (it != map->end())
                    result.push_back(it->second);
            }
        }
    }
}

const std::unordered_map<std::string, std::shared_ptr<ABnfElement>>* ALittleScriptClassData::GetElementMap(ClassAttrType attr_type, ClassAccessType access_type) const
{
    auto it = m_element_map.find(access_type);
    if (it == m_element_map.end()) return nullptr;
    auto sub_it = it->second.find(attr_type);
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}
