#include "ALittleScriptMethodNameDecReference.h"

#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptMethodSetterParamDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptMethodParamTailDecElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Generate/ALittleScriptMethodReturnOneDecElement.h"
#include "../Generate/ALittleScriptMethodReturnTailDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"

#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessStruct.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptOp.h"

ALittleScriptMethodNameDecReference::ALittleScriptMethodNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptMethodNameDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
    m_key = element->GetElementText();
}

int ALittleScriptMethodNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::METHOD_NAME;
}

ABnfGuessError ALittleScriptMethodNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto* index = GetIndex();
    if (index == nullptr) return ABnfGuessError(nullptr, u8"�ļ����ٹ�����");

    guess_list.resize(0);
    auto parent = element->GetParent();
    // ����getter
    if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
    {
        auto class_getter_dec = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent);
        auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_getter_dec->GetParent());
        auto class_body_dec = class_element_dec->GetParent();
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_body_dec->GetParent());

        auto info = std::make_shared<ALittleScriptGuessFunctor>(class_getter_dec);
        info->const_modifier = ALittleScriptUtility::IsConst(class_element_dec->GetModifierList());

        // ��һ����������
        ABnfGuessPtr class_guess;
        auto error = class_dec->GuessType(class_guess);
        if (error) return error;
        info->param_list.push_back(class_guess);
        info->param_nullable_list.push_back(false);
        info->param_name_list.push_back(class_guess->GetValue());

        // ��ӷ���ֵ�б�
        auto all_type = class_getter_dec->GetAllType();
        if (all_type == nullptr) return ABnfGuessError(element, u8"ָ���getter����û�ж��巵��ֵ");
        ABnfGuessPtr all_type_guess;
        error = all_type->GuessType(all_type_guess);
        if (error) return error;
        info->return_list.push_back(all_type_guess);

        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
    {
        auto class_setter_dec = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent);
        auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_setter_dec->GetParent());
        auto class_body_dec = class_element_dec->GetParent();
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_body_dec->GetParent());

        auto info = std::make_shared<ALittleScriptGuessFunctor>(class_setter_dec);
        info->const_modifier = ALittleScriptUtility::IsConst(class_element_dec->GetModifierList());

        // ��һ����������
        ABnfGuessPtr class_guess;
        auto error = class_dec->GuessType(class_guess);
        if (error) return error;
        info->param_list.push_back(class_guess);
        info->param_nullable_list.push_back(false);
        info->param_name_list.push_back(class_guess->GetValue());

        auto param_dec = class_setter_dec->GetMethodSetterParamDec();
        if (param_dec == nullptr)
            return ABnfGuessError(element, u8"ָ���setter����û�ж������");

        // ��Ӳ����б�
        auto one_dec = param_dec->GetMethodParamOneDec();
        if (one_dec == nullptr)
            return ABnfGuessError(element, u8"ָ���setter����û�ж������");
        auto all_type = one_dec->GetAllType();
        if (all_type == nullptr)
            return ABnfGuessError(element, u8"ָ���setter����û�ж����������");

        ABnfGuessPtr all_type_guess;
        error = all_type->GuessType(all_type_guess);
        if (error) return error;
        info->param_list.push_back(all_type_guess);
        info->param_nullable_list.push_back(ALittleScriptUtility::IsNullable(one_dec->GetModifierList()));
        if (one_dec->GetMethodParamNameDec() != nullptr) {
            info->param_name_list.push_back(one_dec->GetMethodParamNameDec()->GetElementText());
        }
        else {
            info->param_name_list.emplace_back("");
        }

        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
    {
        auto class_method_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent);
        auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_method_dec->GetParent());
        auto class_body_dec = class_element_dec->GetParent();
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_body_dec->GetParent());

        auto info = std::make_shared<ALittleScriptGuessFunctor>(class_method_dec);
        const auto& modifier = class_element_dec->GetModifierList();
        info->const_modifier = ALittleScriptUtility::IsConst(class_element_dec->GetModifierList());
        info->await_modifier = ALittleScriptUtility::GetCoroutineType(modifier) == "await";

        // ��һ����������
        ABnfGuessPtr class_guess;
        auto error = class_dec->GuessType(class_guess);
        if (error) return error;
        info->param_list.push_back(class_guess);
        info->param_nullable_list.push_back(false);
        info->param_name_list.push_back(class_guess->GetValue());

        // ���ģ������б�
        auto template_dec = class_method_dec->GetTemplateDec();
        if (template_dec != nullptr)
        {
            std::vector<ABnfGuessPtr> template_guess_list;
            error = template_dec->GuessTypes(template_guess_list);
            if (error) return error;
            for (auto& guess : template_guess_list)
            {
                if (!std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
                    return ABnfGuessError(element, u8"template_dec.GuessTypes()ȡ���Ĳ���ALittleScriptGuessTemplate");
                info->template_param_list.push_back(std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess));
            }
        }

        // ��Ӳ����б�
        auto param_dec = class_method_dec->GetMethodParamDec();
        if (param_dec != nullptr)
        {
            const auto& one_dec_list = param_dec->GetMethodParamOneDecList();
            for (size_t i = 0; i < one_dec_list.size(); ++i)
            {
                auto one_dec = one_dec_list[i];
                auto all_type = one_dec->GetAllType();
                auto param_tail = one_dec->GetMethodParamTailDec();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr all_type_guess;
                    error = all_type->GuessType(all_type_guess);
                    if (error) return error;
                    info->param_list.push_back(all_type_guess);
                    info->param_nullable_list.push_back(ALittleScriptUtility::IsNullable(one_dec->GetModifierList()));
                    if (one_dec->GetMethodParamNameDec() != nullptr)
                        info->param_name_list.push_back(one_dec->GetMethodParamNameDec()->GetElementText());
                    else
                        info->param_name_list.emplace_back("");
                }
                else if (param_tail != nullptr)
                {
                    if (i + 1 != one_dec_list.size())
                        return ABnfGuessError(one_dec, u8"����ռλ�����붨�������");
                    ABnfGuessPtr guess;
                    error = param_tail->GuessType(guess);
                    if (error) return error;
                    info->param_tail = guess;
                }
            }
        }

        // ��ӷ���ֵ�б�
        auto return_dec = class_method_dec->GetMethodReturnDec();
        if (return_dec != nullptr)
        {
            const auto& one_dec_list = return_dec->GetMethodReturnOneDecList();
            for (size_t i = 0; i < one_dec_list.size(); ++i)
            {
                auto one_dec = one_dec_list[i];
                auto all_type = one_dec->GetAllType();
                auto return_tail = one_dec->GetMethodReturnTailDec();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr all_type_guess;
                    error = all_type->GuessType(all_type_guess);
                    if (error) return error;
                    info->return_list.push_back(all_type_guess);
                }
                else if (return_tail != nullptr)
                {
                    if (i + 1 != one_dec_list.size())
                        return ABnfGuessError(one_dec, u8"����ֵռλ�����붨�������");
                    ABnfGuessPtr guess;
                    error = return_tail->GuessType(guess);
                    if (error) return error;
                    info->return_tail = guess;
                }
            }
        }
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
    {
        auto class_static_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent);
        auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_static_dec->GetParent());

        auto info = std::make_shared<ALittleScriptGuessFunctor>(class_static_dec);
        info->await_modifier = ALittleScriptUtility::GetCoroutineType(class_element_dec->GetModifierList()) == "await";

        // ���ģ������б�
        auto template_dec = class_static_dec->GetTemplateDec();
        if (template_dec != nullptr)
        {
            std::vector<ABnfGuessPtr> template_guess_list;
            auto error = template_dec->GuessTypes(template_guess_list);
            if (error) return error;
            for (auto& guess : template_guess_list)
            {
                if (!std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
                    return ABnfGuessError(element, u8"template_dec.GuessTypes()ȡ���Ĳ���ALittleScriptGuessTemplate");
                info->template_param_list.push_back(std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess));
            }
        }

        // ��Ӳ����б�
        auto param_dec = class_static_dec->GetMethodParamDec();
        if (param_dec != nullptr)
        {
            const auto& one_dec_list = param_dec->GetMethodParamOneDecList();
            for (size_t i = 0; i < one_dec_list.size(); ++i)
            {
                auto one_dec = one_dec_list[i];
                auto all_type = one_dec->GetAllType();
                auto param_tail = one_dec->GetMethodParamTailDec();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr all_type_guess;
                    auto error = all_type->GuessType(all_type_guess);
                    if (error) return error;
                    info->param_list.push_back(all_type_guess);
                    info->param_nullable_list.push_back(ALittleScriptUtility::IsNullable(one_dec->GetModifierList()));
                    if (one_dec->GetMethodParamNameDec() != nullptr)
                        info->param_name_list.push_back(one_dec->GetMethodParamNameDec()->GetElementText());
                    else
                        info->param_name_list.push_back("");
                }
                else if (param_tail != nullptr)
                {
                    if (i + 1 != one_dec_list.size())
                        return ABnfGuessError(one_dec, u8"����ռλ�����붨�������");

                    ABnfGuessPtr guess;
                    auto error = param_tail->GuessType(guess);
                    if (error) return error;
                    info->param_tail = guess;
                }
            }
        }

        // ��ӷ���ֵ�б�
        auto return_dec = class_static_dec->GetMethodReturnDec();
        if (return_dec != nullptr)
        {
            const auto& one_dec_list = return_dec->GetMethodReturnOneDecList();
            for (size_t i = 0; i < one_dec_list.size(); ++i)
            {
                auto one_dec = one_dec_list[i];
                auto all_type = one_dec->GetAllType();
                auto return_tail = one_dec->GetMethodReturnTailDec();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr all_type_guess;
                    auto error = all_type->GuessType(all_type_guess);
                    if (error) return error;
                    info->return_list.push_back(all_type_guess);
                }
                else if (return_tail != nullptr)
                {
                    if (i + 1 != one_dec_list.size())
                        return ABnfGuessError(one_dec, u8"����ֵռλ�����붨�������");
                    ABnfGuessPtr guess;
                    auto error = return_tail->GuessType(guess);
                    if (error) return error;
                    info->return_tail = guess;
                }
            }
        }
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
    {
        auto global_method_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent);
        auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(global_method_dec->GetParent());

        auto info = std::make_shared<ALittleScriptGuessFunctor>(global_method_dec);
        info->await_modifier = ALittleScriptUtility::GetCoroutineType(namespace_element_dec->GetModifierList()) == "await";

        auto protocol_type = ALittleScriptUtility::GetProtocolType(namespace_element_dec->GetModifierList());
        if (!protocol_type.empty())
        {
            ABnfElementPtr error_element = global_method_dec->GetMethodNameDec();
            if (error_element == nullptr) error_element = global_method_dec;

            if (global_method_dec->GetTemplateDec() != nullptr)
                return ABnfGuessError(error_element, u8"��" + info->proto + u8"���ܶ��庯��ģ��");

            // ����Ǵ�Э��ע�⣬��ôһ����һ��await
            info->await_modifier = true;
            info->proto = protocol_type;

            auto param_dec = global_method_dec->GetMethodParamDec();
            if (param_dec == nullptr) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�����������������");
            const auto& one_dec_list = param_dec->GetMethodParamOneDecList();
            if (one_dec_list.size() != 2) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�����������������");
            if (ALittleScriptUtility::IsNullable(one_dec_list[0]->GetModifierList()) || ALittleScriptUtility::IsNullable(one_dec_list[1]->GetModifierList()))
                return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�����������ʹ��Nullable����");
            auto all_type = one_dec_list[1]->GetAllType();
            if (all_type == nullptr) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ������ڶ�������û�ж�������");
            ABnfGuessPtr guess;
            auto error = all_type->GuessType(guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess)) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ����ڶ�������������struct");

            if (info->proto == "Http")
            {
                auto class_name_element = index->FindALittleNameDec(ABnfElementType::CLASS_NAME, element->GetFile(), u8"ALittle", u8"IHttpSender", true);
                if (!std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element)) return ABnfGuessError(error_element, u8"���Կ�����Ҳ���ALittle.IHttpSender");
                auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element);
                ABnfGuessPtr class_name_dec_guess;
                error = class_name_dec->GuessType(class_name_dec_guess);
                if (error) return error;
                info->param_list.push_back(class_name_dec_guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("sender");
                info->param_list.push_back(guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("param");

                auto return_dec = global_method_dec->GetMethodReturnDec();
                if (return_dec == nullptr) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ������struct");
                const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
                if (return_one_list.size() != 1) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ���ҽ���һ��struct");
                auto return_one_all_type = return_one_list[0]->GetAllType();
                if (return_one_all_type == nullptr) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ���ҽ���һ��struct");
                ABnfGuessPtr return_guess;
                error = return_one_all_type->GuessType(return_guess);
                if (error) return error;
                if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess)) return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ������struct");
                info->return_list.push_back(ALittleScriptStatic::Inst().sStringGuess);
                info->return_list.push_back(return_guess);
            }
            else if (info->proto == "HttpDownload")
            {
                auto class_name_element = index->FindALittleNameDec(ABnfElementType::CLASS_NAME, element->GetFile(), u8"ALittle", u8"IHttpFileSender", true);
                if (!std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element)) return ABnfGuessError(error_element, u8"���Կ�����Ҳ���ALittle.IHttpFileSender");
                auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element);
                ABnfGuessPtr class_name_dec_guess;
                error = class_name_dec->GuessType(class_name_dec_guess);
                if (error) return error;
                info->param_list.push_back(class_name_dec_guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("sender");
                info->param_list.push_back(guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("param");

                info->return_list.push_back(ALittleScriptStatic::Inst().sStringGuess);
                ABnfGuessPtr sender_guess;
                error = class_name_element->GuessType(sender_guess);
                if (error) return error;
                info->return_list.push_back(sender_guess);
            }
            else if (info->proto == "HttpUpload")
            {
                auto class_name_element = index->FindALittleNameDec(ABnfElementType::CLASS_NAME, element->GetFile(), u8"ALittle", u8"IHttpFileSender", true);
                if (!std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element)) return ABnfGuessError(error_element, u8"���Կ�����Ҳ���ALittle.IHttpFileSender");
                auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element);
                ABnfGuessPtr class_name_dec_guess;
                error = class_name_dec->GuessType(class_name_dec_guess);
                if (error) return error;
                info->param_list.push_back(class_name_dec_guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("sender");
                info->param_list.push_back(guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("param");

                info->return_list.push_back(ALittleScriptStatic::Inst().sStringGuess);
            }
            else if (info->proto == "Msg")
            {
                auto class_name_element = index->FindALittleNameDec(ABnfElementType::CLASS_NAME, element->GetFile(), u8"ALittle", u8"IMsgCommon", true);
                if (!std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element)) return ABnfGuessError(error_element, u8"���Կ�����Ҳ���ALittle.IMsgCommon");
                auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element);
                ABnfGuessPtr class_name_dec_guess;
                error = class_name_dec->GuessType(class_name_dec_guess);
                if (error) return error;
                info->param_list.push_back(class_name_dec_guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("sender");
                info->param_list.push_back(guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("param");

                auto return_dec = global_method_dec->GetMethodReturnDec();
                if (return_dec != nullptr)
                {
                    const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
                    if (!return_one_list.empty())
                    {
                        auto return_one_all_type = return_one_list[0]->GetAllType();
                        if (return_one_all_type == nullptr)
                            return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ������struct");
                        ABnfGuessPtr return_guess;
                        error = return_one_all_type->GuessType(return_guess);
                        if (error) return error;
                        if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess))
                            return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ������struct");
                        info->return_list.push_back(ALittleScriptStatic::Inst().sStringGuess);
                        info->return_list.push_back(return_guess);
                    }
                }
            }
            else if (info->proto == "Worker")
            {
                auto class_name_element = index->FindALittleNameDec(ABnfElementType::CLASS_NAME, element->GetFile(), u8"ALittle", u8"IWorkerCommon", true);
                if (!std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element)) return ABnfGuessError(error_element, u8"���Կ�����Ҳ���ALittle.IWorkerCommon");
                auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(class_name_element);
                ABnfGuessPtr class_name_dec_guess;
                error = class_name_dec->GuessType(class_name_dec_guess);
                if (error) return error;
                info->param_list.push_back(class_name_dec_guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("sender");
                info->param_list.push_back(guess);
                info->param_nullable_list.push_back(false);
                info->param_name_list.emplace_back("param");

                auto return_dec = global_method_dec->GetMethodReturnDec();
                if (return_dec != nullptr)
                {
                    const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
                    if (!return_one_list.empty())
                    {
                        auto return_one_all_type = return_one_list[0]->GetAllType();
                        if (return_one_all_type == nullptr)
                            return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ������struct");
                        ABnfGuessPtr return_guess;
                        error = return_one_all_type->GuessType(return_guess);
                        if (error) return error;
                        if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess))
                            return ABnfGuessError(error_element, u8"��" + info->proto + u8"ע��ĺ�������ֵ������struct");
                        info->return_list.push_back(ALittleScriptStatic::Inst().sStringGuess);
                        info->return_list.push_back(return_guess);
                    }
                }
            }
            else
            {
                return ABnfGuessError(error_element, u8"δ֪��ע������:" + info->proto);
            }
        }
        else
        {
            // ���ģ������б�
            auto template_dec = global_method_dec->GetTemplateDec();
            if (template_dec != nullptr)
            {
                std::vector<ABnfGuessPtr> template_guess_list;
                auto error = template_dec->GuessTypes(template_guess_list);
                if (error) return error;
                for (auto& guess : template_guess_list)
                {
                    if (!std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
                        return ABnfGuessError(element, u8"template_dec.GuessTypes()ȡ���Ĳ���ALittleScriptGuessTemplate");
                    info->template_param_list.push_back(std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess));
                }
            }

            // ��Ӳ����б�
            auto param_dec = global_method_dec->GetMethodParamDec();
            if (param_dec != nullptr)
            {
                const auto& one_dec_list = param_dec->GetMethodParamOneDecList();
                for (size_t i = 0; i < one_dec_list.size(); ++i)
                {
                    auto one_dec = one_dec_list[i];
                    auto all_type = one_dec->GetAllType();
                    auto param_tail = one_dec->GetMethodParamTailDec();
                    if (all_type != nullptr)
                    {
                        ABnfGuessPtr all_type_guess;
                        auto error = all_type->GuessType(all_type_guess);
                        if (error) return error;
                        info->param_list.push_back(all_type_guess);
                        info->param_nullable_list.push_back(ALittleScriptUtility::IsNullable(one_dec->GetModifierList()));
                        if (one_dec->GetMethodParamNameDec() != nullptr)
                            info->param_name_list.push_back(one_dec->GetMethodParamNameDec()->GetElementText());
                        else
                            info->param_name_list.emplace_back("");
                    }
                    else if (param_tail != nullptr)
                    {
                        if (i + 1 != one_dec_list.size())
                            return ABnfGuessError(one_dec, u8"����ռλ�����붨�������");
                        ABnfGuessPtr guess;
                        auto error = param_tail->GuessType(guess);
                        if (error) return error;
                        info->param_tail = guess;
                    }
                }
            }

            // ��ӷ���ֵ�б�
            auto return_dec = global_method_dec->GetMethodReturnDec();
            if (return_dec != nullptr)
            {
                const auto& one_dec_list = return_dec->GetMethodReturnOneDecList();
                for (size_t i = 0; i < one_dec_list.size(); ++i)
                {
                    auto one_dec = one_dec_list[i];
                    auto all_type = one_dec->GetAllType();
                    auto return_tail = one_dec->GetMethodReturnTailDec();
                    if (all_type != nullptr)
                    {
                        ABnfGuessPtr all_type_guess;
                        auto error = all_type->GuessType(all_type_guess);
                        if (error) return error;
                        info->return_list.push_back(all_type_guess);
                    }
                    else if (return_tail != nullptr)
                    {
                        if (i + 1 != one_dec_list.size())
                            return ABnfGuessError(one_dec, u8"����ֵռλ�����붨�������");
                        ABnfGuessPtr guess;
                        auto error = return_tail->GuessType(guess);
                        if (error) return error;
                        info->return_tail = guess;
                    }
                }
            }
        }
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }

    return nullptr;
}

