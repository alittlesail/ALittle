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
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto dot_id_name = element->GetPropertyValueDotIdName();
    if (dot_id_name != nullptr)
        return dot_id_name->GuessTypes(guess_list);

    guess_list.resize(0);
    return nullptr;
}

bool ALittleScriptPropertyValueDotIdReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index_e = GetIndex();
    if (index_e == nullptr) return false;

    // 获取父节点
    auto property_value_dot_id = element;
    auto property_value_suffix = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(property_value_dot_id->GetParent());
    auto property_value = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(property_value_suffix->GetParent());
    auto property_value_first_type = property_value->GetPropertyValueFirstType();
    auto suffix_list = property_value->GetPropertyValueSuffixList();

    // 获取所在位置
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

    // 获取前一个类型
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

    // 处理类的实例对象
    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_type))
    {
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_type)->class_dec.lock();

        // 计算当前元素对这个类的访问权限
        int access_level = ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(element, class_dec);

        std::vector<ABnfElementPtr> class_var_dec_list;
        // 所有成员变量
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::VAR, u8"", class_var_dec_list, 100);
        for (auto& dec : class_var_dec_list)
        {
            auto class_var_dec = std::dynamic_pointer_cast<ALittleScriptClassVarDecElement>(dec);
            if (class_var_dec == nullptr) continue;
            auto class_var_name_dec = class_var_dec->GetClassVarNameDec();
            if (class_var_name_dec == nullptr) continue;
            list.emplace_back(class_var_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptVariableName);
        }

        // 所有setter,getter
        std::vector<ABnfElementPtr> class_method_name_dec_list;
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::SETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::GETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptFieldMethodName);

        // 所有成员函数
        class_method_name_dec_list.resize(0);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::FUN, u8"", class_method_name_dec_list, 10);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptMemberMethodName);

    }
    // 处理结构体的实例对象
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type))
    {
        auto struct_dec = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type)->struct_dec.lock();
        std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> struct_var_dec_list;
        // 所有成员变量
        ALittleScriptUtility::FindStructVarDecList(struct_dec, u8"", struct_var_dec_list, 100);
        for (auto& struct_var_dec : struct_var_dec_list)
        {
            auto name_dec = struct_var_dec->GetStructVarNameDec();
            if (name_dec == nullptr) continue;
            list.emplace_back(name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptProperty);
        }
    }
    // 比如 ALittleName.XXX
    else if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(pre_type))
    {
        auto namespace_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(pre_type)->namespace_name_dec.lock();
        const auto& namespace_name = namespace_name_dec->GetElementText();
        // 所有枚举名
        std::vector<ABnfElementPtr> enum_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), namespace_name, u8"", true, enum_name_dec_list);
        for (auto& enum_name_dec : enum_name_dec_list)
            list.emplace_back(enum_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptEnumName);
        // 所有全局函数
        std::vector<ABnfElementPtr> method_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), namespace_name, u8"", true, method_name_dec_list);
        for (auto& method_name_dec : method_name_dec_list)
            list.emplace_back(method_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptGlobalMethodName);
        // 所有类名
        std::vector<ABnfElementPtr> class_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), namespace_name, u8"", true, class_name_dec_list);
        for (auto& class_name_dec : class_name_dec_list)
            list.emplace_back(class_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
        // 所有结构体名
        std::vector<ABnfElementPtr> struct_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), namespace_name, u8"", true, struct_name_dec_list);
        for (auto& struct_name_dec : struct_name_dec_list)
            list.emplace_back(struct_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptStructName);
        // 所有单例
        std::vector<ABnfElementPtr> instance_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::INSTANCE_NAME, element->GetFile(), namespace_name, u8"", false, instance_name_dec_list);
        for (auto& instance_name_dec : instance_name_dec_list)
            list.emplace_back(instance_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptInstanceName);
    }
    // 比如 AClassName.XXX
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_type))
    {
        auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_type)->class_name_dec.lock();
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_name_dec->GetParent());

        // 计算当前元素对这个类的访问权限
        int access_level = ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(element, class_dec);

        // 所有静态函数
        std::vector<ABnfElementPtr> class_method_name_dec_list;
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::STATIC, u8"", class_method_name_dec_list, 100);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptStaticMethodName);
        // 所有成员函数
        class_method_name_dec_list.resize(0);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::FUN, u8"", class_method_name_dec_list, 100);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptMemberMethodName);
        // 所有setter,getter
        class_method_name_dec_list.resize(0);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::SETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::GETTER, u8"", class_method_name_dec_list, 100);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            list.emplace_back(class_method_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptFieldMethodName);
    }
    // 比如 AEnum.XXX
    else if (std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(pre_type))
    {
        // 所有枚举字段
        auto enum_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(pre_type)->enum_name_dec.lock();
        auto enum_dec = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(enum_name_dec->GetParent());
        std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> var_dec_list;
        ALittleScriptUtility::FindEnumVarDecList(enum_dec, u8"", var_dec_list);
        for (auto& var_dec : var_dec_list)
        {
            auto var_name_dec = var_dec->GetEnumVarNameDec();
            if (var_name_dec == nullptr) continue;
            list.emplace_back(var_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptEnumName);
        }
    }

    return true;
}
