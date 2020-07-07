
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
	ABnfGuessError CheckError() override;

	bool IsLanguageEnable();
};

#endif // _ALITTLE_ALITTLESCRIPTLANGUAGEMODIFIERREFERENCE_H_