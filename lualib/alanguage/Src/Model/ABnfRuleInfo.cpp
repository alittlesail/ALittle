
#include "ABnfRuleInfo.h"
#include "ABnfRuleNodeInfo.h"
#include <set>

ABnfRuleInfo::ABnfRuleInfo(ABnfRule* r) : rule(r) {}

ABnfRuleInfo::~ABnfRuleInfo()
{
    if (node != nullptr)
        delete node;
}

const std::vector<int>* ABnfRuleInfo::CheckNextChar(char next)
{
    if (!calc_next_char) CalcNextChar();
    auto it = next_char_map.find(next);
    if (it == next_char_map.end()) return nullptr;
    return &it->second;
}

const std::unordered_map<char, std::vector<int>>* ABnfRuleInfo::CalcNextChar()
{
    if (calc_next_char) return &next_char_map;
    calc_next_char = true;

    next_char_map.clear();

    // ��鵱ǰ�Ƿ��ж���Ԥ�����
    if (prediction.type != ABnfRuleTokenType::TT_NONE)
    {
        if (prediction.regex == nullptr)
            prediction.regex = std::make_shared<ARegex>(prediction.value);

        for (char i = '!'; i <= '~'; ++i)
        {
            int result_length;
            std::string value; value.push_back(i);
            if (prediction.regex->Match(value.c_str(), result_length))
            {
                std::vector<int>& list = next_char_map[i];
                std::set<size_t> set;
                for (size_t index = 0; index < node->node_list.size(); ++index)
                {
                    if (set.find(index) != set.end()) continue;
                    set.insert(index);
                    list.push_back(static_cast<int>(index));
                }
            }
        }
        return &next_char_map;
    }

    // ֱ�Ӹ������������
    const auto* map = node->CalcNextChar(rule);
    if (map != nullptr) next_char_map = *map;
    return &next_char_map;
}

const std::string& ABnfRuleInfo::GetStopToken()
{
    if (calc_stop_token) return stop_token;
    calc_stop_token = true;

    // û��option
    if (node->node_list.size() != 1) return stop_token;
    if (node->node_list[0].empty()) return stop_token;

    auto& last_node = node->node_list[0][node->node_list[0].size() - 1];
    if (last_node->value.type == ABnfRuleTokenType::TT_NONE) return stop_token;

    // �ظ����������(���ҽ���һ��)
    if (last_node->repeat != ABnfRuleNodeRepeatType::NRT_NONE && last_node->repeat != ABnfRuleNodeRepeatType::NRT_ONE)
        return stop_token;

    // ���һ��������TT_STRING
    if (last_node->value.type == ABnfRuleTokenType::TT_STRING)
        stop_token = last_node->value.value;

    return stop_token;
}
