
#include "ALittleScriptGuessFunctor.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFactory.h"
#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"
#include "../../alanguage/Model/ABnfElement.h"

ALittleScriptGuessFunctor::ALittleScriptGuessFunctor(std::shared_ptr<ABnfElement> p_element)
{
    is_register = ALittleScriptUtility::IsRegister(p_element);
    element = p_element;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessFunctor::GetElement()
{
    return element.lock();
}

bool ALittleScriptGuessFunctor::HasAny() const
{
    for (auto& guess : param_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->HasAny()) return true;
    }
    
    for (auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->HasAny()) return true;
    }
    return false;
}

bool ALittleScriptGuessFunctor::NeedReplace() const
{
    for (auto& guess : param_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->NeedReplace())
            return true;
    }

    for (auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->NeedReplace())
            return true;
    }
    return false;
}

ABnfGuessPtr ALittleScriptGuessFunctor::ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    // 克隆一份
    auto new_guess = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(Clone());
    // 清理参数列表，重新按模板替换
    new_guess->param_list.resize(0);
    new_guess->param_nullable_list.resize(0);
    for (size_t i = 0; i < param_list.size(); ++i)
    {
        auto guess = param_list[i];
        auto guess_e = guess.lock();
        if (guess_e == nullptr) return nullptr;

        auto replace = guess_e->ReplaceTemplate(fill_map);
        if (replace == nullptr) return nullptr;
        new_guess->param_list.push_back(replace);
        if (i < param_nullable_list.size())
            new_guess->param_nullable_list.push_back(param_nullable_list[i]);
        else
            new_guess->param_nullable_list.push_back(false);
    }
    // 清理返回值列表，重新按模板替换
    new_guess->return_list.resize(0);
    for (auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr) return nullptr;
        auto replace = guess_e->ReplaceTemplate(fill_map);
        if (replace == nullptr) return nullptr;
        new_guess->return_list.push_back(replace);
    }
    // 返回拷贝
    return new_guess;
}

ABnfGuessPtr ALittleScriptGuessFunctor::Clone() const
{
    auto guess = std::shared_ptr<ALittleScriptGuessFunctor>(new ALittleScriptGuessFunctor(element.lock()));
    guess->template_param_list = template_param_list;
    guess->param_list = param_list;
    guess->param_nullable_list = param_nullable_list;
    guess->param_name_list = param_name_list;
    guess->param_tail = param_tail;
    guess->return_list = return_list;
    guess->return_tail = return_tail;
    guess->proto = proto;
    guess->await_modifier = await_modifier;
    guess->const_modifier = const_modifier;
    guess->UpdateValue();
    return guess;
}

void ALittleScriptGuessFunctor::UpdateValue()
{
    value = "Functor<";

    // proto和await修饰
    std::vector<std::string> pre_list;
    if (proto.size()) pre_list.push_back(proto);
    if (const_modifier) pre_list.push_back("const");
    if (await_modifier) pre_list.push_back("await");
    value += ABnfFactory::Join(pre_list, ",");

    // 模板参数列表
    if (template_param_list.size() > 0)
    {
        std::vector<std::string> template_string_list;
        for (auto& guess : template_param_list)
        {
            auto guess_e = guess.lock();
            if (guess_e == nullptr) continue;
            template_string_list.push_back(guess_e->GetTotalValue());
        }
        value += "<" + ABnfFactory::Join(template_string_list, ",") + ">";
    }

    // 参数类型列表
    std::vector<std::string> param_string_list;
    for (size_t i = 0; i < param_list.size(); ++i)
    {
        if (i < param_nullable_list.size() && param_nullable_list[i])
            param_string_list.push_back("[Nullable] " + param_list[i]->GetValue());
        else
            param_string_list.push_back(param_list[i]->GetValue());
    }
    if (param_tail != nullptr)
        param_string_list.push_back(param_tail->GetValue());
    value += "(" + ABnfFactory::Join(param_string_list, ",") + ")";

    // 返回值类型列表
    std::vector<std::string> return_string_list;
    for (auto& guess : return_list)
        return_string_list.push_back(guess->GetValue());
    if (return_tail != nullptr)
        return_string_list.push_back(return_tail->GetValue());
    if (return_string_list.size() > 0) value += ":";
    value += ABnfFactory::Join(return_string_list, ",");

    value += ">";
    value_without_const = value;
    if (is_const) value = "const " + value;
}

bool ALittleScriptGuessFunctor::IsChanged() const
{
    for (auto& guess : param_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr || guess_e->IsChanged())
            return true;
    }
    for (auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr || guess_e->IsChanged())
            return true;
    }
    auto param_tail_e = param_tail.lock();
    if (param_tail_e != nullptr && param_tail_e->IsChanged())
        return true;
    auto return_tail_e = return_tail.lock();
    if (return_tail_e != nullptr && return_tail_e->IsChanged())
        return true;
    auto element_e = element.lock();
    if (element_e == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element_e->GetFile()->GetProject())->GetGuessTypeList(element_e) == nullptr;

}
