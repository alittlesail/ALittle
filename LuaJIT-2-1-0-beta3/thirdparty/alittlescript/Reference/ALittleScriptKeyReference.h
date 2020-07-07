#ifndef _ALITTLE_ALITTLESCRIPTKEYREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTKEYREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptKeyElement.h"

class ALittleScriptKeyReference : public ALittleScriptReferenceTemplate<ALittleScriptKeyElement>
{
    int QueryClassificationTag(bool& blur) override;

    ABnfElementPtr GotoDefinition() override;

    bool CanGotoDefinition() override;
};

#endif // _ALITTLE_ALITTLESCRIPTKEYREFERENCE_H_