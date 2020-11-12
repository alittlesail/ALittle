
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
    // ABnf规则内容
    std::string m_buffer = "";
    // 规则集合
    std::unordered_map<std::string, ABnfRuleInfo*> m_rule_map;
    // 关键字集合
    std::unordered_set<std::string> m_key_set;
    // 符号集合
    std::unordered_set<std::string> m_symbol_set;

public:
    ~ABnfRule() { Clear(); }

    // 初始化参数
    void Clear();

    // 加载文法
    bool Load(const std::string& buffer, std::string& error);

    // 获取所有关键字
    inline const std::unordered_set<std::string>& GetKeySet() const { return m_key_set; }

    // 获取所有符号集合
    inline const std::unordered_set<std::string>& GetSymbolSet() const { return m_symbol_set; }

    // 根绝规则名称查找规则对象
    ABnfRuleInfo* FindRuleInfo(const std::string& id);

    // 获取所有规则
    const std::unordered_map<std::string, ABnfRuleInfo*>& GetRuleSet() const;

private:
    // 解析规则语句
    ABnfRuleInfo* CalcABnfRule(const std::vector<ABnfRuleTokenInfo>& token_list, int rule_id, size_t& offset, std::string& error);

    // 解析规则节点
    ABnfRuleNodeInfo* CalcABnfNode(const std::vector<ABnfRuleTokenInfo>& token_list, size_t& offset, std::string& error) const;

    // Token解析
    void CalcToken(std::vector<ABnfRuleTokenInfo>& token_list);
};

#endif