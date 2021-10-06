
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
    ABnfRuleNodeRepeatType repeat = ABnfRuleNodeRepeatType::NRT_NONE;   // �ظ�����
    ABnfRuleNodePinType pin = ABnfRuleNodePinType::NPT_NONE;            // �̶�����
    ABnfRuleNodeNotKeyType not_key = ABnfRuleNodeNotKeyType::NNKT_NONE; // ��key����

    ABnfRuleTokenInfo value;                                            // ��Ϊ������ʱ���ڵ��ƥ�����
    std::vector<std::vector<ABnfRuleNodeInfo*>> node_list;              // ����ڵ��б�һ��List��ʾ��ѡ���򣬶���List��ʾ��������
    
private:
    // ��һ���ַ�Ԥ��飨������й��������м����ܽ�����ģ�
    bool calc_next_char = false;    // �����ռ���һ���ַ�
    std::unordered_map<char, std::vector<int>> next_char_map;   // ��һ���ַ�����
    
    // ǿ����Ԥ���������������ABnf�ļ������У�
    ABnfRuleTokenInfo pre_check_value;
    
public:
    ABnfRuleNodeInfo() = default;
    ABnfRuleNodeInfo(const ABnfRuleTokenInfo& v) : value(v) { }
    ~ABnfRuleNodeInfo();

public:
    // Ԥ����һ���ַ�
    const std::vector<int>* CheckNextChar(ABnfRule* rule, char next);
    // Ԥ�����
    bool PreCheck(const std::string& text, size_t offset);
    // ����Ԥ����һ���ַ�
    const std::unordered_map<char, std::vector<int>>* CalcNextChar(ABnfRule* rule);

private:
    // ����Ԥ�����
    void CalcPreCheck();
};


#endif // _ALITTLE_ABNFRULENODEINFO_H_