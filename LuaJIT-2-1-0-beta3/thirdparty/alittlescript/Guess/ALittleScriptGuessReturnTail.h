
#ifndef _ALITTLE_ALITTLESCRIPTGUESSRETURNTAIL_H_
#define _ALITTLE_ALITTLESCRIPTGUESSRETURNTAIL_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptGuessReturnTail : public ALittleScriptGuess
{
public:
    ALittleScriptGuessReturnTail(const std::string& p_value);

    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    bool IsChanged() const override { return false; }
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSRETURNTAIL_H_
