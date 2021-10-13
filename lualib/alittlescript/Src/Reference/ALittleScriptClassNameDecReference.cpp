#include "ALittleScriptClassNameDecReference.h"

#include "../Generate/ALittleScriptClassExtendsDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptTemplatePairDecElement.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptOp.h"
#include "../Guess/ALittleScriptGuessClass.h"

ALittleScriptClassNameDecReference::ALittleScriptClassNameDecReference(const ABnfElementPtr& p_element) : ALittleScriptReferenceTemplate<ALittleScriptClassNameDecElement>(p_element)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);

    // ������ڵ���extends����ô�ͻ�ȡָ����������
    const auto parent = element->GetParent();
    auto extends = std::dynamic_pointer_cast<ALittleScriptClassExtendsDecElement>(parent);
    if (extends != nullptr)
    {
        auto namespace_name_dec = extends->GetNamespaceNameDec();
        if (namespace_name_dec != nullptr)
            m_namespace_name = namespace_name_dec->GetElementText();
    }

    m_key = element->GetElementText();
}

int ALittleScriptClassNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::DEFINE_NAME;
}

ABnfGuessError ALittleScriptClassNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);
    auto parent = element->GetParent();

    // ���ֱ�Ӿ��Ƕ��壬��ôֱ�ӻ�ȡ
    if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent))
    {
        ABnfGuessPtr guess;
        auto error = parent->GuessType(guess);
        if (error) return error;
        guess_list.push_back(guess);
    }
    // ����Ǽ̳���ô�ʹӼ̳��Ǳ߻�ȡ
    else if (std::dynamic_pointer_cast<ALittleScriptClassExtendsDecElement>(parent))
    {
        if (m_key.size() == 0)
            return ABnfGuessError(element, u8"�Ҳ�����, namespace:" + m_namespace_name + ", key:" + m_key);

        // ���Ҽ̳�
        auto* index = GetIndex();
        std::vector<ABnfElementPtr> class_name_dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true, class_name_dec_list);
        if (class_name_dec_list.size() == 0)
            return ABnfGuessError(element, u8"�Ҳ�����, namespace:" + m_namespace_name + ", key:" + m_key);

        for (auto& class_name_dec : class_name_dec_list)
        {
            ABnfGuessPtr guess;
            auto error = class_name_dec->GuessType(guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                return ABnfGuessError(element, u8"�̳еĲ���һ����, namespace:" + m_namespace_name + ", key:" + m_key);

            auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
            if (!guess_class->template_list.empty())
            {
                auto sub_class = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent->GetParent());
                if (sub_class == nullptr)
                    return ABnfGuessError(parent, u8"���岻����");

                auto sub_template_dec = sub_class->GetTemplateDec();
                if (sub_template_dec == nullptr)
                    return ABnfGuessError(parent, u8"�����ģ������б���뺭�Ǹ����ģ������б�");

                const auto& sub_template_pair_list = sub_template_dec->GetTemplatePairDecList();
                if (sub_template_pair_list.size() < guess_class->template_list.size())
                    return ABnfGuessError(parent, u8"�����ģ������б���뺭�Ǹ����ģ������б�");

                for (size_t i = 0; i < guess_class->template_list.size(); ++i)
                {
                    ABnfGuessPtr sub_template;
                    error = sub_template_pair_list[i]->GuessType(sub_template);
                    if (error) return error;
                    error = ALittleScriptOp::GuessTypeEqual(guess_class->template_list[i].lock(), sub_template_pair_list[i], sub_template, false, false);
                    if (error)
                        return ABnfGuessError(sub_template_pair_list[i], u8"�����ģ������͸����ģ�������һ��:" + error.error);
                }
            }
            guess_list.push_back(guess);
        }
    }
    else
    {
        return ABnfGuessError(element, u8"ALittleClassNameDec����δ֪�ĸ��ڵ�");
    }

    return nullptr;
}

ABnfGuessError ALittleScriptClassNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"����������3���»��߿�ͷ");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"δ֪����");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"�ظ�����");
    return nullptr;
}

ABnfElementPtr ALittleScriptClassNameDecReference::GotoDefinition()
{
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    auto* index = GetIndex();
    auto dec = index->FindALittleNameDec(
        ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true);
    if (dec != nullptr) return dec;
    return nullptr;
}

// �������ܲ�ȫ
bool ALittleScriptClassNameDecReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* index = GetIndex();
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);

        for (auto& dec : dec_list)
        {
            if (m_key == dec->GetElementText()) continue;
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
        }
    }

    if (std::dynamic_pointer_cast<ALittleScriptClassExtendsDecElement>(element->GetParent()))
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_list;
        index->FindNamespaceNameDecList("", dec_list);
        for (auto& pair : dec_list)
        {
            if (m_key == pair.first) continue;
            list.emplace_back(pair.first, ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
        }
    }
    return true;
}
