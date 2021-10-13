
#include "ARegex.h"

ARegex::ARegex(const std::string& rule) : m_rule(rule)
{
    // 清空规则编译错误
    m_rule_error.clear();
    // 根节点是一个OPTION
    size_t offset = 0;
    m_node.type = ARegexNodeType::NT_OPTION;
    // 开始解析规则串
    CompileOption(m_rule, offset, m_node, m_rule_error);
}

bool ARegex::Match(const char* src, int& length)
{
    // 初始化长度为0
    length = 0;
    // 进行repeated节点匹配
    return MatchNodeRepeated(src, m_node, length);
}

bool ARegex::MatchNode(const char* src, const ARegexNode& node, int& length)
{
    // 取出当前字符
    const char c = src[length];
    // 如果已经到结尾了，那么就直接返回
    if (c == 0) return false;

    // 处理当个字符匹配
    if (node.type == ARegexNodeType::NT_CHAR)
    {
        // 如果字符相等，那么就算是匹配成功
        if (node.value == c)
        {
            ++length;
            return true;
        }
        // 否则匹配失败
        return false;
    }

    // 处理查找字符串匹配
    if (node.type == ARegexNodeType::NT_FIND_STRING)
    {
        const auto* find = strstr(src + length, node.find.c_str());
        // 如果查找到，就算是匹配成功
        if (find != nullptr)
        {
            length += static_cast<int>(find - src - length) + static_cast<int>(node.find.length());
            return true;
        }
        // 否则匹配失败
        return false;
    }

    // 处理字符集合匹配
    if (node.type == ARegexNodeType::NT_CHARSET)
    {
        bool check = false;
        // 全匹配
        if (node.char_set_type == ARegexCharSetType::CST_ALL)
        {
            check = true;
        }
        // 自定义匹配
        else if (node.char_set_type == ARegexCharSetType::CST_CUSTOM)
        {
            check = node.char_set.find(c) != node.char_set.end();
        }
        // 字母匹配
        else if (node.char_set_type == ARegexCharSetType::CST_A)
        {
            check = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
        }
        // 数字匹配
        else if (node.char_set_type == ARegexCharSetType::CST_D)
        {
            check = c >= '0' && c <= '9';
        }
        // 字母，数字，下划线匹配
        else if (node.char_set_type == ARegexCharSetType::CST_W)
        {
            check = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_';
        }
        // 非换行任意字符匹配
        else if (node.char_set_type == ARegexCharSetType::CST_DOT)
        {
            check = c != '\n';
        }

        // 处理取反
        if (node.negate == ARegexNegateType::NNT_TRUE)
        {
            // 如果有取反，并且check失败，那么就认为成功
            if (!check)
            {
                ++length;
                return true;
            }
        }
        else
        {
            // 没有取反，并且check成功才是成功
            if (check)
            {
                ++length;
                return true;
            }
        }

        // 最后是匹配失败
        return false;
    }

    // 处理分支匹配，只要某个子节点匹配成功才是成功
    if (node.type == ARegexNodeType::NT_OPTION)
    {
        // 遍历所有子节点
        for (const auto& child : node.childs)
        {
            // 保存临时值，每个子节点都是从这个位置开始匹配
            int length_temp = length;
            // 开始匹配
            if (MatchNodeRepeated(src, child, length_temp))
            {
                // 如果有取反，那么直接返回失败
                if (node.negate == ARegexNegateType::NNT_TRUE)
                    return false;

                // 匹配成功了，就停止剩下的子节点匹配，返回成功
                length = length_temp;
                return true;
            }
        }

        // 执行到这里，说明匹配失败了

        // 如果有取反，那么就表示匹配成功
        if (node.negate == ARegexNegateType::NNT_TRUE)
        {
            ++length;
            return true;
        }

        // 否则返回匹配失败
        return false;
    }

    // 处理列表匹配，必须全部成功才是成功
    if (node.type == ARegexNodeType::NT_LIST)
    {
        // 遍历所有子节点
        for (const auto& child : node.childs)
        {
            // 如果匹配失败了，就是失败了
            if (!MatchNodeRepeated(src, child, length))
                return false;
        }

        // 这里不用处理node.negate，因为正则表达式规则上，'!'符号不可能修饰的了LIST

        // 执行到这里，所有全部成功了
        return true;
    }

    // 未知类型的节点
    return false;
}

