#include "ALittleScriptClassCtorDecReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptKeyElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"

ABnfElementPtr ALittleScriptClassCtorDecReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    auto class_dec = ALittleScriptUtility::FindClassDecFromParent(element);
    if (class_dec == nullptr) return nullptr;

    auto class_extends_dec = ALittleScriptUtility::FindClassExtends(class_dec);
    if (class_extends_dec == nullptr) return nullptr;

    auto extends_ctor_dec = ALittleScriptUtility::FindFirstCtorDecFromExtends(class_extends_dec, 100);
    if (extends_ctor_dec == nullptr) return nullptr;

    return extends_ctor_dec->GetKey();
}

ABnfGuessError ALittleScriptClassCtorDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto class_dec = ALittleScriptUtility::FindClassDecFromParent(element);
    if (class_dec == nullptr) return nullptr;

    auto class_extends_dec = ALittleScriptUtility::FindClassExtends(class_dec);
    if (class_extends_dec == nullptr) return nullptr;

    auto extends_ctor_dec = ALittleScriptUtility::FindFirstCtorDecFromExtends(class_extends_dec, 100);
    if (extends_ctor_dec == nullptr) return nullptr;

    // 参数必须一致并且可转化
    auto extends_method_param_dec = extends_ctor_dec->GetMethodParamDec();
    auto my_method_param_dec = element->GetMethodParamDec();
    if (extends_method_param_dec == nullptr && my_method_param_dec == nullptr) return nullptr;
    if (extends_method_param_dec == nullptr || my_method_param_dec == nullptr)
        return ABnfGuessError(element, u8"该函数是从父类继承下来，但是参数数量不一致");

    auto extends_param_one_dec_list = extends_method_param_dec->GetMethodParamOneDecList();
    auto my_param_one_dec_list = my_method_param_dec->GetMethodParamOneDecList();
    if (extends_param_one_dec_list.size() > my_param_one_dec_list.size())
        return ABnfGuessError(my_method_param_dec, u8"该函数是从父类继承下来，但是子类的参数数量少于父类的构造函数");

    for (int i = 0; i < extends_param_one_dec_list.size(); ++i)
    {
        auto extends_one_dec = extends_param_one_dec_list[i];
        auto extends_name_dec = extends_one_dec->GetMethodParamNameDec();
        if (extends_name_dec == nullptr) return ABnfGuessError(my_method_param_dec, u8"该函数是从父类继承下来，但是定义不一致");
        auto my_one_dec = my_param_one_dec_list[i];
        auto my_name_dec = my_one_dec->GetMethodParamNameDec();
        if (my_name_dec == nullptr) return ABnfGuessError(my_method_param_dec, u8"该函数是从父类继承下来，但是定义不一致");

        ABnfGuessPtr extends_name_dec_guess;
        auto error = extends_name_dec->GuessType(extends_name_dec_guess);
        if (error) return error;
        ABnfGuessPtr my_name_dec_guess;
        error = my_name_dec->GuessType(my_name_dec_guess);
        if (error) return error;
        if (extends_name_dec_guess->GetValue() != my_name_dec_guess->GetValue())
            return ABnfGuessError(my_method_param_dec, u8"该函数是从父类继承下来，但是子类参数和父类参数类型不一致");
    }

    return nullptr;
}
