
#ifndef _ALITTLE_ABNF_H_
#define _ALITTLE_ABNF_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <regex>

#include "ABnfRule.h"
#include "ALanguageHelperInfo.h"
#include "ARegex.h"

class ABnfNodeElement;
class ABnfFile;

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
    
    // 符号集合，当前符号如果遇到后面字符，那么就匹配失败
    std::unordered_map<std::string, std::unordered_set<char>> m_symbol_check;

public:
    // 初始化参数
    void Clear();

    // 加载文法
    bool Load(const std::string& buffer, ABnfFactory* factory, std::string& error);

    // 查找规则
    ABnfRuleInfo* GetRule(const std::string& name);
    // 获取所有关键字
    const std::unordered_set<std::string>& GetKeySet() const;
    // 获取所有规则
    const std::unordered_map<std::string, ABnfRuleInfo*>& GetRuleSet() const;

    // 查询关键字
    void QueryKeyWordCompletion(const std::string& input, std::vector<ALanguageCompletionInfo>& list) const;
    // 创建节点
    ABnfNodeElementPtr CreateNodeElement(int line, int col, int offset, const std::string& type) const;
    ABnfKeyElementPtr CreateKeyElement(int line, int col, int offset, const std::string& value) const;
    ABnfStringElementPtr CreateStringElement(int line, int col, int offset, const std::string& value) const;
    ABnfRegexElementPtr CreateRegexElement(int line, int col, int offset, const std::string& value, const std::shared_ptr<ARegex>& regex) const;

    // 解析文件
    ABnfNodeElementPtr Analysis(ABnfFile* file);

    // 分析规则语句
    bool AnalysisABnfNode(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    bool AnalysisABnfNodeMore(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 规则节点
    bool AnalysisABnfRuleMatch(ABnfRuleInfo* rule, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 分析节点
    bool AnalysisABnfNodeMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 关键字匹配
    bool AnalysisABnfKeyMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, bool ignore_error);

    // 字符串匹配
    bool AnalysisABnfStringMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, bool ignore_error);

    // 正则表达式匹配
    bool AnalysisABnfRegexMatch(ABnfRuleInfo* rule
        , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
        , int& line, int& col, int& offset, int& pin_offset, bool ignore_error);

    // 行注释匹配
    bool AnalysisABnfCommentMatch(ABnfRuleInfo* rule, const ABnfNodeElementPtr& parent, bool not_key, int& line, int& col, int& offset);

    // 根据接收的大小，进行偏移
    void AnalysisOffset(int value_len, int& line, int& col, int& offset) const;

    // 跳到另一行
    bool JumpToNextLine(int& line, int& col, int& offset) const;

    // 对切割字符进行跳跃
    void AnalysisSkip(int& line, int& col, int& offset) const;
};

#endif // _ALITTLE_ABNF_H_