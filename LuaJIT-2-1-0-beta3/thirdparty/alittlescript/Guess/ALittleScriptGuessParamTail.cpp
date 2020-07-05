
#include "ALittleScriptGuessParamTail.h"

ALittleScriptGuessParamTail::ALittleScriptGuessParamTail(const std::string& p_value)
{
    value = p_value;
    value_without_const = p_value;
}

bool ALittleScriptGuessParamTail::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessParamTail::ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessParamTail::Clone() const
{
    return ABnfGuessPtr(new ALittleScriptGuessParamTail(value));
}

