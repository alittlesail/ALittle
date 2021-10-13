
#ifndef _ALITTLE_ABNFRULENODEINFO_H_
#define _ALITTLE_ABNFRULENODEINFO_H_

#include <vector>
#include <unordered_map>

#include "ABnfRuleTokenInfo.h"

class ABnfRuleNodeInfo;
class ABnfRule;

class ABnfRuleNodeInfo
{
public:
    ABnfRuleNodeRepeatType repeat = ABnfRuleNodeRepeatType::NRT_NONE;   // 重复规则
    ABnfRuleNodePinType pin = ABnfRuleNodePinType::NPT_NONE;            // 固定规则
    ABnfRuleNodeNotKeyType not_key = ABnfRuleNodeNotKeyType::NNKT_NONE; // 非key规则

    ABnfRuleTokenInfo value;                                            // 当为根规则时，节点的匹配规则
    std::vector<std::vector<ABnfRuleNodeInfo*>> node_list;              // 规则节点列表，一级List表示可选规则，二级List表示连续规则
    
private:
    // 下一个字符预检查（这个是有规则树进行计算总结出来的）
    bool calc_next_char = false;    // 运算收集第一个字符
    std::unordered_map<char, std::vector<int>> next_char_map;   // 第一个字符集合
    
    // 强制性预检查规则（这个定义在ABnf文件规则中）
    ABnfRuleTokenInfo pre_check_value;
    
public:
    ABnfRuleNodeInfo() = default;
    ABnfRuleNodeInfo(const ABnfRuleTokenInfo& v) : value(v) { }
    ~ABnfRuleNodeInfo();

public:
    // 预测下一个字符
    const std::vector<int>* CheckNextChar(ABnfRule* rule, char next);
    // 预测规则
    bool PreCheck(const std::string& text, size_t offset);
    // 计算预测下一个字符
    const std::unordered_map<char, std::vector<int>>* CalcNextChar(ABnfRule* rule);

private:
    // 计算预测规则
    void CalcPreCheck();
};


#endif // _ALITTLE_ABNFRULENODEINFO_H_