
#ifndef _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
#define _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Index/ABnfProject.h"
#include "ALittleScriptIndex.h"
#include "ALittleScriptFactoryClass.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class ALittleScriptProjectClass : public ABnfProject, public ALittleScriptIndex
{
private:
    ALittleScriptFactoryClass m_factory;
    std::string m_target_language;

public:
    ALittleScriptProjectClass(const std::string& full_path);
    virtual ~ALittleScriptProjectClass();

public:
    ABnfFactory& RefFactory() override { return m_factory; }

public:
    void SetTargetLanguage(const std::string& language);
    const std::string& GetTargetLanguage() const { return m_target_language; }
};

#endif // _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
