#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptCustomTypeTemplateElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptTemplatePairDecElement.h"
#include "../Generate/ALittleScriptTemplateNameDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptCustomTypeDotIdElement.h"
#include "../Generate/ALittleScriptUsingNameDecElement.h"
#include "../Generate/ALittleScriptUsingDecElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptOp.h"

#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessEnum.h"

ALittleScriptCustomTypeCommonReference::ALittleScriptCustomTypeCommonReference(const std::shared_ptr<ALittleScriptCustomTypeElement>& custom_type, const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ABnfElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
    m_key = element->GetElementText();
    m_custom_type = custom_type;
}

std::shared_ptr<ALittleScriptClassDecElement> ALittleScriptCustomTypeCommonReference::GetClassDec()
{
    auto class_dec = m_class_dec.lock();
    if (class_dec != nullptr) return class_dec;
    class_dec = ALittleScriptUtility::FindClassDecFromParent(m_element.lock());
    m_class_dec = class_dec;
    return class_dec;
}

// ��ȡ����ģ��
inline std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptCustomTypeCommonReference::GetMethodTemplateDec()
{
    auto template_param_dec = m_template_param_dec.lock();
    if (template_param_dec != nullptr) return template_param_dec;
    template_param_dec = ALittleScriptUtility::FindMethodTemplateDecFromParent(m_element.lock());
    m_template_param_dec = template_param_dec;
    return template_param_dec;
}

ABnfGuessError ALittleScriptCustomTypeCommonReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto custom_type = m_custom_type.lock();
    if (custom_type == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    guess_list.resize(0);
    if (m_key.size() == 0) return ABnfGuessError(element, u8"�Ҳ���ָ������, namespace:" + m_namespace_name + ", key:" + m_key);

    auto* index = GetIndex();
    auto custom_type_template = custom_type->GetCustomTypeTemplate();
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error) return error;
            guess_list.push_back(guess);
        }

        if (dec_list.size() > 0 && custom_type_template != nullptr && custom_type_template->GetAllTypeList().size() > 0)
            return ABnfGuessError(element, u8"ʹ��using������಻����ʹ��ģ�����, namespace:" + m_namespace_name + ", key:" + m_key);
    }
    {
        // �������ֻ�ȡ��Ӧ����
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);

        // ��ȡģ��������󣬲���������
        std::vector<ABnfGuessPtr> src_guess_list;
        std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> template_list;
        if (custom_type_template != nullptr)
        {
            template_list = custom_type_template->GetAllTypeList();
            for (auto& all_type : template_list)
            {
                ABnfGuessPtr all_type_guess;
                auto error = all_type->GuessType(all_type_guess);
                if (error) return error;
                src_guess_list.push_back(all_type_guess);
            }
        }
        else
        {
            template_list.resize(0);
        }

        // �������е���
        for (auto& dec : dec_list)
        {
            // ��ȡdec������
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error) return error;
            auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
            if (guess_class == nullptr)
                return ABnfGuessError(element, u8"ģ������������ඨ��Ĳ�һ��, namespace:" + m_namespace_name + ", key:" + m_key);
            // ��ģ���б�Ĳ����������������һ��
            if (template_list.size() != guess_class->template_list.size())
                return ABnfGuessError(element, u8"ģ������������ඨ��Ĳ�һ��, namespace:" + m_namespace_name + ", key:" + m_key);

            // �Ա�����
            for (size_t i = 0; i < template_list.size(); ++i)
            {
                error = ALittleScriptOp::GuessTypeEqual(guess_class->template_list[i].lock(), template_list[i], src_guess_list[i], false, false);
                if (error) return error;
            }

            if (!guess_class->template_list.empty())
            {
                auto src_class_dec = guess_class->class_dec.lock();
                auto src_class_name_dec = src_class_dec->GetClassNameDec();
                if (src_class_name_dec == nullptr)
                    return ABnfGuessError(custom_type, u8"��ģ��û�ж�������");

                auto info = std::make_shared<ALittleScriptGuessClass>(
	                ALittleScriptUtility::GetNamespaceName(src_class_dec),
	                src_class_name_dec->GetElementText(),
	                guess_class->class_dec.lock(), guess_class->using_name, guess_class->is_const,
	                guess_class->is_native);

                info->template_list = guess_class->template_list;
                for (size_t i = 0; i < guess_class->template_list.size(); ++i)
                {
                    auto template_guess = guess_class->template_list[i].lock();
                    if (template_guess == nullptr) continue;
                    info->template_map[template_guess->GetValueWithoutConst()] = src_guess_list[i];
                }
                info->UpdateValue();
                element->GetFile()->AddGuessType(info);
                guess = info;
            }

            guess_list.push_back(guess);
        }
    }
    {
        auto class_dec = GetClassDec();
        if (class_dec != nullptr)
        {
            std::vector<ABnfElementPtr> dec_list;
            index->FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::TEMPLATE, m_key, dec_list);
            // �����پ�̬������ʹ��ģ�嶨��
            if (dec_list.size() > 0 && ALittleScriptUtility::IsInClassStaticMethod(element))
                return ABnfGuessError(element, u8"�ྲ̬��������ʹ��ģ�����");
            for (auto& dec : dec_list)
            {
                ABnfGuessPtr guess;
                auto error = dec->GuessType(guess);
                if (error) return error;
                guess_list.push_back(guess);
            }
        }
    }
    {
        auto template_dec = GetMethodTemplateDec();
        if (template_dec != nullptr)
        {
            const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
            for (const auto& dec : pair_dec_list)
            {
                auto name_dec = dec->GetTemplateNameDec();
                if (name_dec == nullptr) continue;

                if (name_dec->GetElementText() == m_key)
                {
                    ABnfGuessPtr guess;
                    auto error = dec->GuessType(guess);
                    if (error) return error;
                    guess_list.push_back(guess);
                }
            }
        }
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error) return error;
            guess_list.push_back(guess);
        }
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error) return error;
            guess_list.push_back(guess);
        }
    }
    if (std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element))
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_list;
        index->FindNamespaceNameDecList(m_key, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec.second->GuessType(guess);
            if (error) return error;
            guess_list.push_back(guess);
        }
    }

    if (guess_list.size() == 0) return ABnfGuessError(element, u8"�Ҳ���ָ������, namespace:" + m_namespace_name + ", key:" + m_key);

    return nullptr;
}

