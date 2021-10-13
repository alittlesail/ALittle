
#ifndef _ALITTLE_ABNFRULE_H_
#define _ALITTLE_ABNFRULE_H_

#include <string>
#include <unordered_map>
#include <unordered_set>

class ABnfRuleInfo;
struct ABnfRuleTokenInfo;
class ABnfRuleNodeInfo;

class ABnfRule
{
private:
    // ABnf��������
    std::string m_buffer = "";
    // ���򼯺�
    std::unordered_map<std::string, ABnfRuleInfo*> m_rule_map;
    // �ؼ��ּ���
    std::unordered_set<std::string> m_key_set;
    // ���ż���
    std::unordered_set<std::string> m_symbol_set;

public:
    ~ABnfRule() { Clear(); }

    // ��ʼ������
    void Clear();

    // �����ķ�
    bool Load(const std::string& buffer, std::string& error);

    // ��ȡ���йؼ���
    inline const std::unordered_set<std::string>& GetKeySet() const { return m_key_set; }

    // ��ȡ���з��ż���
    inline const std::unordered_set<std::string>& GetSymbolSet() const { return m_symbol_set; }

    // �����������Ʋ��ҹ������
    ABnfRuleInfo* FindRuleInfo(const std::string& id);

    // ��ȡ���й���
    const std::unordered_map<std::string, ABnfRuleInfo*>& GetRuleSet() const;

private:
    // �����������
    ABnfRuleInfo* CalcABnfRule(const std::vector<ABnfRuleTokenInfo>& token_list, int rule_id, size_t& offset, std::string& error);

    // ��������ڵ�
    ABnfRuleNodeInfo* CalcABnfNode(const std::vector<ABnfRuleTokenInfo>& token_list, size_t& offset, std::string& error) const;

    // Token����
    void CalcToken(std::vector<ABnfRuleTokenInfo>& token_list);
};

#endif