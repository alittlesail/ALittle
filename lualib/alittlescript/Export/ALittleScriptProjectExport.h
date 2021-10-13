
#ifndef _ALITTLE_ALITTLESCRIPTPROJECTEXPORT_H_
#define _ALITTLE_ALITTLESCRIPTPROJECTEXPORT_H_

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

#include "alanguage/Export/ABnfProjectExport.h"
#include "alittlescript/Src/Index/ALittleScriptIndex.h"
#include "alittlescript/Src/Reference/ALittleScriptFactoryClassEx.h"

class ALittleScriptProjectExport : public ABnfProjectExport, public ALittleScriptIndex
{
private:
    ALittleScriptFactoryClassEx m_factory;
    std::string m_target_language_ui;
    std::string m_target_language;
    std::unordered_set<std::string> m_language_set;

protected:
    void ClearImpl() override;

public:
    ALittleScriptProjectExport();
    virtual ~ALittleScriptProjectExport() = default;

public:
    ABnfFactory& RefFactory() override { return m_factory; }

    void FindDefineImpl(const std::string& pre_input, const std::string& input, std::vector<ALanguageCompletionInfo>& info_list) override;
    void FindGotoImpl(const std::string& text, ALanguageGotoInfo& info) override;

public:
    void SetTargetLanguage(const std::string& language);
    void SetTargetLanguageUI(const std::string& language);
    void Generate(int query_id, const std::string& full_path);
    const std::string& GetTargetLanguage() const { return m_target_language; }
    const std::string& GetTargetLanguageUI() const { return m_target_language_ui; }
    const std::unordered_set<std::string>& GetLanguageSet() const { return m_language_set; }
};

#endif // _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
