#include "ALittleScriptGlobalMethodDecReference.h"

#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Generate/ALittleScriptMethodReturnOneDecElement.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptStructDecElement.h"
#include "../Generate/ALittleScriptStructExtendsDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptStructBodyDecElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessFunctor.h"

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckCmdError() const
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    auto parent = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(element->GetParent());
    std::string command_type;
    std::string desc;
    if (!ALittleScriptUtility::GetCommandDetail(parent->GetModifierList(), command_type, desc)) return nullptr;

    if (element->GetTemplateDec() != nullptr)
        return ABnfGuessError(element, u8"��Cmd��ȫ�ֺ���������ʹ��ģ��");
    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckProtoError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    auto parent = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(element->GetParent());
    auto proto_type = ALittleScriptUtility::GetProtocolType(parent->GetModifierList());
    if (proto_type.empty()) return nullptr;

    auto co_text = ALittleScriptUtility::GetCoroutineType(parent->GetModifierList());

    auto param_dec = element->GetMethodParamDec();
    auto return_dec = element->GetMethodReturnDec();

    const std::string& text = proto_type;

    if (element->GetTemplateDec() != nullptr)
        return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ʹ��ģ��");

    if (param_dec == nullptr) return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ����������в���");
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> return_list;
    if (return_dec != nullptr)
    {
        const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
        for (const auto& return_one : return_one_list)
        {
            if (return_one->GetMethodReturnTailDec() != nullptr)
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ʹ�÷���ֵռλ��");
            auto all_type = return_one->GetAllType();
            if (all_type == nullptr)
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ֵû�ж�������");
            return_list.push_back(all_type);
        }
    }

    const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
    std::vector<ABnfGuessPtr> param_guess_list;
    for (const auto& param_one_dec : param_one_dec_list)
    {
        if (param_one_dec->GetMethodParamTailDec() != nullptr)
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ʹ�ò���ռλ��");
        auto all_type = param_one_dec->GetAllType();
        if (all_type == nullptr)
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������û�ж�������");

        ABnfGuessPtr all_type_guess;
        auto guess_error = all_type->GuessType(all_type_guess);
        if (guess_error) return guess_error;
        param_guess_list.push_back(all_type_guess);
    }

    std::vector<ABnfGuessPtr> return_guess_list;
    for (auto& all_type : return_list)
    {
        ABnfGuessPtr all_type_guess;
        auto guess_error = all_type->GuessType(all_type_guess);
        if (guess_error) return guess_error;
        return_guess_list.push_back(all_type_guess);
    }

    if (co_text == "async" && return_guess_list.size() > 0)
        return ABnfGuessError(return_dec, u8"��async���εĺ����������з���ֵ");

    // ����������
    if (param_guess_list.size() != 2) return ABnfGuessError(param_dec, u8"��" + text + u8"��ȫ�ֺ�������������������");

    // �ڶ�������
    if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(param_guess_list[1]))
        return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ������ڶ�������������struct");
    ABnfGuessError error;
    if (text == "Http")
    {
        if (co_text != "await")
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ʹ��await����");

        if (return_guess_list.size() != 1) return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ�����������һ������ֵ");
        // ��һ������
        if (param_guess_list[0]->GetValue() != "ALittle.IHttpReceiver")
            return ABnfGuessError(param_one_dec_list[0], u8"��" + text + u8"��ȫ�ֺ�������һ������������ALittle.IHttpReceiver");

        // ����ֵ
        if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess_list[0]))
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ֵ������struct");

        std::unordered_set<std::string> temp;
        error = CheckJsonStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;
        
        temp.clear();
        error = CheckJsonStruct(return_list[0], return_guess_list[0], temp);
        if (error) return error;
    }
    else if (text == "HttpDownload")
    {
        if (co_text != "await")
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ʹ��await����");

        if (return_guess_list.size() != 2) return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ�������������������ֵ��һ����string��һ����int");
        if (return_guess_list[0]->GetValue() != "string") return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ�������һ������������string");
        if (return_guess_list[1]->GetValue() != "int") return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ������ڶ�������������int");
        // ��һ������
        if (param_guess_list[0]->GetValue() != "ALittle.IHttpReceiver")
            return ABnfGuessError(param_one_dec_list[0], u8"��" + text + u8"��ȫ�ֺ�������һ������������ALittle.IHttpReceiver");

        std::unordered_set<std::string> temp;
        error = CheckJsonStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;
    }
    else if (text == "HttpUpload")
    {
        if (co_text != "await")
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ʹ��await����");

        // ��һ������
        if (param_guess_list[0]->GetValue() != "ALittle.IHttpFileReceiver")
            return ABnfGuessError(param_one_dec_list[0], u8"��" + text + u8"��ȫ�ֺ�������һ������������ALittle.IHttpFileReceiver");

        std::unordered_set<std::string> temp;
        error = CheckJsonStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;

        // ����ֵ
        if (return_guess_list.size() != 0)
            return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ����������з���ֵ");
    }
    else if (text == "Msg")
    {
        if (return_guess_list.size() > 1) return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ��������ֻ����һ������ֵ");
        // ��һ������
        if (param_guess_list[0]->GetValue() != "ALittle.IMsgCommon")
            return ABnfGuessError(param_one_dec_list[0], u8"��" + text + u8"��ȫ�ֺ�������һ������������ALittle.IMsgCommon");

        std::unordered_set<std::string> temp;
        error = CheckMsgStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;

        // ����ֵ
        if (!return_guess_list.empty())
        {
            if (co_text != "await")
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ����������з���ֵ������ʹ��await����");

            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess_list[0]))
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ֵ������struct");

            std::unordered_set<std::string> temp;
            error = CheckMsgStruct(return_list[0], return_guess_list[0], temp);
            if (error) return error;
        }
        else
        {
            // ���û�з���ֵ����ô����ʹ��await��ֻ��ʹ��async�����߲�ʹ��
            if (co_text == "await")
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ�������û�з���ֵʱ������ʹ��await������ʹ��async");
        }
    }
    else if (text == "Worker")
    {
        if (return_guess_list.size() > 1) return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ��������ֻ����һ������ֵ");
        // ��һ������
        if (param_guess_list[0]->GetValue() != "ALittle.IWorkerCommon")
            return ABnfGuessError(param_one_dec_list[0], u8"��" + text + u8"��ȫ�ֺ�������һ������������ALittle.IWorkerCommon");

        std::unordered_set<std::string> temp;
        error = CheckMsgStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;

        // ����ֵ
        if (!return_guess_list.empty())
        {
            if (co_text != "await")
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ����������з���ֵ������ʹ��await����");

            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess_list[0]))
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ���������ֵ������struct");

            std::unordered_set<std::string> temp;
            error = CheckMsgStruct(return_list[0], return_guess_list[0], temp);
            if (error) return error;
        }
        else
        {
            // ���û�з���ֵ����ô����ʹ��await��ֻ��ʹ��async�����߲�ʹ��
            if (co_text == "await")
                return ABnfGuessError(element, u8"��" + text + u8"��ȫ�ֺ�������û�з���ֵʱ������ʹ��await������ʹ��async");
        }
    }
    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckMsgStruct(const ABnfElementPtr& element, ABnfGuessPtr guess, std::unordered_set<std::string>& map) const
{
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
    {
	    const auto guess_list = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess);
        auto error = CheckMsgStruct(element, guess_list->sub_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
    {
        auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess);
        if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess_map->key_type.lock())
            && !std::dynamic_pointer_cast<ALittleScriptGuessInt>(guess_map->key_type.lock())
            && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(guess_map->key_type.lock()))
            return ABnfGuessError(element, u8"MsgЭ��ӿڵĲ���ʹ�ö��������л����ڲ�ʹ�õ�Map��key������string,int,long����");
        auto error = CheckMsgStruct(element, guess_map->value_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
    {
	    const auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
        // ����м̳У���ô�ͼ��һ�¼̳�
        auto struct_dec = guess_struct->struct_dec.lock();
        if (struct_dec != nullptr && struct_dec->GetStructExtendsDec() != nullptr)
        {
            auto extends_name = struct_dec->GetStructExtendsDec()->GetStructNameDec();
            if (extends_name != nullptr)
            {
                ABnfGuessPtr extends_guess;
                auto extends_error = extends_name->GuessType(extends_guess);
                if (extends_error) return extends_error;
                const auto extends_struct_guess = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(extends_guess);
                extends_error = CheckMsgStruct(element, extends_struct_guess, map);
                if (extends_error) return extends_error;
            }
        }

        if (guess_struct->GetValueWithoutConst() == "ALittle.ProtocolAnyStruct") return nullptr;

        // ����Ѿ�ʶ���ˣ���ô��ֱ�ӷ���
        if (map.find(guess_struct->GetValueWithoutConst()) != map.end()) return nullptr;
        map.insert(guess_struct->GetValueWithoutConst());

        std::shared_ptr<ALittleScriptStructBodyDecElement> body_dec;
        if (struct_dec) body_dec = struct_dec->GetStructBodyDec();
        if (body_dec == nullptr)
            return ABnfGuessError(element, u8"struct������");

        const auto& var_dec_list = body_dec->GetStructVarDecList();
        for (const auto& var_dec : var_dec_list)
        {
            auto error = var_dec->GuessType(guess);
            if (error) return error;
            error = CheckMsgStruct(element, guess, map);
            if (error) return error;
        }
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
    {
        return ABnfGuessError(element, u8"MsgЭ��ӿڵĲ���ʹ�ö��������л����ڲ�����ʹ����");
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        return ABnfGuessError(element, u8"MsgЭ��ӿڵĲ���ʹ�ö��������л����ڲ�����ʹ�ú���");
    }
    else if (guess->HasAny())
    {
        return ABnfGuessError(element, u8"MsgЭ��ӿڵĲ���ʹ�ö��������л����ڲ�����ʹ��any");
    }

    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckJsonStruct(const ABnfElementPtr& element, ABnfGuessPtr guess, std::unordered_set<std::string>& map) const
{
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
    {
	    const auto guess_list = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess);
        auto error = CheckJsonStruct(element, guess_list->sub_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
    {
	    const auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess);
        if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess_map->key_type.lock()))
            return ABnfGuessError(element, u8"httpЭ��ӿڵĲ���ʹ��json���л����ڲ�ʹ�õ�Map��key������string����");
        auto error = CheckJsonStruct(element, guess_map->value_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
    {
	    const auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
        // ����м̳У���ô�ͼ��һ�¼̳�
        auto struct_dec = guess_struct->struct_dec.lock();
        if (struct_dec != nullptr && struct_dec->GetStructExtendsDec() != nullptr)
        {
            auto extends_name = struct_dec->GetStructExtendsDec()->GetStructNameDec();
            if (extends_name != nullptr)
            {
                ABnfGuessPtr extends_guess;
                auto extends_error = extends_name->GuessType(extends_guess);
                if (extends_error) return extends_error;
                const auto extends_struct_guess = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(extends_guess);
                extends_error = CheckJsonStruct(element, extends_struct_guess, map);
                if (extends_error) return extends_error;
            }
        }

        // ����Ѿ�ʶ���ˣ���ô��ֱ�ӷ���
        if (map.find(guess_struct->GetValueWithoutConst()) != map.end()) return nullptr;
        map.insert(guess_struct->GetValueWithoutConst());

        std::shared_ptr<ALittleScriptStructBodyDecElement> body_dec;
        if (struct_dec) body_dec = struct_dec->GetStructBodyDec();
        if (body_dec == nullptr)
            return ABnfGuessError(element, u8"struct������");

        const auto& var_dec_list = body_dec->GetStructVarDecList();
        for (const auto& var_dec : var_dec_list)
        {
            auto error = var_dec->GuessType(guess);
            if (error) return error;
            error = CheckJsonStruct(element, guess, map);
            if (error) return error;
        }
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
    {
        return ABnfGuessError(element, u8"httpЭ��ӿڵĲ���ʹ��json���л����ڲ�����ʹ����");
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        return ABnfGuessError(element, u8"httpЭ��ӿڵĲ���ʹ��json���л����ڲ�����ʹ�ú���");
    }
    else if (guess->HasAny())
    {
        return ABnfGuessError(element, u8"httpЭ��ӿڵĲ���ʹ��json���л����ڲ�����ʹ��any");
    }

    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetMethodNameDec() == nullptr)
        return ABnfGuessError(element, u8"û�к�����");
    if (element->GetMethodBodyDec() == nullptr)
        return ABnfGuessError(element, u8"û�к�����");

    auto error = CheckCmdError();
    if (error) return error;
    error = CheckProtoError();
    if (error) return error;
    return nullptr;
}
