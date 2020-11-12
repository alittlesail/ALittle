#ifndef _ALITTLE_ALITTLESCRIPTFACTORYCLASSEX_H_
#define _ALITTLE_ALITTLESCRIPTFACTORYCLASSEX_H_

#include "../Index/ALittleScriptFactoryClass.h"

#include <unordered_map>

class ALittleScriptFactoryClassEx : public ALittleScriptFactoryClass
{
private:
    std::unordered_map<std::string, std::function<ABnfReference* (ABnfElementPtr)>> m_create_map;

public:
    ALittleScriptFactoryClassEx();

    ABnfReference* CreateReference(const ABnfElementPtr& element) override;

    ABnfGuessError GuessTypes(const ABnfElementPtr& element, std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTFACTORYCLASSEX_H_