bool ARegex::MatchNodeRepeated(const char* src, const ARegexNode& node, int& length)
{
    // 处理有且仅有一个，则直接调用MatchNode
    if (node.repeat == ARegexRepeatType::NRT_NONE || node.repeat == ARegexRepeatType::NRT_ONE)
        return MatchNode(src, node, length);

    // 处理有一个或者没有
    if (node.repeat == ARegexRepeatType::NRT_ONE_OR_NOT)
    {
        // 保存当前值
        int length_temp = length;
        // 如果匹配成功，那么就保存新的值
        if (MatchNode(src, node, length_temp))
            length = length_temp;
        // 不论成功失败，都认为是成功
        return true;
    }

    // 处理没有或者多个
    if (node.repeat == ARegexRepeatType::NRT_NOT_OR_MORE)
    {
        // 循环处理
        while (true)
        {
            // 保存当前值
            int length_temp = length;
            // 如果匹配成功，就保存新的值
            if (MatchNode(src, node, length_temp))
                length = length_temp;
            // 匹配失败就退出
            else
                break;
        }

        // 不论匹配了多少个，都认为是成功
        return true;
    }

    // 处理至少一个
    if (node.repeat == ARegexRepeatType::NRT_AT_LEAST_ONE)
    {
        // 处理匹配一个，如果失败了就认为是失败
        if (!MatchNode(src, node, length)) return false;

        // 循环处理
        while (true)
        {
            // 保存当前值
            int length_temp = length;
            // 如果匹配成功，就保存新的值
            if (MatchNode(src, node, length_temp))
                length = length_temp;
            // 匹配失败就退出
            else
                break;
        }

        // 否则就是成功
        return true;
    }

    // 未知类型就返回失败
    return false;
}

