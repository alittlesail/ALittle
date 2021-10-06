#ifndef _ALITTLE_ALITTLESCRIPTGLOBALMETHODDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTGLOBALMETHODDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptGlobalMethodDecElement.h"

#include <unordered_set>

class ALittleScriptGlobalMethodDecReference : public ALittleScriptReferenceTemplate<ALittleScriptGlobalMethodDecElement>
{
public:
    ALittleScriptGlobalMethodDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptGlobalMethodDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptGlobalMethodDecReference(element); }
private:
    ABnfGuessError CheckCmdError() const;

    ABnfGuessError CheckProtoError();

    ABnfGuessError CheckMsgStruct(const ABnfElementPtr& element, ABnfGuessPtr guess, std::unordered_set<std::string>& map) const;

    ABnfGuessError CheckJsonStruct(const ABnfElementPtr& element, ABnfGuessPtr guess, std::unordered_set<std::string>& map) const;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTGLOBALMETHODDECREFERENCE_H_