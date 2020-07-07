
#ifndef _ALITTLE_ALITTLESCRIPTNAMESPACEELEMENTDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTNAMESPACEELEMENTDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptNamespaceElementDecElement.h"

class ALittleScriptNamespaceElementDecReference : public ALittleScriptReferenceTemplate<ALittleScriptNamespaceElementDecElement>
{
    ABnfGuessError CheckError() override;

    int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ALITTLESCRIPTNAMESPACEELEMENTDECREFERENCE_H_