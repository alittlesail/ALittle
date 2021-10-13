#include "ALittleScriptPropertyValueDotIdReference.h"

#include "../Generate/ALittleScriptPropertyValueDotIdNameElement.h"
#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptPropertyValueFirstTypeElement.h"
#include "../Generate/ALittleScriptClassVarDecElement.h"
#include "../Generate/ALittleScriptClassVarNameDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"
#include "../Generate/ALittleScriptStructVarNameDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptEnumVarNameDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptEnumDecElement.h"

#include "../Guess/ALittleScriptGuessEnumName.h"
#include "../Guess/ALittleScriptGuessNamespaceName.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessClassName.h"
#include "../Guess/ALittleScriptGuessClass.h"

#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ABnfGuessError ALittleScriptPropertyValueDotIdReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto dot_id_name = element->GetPropertyValueDotIdName();
    if (dot_id_name != nullptr)
        return dot_id_name->GuessTypes(guess_list);

    guess_list.resize(0);
    return nullptr;
}

bool ALittleScriptPropertyValueDotIdReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index_e = GetIndex();
    if (index_e == nullptr) return false;

    bool is_dot_id = std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdElement>(select) != nullptr;

    // ��ȡ���ڵ�
    const auto& property_value_dot_id = element;
    auto property_value_suffix = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(property_value_dot_id->GetParent());
    auto property_value = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(property_value_suffix->GetParent());
    auto property_value_first_type = property_value->GetPropertyValueFirstType();
    const auto& suffix_list = property_value->GetPropertyValueSuffixList();

    // ��ȡ����λ��
    int index = -1;
    for (size_t i = 0; i < suffix_list.size(); ++i)
    {
        if (suffix_list[i] == property_value_suffix)
        {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1) return false;

    // ��ȡǰһ������
    ABnfGuessPtr pre_type;
    ABnfGuessError error;
    if (index == 0)
        error = property_value_first_type->GuessType(pre_type);
    else
        error = suffix_list[index - 1]->GuessType(pre_type);
    if (error) return false;

    bool is_const = false;
    if (pre_type != nullptr) is_const = pre_type->is_const;

    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pre_type))
    {
        pre_type = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pre_type)->template_extends.lock();
        if (pre_type != nullptr && is_const && !pre_type->is_const)
        {
            pre_type = pre_type->Clone();
            pre_type->is_const = true;
            pre_type->UpdateValue();
            element->GetFile()->AddGuessType(pre_type);
        }
    }

    if (pre_type == nullptr) return false;

    // �������ʵ������
    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_type))
    {
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_type)->class_dec.lock();

        // ���㵱ǰԪ�ض������ķ���Ȩ��
        int access_level = ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(element, class_dec);

        std::vector<ABnfElementPtr> class_var_dec_list;
        // ���г�Ա����
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::VAR, u8"", class_var_dec_list, 100);
        for (auto& dec : class_var_dec_list)
        {
            auto class_var_dec = std::dynamic_pointer_cast<ALittleScriptClassVarDecElement>(dec);
            if (class_var_dec == nullptr) continue;
            auto class_var_name_dec = class_var_dec->GetClassVarNameDec();
            if (class_var_name_dec == nullptr) continue;
            if (is_dot_id)
                list.emplace_back(class_var_name_dec->GetElementText(), "." + class_var_name_dec->GetElementText(), ALittleScriptIconType::VARIABLE, dec->GetDescriptor());
            else
                list.emplace_back(class_var_name_dec->GetElementText(), ALittleScriptIconType::VARIABLE, dec->GetDescriptor());
        }

        // ����setter,getter
        std::vector<ABnfElementPtr> class_method_name_dec_list;
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::SETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::GETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(class_method_name_dec->GetElementText(), "." + class_method_name_dec->GetElementText(), ALittleScriptIconType::FIELD_METHOD, class_method_name_dec->GetDescriptor());
            else
                list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptIconType::FIELD_METHOD, class_method_name_dec->GetDescriptor());
        }

        // ���г�Ա����
        class_method_name_dec_list.resize(0);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::FUN, u8"", class_method_name_dec_list, 10);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(class_method_name_dec->GetElementText(), "." + class_method_name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, class_method_name_dec->GetDescriptor());
            else
                list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, class_method_name_dec->GetDescriptor());
        }
    }
    // ����ṹ���ʵ������
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type))
    {
        auto struct_dec = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type)->struct_dec.lock();
        std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> struct_var_dec_list;
        // ���г�Ա����
        ALittleScriptUtility::FindStructVarDecList(struct_dec, u8"", struct_var_dec_list, 100);
        for (auto& struct_var_dec : struct_var_dec_list)
        {
            auto name_dec = struct_var_dec->GetStructVarNameDec();
            if (name_dec == nullptr) continue;

            if (is_dot_id)
                list.emplace_back(name_dec->GetElementText(), "." + name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, struct_var_dec->GetDescriptor());
            else
                list.emplace_back(name_dec->GetElementText(), ALittleScriptIconType::PROPERTY, struct_var_dec->GetDescriptor());
        }
    }
    // ���� ALittleName.XXX
    else if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(pre_type))
    {
        auto namespace_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(pre_type)->namespace_name_dec.lock();
        const auto& namespace_name = namespace_name_dec->GetElementText();
        // ����ö����
        std::vector<ABnfElementPtr> enum_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), namespace_name, u8"", true, enum_name_dec_list);
        for (auto& enum_name_dec : enum_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(enum_name_dec->GetElementText(), "." + enum_name_dec->GetElementText(), ALittleScriptIconType::ENUM, enum_name_dec->GetDescriptor());
            else
                list.emplace_back(enum_name_dec->GetElementText(), ALittleScriptIconType::ENUM, enum_name_dec->GetDescriptor());
        }
        // ����ȫ�ֺ���
        std::vector<ABnfElementPtr> method_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), namespace_name, u8"", true, method_name_dec_list);
        for (auto& method_name_dec : method_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(method_name_dec->GetElementText(), "." + method_name_dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, method_name_dec->GetDescriptor());
            else
                list.emplace_back(method_name_dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, method_name_dec->GetDescriptor());
        }   
        // ��������
        std::vector<ABnfElementPtr> class_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), namespace_name, u8"", true, class_name_dec_list);
        for (auto& class_name_dec : class_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(class_name_dec->GetElementText(), "." + class_name_dec->GetElementText(), ALittleScriptIconType::CLASS, class_name_dec->GetDescriptor());
            else
                list.emplace_back(class_name_dec->GetElementText(), ALittleScriptIconType::CLASS, class_name_dec->GetDescriptor());
        }   
        // ���нṹ����
        std::vector<ABnfElementPtr> struct_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), namespace_name, u8"", true, struct_name_dec_list);
        for (auto& struct_name_dec : struct_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(struct_name_dec->GetElementText(), "." + struct_name_dec->GetElementText(), ALittleScriptIconType::STRUCT, struct_name_dec->GetDescriptor());
            else
                list.emplace_back(struct_name_dec->GetElementText(), ALittleScriptIconType::STRUCT, struct_name_dec->GetDescriptor());
        }
        // ���е���
        std::vector<ABnfElementPtr> instance_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::INSTANCE_NAME, element->GetFile(), namespace_name, u8"", false, instance_name_dec_list);
        for (auto& instance_name_dec : instance_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(instance_name_dec->GetElementText(), "." + instance_name_dec->GetElementText(), ALittleScriptIconType::INSTANCE, instance_name_dec->GetDescriptor());
            else
                list.emplace_back(instance_name_dec->GetElementText(), ALittleScriptIconType::INSTANCE, instance_name_dec->GetDescriptor());
        }
    }
    // ���� AClassName.XXX
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_type))
    {
        auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_type)->class_name_dec.lock();
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_name_dec->GetParent());

        // ���㵱ǰԪ�ض������ķ���Ȩ��
        int access_level = ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(element, class_dec);

        // ���о�̬����
        std::vector<ABnfElementPtr> class_method_name_dec_list;
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::STATIC, u8"", class_method_name_dec_list, 100);
        for (auto& class_method_name_dec : class_method_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(class_method_name_dec->GetElementText(), "." + class_method_name_dec->GetElementText(), ALittleScriptIconType::STATIC_METHOD, class_method_name_dec->GetDescriptor());
            else
                list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptIconType::STATIC_METHOD, class_method_name_dec->GetDescriptor());
        }   
        // ���г�Ա����
        class_method_name_dec_list.resize(0);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::FUN, u8"", class_method_name_dec_list, 100);
        for (auto& class_method_name_dec : class_method_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(class_method_name_dec->GetElementText(), "." + class_method_name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, class_method_name_dec->GetDescriptor());
            else
                list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, class_method_name_dec->GetDescriptor());
        }   
        // ����setter,getter
        class_method_name_dec_list.resize(0);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::SETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::GETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
        {
            if (is_dot_id)
                list.emplace_back(class_method_name_dec->GetElementText(), "." + class_method_name_dec->GetElementText(), ALittleScriptIconType::FIELD_METHOD, class_method_name_dec->GetDescriptor());
            else
                list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptIconType::FIELD_METHOD, class_method_name_dec->GetDescriptor());
        }   
    }
    // ���� AEnum.XXX
    else if (std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(pre_type))
    {
        // ����ö���ֶ�
        auto enum_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(pre_type)->enum_name_dec.lock();
        auto enum_dec = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(enum_name_dec->GetParent());
        std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> var_dec_list;
        ALittleScriptUtility::FindEnumVarDecList(enum_dec, u8"", var_dec_list);
        for (auto& var_dec : var_dec_list)
        {
            auto var_name_dec = var_dec->GetEnumVarNameDec();
            if (var_name_dec == nullptr) continue;

            if (is_dot_id)
                list.emplace_back(var_name_dec->GetElementText(), "." + var_name_dec->GetElementText(), ALittleScriptIconType::ENUM, var_dec->GetDescriptor());
            else
                list.emplace_back(var_name_dec->GetElementText(), ALittleScriptIconType::ENUM, var_dec->GetDescriptor());
        }
    }

    return true;
}
