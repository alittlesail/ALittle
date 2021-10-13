
#include "ALittleScriptGuessMap.h"
#include "../Index/ALittleScriptFileClass.h"

ALittleScriptGuessMap::ALittleScriptGuessMap(const ABnfGuessPtr& p_key_type, const ABnfGuessPtr& p_value_type, bool p_is_const)
{
    key_type = p_key_type;
    value_type = p_value_type;
    is_const = p_is_const;
}

bool ALittleScriptGuessMap::HasAny() const
{
    const auto key_type_e = key_type.lock();
    if (key_type_e != nullptr && key_type_e->HasAny()) return true;

    const auto value_type_e = value_type.lock();
    if (value_type_e != nullptr && value_type_e->HasAny()) return true;

    return false;
}

bool ALittleScriptGuessMap::NeedReplace() const
{
    const auto key_type_e = key_type.lock();
    if (key_type_e != nullptr && key_type_e->NeedReplace()) return true;

    const auto value_type_e = value_type.lock();
    if (value_type_e != nullptr && value_type_e->NeedReplace()) return true;

    return false;
}

ABnfGuessPtr ALittleScriptGuessMap::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    auto key_type_e = key_type.lock();
    if (key_type_e == nullptr) return nullptr;

    const auto key_replace = key_type_e->ReplaceTemplate(file, fill_map);
    if (key_replace == nullptr) return nullptr;

    auto value_type_e = value_type.lock();
    if (value_type_e == nullptr) return nullptr;

    const auto value_replace = value_type_e->ReplaceTemplate(file, fill_map);
    if (value_replace == nullptr) return nullptr;
    
    if (key_type_e == key_replace && value_type_e == value_replace) return shared_from_this();

    auto guess = std::static_pointer_cast<ABnfGuess>(
	    std::make_shared<ALittleScriptGuessMap>(key_replace, value_replace, is_const));
    guess->UpdateValue();
    file->AddGuessType(guess);
    return guess;
}

ABnfGuessPtr ALittleScriptGuessMap::Clone() const
{
    auto guess = std::static_pointer_cast<ABnfGuess>(
	    std::make_shared<ALittleScriptGuessMap>(key_type.lock(), value_type.lock(), is_const));
    guess->UpdateValue();
    return guess;
}

void ALittleScriptGuessMap::UpdateValue()
{
    value = "";
    value += "Map<";
    const auto key_type_e = key_type.lock();
    if (key_type_e != nullptr)
        value += key_type_e->GetValue();
    value += ",";
    const auto value_type_e = value_type.lock();
    if (value_type_e != nullptr)
        value += value_type_e->GetValue();
    value += ">";
    value_without_const = value;
    if (is_const) value = "const " + value;
}

bool ALittleScriptGuessMap::IsChanged() const
{
    const auto key_type_e = key_type.lock();
    if (key_type_e == nullptr || key_type_e->IsChanged()) return true;

    const auto value_type_e = value_type.lock();
    if (value_type_e == nullptr || value_type_e->IsChanged()) return true;

    return false;
}
