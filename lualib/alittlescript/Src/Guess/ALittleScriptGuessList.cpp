
#include "ALittleScriptGuessList.h"
#include "../Index/ALittleScriptFileClass.h"

ALittleScriptGuessList::ALittleScriptGuessList(const ABnfGuessPtr& p_sub_type, bool p_is_const, bool p_is_native)
{
    sub_type = p_sub_type;
    is_const = p_is_const;
    is_native = p_is_native;
}

bool ALittleScriptGuessList::HasAny() const
{
    const auto sub_type_e = sub_type.lock();
    if (sub_type_e == nullptr) return false;
    return sub_type_e->HasAny();
}

bool ALittleScriptGuessList::NeedReplace() const
{
    const auto sub_type_e = sub_type.lock();
    if (sub_type_e == nullptr) return false;
    return sub_type_e->NeedReplace();
}

ABnfGuessPtr ALittleScriptGuessList::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    auto sub_type_e = sub_type.lock();
    if (sub_type_e == nullptr) return nullptr;
    const auto replace = sub_type_e->ReplaceTemplate(file, fill_map);
    if (replace == nullptr) return nullptr;
    if (sub_type_e == replace) return shared_from_this();

    auto guess = std::static_pointer_cast<ABnfGuess>(
	    std::make_shared<ALittleScriptGuessList>(replace, is_const, is_native));
    guess->UpdateValue();
    file->AddGuessType(guess);
    return guess;
}

ABnfGuessPtr ALittleScriptGuessList::Clone() const
{
    auto guess = std::static_pointer_cast<ABnfGuess>(
	    std::make_shared<ALittleScriptGuessList>(sub_type.lock(), is_const, is_native));
    guess->UpdateValue();
    return guess;
}

void ALittleScriptGuessList::UpdateValue()
{
    value = "";
    if (is_native) value += "native ";
    value += "List<";
    const auto sub_type_e = sub_type.lock();
    if (sub_type_e != nullptr)
        value += sub_type_e->GetValue();
    value += ">";
    value_without_const = value;
    if (is_const) value = "const " + value;
}

bool ALittleScriptGuessList::IsChanged() const
{
    const auto sub_type_e = sub_type.lock();
    if (sub_type_e == nullptr) return true;
    return sub_type_e->IsChanged();
}
