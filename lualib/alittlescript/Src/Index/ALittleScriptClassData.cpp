
#include "ALittleScriptClassData.h"
#include "ALittleScriptUtility.h"

#include "alanguage/Src/Model/ABnfElement.h"
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

// �����Ԫ��
void ALittleScriptClassData::AddClassChildDec(std::shared_ptr<ABnfElement> dec, const std::shared_ptr<ABnfElement>& pre_dec, const std::shared_ptr<ABnfElement>& next_dec)
{
    // ģ�嶨�����⴦��
    auto template_dec = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(dec);
    if (template_dec)
    {
        const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
        for (const auto& pair_dec : pair_dec_list)
            AddClassChildDec(pair_dec, nullptr, nullptr);
        return;
    }

    ClassAccessType access_type = ClassAccessType::PRIVATE;
    ClassAttrType attr_type;
    std::string name;
    
    // ����ģ�����
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
        // �����Ա����
        if (element_dec->GetClassVarDec() != nullptr)
        {
            auto var_dec = element_dec->GetClassVarDec();
            auto name_dec = var_dec->GetClassVarNameDec();
            if (name_dec == nullptr) return;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::VAR;
            dec = element_dec->GetClassVarDec();

            // ���next_dec����ע�ͣ�����ͬ�У���ô����ע��
            if (std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(next_dec) && next_dec->GetStartLine() == name_dec->GetEndLine())
                dec->SetDescriptor(next_dec->GetElementText());
        }
        // �����Ա����
        else if (element_dec->GetClassMethodDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassMethodDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::FUN;

            // ���pre_dec��ע�ͣ���ô��ȥ����
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        // ����getter����
        else if (element_dec->GetClassGetterDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassGetterDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::GETTER;

            // ���pre_dec��ע�ͣ���ô��ȥ����
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        // ����setter����
        else if (element_dec->GetClassSetterDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassSetterDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::SETTER;

            // ���pre_dec��ע�ͣ���ô��ȥ����
            if (std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(pre_dec) || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(pre_dec))
                dec->SetDescriptor(pre_dec->GetElementText());
        }
        // ����̬����
        else if (element_dec->GetClassStaticDec() != nullptr)
        {
            auto method_dec = element_dec->GetClassStaticDec();
            auto name_dec = method_dec->GetMethodNameDec();
            if (name_dec == nullptr) return;
            dec = name_dec;
            name = name_dec->GetElementText();
            attr_type = ClassAttrType::STATIC;

            // ���pre_dec��ע�ͣ���ô��ȥ����
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

// ����Ԫ��
void ALittleScriptClassData::FindClassAttrList(int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result) const
{
    if (access_level >= ALittleScriptUtility::sAccessOnlyPublic)
    {
        const auto* map = GetElementMap(attr_type, ClassAccessType::PUBLIC);
        if (map != nullptr)
        {
            if (name.empty())
            {
                for (const auto& pair : *map)
                    result.push_back(pair.second);
            }   
            else
            {
                const auto it = map->find(name);
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
                for (const auto& pair : *map)
                    result.push_back(pair.second);
            }   
            else
            {
                const auto it = map->find(name);
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
                for (const auto& pair : *map)
                    result.push_back(pair.second);
            }
            else
            {
                const auto it = map->find(name);
                if (it != map->end())
                    result.push_back(it->second);
            }
        }
    }
}

const std::unordered_map<std::string, std::shared_ptr<ABnfElement>>* ALittleScriptClassData::GetElementMap(ClassAttrType attr_type, ClassAccessType access_type) const
{
    const auto it = m_element_map.find(access_type);
    if (it == m_element_map.end()) return nullptr;
    const auto sub_it = it->second.find(attr_type);
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}
