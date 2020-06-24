
#include "ABnfRuleNodeInfo.h"
#include "ABnfRule.h"
#include "ABnfRuleInfo.h"

ABnfRuleNodeInfo::~ABnfRuleNodeInfo()
{
    for (auto& list : node_list)
    {
        for (auto& node : list)
            delete node;
    }
}

const std::vector<int>* ABnfRuleNodeInfo::CheckNextChar(ABnfRule* rule, char next)
{
    if (!calc_next_char) CalcNextChar(rule);
    auto it = next_char_map.find(next);
    if (it == next_char_map.end()) return nullptr;
    return &it->second;
}

bool ABnfRuleNodeInfo::PreCheck(const std::string& text, size_t offset)
{
    if (pre_check_value.type == ABnfRuleTokenType::TT_NONE) return true;

    for (size_t i = 0; i < pre_check_value.value.size(); ++i)
    {
        if (i + offset >= text.size()) return false;
        if (pre_check_value.value[i] != text[i + offset]) return false;
    }
    return true;
}

void ABnfRuleNodeInfo::CalcPreCheck()
{
    pre_check_value = ABnfRuleTokenInfo();
    if (node_list.size() != 1) return;
    if (node_list[0].size() < 1) return;
    if (node_list[0][0]->repeat == ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE || node_list[0][0]->repeat == ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT) return;
    if (node_list[0][0]->value.type == ABnfRuleTokenType::TT_NONE) return;
    auto& value = node_list[0][0]->value;
    if (value.type != ABnfRuleTokenType::TT_STRING && value.type != ABnfRuleTokenType::TT_KEY) return;
    pre_check_value = value;
}

const std::unordered_map<char, std::vector<int>>* ABnfRuleNodeInfo::CalcNextChar(ABnfRule* rule)
{
    // 判断是否已经计算
    if (calc_next_char) return &next_char_map;
    calc_next_char = true;

    // 计算预测
    CalcPreCheck();

    // 创建对象
    next_char_map.clear();

    // 遍历可选序列
    for (size_t index = 0; index < node_list.size(); ++index)
    {
        // 遍历规则序列
        for (size_t i = 0; i < node_list[index].size(); ++i)
        {
            auto& node_value = node_list[index][i];
            // 如果是子规则
            if (node_value->value.type != ABnfRuleTokenType::TT_NONE)
            {
                // 子规则
                if (node_value->value.type == ABnfRuleTokenType::TT_ID)
                {
                    // 查找子规则
                    auto* sub_rule = rule->FindRuleInfo(node_value->value.value);
                    if (sub_rule == nullptr)
                    {
                        next_char_map.clear();
                        return nullptr;
                    }
                    // 子规则计算
                    auto* sub_next_char_map = sub_rule->CalcNextChar();
                    if (sub_next_char_map == nullptr)
                    {
                        next_char_map.clear();
                        return nullptr;
                    }
                    // 遍历合并
                    for (auto& pair : *sub_next_char_map)
                    {
                        next_char_map[pair.first].push_back(index);
                    }
                }
                // 如果遇到正则表达式，那么直接设置为无预测
                else if (node_value->value.type == ABnfRuleTokenType::TT_REGEX)
                {
                    next_char_map.clear();
                    return nullptr;
                }
                else if (node_value->value.type == ABnfRuleTokenType::TT_STRING
                    || node_value->value.type == ABnfRuleTokenType::TT_KEY)
                {
                    if (node_value->value.value.size() > 0)
                    {
                        next_char_map[node_value->value.value[0]].push_back(index);
                    }
                }
            }
            // 如果是组规则
            else
            {
                auto* sub_next_char_map = node_value->CalcNextChar(rule);
                if (sub_next_char_map == nullptr)
                {
                    next_char_map.clear();
                    return nullptr;
                }

                for (auto& pair : *sub_next_char_map)
                {
                    next_char_map[pair.first].push_back(index);
                }
            }

            if (node_value->repeat != ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE
                && node_value->repeat != ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT)
            {
                break;
            }
        }
    }

    return &next_char_map;
}