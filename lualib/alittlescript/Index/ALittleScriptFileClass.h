
#ifndef _ALITTLE_ALITTLESCRIPTFILECLASS_H_
#define _ALITTLE_ALITTLESCRIPTFILECLASS_H_

#include "../../alanguage/Index/ABnfFile.h"
#include <unordered_set>
#include <string>

class ALittleScriptFileClass : public ABnfFile
{
public:
    ALittleScriptFileClass(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len, bool in_ui);
    virtual ~ALittleScriptFileClass();

    // 更新分析内容
    void UpdateAnalysis() override;

protected:
    // 移除内容
    void OnRemove() override;

    // 强制错误解析
    void OnForceAnalysisError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTFILECLASS_H_
