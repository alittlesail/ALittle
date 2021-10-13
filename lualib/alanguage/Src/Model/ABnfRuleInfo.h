
#ifndef _ALITTLE_ABNFRULEINFO_H_
#define _ALITTLE_ABNFRULEINFO_H_

#include "ABnfRuleTokenInfo.h"
#include <unordered_map>

class ABnfRule;
class ABnfRuleNodeInfo;

class ABnfRuleInfo
{
private:
    ABnfRule* rule = nullptr; // 规则集合

public:
    ABnfRuleTokenInfo id;           // 规则名
    ABnfRuleTokenInfo prediction;   // 下一个字符预测的正则表达式
    ABnfRuleNodePinType prediction_pin = ABnfRuleNodePinType::NPT_NONE;  // 预测表达式pin类型
    ABnfRuleTokenInfo assign;           // 等号
    ABnfRuleNodeInfo* node = nullptr;   // 规则节点

    int rule_id = 0;
    // 颜色
    bool has_color = false;
    int red = 0;
    int green = 0;
    int blue = 0;

private:
    // 计算结束符
    bool calc_stop_token = false;
    std::string stop_token;

    // 计算字符预测
    bool calc_next_char = false;
    std::unordered_map<char, std::vector<int>> next_char_map;

public:
    ABnfRuleInfo(ABnfRule* r);
    ~ABnfRuleInfo();

    // 获取下一个字符预测
    const std::vector<int>* CheckNextChar(char next);
    // 获取字符预测
    const std::unordered_map<char, std::vector<int>>* CalcNextChar();
    // 获取截止字符
    const std::string& GetStopToken();
};

#endif // _ALITTLE_ABNFRULEINFO_H_