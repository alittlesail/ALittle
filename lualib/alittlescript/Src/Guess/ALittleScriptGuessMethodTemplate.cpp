
#include "ALittleScriptGuessMethodTemplate.h"

#include "../Generate/ALittleScriptTemplatePairDecElement.h"

ALittleScriptGuessMethodTemplate::ALittleScriptGuessMethodTemplate(const std::shared_ptr<ALittleScriptTemplatePairDecElement>& p_template_pair_dec
    , const ABnfGuessPtr& p_template_extends
    , bool p_is_class, bool p_is_struct)
    : ALittleScriptGuessTemplate(p_template_pair_dec, p_template_extends, p_is_class, p_is_struct)
{
}

ABnfGuessPtr ALittleScriptGuessMethodTemplate::Clone() const
{
    auto guess = std::make_shared<ALittleScriptGuessMethodTemplate>(template_pair_dec.lock(), template_extends.lock(),
                                                                    is_class, is_struct);
    guess->UpdateValue();
    return guess;
}