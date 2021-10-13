
#ifndef _ALITTLE_ALITTLESCRIPTGUESSMAP_H_
#define _ALITTLE_ALITTLESCRIPTGUESSMAP_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptGuessMap : public ALittleScriptGuess
{
public:
    ABnfGuessWeakPtr key_type;
    ABnfGuessWeakPtr value_type;

public:
    ALittleScriptGuessMap(const ABnfGuessPtr& p_key_type, const ABnfGuessPtr& p_value_type, bool p_is_const);

    bool HasAny() const override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSMAP_H_
