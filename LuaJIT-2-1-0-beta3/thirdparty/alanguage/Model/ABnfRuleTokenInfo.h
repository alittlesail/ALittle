
#ifndef _ALITTLE_ABNFRULETOKENINFO_H_
#define _ALITTLE_ABNFRULETOKENINFO_H_

#include <string>
#include <regex>
#include <memory>

enum class ABnfRuleTokenType
{
    TT_NONE,            // 无效枚举
    TT_ID,				// 规则名
    TT_STRING,			// 字符串
    TT_KEY,             // 关键字
    TT_REGEX,			// 正则表达式字符串
    TT_LINE_COMMENT,	// 行注释
    TT_BLOCK_COMMENT,	// 块注释
    TT_SYMBOL,			// 符号
};

class ABnfRuleInfo;

struct ABnfRuleTokenInfo
{
    ABnfRuleInfo* rule = nullptr;   // 当type时ID时，查找到的规则

    ABnfRuleTokenType type = ABnfRuleTokenType::TT_NONE;    // 类型
    std::string value;                                      // 值
    std::shared_ptr<std::regex> regex;                      // 正则表达式

    int line = 0;   // 所在行，从1开始算
    int col = 0;    // 所在列，从1开始算
};

enum class ABnfRuleNodeRepeatType
{
    NRT_NONE,		    // 未设置，并可以当NRT_ONE处理
    NRT_ONE,	        // 有且仅有一个
    NRT_NOT_OR_MORE,    // 0个或者多个
    NRT_AT_LEAST_ONE,   // 至少一个
    NRT_ONE_OR_NOT,	    // 有且仅有一个 或者没有
};

enum class ABnfRuleNodePinType
{
    NPT_NONE,		// 未设置，并可以当NPT_FALSE处理
    NPT_FALSE,		// 没有设置
    NPT_TRUE,		// 有设置
};

enum class ABnfRuleNodeNotKeyType
{
    NNKT_NONE,      // 未设置，并可以当NPT_FALSE处理
    NNKT_FALSE,     // 没有设置
    NNKT_TRUE,      // 有设置
};

#endif // _ALITTLE_ABNFRULETOKENINFO_H_