
#ifndef _ALITTLE_ABNFFILECLASS_H_
#define _ALITTLE_ABNFFILECLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Index/ABnfFile.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

class ABnfFileClass : public ABnfFile
{
private:
    // 规则名映射规则内容
    std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>> m_rule;
    // 获取规则
    std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>> m_index;

public:
	ABnfFileClass(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len);
    virtual ~ABnfFileClass();

    inline const std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>>& GetRuleSet() { return m_rule; }
    inline const std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>>& GetIndex() { return m_index; }

    // 更新分析内容
    void UpdateAnalysis() override;
    // 更新错误信息
    void UpdateError() override;
    // 收集索引
    void CollectIndex(ABnfNodeElementPtr node);
    // 收集规则ID
    void CollectRule();
};

#endif // _ALITTLE_ABNFFILECLASS_H_