bool ARegex::CompileOption(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
    // 往当前节点添加一个NT_LIST
    node.childs.emplace_back(ARegexNode());
    auto* list = &node.childs.back();
    list->type = ARegexNodeType::NT_LIST;

    // 循环向后匹配
    while (offset < rule.size())
    {
        // 读取当前字符
        const char c = rule[offset];
        // 读取下一个字符
        char next_c = 0;
        if (offset + 1 < rule.size()) next_c = rule[offset + 1];
        
        // 遇到'['，说明接下来会是一个字符集合
        if (c == '[')
        {
            // 往list中添加一个NT_CHARSET
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_CHARSET;
            child.char_set_type = ARegexCharSetType::CST_CUSTOM;

            ++offset;
            // 开始解析字符集合
            if (!CompileCustomSet(rule, offset, child, error)) return false;
            ++offset;
        }
        else if (c == ']')
        {
            error = "error close char ] in option, offset:" + std::to_string(offset);
            return false;
        }
        // 遇到'{'，说明接下来会是一个字符串查找
        else if (c == '{')
        {
            // 往list中添加一个NT_FIND_STRING
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_FIND_STRING;

            ++offset;
            // 开始解析字符串查找
            if (!CompileFindString(rule, offset, child, error)) return false;
            ++offset;
        }
        else if (c == '}')
        {
            error = "error close char } in option, offset:" + std::to_string(offset);
            return false;
        }
        // 遇到'|'，说明接下来会出现一个同级的NT_LIST
        else if (c == '|')
        {
            // 往父节点添加一个NT_LIST，并把当前的list设置为新的NT_LIST
            node.childs.emplace_back(ARegexNode());
            list = &node.childs.back();
            list->type = ARegexNodeType::NT_LIST;

            ++offset;
        }
        // 遇到'!'，说明接下来会有一个取反操作
        else if (c == '!')
        {
            // 对于'!'操作必须操作于'()'
            if (next_c != '(')
            {
                error = "next char must be ( after !, offset:" + std::to_string(offset);
                return false;
            }
            ++offset;
        }
        // 遇到'('，说明接下来会有一个NT_OPTION
        else if (c == '(')
        {
            // 往list中添加一个NT_OPTION
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_OPTION;
            // 如果前面一个字符是'!'，说明是一个取反操作
            if (offset > 0 && rule[offset - 1] == '!')
                child.negate = ARegexNegateType::NNT_TRUE;

            ++offset;
            // 递归处理Option，把child作为Option的根节点
            if (!CompileOption(rule, offset, child, error)) return false;
            ++offset;
        }
        else if (c == ')')
        {
            return true;
        }
        // 遇到'%'，说明接下来是一个字符转义
        else if (c == '%')
        {
            // 特殊规则
            if (next_c == 'w' || next_c == 'a' || next_c == 'd')
            {
                // 往list添加一个NT_CHARSET
                list->childs.emplace_back(ARegexNode());
                ARegexNode& child = list->childs.back();
                child.type = ARegexNodeType::NT_CHARSET;
                if (next_c == 'w')
                    child.char_set_type = ARegexCharSetType::CST_W;
                else if (next_c == 'a')
                    child.char_set_type = ARegexCharSetType::CST_A;
                else if (next_c == 'd')
                    child.char_set_type = ARegexCharSetType::CST_D;
                else
                {
                    error = "error char after %, offset:" + std::to_string(offset);
                    return false;
                }
                ++offset;
            }
            // 否则只是字符转义
            else
            {
                // 往list添加一个NT_CHAR
                list->childs.emplace_back(ARegexNode());
                ARegexNode& child = list->childs.back();
                child.type = ARegexNodeType::NT_CHAR;

                // 处理特殊ascii的转义
                if (next_c == 'a') child.value = '\a';
                else if (next_c == 'b') child.value = '\b';
                else if (next_c == 'f') child.value = '\f';
                else if (next_c == 'n') child.value = '\n';
                else if (next_c == 'r') child.value = '\r';
                else if (next_c == 't') child.value = '\t';
                else if (next_c == 'v') child.value = '\v';
                else if (next_c != 0) child.value = next_c;
                else
                {
                    error = "error char after %, offset:" + std::to_string(offset);
                    return false;
                }
                ++offset;
            }

            ++offset;
        }
        // 遇到'.'，说明接下来是一个NT_CHARSET
        else if (c == '.')
        {
            // 往list添加一个NT_CHARSET
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_CHARSET;
            child.char_set_type = ARegexCharSetType::CST_DOT;

            ++offset;
        }
        // 剩下的就是普通字符了
        else
        {
            // 往list添加一个NT_CHAR
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_CHAR;
            child.value = c;

            ++offset;
        }

        // 读取当前list的重复规则
        if (list->childs.size() > 0 && offset < rule.size())
        {
            if (rule[offset] == '*') list->childs.back().repeat = ARegexRepeatType::NRT_NOT_OR_MORE;
            if (rule[offset] == '+') list->childs.back().repeat = ARegexRepeatType::NRT_AT_LEAST_ONE;
            if (rule[offset] == '?') list->childs.back().repeat = ARegexRepeatType::NRT_ONE_OR_NOT;

            if (list->childs.back().repeat != ARegexRepeatType::NRT_NONE)
                ++offset;
        }
    }

    // 如果最后一个子节点的规则是空的，那么就丢弃
    if (node.childs.size() > 0 && node.childs.back().childs.empty())
        node.childs.pop_back();

    // 如果当前的节点规则都是空的，那么就出错了
    if (node.childs.empty())
    {
        error += "empty group";
        return false;
    }
    return true;
}

