
#include "ALittleScriptGuessFunctor.h"
#include "ALittleScriptGuessTemplate.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFactory.h"
#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"
#include "../../alanguage/Model/ABnfElement.h"

ALittleScriptGuessFunctor::ALittleScriptGuessFunctor(const std::shared_ptr<ABnfElement>& p_element)
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
    for (const auto& guess : param_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->HasAny()) return true;
    }
    
    for (const auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->HasAny()) return true;
    }
    return false;
}

bool ALittleScriptGuessFunctor::NeedReplace() const
{
    for (const auto& guess : param_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->NeedReplace())
            return true;
    }

    for (const auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e != nullptr && guess_e->NeedReplace())
            return true;
    }
    return false;
}

ABnfGuessPtr ALittleScriptGuessFunctor::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    bool has_replace = false;
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

        auto replace = guess_e->ReplaceTemplate(file, fill_map);
        if (replace == nullptr) return nullptr;
        if (guess_e != replace) has_replace = true;
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
        auto replace = guess_e->ReplaceTemplate(file, fill_map);
        if (replace == nullptr) return nullptr;
        if (guess_e != replace) has_replace = true;
        new_guess->return_list.push_back(replace);
    }
    if (!has_replace) return shared_from_this();
    // 返回拷贝
    file->AddGuessType(new_guess);
    return new_guess;
}

ABnfGuessPtr ALittleScriptGuessFunctor::Clone() const
{
    auto guess = std::make_shared<ALittleScriptGuessFunctor>(element.lock());
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
    if (!proto.empty()) pre_list.push_back(proto);
    if (const_modifier) pre_list.emplace_back("const");
    if (await_modifier) pre_list.emplace_back("await");
    value += ABnfFactory::Join(pre_list, ",");

    // 模板参数列表
    if (!template_param_list.empty())
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
        auto param_e = param_list[i].lock();
        if (param_e == nullptr) continue;
        if (i < param_nullable_list.size() && param_nullable_list[i])
            param_string_list.push_back("[Nullable] " + param_e->GetValue());
        else
            param_string_list.push_back(param_e->GetValue());
    }
    const auto param_tail_e = param_tail.lock();
    if (param_tail_e != nullptr)
        param_string_list.push_back(param_tail_e->GetValue());
    value += "(" + ABnfFactory::Join(param_string_list, ",") + ")";

    // 返回值类型列表
    std::vector<std::string> return_string_list;
    for (auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr) continue;
        return_string_list.push_back(guess_e->GetValue());
    }
    const auto return_tail_e = return_tail.lock();
    if (return_tail_e != nullptr)
        return_string_list.push_back(return_tail_e->GetValue());
    if (!return_string_list.empty()) value += ":";
    value += ABnfFactory::Join(return_string_list, ",");

    value += ">";
    value_without_const = value;
    if (is_const) value = "const " + value;
}

bool ALittleScriptGuessFunctor::IsChanged() const
{
    for (const auto& guess : param_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr || guess_e->IsChanged())
            return true;
    }
    for (const auto& guess : return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr || guess_e->IsChanged())
            return true;
    }
    const auto param_tail_e = param_tail.lock();
    if (param_tail_e != nullptr && param_tail_e->IsChanged())
        return true;
    const auto return_tail_e = return_tail.lock();
    if (return_tail_e != nullptr && return_tail_e->IsChanged())
        return true;
    const auto element_e = element.lock();
    if (element_e == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element_e->GetFile()->GetProject())->GetGuessTypeList(element_e) == nullptr;

}
