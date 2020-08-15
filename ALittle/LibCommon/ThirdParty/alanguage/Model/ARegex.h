
#ifndef _ALITTLE_AREGEX_H_
#define _ALITTLE_AREGEX_H_

#include <string>
#include <vector>
#include <unordered_set>

enum class ARegexType
{
    T_NONE,            // 无效枚举
    T_CHAR,            // 一个字符
    T_CHARSET,         // 字符集合
    T_LIST,           // 子节点列表 逐个匹配
    T_OPTION,           // 子节点列表 分支匹配
};

enum class ARegexRepeatType
{
    NRT_NONE,		    // 未设置，并可以当NRT_ONE处理
    NRT_ONE,	        // 有且仅有一个
    NRT_NOT_OR_MORE,    // 0个或者多个
    NRT_AT_LEAST_ONE,   // 至少一个
    NRT_ONE_OR_NOT,	    // 有且仅有一个 或者没有
};

enum class ARegexCharSetType
{
    CST_CUSTOM, // 自定义，读取char_set
    CST_A,      // 字母
    CST_D,      // 数字
    CST_W,      // 字母数字下划线
    CST_DOT,      // 除了\n以外的字符
    CST_ALL,      // 全部字符
};

enum class ARegexNegateType
{
    NNT_NONE,		    // 未设置，并可以当NNT_ONE处理
    NNT_FALSE,	        // 没有取反
    NNT_TRUE,	        // 有取反
};

struct ARegexNode
{
    ARegexType type = ARegexType::T_NONE;        // 节点类型

    // CHAR
    char value = 0;     // 字符内容

    // CHARSET
    std::unordered_set<char> char_set;// 字符集合
    ARegexCharSetType char_set_type = ARegexCharSetType::CST_CUSTOM;
    ARegexNegateType negate = ARegexNegateType::NNT_NONE;   // 是否有取反

    // GROUP
    std::vector<ARegexNode> childs; // 子节点

    ARegexRepeatType repeat = ARegexRepeatType::NRT_NONE;
};

class ARegex
{
private:
	std::string m_rule;	// 规则
    std::string m_rule_error;    // 记录编译规则错误

    // 已编译好的规则类型
    ARegexNode m_node;

public:
	ARegex(const std::string& rule);
    // 从该位置进行匹配
    bool Match(const char* src, int& length);

private:
    bool MatchNode(const char* src, const ARegexNode& node, int& length);
    bool MatchNodeRepeated(const char* src, const ARegexNode& node, int& length);

private:
    static bool CompileOption(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error);
    static bool CompileCustomSet(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error);
};

#endif // _ALITTLE_AREGEX_H_