bool ARegex::CompileCustomSet(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
    // 如果没有字符了就报错
    if (offset >= rule.size())
    {
        error = "custom set not complete";
        return false;
    }

    // 检查是否取反
    if (rule[offset] == '^')
    {
        node.negate = ARegexNegateType::NNT_TRUE;
        ++offset;
    }

    // 用于保存是否有句点
    bool has_dot = false;
    // 循环向后匹配
    while (offset < rule.size())
    {
        // 取出当前字符
        char c = rule[offset];
        // 取出下一个字符
        char next_c = 0;
        if (offset + 1 < rule.size()) next_c = rule[offset + 1];
        // 取出下下个字符
        char next_next_c = 0;
        if (offset + 2 < rule.size()) next_next_c = rule[offset + 2];
        // 内部不能出现'['，除非转义
        if (c == '[')
        {
            error = "custom set can't not nested custom set";
            return false;
        }
        // 内部不能出现'('，除非转义
        else if (c == '(')
        {
            error = "custom set can't not nested group";
            return false;
        }
        // 如果当前已经是']'，说明表示规则结束了
        else if (c == ']')
        {
            // 如果有句点，那么就要优化处理下
            if (has_dot)
            {
                // 如果又有句点，又有回车，那么就表示匹配所有字符
                // 否则匹配除了回车以外的所有字符
                if (node.char_set.find('\n') != node.char_set.end())
                    node.char_set_type = ARegexCharSetType::CST_ALL;
                else
                    node.char_set_type = ARegexCharSetType::CST_DOT;
                // 其他的字符集合可以清理掉了
                node.char_set.clear();
            }
            return true;
        }
        // 遇到'%'，说明接下来是一个字符转义
        else if (c == '%')
        {
            // 特殊的ascii码
            if (next_c == 'b') node.value += '\b';
            else if (next_c == 'f') node.value += '\f';
            else if (next_c == 'n') node.value += '\n';
            else if (next_c == 'r') node.value += '\r';
            else if (next_c == 't') node.value += '\t';
            else if (next_c == 'v') node.value += '\v';
            // 处理%w
            else if (next_c == 'w')
            {
                for (char i = '0'; i <= '9'; ++i)
                    node.char_set.insert(i);
                for (char i = 'a'; i <= 'z'; ++i)
                    node.char_set.insert(i);
                for (char i = 'A'; i <= 'Z'; ++i)
                    node.char_set.insert(i);
                node.char_set.insert('_');
            }
            // 处理%d
            else if (next_c == 'd')
            {
                for (char i = '0'; i <= '9'; ++i)
                    node.char_set.insert(i);
            }
            // 处理%a
            else if (next_c == 'a')
            {
                for (char i = 'a'; i <= 'z'; ++i)
                    node.char_set.insert(i);
                for (char i = 'A'; i <= 'Z'; ++i)
                    node.char_set.insert(i);
            }
            // 其他则直接纳入字符集
            else if (next_c != 0)
            {
                node.char_set.insert(next_c);
            }
            ++offset;
        }
        // 处理数字
        else if (c >= '0' && c <= '9')
        {
            // 如果遇到横线，并且下一个字符依然是数字，那么就是取数字范围
            if (next_c == '-' && next_next_c >= '0' && next_next_c <= '9')
            {
                for (char i = c; i <= next_next_c; ++i)
                    node.char_set.insert(i);
                offset += 2;
            }
            else
            {
                node.char_set.insert(c);
            }
        }
        // 处理小写字母
        else if (c >= 'a' && c <= 'z')
        {
            // 如果遇到横线，并且下一个字符依然是小写字母，那么就是取字母范围
            if (next_c == '-' && next_next_c >= 'a' && next_next_c <= 'z')
            {
                for (char i = c; i <= next_next_c; ++i)
                    node.char_set.insert(i);
                offset += 2;
            }
            else
            {
                node.char_set.insert(c);
            }
        }
        // 处理大写字母
        else if (c >= 'A' && c <= 'Z')
        {
            // 如果遇到横线，并且下一个字符依然是大写字母，那么就是取字母范围
            if (next_c == '-' && next_next_c >= 'A' && next_next_c <= 'Z')
            {
                for (char i = c; i <= next_next_c; ++i)
                    node.char_set.insert(i);
                offset += 2;
            }
            else
            {
                node.char_set.insert(c);
            }
        }
        // 处理句点
        else if (c == '.')
        {
            has_dot = true;
        }
        // 处理其他字符
        else
        {
            node.char_set.insert(c);
        }

        ++offset;
    }

    error = "custom set not complete";
    return false;
}

bool ARegex::CompileFindString(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
    // 如果没有字符了就报错
    if (offset >= rule.size())
    {
        error = "find string not complete";
        return false;
    }

    // 循环向后匹配
    while (offset < rule.size())
    {
        // 取出当前字符
        const char c = rule[offset];
        // 取出下一个字符
        char next_c = 0;
        if (offset + 1 < rule.size()) next_c = rule[offset + 1];
        
        // 查找字符串内部不能在出现'{'，要么就用%转义
        if (c == '{')
        {
            error = "find string can't not nested find string";
            return false;
        }
        // 遇到'}'，说明规则结束了
        else if (c == '}')
        {
            return true;
        }
        // 遇到'%'只会转义'}'
        else if (c == '%' && next_c == '}')
        {
            node.find.push_back(next_c);
            ++offset;
        }
        // 剩下的就是普通字符
        else
        {
            node.find.push_back(c);
        }

        ++offset;
    }

    error = "find string not complete";
    return false;
}
