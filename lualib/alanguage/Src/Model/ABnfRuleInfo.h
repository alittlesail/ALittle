
#ifndef _ALITTLE_ABNFRULEINFO_H_
#define _ALITTLE_ABNFRULEINFO_H_

#include "ABnfRuleTokenInfo.h"
#include <unordered_map>

class ABnfRule;
class ABnfRuleNodeInfo;

class ABnfRuleInfo
{
private:
    ABnfRule* rule = nullptr; // ���򼯺�

public:
    ABnfRuleTokenInfo id;           // ������
    ABnfRuleTokenInfo prediction;   // ��һ���ַ�Ԥ���������ʽ
    ABnfRuleNodePinType prediction_pin = ABnfRuleNodePinType::NPT_NONE;  // Ԥ����ʽpin����
    ABnfRuleTokenInfo assign;           // �Ⱥ�
    ABnfRuleNodeInfo* node = nullptr;   // ����ڵ�

    int rule_id = 0;
    // ��ɫ
    bool has_color = false;
    int red = 0;
    int green = 0;
    int blue = 0;

private:
    // ���������
    bool calc_stop_token = false;
    std::string stop_token;

    // �����ַ�Ԥ��
    bool calc_next_char = false;
    std::unordered_map<char, std::vector<int>> next_char_map;

public:
    ABnfRuleInfo(ABnfRule* r);
    ~ABnfRuleInfo();

    // ��ȡ��һ���ַ�Ԥ��
    const std::vector<int>* CheckNextChar(char next);
    // ��ȡ�ַ�Ԥ��
    const std::unordered_map<char, std::vector<int>>* CalcNextChar();
    // ��ȡ��ֹ�ַ�
    const std::string& GetStopToken();
};

#endif // _ALITTLE_ABNFRULEINFO_H_