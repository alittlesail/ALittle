#ifndef _ALITTLE_ALITTLESCRIPTGLOBALMETHODDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTGLOBALMETHODDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptGlobalMethodDecElement.h"

#include <unordered_set>

class ALittleScriptGlobalMethodDecReference : public ALittleScriptReferenceTemplate<ALittleScriptGlobalMethodDecElement>
{
public:
    ALittleScriptGlobalMethodDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptGlobalMethodDecElement>(element) {}
private:
    ABnfGuessError CheckCmdError();

    ABnfGuessError CheckProtoError();

    ABnfGuessError CheckMsgStruct(ABnfElementPtr element, ABnfGuessPtr guess, std::unordered_set<std::string>& map);

    ABnfGuessError CheckJsonStruct(ABnfElementPtr element, ABnfGuessPtr guess, std::unordered_set<std::string>& map);

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTGLOBALMETHODDECREFERENCE_H_