
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
    if (node_list[0].empty()) return;
    if (node_list[0][0]->repeat == ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE || node_list[0][0]->repeat == ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT) return;
    if (node_list[0][0]->value.type == ABnfRuleTokenType::TT_NONE) return;
    auto& value = node_list[0][0]->value;
    if (value.type != ABnfRuleTokenType::TT_STRING && value.type != ABnfRuleTokenType::TT_KEY) return;
    pre_check_value = value;
}

const std::unordered_map<char, std::vector<int>>* ABnfRuleNodeInfo::CalcNextChar(ABnfRule* rule)
{
    // �ж��Ƿ��Ѿ�����
    if (calc_next_char) return &next_char_map;
    calc_next_char = true;

    // ����Ԥ��
    CalcPreCheck();

    // ��������
    next_char_map.clear();

    // ������ѡ����
    for (size_t index = 0; index < node_list.size(); ++index)
    {
        // ������������
        for (size_t i = 0; i < node_list[index].size(); ++i)
        {
            auto& node_value = node_list[index][i];
            // ������ӹ���
            if (node_value->value.type != ABnfRuleTokenType::TT_NONE)
            {
                // �ӹ���
                if (node_value->value.type == ABnfRuleTokenType::TT_ID)
                {
                    // �����ӹ���
                    auto* sub_rule = rule->FindRuleInfo(node_value->value.value);
                    if (sub_rule == nullptr)
                    {
                        next_char_map.clear();
                        return nullptr;
                    }
                    // �ӹ������
                    auto* sub_next_char_map = sub_rule->CalcNextChar();
                    if (sub_next_char_map == nullptr)
                    {
                        next_char_map.clear();
                        return nullptr;
                    }
                    // �����ϲ�
                    for (auto& pair : *sub_next_char_map)
                    {
                        auto& list = next_char_map[pair.first];
                        if (std::find(list.begin(), list.end(), index) == list.end())
                            list.push_back(static_cast<int>(index));
                    }
                }
                // �������������ʽ����ôֱ������Ϊ��Ԥ��
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
                        auto& list = next_char_map[node_value->value.value[0]];
                        if (std::find(list.begin(), list.end(), index) == list.end())
                            list.push_back(static_cast<int>(index));
                    }
                }
            }
            // ����������
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
                    auto& list = next_char_map[pair.first];
                    if (std::find(list.begin(), list.end(), index) == list.end())
                        list.push_back(static_cast<int>(index));
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