ABnfElementPtr ALittleScriptCustomTypeCommonReference::GotoDefinition()
{
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    auto* index = GetIndex();
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list) return dec;
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list) return dec;
    }
    {
        const auto class_dec = GetClassDec();
        if (class_dec != nullptr)
        {
            std::vector<ABnfElementPtr> dec_list;
            index->FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, ClassAttrType::TEMPLATE, m_key, dec_list);
            for (auto& dec : dec_list) return dec;
        }
    }
    {
        auto template_dec = GetMethodTemplateDec();
        if (template_dec != nullptr)
        {
            const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
            for (const auto& pair_dec : pair_dec_list)
            {
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec != nullptr && pair_name_dec->GetElementText() == m_key)
                    return pair_name_dec;
            }
        }
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list) return dec;
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list) return dec;
    }

    return nullptr;
}

bool ALittleScriptCustomTypeCommonReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index = GetIndex();
    if (index == nullptr) return false;

    bool is_dot_it = std::dynamic_pointer_cast<ALittleScriptCustomTypeDotIdElement>(select) != nullptr;

    // ���Ҹ��������µ�
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (is_dot_it)
            {
                if (error)
                    list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
                else
                {
                    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                        list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
                    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
                        list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
                    else
                        list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::PROPERTY, dec->GetDescriptor());
                }
            }
            else
            {
                if (error)
                    list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
                else
                {
                    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                        list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
                    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
                        list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
                    else
                        list.emplace_back(dec->GetElementText(), ALittleScriptIconType::PROPERTY, dec->GetDescriptor());
                }
            }
        }
    }

    // ���Ҷ�Ӧ�������µ�����
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            if (is_dot_it)
                list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
            else
                list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
        }   
    }
    // ������ģ��
    {
        auto class_dec = GetClassDec();
        if (class_dec != nullptr)
        {
            std::vector<ABnfElementPtr> dec_list;
            index->FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic
                , ClassAttrType::TEMPLATE, u8"", dec_list);
            for (auto& dec : dec_list)
            {
                auto pair_dec = std::dynamic_pointer_cast<ALittleScriptTemplatePairDecElement>(dec);
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec == nullptr) continue;

                if (is_dot_it)
                    list.emplace_back(pair_name_dec->GetElementText(), "." + pair_name_dec->GetElementText(), ALittleScriptIconType::TEMPLATE, dec->GetDescriptor());
                else
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptIconType::TEMPLATE, dec->GetDescriptor());
            }
        }
    }
    // ���Һ���ģ��
    {
        auto template_dec = GetMethodTemplateDec();
        if (template_dec != nullptr)
        {
            const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
            for (const auto& pair_dec : pair_dec_list)
            {
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec == nullptr) continue;

                if (is_dot_it)
                    list.emplace_back(pair_name_dec->GetElementText(), "." + pair_name_dec->GetElementText(), ALittleScriptIconType::TEMPLATE, pair_name_dec->GetDescriptor());
                else
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptIconType::TEMPLATE, pair_name_dec->GetDescriptor());
            }
        }
    }
    // �ṹ����
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            if (is_dot_it)
                list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
            else
                list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
        }   
    }
    // ö����
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::ENUM, dec->GetDescriptor());
    }
    // ����ȫ�ֺ���
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            if (is_dot_it)
                list.emplace_back(dec->GetElementText(), "." + dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, dec->GetDescriptor());
            else
                list.emplace_back(dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, dec->GetDescriptor());
        }
            
    }
    // ��������������
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_map;
        index->FindNamespaceNameDecList("", dec_map);
        for (auto& pair : dec_map)
        {
            if (is_dot_it)
                list.emplace_back(pair.second->GetElementText(), "." + pair.second->GetElementText(), ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
            else
                list.emplace_back(pair.second->GetElementText(), ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
        }
            
    }

    return true;
}

