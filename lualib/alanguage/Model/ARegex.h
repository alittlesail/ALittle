
#ifndef _ALITTLE_AREGEX_H_
#define _ALITTLE_AREGEX_H_

#include <string>
#include <vector>
#include <unordered_set>

enum class ARegexNodeType
{
    NT_NONE,            // 无效枚举
    NT_CHAR,            // 一个字符
    NT_FIND_STRING,     // 查找字符串
    NT_CHARSET,         // 字符集合
    NT_LIST,            // 子节点列表 逐个匹配
    NT_OPTION,          // 子节点列表 分支匹配
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
    CST_CUSTOM,         // 自定义，读取char_set
    CST_A,              // 字母
    CST_D,              // 数字
    CST_W,              // 字母数字下划线
    CST_DOT,            // 除了\n以外的字符
    CST_ALL,            // 全部字符
};

enum class ARegexNegateType
{
    NNT_NONE,		    // 未设置，并可以当NNT_FALSE处理
    NNT_FALSE,	        // 没有取反
    NNT_TRUE,	        // 有取反
};

struct ARegexNode
{
    // 节点类型
    ARegexNodeType type = ARegexNodeType::NT_NONE;
    // 重复匹配规则
    ARegexRepeatType repeat = ARegexRepeatType::NRT_NONE;
    // 匹配结果取反
    ARegexNegateType negate = ARegexNegateType::NNT_NONE;

    // 当type为NT_CHAR时，表示要匹配的字符
    char value = 0;

    // 当type为NT_FIND_STRING时，表示要查找的字符串
    std::string find;

    // 当type为NT_CHARSET时，表示要匹配字符集合
    ARegexCharSetType char_set_type = ARegexCharSetType::CST_CUSTOM;
    // 当char_set_type为ARegexCharSetType::CST_CUSTOM时，表示字符集合
    std::unordered_set<char> char_set;

    // 当type为NT_LIST或者NT_OPTION时，表示子节点
    std::vector<ARegexNode> childs;
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
    static bool CompileFindString(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error);
};

#endif // _ALITTLE_AREGEX_H_