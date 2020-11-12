
#ifndef _ALITTLE_ALITTLESCRIPTGUESSMTHODTEMPLATE_H_
#define _ALITTLE_ALITTLESCRIPTGUESSMTHODTEMPLATE_H_

#include "ALittleScriptGuessTemplate.h"

#include <map>

class ALittleScriptTemplatePairDecElement;

class ALittleScriptGuessMethodTemplate : public ALittleScriptGuessTemplate
{
public:
    ALittleScriptGuessMethodTemplate(const std::shared_ptr<ALittleScriptTemplatePairDecElement>& p_template_pair_dec
        , const ABnfGuessPtr& p_template_extends
        , bool p_is_class, bool p_is_struct);

    ABnfGuessPtr Clone() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSMTHODTEMPLATE_H_
