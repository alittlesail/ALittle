
#include "ALittleScriptGuessClass.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Generate/ALittleScriptClassDecElement.h"

#include "alanguage/Src/Index/ABnfFactory.h"
#include "alanguage/Src/Index/ABnfFile.h"
#include "alanguage/Src/Index/ABnfProject.h"

ALittleScriptGuessClass::ALittleScriptGuessClass(const std::string& p_namespace_name, const std::string& p_class_name, const std::shared_ptr<ALittleScriptClassDecElement>& p_class_dec, const std::string& p_using_name, bool p_is_const, bool p_is_native)
{
    is_register = ALittleScriptUtility::IsRegister(p_class_dec);
    namespace_name = p_namespace_name;
    class_name = p_class_name;
    class_dec = p_class_dec;
    using_name = p_using_name;
    is_const = p_is_const;
    is_native = p_is_native;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessClass::GetElement() { return class_dec.lock(); }

bool ALittleScriptGuessClass::NeedReplace() const
{
    if (template_list.empty()) return false;

    for (const auto& pair : template_map)
    {
        auto guess = pair.second.lock();
        if (guess == nullptr) return false;

        if (guess->NeedReplace()) return true;
    }
    return false;
}

ABnfGuessPtr ALittleScriptGuessClass::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    if (template_map.empty()) return shared_from_this();

    bool has_replace = false;
    auto new_guess = std::dynamic_pointer_cast<ALittleScriptGuessClass>(Clone());
    for (auto& pair : template_map)
    {
        auto template_guess = pair.second.lock();
        if (template_guess == nullptr) return nullptr;

        auto replace = template_guess->ReplaceTemplate(file, fill_map);
        if (replace == nullptr) return nullptr;
        if (replace != template_guess)
        {
            has_replace = true;
            new_guess->template_map[pair.first] = replace;
        }
    }

    if (!has_replace) return shared_from_this();

    file->AddGuessType(new_guess);
    return new_guess;
}

ABnfGuessPtr ALittleScriptGuessClass::Clone() const
{
    auto guess = std::make_shared<ALittleScriptGuessClass>(namespace_name, class_name, class_dec.lock(), using_name,
                                                           is_const, is_native);
    guess->template_list = template_list;
    guess->template_map = template_map;
    guess->UpdateValue();
    return guess;
}

void ALittleScriptGuessClass::UpdateValue()
{
    value = "";
    if (is_native) value += "native ";
    value += namespace_name + "." + class_name;
    std::vector<std::string> name_list;
    for (const auto& template_guess : template_list)
    {
        auto guess = template_guess.lock();
        if (guess == nullptr) continue;

        auto it = template_map.find(guess->GetValueWithoutConst());
        if (it != template_map.end())
        {
            auto impl = it->second.lock();
            if (impl == nullptr) continue;

            if (guess->is_const && !impl->is_const)
            {
                impl = impl->Clone();
                impl->is_const = true;
                impl->UpdateValue();
            }
            name_list.push_back(impl->GetValue());
        }
        else
            name_list.push_back(guess->GetValue());
    }
    if (!name_list.empty())
        value += "<" + ABnfFactory::Join(name_list, ",") + ">";

    value_without_const = value;
    if (is_const) value = "const " + value;
}

bool ALittleScriptGuessClass::IsChanged() const
{
    for (const auto& template_guess : template_list)
    {
        auto guess = template_guess.lock();
        if (guess == nullptr || guess->IsChanged())
            return true;
    }
    for (const auto& pair : template_map)
    {
        auto guess = pair.second.lock();
        if (guess == nullptr || guess->IsChanged())
            return true;
    }

    const auto element = class_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}