ABnfGuessError ALittleScriptMethodNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto method_dec = element->GetParent();
    if (method_dec == nullptr) return nullptr;
    const auto class_element_dec = method_dec->GetParent();
    if (class_element_dec == nullptr) return nullptr;
    const auto class_body = class_element_dec->GetParent();
    if (class_body == nullptr) return nullptr;
    const auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_body->GetParent());
    if (class_dec == nullptr) return nullptr;

    // ���㸸��
    const auto class_extends_dec = ALittleScriptUtility::FindClassExtends(class_dec);
    if (class_extends_dec == nullptr) return nullptr;

    ClassAttrType attrType;
    if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(method_dec))
        attrType = ClassAttrType::FUN;
    else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(method_dec))
        attrType = ClassAttrType::STATIC;
    else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(method_dec))
        attrType = ClassAttrType::GETTER;
    else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(method_dec))
        attrType = ClassAttrType::SETTER;
    else
        return nullptr;

    const auto result = ALittleScriptUtility::FindFirstClassAttrFromExtends(class_extends_dec, attrType, m_key, 100);
    if (!std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(result)) return nullptr;
    auto method_name_dec = std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(result);

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return error;
    ABnfGuessPtr extends_guess;
    error = method_name_dec->GuessType(extends_guess);
    if (error) return error;
    error = ALittleScriptOp::GuessTypeEqual(extends_guess, element, guess, false, false);
    if (error)
        return ABnfGuessError(element, u8"�ú����ǴӸ���̳����������Ƕ��岻һ��:" + extends_guess->GetValue());
    return nullptr;
}

bool ALittleScriptMethodNameDecReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index = GetIndex();
    if (index == nullptr) return false;

    const auto method_dec = element->GetParent();
    // ���ڲ��ĺ���
    if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(method_dec->GetParent()))
    {
        const auto class_dec = ALittleScriptUtility::FindClassDecFromParent(method_dec->GetParent());

        std::vector<ABnfElementPtr> dec_list;
        ALittleScriptUtility::FindClassMethodNameDecList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic, u8"", dec_list, 100);
        for (size_t i = 0; i < dec_list.size(); ++i)
        {
            if (m_key == dec_list[i]->GetElementText()) continue;
            list.emplace_back(dec_list[i]->GetElementText(), ALittleScriptIconType::MEMBER_METHOD, dec_list[i]->GetDescriptor());
        }
            
    }
    // ȫ�ֺ���
    else if (std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(method_dec->GetParent()))
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            if (m_key == dec->GetElementText()) continue;
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, dec->GetDescriptor());
        }
    }

    return true;
}

ABnfElementPtr ALittleScriptMethodNameDecReference::GotoDefinition()
{
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    const auto method_dec = element->GetParent();
    if (method_dec == nullptr) return nullptr;
    const auto class_element_dec = method_dec->GetParent();
    if (class_element_dec == nullptr) return nullptr;
    const auto class_body = method_dec->GetParent();
    if (class_body == nullptr) return nullptr;
    const auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_body->GetParent());
    if (class_dec == nullptr) return nullptr;

    // ���㸸��
    const auto class_extends_dec = ALittleScriptUtility::FindClassExtends(class_dec);
    if (class_extends_dec == nullptr) return nullptr;

    ClassAttrType attrType;
    if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(method_dec))
        attrType = ClassAttrType::FUN;
    else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(method_dec))
        attrType = ClassAttrType::STATIC;
    else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(method_dec))
        attrType = ClassAttrType::GETTER;
    else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(method_dec))
        attrType = ClassAttrType::SETTER;
    else
        return nullptr;

    return ALittleScriptUtility::FindFirstClassAttrFromExtends(class_extends_dec, attrType, m_key, 100);
}
