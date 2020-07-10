
#ifndef _ALITTLE_ALITTLESCRIPTFILECLASS_H_
#define _ALITTLE_ALITTLESCRIPTFILECLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Index/ABnfFile.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class ALittleScriptFileClass : public ABnfFile
{
public:
    ALittleScriptFileClass(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len, bool in_ui);
    virtual ~ALittleScriptFileClass();

    // 更新分析内容
    void UpdateAnalysis() override;
    // 更新错误信息
    void UpdateError() override;

protected:
    // 移除内容
    void OnRemove() override;
};

#endif // _ALITTLE_ALITTLESCRIPTFILECLASS_H_