ABnfGuessError ALittleScriptCustomTypeCommonReference::CalcNamespaceName(std::string& namespace_name)
{
    namespace_name = "";
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto custom_type = m_custom_type.lock();
    if (custom_type == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    if (m_key.size() == 0) return ABnfGuessError(element, u8"�Ҳ���ָ������, namespace:" + m_namespace_name + ", key:" + m_key);

    auto* index = GetIndex();
    auto custom_type_template = custom_type->GetCustomTypeTemplate();
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
        {
            if (std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(dec))
            {
                auto using_dec = std::dynamic_pointer_cast<ALittleScriptUsingDecElement>(dec->GetParent());
                if (using_dec == nullptr)
                    return ABnfGuessError(element, u8"ALittleScriptUsingNameDecElement�ĸ��ڵ㲻��ALittleScriptUsingDecElement");
                auto element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(using_dec->GetParent());
                if (element_dec == nullptr)
                    return ABnfGuessError(element, u8"ALittleScriptUsingDecElement�ĸ��ڵ㲻��ALittleScriptNamespaceElementDecElement");
                auto access_type = ALittleScriptUtility::CalcAccessType(element_dec->GetModifierList());
                if (access_type != ClassAccessType::PRIVATE)
                    namespace_name = ALittleScriptUtility::GetNamespaceName(dec);
                return nullptr;
            }
        }
    }
    {
        // �������ֻ�ȡ��Ӧ����
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);

        // �������е���
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr class_guess;
            auto error = dec->GuessType(class_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess))
                return ABnfGuessError(element, u8"ALittleClassNameDec->GuessType()�Ľ������ALittleScriptGuessClass");

            auto class_guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess);
            namespace_name = class_guess_class->namespace_name;
            return nullptr;
        }
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr struct_guess;
            auto error = dec->GuessType(struct_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess))
                return ABnfGuessError(element, u8"ALittleStructNameDec->GuessType()�Ľ������ALittleScriptGuessStruct");
            auto struct_guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess);
            namespace_name = struct_guess_struct->namespace_name;
            return nullptr;
        }
    }
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr enum_guess;
            auto error = dec->GuessType(enum_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess))
                return ABnfGuessError(element, u8"ALittleEnumNameDec->GuessType()�Ľ������ALittleScriptGuessEnum");
            auto enum_guess_enum = std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess);
            namespace_name = enum_guess_enum->namespace_name;
            return nullptr;
        }
    }

    return nullptr;
}