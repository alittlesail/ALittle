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

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"

#include "../Guess/ALittleScriptGuessClass.h"

ALittleScriptCustomTypeCommonReference::ALittleScriptCustomTypeCommonReference(std::shared_ptr<ALittleScriptCustomTypeElement> custom_type, ABnfElementPtr element) : ALittleScriptReferenceTemplate<ABnfElement>(element)
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

// 获取函数模板
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
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto custom_type = m_custom_type.lock();
    if (custom_type == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    guess_list.resize(0);
    if (m_key.size() == 0) return ABnfGuessError(element, u8"找不到指定类型, namespace:" + m_namespace_name + ", key:" + m_key);

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
            return ABnfGuessError(element, u8"使用using定义的类不能再使用模板参数, namespace:" + m_namespace_name + ", key:" + m_key);
    }
    {
        // 根据名字获取对应的类
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);

        // 获取模板的填充对象，并计算类型
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

        // 遍历所有的类
        for (auto& dec : dec_list)
        {
            // 获取dec的类型
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error) return error;
            auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
            if (guess_class == nullptr)
                return ABnfGuessError(element, u8"模板参数数量和类定义的不一致, namespace:" + m_namespace_name + ", key:" + m_key);
            // 类模板列表的参数数量必须和填充的一致
            if (template_list.size() != guess_class->template_list.size())
                return ABnfGuessError(element, u8"模板参数数量和类定义的不一致, namespace:" + m_namespace_name + ", key:" + m_key);

            // 对比两种
            for (int i = 0; i < template_list.size(); ++i)
            {
                error = ALittleScriptOp::GuessTypeEqual(guess_class->template_list[i], template_list[i], src_guess_list[i], false, false);
                if (error) return error;
            }

            if (guess_class->template_list.size() > 0)
            {
                auto src_class_dec = guess_class->class_dec.lock();
                auto src_class_name_dec = src_class_dec->GetClassNameDec();
                if (src_class_name_dec == nullptr)
                    return ABnfGuessError(custom_type, u8"类模板没有定义类名");

                auto info = std::shared_ptr<ALittleScriptGuessClass>(new ALittleScriptGuessClass(ALittleScriptUtility::GetNamespaceName(src_class_dec),
                    src_class_name_dec->GetElementText(),
                    guess_class->class_dec.lock(), guess_class->using_name, guess_class->is_const, guess_class->is_native));

                info->template_list = guess_class->template_list;
                for (size_t i = 0; i < guess_class->template_list.size(); ++i)
                {
                    auto template_guess = guess_class->template_list[i].lock();
                    if (template_guess == nullptr) continue;
                    info->template_map[template_guess->GetValueWithoutConst()] = src_guess_list[i];
                }
                info->UpdateValue();
                ABnfGuessPtr cache = info;
                element->GetFile()->AddGuessType(cache);
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
            // 不能再静态函数中使用模板定义
            if (dec_list.size() > 0 && ALittleScriptUtility::IsInClassStaticMethod(element))
                return ABnfGuessError(element, u8"类静态函数不能使用模板符号");
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
            for (auto& dec : pair_dec_list)
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

    if (guess_list.size() == 0) return ABnfGuessError(element, u8"找不到指定类型, namespace:" + m_namespace_name + ", key:" + m_key);

    return nullptr;
}

ABnfElementPtr ALittleScriptCustomTypeCommonReference::GotoDefinition()
{
    auto element = m_element.lock();
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
        auto class_dec = GetClassDec();
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
            auto pair_dec_list = template_dec->GetTemplatePairDecList();
            for (auto& pair_dec : pair_dec_list)
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

bool ALittleScriptCustomTypeCommonReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* index = GetIndex();
    // 查找该命名域下的
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error)
            {
                list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
            }
            else
            {
                if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                    list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
                else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
                    list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptStructName);
                else
                    list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptProperty);
            }
        }
    }

    // 查找对应命名域下的类名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
    }
    // 查找类模板
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
                if (pair_name_dec != nullptr)
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptTemplateName);
            }
        }
    }
    // 查找函数模板
    {
        auto template_dec = GetMethodTemplateDec();
        if (template_dec != nullptr)
        {
            const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
            for (auto& pair_dec : pair_dec_list)
            {
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec != nullptr)
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptTemplateName);
            }
        }
    }
    // 结构体名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptStructName);
    }
    // 枚举名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptEnumName);
    }
    // 查找全局函数
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptGlobalMethodName);
    }
    // 查找所有命名域
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_map;
        index->FindNamespaceNameDecList("", dec_map);
        for (auto& pair : dec_map)
            list.emplace_back(pair.second->GetElementText(), ALittleScriptColorType::ALittleScriptNamespaceName);
    }

    return true;
}
