
#ifndef _ALITTLE_ALITTLESCRIPTGUESSLIST_H_
#define _ALITTLE_ALITTLESCRIPTGUESSLIST_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptGuessList : public ALittleScriptGuess
{
public:
    ABnfGuessWeakPtr sub_type;
    bool is_native;

public:
    ALittleScriptGuessList(ABnfGuessPtr p_sub_type, bool p_is_const, bool p_is_native);

    bool HasAny() const override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSLIST_H_
