
#include "ALittleScriptGuessReturnTail.h"

ALittleScriptGuessReturnTail::ALittleScriptGuessReturnTail(const std::string& p_value)
{
    value = p_value;
    value_without_const = p_value;
}

bool ALittleScriptGuessReturnTail::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessReturnTail::ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessReturnTail::Clone() const
{
    return ABnfGuessPtr(new ALittleScriptGuessReturnTail(value));
}

