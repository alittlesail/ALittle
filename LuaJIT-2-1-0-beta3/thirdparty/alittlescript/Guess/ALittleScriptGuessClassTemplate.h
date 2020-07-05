
#ifndef _ALITTLE_ALITTLESCRIPTGUESSCLASSTEMPLATE_H_
#define _ALITTLE_ALITTLESCRIPTGUESSCLASSTEMPLATE_H_

#include "ALittleScriptGuessTemplate.h"

#include <map>

class ALittleScriptTemplatePairDecElement;

class ALittleScriptGuessClassTemplate : public ALittleScriptGuessTemplate
{
public:
    ALittleScriptGuessClassTemplate(std::shared_ptr<ALittleScriptTemplatePairDecElement> p_template_pair_dec
        , ABnfGuessPtr p_template_extends
        , bool p_is_class, bool p_is_struct);

    ABnfGuessPtr Clone() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSCLASSTEMPLATE_H_
