
#ifndef _ALITTLE_ALITTLESCRIPTGUESSCONST_H_
#define _ALITTLE_ALITTLESCRIPTGUESSCONST_H_

#include "ALittleScriptGuess.h"

class ALittleScriptGuessConst : public ALittleScriptGuess
{
public:
    ALittleScriptGuessConst(const std::string& p_value);

    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    bool IsChanged() const override { return false; }
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSCONST_H_
