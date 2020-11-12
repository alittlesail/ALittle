
#include "ALittleScriptGuessClassTemplate.h"

#include "../Generate/ALittleScriptTemplatePairDecElement.h"

ALittleScriptGuessClassTemplate::ALittleScriptGuessClassTemplate(const std::shared_ptr<ALittleScriptTemplatePairDecElement>& p_template_pair_dec
    , ABnfGuessPtr p_template_extends
    , bool p_is_class, bool p_is_struct)
    : ALittleScriptGuessTemplate(p_template_pair_dec, p_template_extends, p_is_class, p_is_struct)
{
}

ABnfGuessPtr ALittleScriptGuessClassTemplate::Clone() const
{
    auto guess = std::make_shared<ALittleScriptGuessClassTemplate>(template_pair_dec.lock(), template_extends.lock(),
                                                                   is_class, is_struct);
    guess->UpdateValue();
    return guess;
}