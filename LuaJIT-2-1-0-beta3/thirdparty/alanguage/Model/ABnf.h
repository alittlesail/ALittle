
#ifndef _ALITTLE_ABNF_H_
#define _ALITTLE_ABNF_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "ABnfRule.h"
#include "ALanguageHelperInfo.h"

class ABnfNodeElement;

struct ABnfRuleCahce
{
    std::vector<ABnfNodeElement> option_list;
    int pin_offset = 0;
    int line = 0;
    int col = 0;
    int offset = 0;
    bool match = false;
};

class ABnfRuleStat
{
public:
    int create_node_count = 0;
    int use_node_count = 0;
    double use_node_rate = 0;

    int create_key_count = 0;
    int use_key_count = 0;
    double use_key_rate = 0;

    int create_string_count = 0;
    int use_string_count = 0;
    double use_string_rate = 0;

    int create_regex_count = 0;
    int use_regex_count = 0;
    double use_regex_rate = 0;

    std::unordered_map<std::string, int> create_node_count_map;
    std::unordered_map<std::string, int> use_node_count_map;
    std::unordered_map<std::string, double> use_node_rate_map;

    void CalcRate()
    {
        use_key_rate = 1;
        if (create_key_count > 0)
            use_key_rate = use_key_count / (double)create_key_count;

        use_string_rate = 1;
        if (create_string_count > 0)
            use_string_rate = use_string_count / (double)create_string_count;

        use_regex_rate = 1;
        if (create_regex_count > 0)
            use_regex_rate = use_regex_count / (double)create_regex_count;

        for (auto& create_pair : create_node_count_map)
        {
            auto it = use_node_count_map.find("ALittleScript" + create_pair.first + "Element");
            if (it != use_node_count_map.end() && create_pair.second != 0)
                use_node_rate_map[create_pair.first] = it->second / (double)create_pair.second;
            else
                use_node_rate_map[create_pair.first] = 1;
        }
    }

    void CreateNode(const std::string& type)
    {
        auto it = create_node_count_map.find(type);
        if (it != create_node_count_map.end())
            it->second++;
        else
            create_node_count_map[type] = 1;
        create_node_count++;
    }
};

class ABnfFactory;
using ABnfNodeElementPtr = std::shared_ptr<ABnfNodeElement>;
class ABnfErrorElement;
using ABnfErrorElementPtr = std::shared_ptr<ABnfErrorElement>;
class ABnfKeyElement;
using ABnfKeyElementPtr = std::shared_ptr<ABnfKeyElement>;
class ABnfStringElement;
using ABnfStringElementPtr = std::shared_ptr<ABnfStringElement>;
class ABnfRegexElement;
using ABnfRegexElementPtr = std::shared_ptr<ABnfRegexElement>;

class ABnf
{
private:
    // ABnf规则对象
    ABnfRule m_rule;
    ABnfRuleInfo* m_root = nullptr;            // 规则入口
    ABnfRuleInfo* m_line_comment = nullptr;    // 单行注释
    ABnfRuleInfo* m_block_comment = nullptr;   // 多行注释

    // 节点工厂
    ABnfFactory* m_factory = nullptr;

    // 正在解析的代码
    ABnfFile* m_file = nullptr;
    // 已经验证过的正则，用于缓存
    std::unordered_map<int, std::unordered_map<ABnfRuleNodeInfo*, int>> m_regex_skip;
    // 已经验证过的单行注释，用于缓存
    std::unordered_set<int> m_line_comment_skip;
    // 已经验证过的多行注释，用于缓存
    std::unordered_set<int> m_block_comment_skip;
    // 结束符栈
    std::vector<ABnfRuleInfo*> m_stop_stack;
    // 统计
    ABnfRuleStat m_stat;

    // 符号集合，当前符号如果遇到后面字符，那么就匹配失败
    std::unordered_map<std::string, std::unordered_set<char>> m_symbol_check;

public:
    ABnf();

    // 初始化参数
    void Clear();

    // 加载文法
    bool Load(const std::string& buffer, ABnfFactory* factory, std::string& error);

    // 查找规则
    ABnfRuleInfo* GetRule(const std::string& name);

    // 查询关键字
    void QueryKeyWordCompletion(const std::string& input, std::vector<ALanguageCompletionInfo>& list);
    // 创建节点
    ABnfNodeElementPtr CreateNodeElement(int line, int col, int offset, const std::string& type);
    ABnfKeyElementPtr CreateKeyElement(int line, int col, int offset, const std::string& value);
    ABnfStringElementPtr CreateStringElement(int line, int col, int offset, const std::string& value);
    ABnfRegexElementPtr CreateRegexElement(int line, int col, int offset, const std::string& value, std::shared_ptr<std::regex> regex);

    // 解析文件
    ABnfNodeElementPtr Analysis(ABnfFile* file);

    // 统计
    void StatElement(ABnfElementPtr element);

    // 分析规则语句
    bool AnalysisABnfNode(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    bool AnalysisABnfNodeMore(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 规则节点
    bool AnalysisABnfRuleMatch(ABnfRuleInfo* rule, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 分析节点
    bool AnalysisABnfNodeMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 关键字匹配
    bool AnalysisABnfKeyMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, bool ignore_error);

    // 字符串匹配
    bool AnalysisABnfStringMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, bool ignore_error);

    // 正则表达式匹配
    bool AnalysisABnfRegexMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 行注释匹配
    bool AnalysisABnfCommentMatch(ABnfRuleInfo* rule, ABnfNodeElementPtr parent, bool not_key, int& line, int& col, int& offset);

    // 根据接收的大小，进行偏移
    void AnalysisOffset(int value_len, int& line, int& col, int& offset);

    // 跳到另一行
    bool JumpToNextLine(int& line, int& col, int& offset);

    // 对切割字符进行跳跃
    void AnalysisSkip(int& line, int& col, int& offset);
};

using ABnfPtr = std::shared_ptr<ABnf>;

#endif // _ALITTLE_ABNF_H_