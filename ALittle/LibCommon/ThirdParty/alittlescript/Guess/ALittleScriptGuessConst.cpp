
#include "ALittleScriptGuessConst.h"

ALittleScriptGuessConst::ALittleScriptGuessConst(const std::string& p_value)
{
    value = p_value;
    value_without_const = p_value;
}

bool ALittleScriptGuessConst::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessConst::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessConst::Clone() const
{
    return ABnfGuessPtr(new ALittleScriptGuessConst(value));
}

