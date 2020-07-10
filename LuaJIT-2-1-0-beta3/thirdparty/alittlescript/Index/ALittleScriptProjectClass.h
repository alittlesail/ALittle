
#ifndef _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
#define _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Index/ABnfProject.h"
#include "ALittleScriptIndex.h"
#include "../Reference/ALittleScriptFactoryClassEx.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class ALittleScriptProjectClass : public ABnfProject, public ALittleScriptIndex
{
private:
    ALittleScriptFactoryClassEx m_factory;
    std::string m_target_language;
    std::unordered_set<std::string> m_language_set;

protected:
    void ClearImpl() override;

public:
    ALittleScriptProjectClass();
    virtual ~ALittleScriptProjectClass();

public:
    ABnfFactory& RefFactory() override { return m_factory; }

public:
    void SetTargetLanguage(const std::string& language);
    void Generate(int query_id, const std::string& full_path);
    const std::string& GetTargetLanguage() const { return m_target_language; }
    const std::unordered_set<std::string>& GetLanguageSet() const { return m_language_set; }
};

#endif // _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
