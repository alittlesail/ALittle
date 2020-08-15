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

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckCmdError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    auto parent = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(element->GetParent());
    std::string command_type;
    std::string desc;
    if (!ALittleScriptUtility::GetCommandDetail(parent->GetModifierList(), command_type, desc)) return nullptr;

    if (element->GetTemplateDec() != nullptr)
        return ABnfGuessError(element, u8"带Cmd的全局函数，不能使用模板");
    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckProtoError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    auto parent = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(element->GetParent());
    auto proto_type = ALittleScriptUtility::GetProtocolType(parent->GetModifierList());
    if (proto_type.empty()) return nullptr;

    auto co_text = ALittleScriptUtility::GetCoroutineType(parent->GetModifierList());

    auto param_dec = element->GetMethodParamDec();
    auto return_dec = element->GetMethodReturnDec();

    std::string text = proto_type;

    if (element->GetTemplateDec() != nullptr)
        return ABnfGuessError(element, u8"带" + text + u8"的全局函数，不能使用模板");

    if (param_dec == nullptr) return ABnfGuessError(element, u8"带" + text + u8"的全局函数，必须有参数");
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> return_list;
    if (return_dec != nullptr)
    {
        const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
        for (auto& return_one : return_one_list)
        {
            if (return_one->GetMethodReturnTailDec() != nullptr)
                return ABnfGuessError(element, u8"带" + text + u8"的全局函数，不能使用返回值占位符");
            auto all_type = return_one->GetAllType();
            if (all_type == nullptr)
                return ABnfGuessError(element, u8"带" + text + u8"的全局函数，返回值没有定义类型");
            return_list.push_back(all_type);
        }
    }

    const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
    std::vector<ABnfGuessPtr> param_guess_list;
    for (auto& param_one_dec : param_one_dec_list)
    {
        if (param_one_dec->GetMethodParamTailDec() != nullptr)
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，不能使用参数占位符");
        auto all_type = param_one_dec->GetAllType();
        if (all_type == nullptr)
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，参数没有定义类型");

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
        return ABnfGuessError(return_dec, u8"带async修饰的函数，不能有返回值");

    // 检查参数个数
    if (param_guess_list.size() != 2) return ABnfGuessError(param_dec, u8"带" + text + u8"的全局函数，必须有两个参数");

    // 第二个参数
    if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(param_guess_list[1]))
        return ABnfGuessError(element, u8"带" + text + u8"的全局函数，第二个参数必须是struct");
    ABnfGuessError error;
    if (text == "Http")
    {
        if (co_text != "await")
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，必须使用await修饰");

        if (return_guess_list.size() != 1) return ABnfGuessError(element, u8"带" + text + u8"的全局函数，必须有一个返回值");
        // 第一个参数
        if (param_guess_list[0]->GetValue() != "ALittle.IHttpReceiver")
            return ABnfGuessError(param_one_dec_list[0], u8"带" + text + u8"的全局函数，第一个参数必须是ALittle.IHttpReceiver");

        // 返回值
        if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess_list[0]))
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，返回值必须是struct");

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
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，必须使用await修饰");

        if (return_guess_list.size() != 2) return ABnfGuessError(element, u8"带" + text + u8"的全局函数，必须有两个返回值，一个是string，一个是int");
        if (return_guess_list[0]->GetValue() != "string") return ABnfGuessError(element, u8"带" + text + u8"的全局函数，第一个参数必须是string");
        if (return_guess_list[1]->GetValue() != "int") return ABnfGuessError(element, u8"带" + text + u8"的全局函数，第二个参数必须是int");
        // 第一个参数
        if (param_guess_list[0]->GetValue() != "ALittle.IHttpReceiver")
            return ABnfGuessError(param_one_dec_list[0], u8"带" + text + u8"的全局函数，第一个参数必须是ALittle.IHttpReceiver");

        std::unordered_set<std::string> temp;
        error = CheckJsonStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;
    }
    else if (text == "HttpUpload")
    {
        if (co_text != "await")
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，必须使用await修饰");

        // 第一个参数
        if (param_guess_list[0]->GetValue() != "ALittle.IHttpFileReceiver")
            return ABnfGuessError(param_one_dec_list[0], u8"带" + text + u8"的全局函数，第一个参数必须是ALittle.IHttpFileReceiver");

        std::unordered_set<std::string> temp;
        error = CheckJsonStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;

        // 返回值
        if (return_guess_list.size() != 0)
            return ABnfGuessError(element, u8"带" + text + u8"的全局函数，不能有返回值");
    }
    else if (text == "Msg")
    {
        if (return_guess_list.size() > 1) return ABnfGuessError(element, u8"带" + text + u8"的全局函数，最多只能有一个返回值");
        // 第一个参数
        if (param_guess_list[0]->GetValue() != "ALittle.IMsgCommon")
            return ABnfGuessError(param_one_dec_list[0], u8"带" + text + u8"的全局函数，第一个参数必须是ALittle.IMsgCommon");

        std::unordered_set<std::string> temp;
        error = CheckMsgStruct(param_one_dec_list[1], param_guess_list[1], temp);
        if (error) return error;

        // 返回值
        if (return_guess_list.size() > 0)
        {
            if (co_text != "await")
                return ABnfGuessError(element, u8"带" + text + u8"的全局函数，并且有返回值，必须使用await修饰");

            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(return_guess_list[0]))
                return ABnfGuessError(element, u8"带" + text + u8"的全局函数，返回值必须是struct");

            std::unordered_set<std::string> temp;
            error = CheckMsgStruct(return_list[0], return_guess_list[0], temp);
            if (error) return error;
        }
        else
        {
            // 如果没有返回值，那么不能使用await，只能使用async，或者不使用
            if (co_text == "await")
                return ABnfGuessError(element, u8"带" + text + u8"的全局函数，当没有返回值时，不能使用await，可以使用async");
        }
    }
    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckMsgStruct(ABnfElementPtr element, ABnfGuessPtr guess, std::unordered_set<std::string>& map)
{
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
    {
        auto guess_list = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess);
        auto error = CheckMsgStruct(element, guess_list->sub_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
    {
        auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess);
        if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess_map->key_type.lock())
            && !std::dynamic_pointer_cast<ALittleScriptGuessInt>(guess_map->key_type.lock())
            && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(guess_map->key_type.lock()))
            return ABnfGuessError(element, u8"Msg协议接口的参数使用二进制序列化，内部使用的Map的key必须是string,int,long类型");
        auto error = CheckMsgStruct(element, guess_map->value_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
    {
        auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
        // 如果有继承，那么就检查一下继承
        auto struct_dec = guess_struct->struct_dec.lock();
        if (struct_dec != nullptr && struct_dec->GetStructExtendsDec() != nullptr)
        {
            auto extends_name = struct_dec->GetStructExtendsDec()->GetStructNameDec();
            if (extends_name != nullptr)
            {
                ABnfGuessPtr extends_guess;
                auto extends_error = extends_name->GuessType(extends_guess);
                if (extends_error) return extends_error;
                auto extends_struct_guess = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(extends_guess);
                extends_error = CheckMsgStruct(element, extends_struct_guess, map);
                if (extends_error) return extends_error;
            }
        }

        if (guess_struct->GetValueWithoutConst() == "ALittle.ProtocolAnyStruct") return nullptr;

        // 如果已经识别了，那么就直接返回
        if (map.find(guess_struct->GetValueWithoutConst()) != map.end()) return nullptr;
        map.insert(guess_struct->GetValueWithoutConst());

        std::shared_ptr<ALittleScriptStructBodyDecElement> body_dec;
        if (struct_dec) body_dec = struct_dec->GetStructBodyDec();
        if (body_dec == nullptr)
            return ABnfGuessError(element, u8"struct不完整");

        const auto& var_dec_list = body_dec->GetStructVarDecList();
        for (auto& var_dec : var_dec_list)
        {
            auto error = var_dec->GuessType(guess);
            if (error) return error;
            error = CheckMsgStruct(element, guess, map);
            if (error) return error;
        }
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
    {
        return ABnfGuessError(element, u8"Msg协议接口的参数使用二进制序列化，内部不能使用类");
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        return ABnfGuessError(element, u8"Msg协议接口的参数使用二进制序列化，内部不能使用函数");
    }
    else if (guess->HasAny())
    {
        return ABnfGuessError(element, u8"Msg协议接口的参数使用二进制序列化，内部不能使用any");
    }

    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckJsonStruct(ABnfElementPtr element, ABnfGuessPtr guess, std::unordered_set<std::string>& map)
{
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
    {
        auto guess_list = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess);
        auto error = CheckJsonStruct(element, guess_list->sub_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
    {
        auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess);
        if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess_map->key_type.lock()))
            return ABnfGuessError(element, u8"http协议接口的参数使用json序列化，内部使用的Map的key必须是string类型");
        auto error = CheckJsonStruct(element, guess_map->value_type.lock(), map);
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
    {
        auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
        // 如果有继承，那么就检查一下继承
        auto struct_dec = guess_struct->struct_dec.lock();
        if (struct_dec != nullptr && struct_dec->GetStructExtendsDec() != nullptr)
        {
            auto extends_name = struct_dec->GetStructExtendsDec()->GetStructNameDec();
            if (extends_name != nullptr)
            {
                ABnfGuessPtr extends_guess;
                auto extends_error = extends_name->GuessType(extends_guess);
                if (extends_error) return extends_error;
                auto extends_struct_guess = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(extends_guess);
                extends_error = CheckJsonStruct(element, extends_struct_guess, map);
                if (extends_error) return extends_error;
            }
        }

        // 如果已经识别了，那么就直接返回
        if (map.find(guess_struct->GetValueWithoutConst()) != map.end()) return nullptr;
        map.insert(guess_struct->GetValueWithoutConst());

        std::shared_ptr<ALittleScriptStructBodyDecElement> body_dec;
        if (struct_dec) body_dec = struct_dec->GetStructBodyDec();
        if (body_dec == nullptr)
            return ABnfGuessError(element, u8"struct不完整");

        const auto& var_dec_list = body_dec->GetStructVarDecList();
        for (auto& var_dec : var_dec_list)
        {
            auto error = var_dec->GuessType(guess);
            if (error) return error;
            error = CheckJsonStruct(element, guess, map);
            if (error) return error;
        }
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
    {
        return ABnfGuessError(element, u8"http协议接口的参数使用json序列化，内部不能使用类");
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        return ABnfGuessError(element, u8"http协议接口的参数使用json序列化，内部不能使用函数");
    }
    else if (guess->HasAny())
    {
        return ABnfGuessError(element, u8"http协议接口的参数使用json序列化，内部不能使用any");
    }

    return nullptr;
}

ABnfGuessError ALittleScriptGlobalMethodDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetMethodNameDec() == nullptr)
        return ABnfGuessError(element, u8"没有函数名");
    if (element->GetMethodBodyDec() == nullptr)
        return ABnfGuessError(element, u8"没有函数体");

    auto error = CheckCmdError();
    if (error) return error;
    error = CheckProtoError();
    if (error) return error;
    return nullptr;
}
