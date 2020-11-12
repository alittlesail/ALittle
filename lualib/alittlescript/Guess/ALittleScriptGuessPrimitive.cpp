
#include "ALittleScriptGuessPrimitive.h"

ALittleScriptGuessPrimitive::ALittleScriptGuessPrimitive(const std::string& p_value, bool p_is_const)
{
    is_const = p_is_const;
    native_value = p_value;
    UpdateValue();
}

bool ALittleScriptGuessPrimitive::HasAny() const
{
    return value_without_const == "any";
}

bool ALittleScriptGuessPrimitive::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessPrimitive::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessPrimitive::Clone() const
{
    return std::make_shared<ALittleScriptGuessPrimitive>(value, is_const);
}

void ALittleScriptGuessPrimitive::UpdateValue()
{
    value = native_value;
    value_without_const = value;
    if (is_const) value = "const " + value;
}

