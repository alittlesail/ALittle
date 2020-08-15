
#ifndef _ALITTLE_ABNFFILECLASS_H_
#define _ALITTLE_ABNFFILECLASS_H_

#include "../../alanguage/Index/ABnfFile.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class ABnfFileClass : public ABnfFile
{
private:
    // 规则名映射规则内容
    std::unordered_map<std::string, std::map<ABnfNodeElementPtr, std::string>> m_rule;
    // 获取规则
    std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>> m_index;

public:
	ABnfFileClass(ABnfProject* project, const std::string& full_path, const char* text, size_t len, bool in_ui);
    virtual ~ABnfFileClass();

    inline const std::unordered_map<std::string, std::map<ABnfNodeElementPtr, std::string>>& GetRuleSet() { return m_rule; }
    inline const std::unordered_map<std::string, std::unordered_set<ABnfNodeElementPtr>>& GetIndex() { return m_index; }

    // 更新分析内容
    void UpdateAnalysis() override;
    // 收集索引
    void CollectIndex(ABnfNodeElementPtr node);
    // 收集规则ID
    void CollectRule();

public:
    // 生成C++代码
    std::string Generate(int version, const std::string& target_path, const std::string& language_name);

private:
    struct CollectCompileInfo
    {
        // 0 表示没有，1表示一个，大于1表示多个
        std::unordered_map<std::string, int> id_map;
        int has_string = 0;
        int has_regex = 0;
        int has_key = 0;
    };
    void CollectCompile(ABnfElementPtr element, CollectCompileInfo& info, bool multi);
};

#endif // _ALITTLE_ABNFFILECLASS_H_
