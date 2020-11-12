
#ifndef _ALITTLE_ALITTLESCRIPTLANGUAGEMODIFIERREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTLANGUAGEMODIFIERREFERENCE_H_

#include <string>
#include <unordered_set>

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptLanguageModifierElement.h"

class ALittleScriptLanguageModifierReference : public ALittleScriptReferenceTemplate<ALittleScriptLanguageModifierElement>
{
private:
	bool m_init = false;
	std::unordered_set<std::string> m_name_set;

public:
	ALittleScriptLanguageModifierReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptLanguageModifierElement>(element) {}
	static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptLanguageModifierReference(element); }
	ABnfGuessError CheckError() override;

	bool IsLanguageEnable();
};

#endif // _ALITTLE_ALITTLESCRIPTLANGUAGEMODIFIERREFERENCE_H_