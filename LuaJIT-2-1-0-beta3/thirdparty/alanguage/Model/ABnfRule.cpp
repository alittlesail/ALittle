
#include "ABnfRule.h"
#include "ABnfRuleInfo.h"
#include "ABnfRuleTokenInfo.h"
#include "ABnfRuleNodeInfo.h"

ABnfRule::ABnfRule()
{
}

ABnfRule::~ABnfRule()
{
    Clear();
}

// 初始化参数
void ABnfRule::Clear()
{
    m_buffer = "";
    for (auto& pair : m_rule_map) delete pair.second;
    m_rule_map.clear();
    m_key_set.clear();
    m_symbol_set.clear();
}

// 加载文法
bool ABnfRule::Load(const std::string& buffer, std::string& error)
{
    // 清理
    Clear();

    // 保存字符串内容
    m_buffer = buffer;

    // 解析token
    std::vector<ABnfRuleTokenInfo> token_list;
    CalcToken(token_list);

    // 对tokencol表进line语法分析
    size_t offset = 0;
    while (offset < token_list.size())
    {
        // 解析规则
        ABnfRuleInfo* rule = CalcABnfRule(token_list, offset, error);
        if (rule == nullptr)
        {
            Clear();
            return false;
        }

        // 检查是否重复
        auto it = m_rule_map.find(rule->id.value);
        if (it != m_rule_map.end())
        {
            std::string name = rule->id.value;
            delete rule;
            Clear();
            error = "rule name repeated:" + name;
            return false;
        }
        m_rule_map[rule->id.value] = rule;
    }

    for (auto& pair : m_rule_map)
        pair.second->CalcNextChar();

    return true;
}

// 根绝规则名称查找规则对象
ABnfRuleInfo* ABnfRule::FindRuleInfo(const std::string& id)
{
    auto it = m_rule_map.find(id);
    if (it == m_rule_map.end()) return nullptr;
    return it->second;
}

// 解析规则语句
ABnfRuleInfo* ABnfRule::CalcABnfRule(const std::vector<ABnfRuleTokenInfo>& token_list, size_t& offset, std::string& error)
{
    ABnfRuleInfo* rule = new ABnfRuleInfo(this);

    // 跳过注释
    while (offset < token_list.size() &&
        (token_list[offset].type == ABnfRuleTokenType::TT_LINE_COMMENT
            || token_list[offset].type == ABnfRuleTokenType::TT_BLOCK_COMMENT))
        ++offset;

    // 处理ID
    if (offset >= token_list.size())
    {
        if (rule != nullptr) delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }

    if (token_list[offset].type != ABnfRuleTokenType::TT_ID)
    {
        if (rule != nullptr) delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + " expect ID bug get:" + token_list[offset].value;
        return nullptr;
    }

    // 正则表达式匹配
    std::smatch result;
    static std::regex pattern("^[_a-zA-Z][_a-zA-Z0-9]*$");
    if (!std::regex_match(token_list[offset].value, result, pattern))
    {
        if (rule != nullptr) delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + "ID must be alpha, number, _, and not start with number, but get:" + token_list[offset].value;
        return nullptr;
    }

    rule->id = token_list[offset];
    ++offset;

    // 处理冒号
    if (offset >= token_list.size())
    {
        if (rule != nullptr) delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }

    if (token_list[offset].type == ABnfRuleTokenType::TT_SYMBOL && token_list[offset].value == ":")
    {
        ++offset;
        // 处理预测正则表达式
        if (offset >= token_list.size())
        {
            if (rule != nullptr) delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }
            
        if (token_list[offset].type != ABnfRuleTokenType::TT_REGEX)
        {
            if (rule != nullptr) delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect regex but get:" + token_list[offset].value;
            return nullptr;
        }

        rule->prediction = token_list[offset];
        ++offset;

        // 处理预测pin
        if (offset < token_list.size()
            && token_list[offset].type == ABnfRuleTokenType::TT_SYMBOL
            && token_list[offset].value == "@")
        {
            rule->prediction_pin = ABnfRuleNodePinType::NPT_TRUE;
            ++offset;
        }
    }

    // 处理等号
    if (offset >= token_list.size())
    {
        if (rule != nullptr) delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }
        
    if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL && token_list[offset].value != "=")
    {
        if (rule != nullptr) delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + " expect = but get:" + token_list[offset].value;
        return nullptr;
    }
    rule->assign = token_list[offset];
    ++offset;

    // 获取规则内容
    rule->node = CalcABnfNode(token_list, offset, error);
    if (rule->node == nullptr || rule->node->node_list.size() == 0)
    {
        if (rule != nullptr) delete rule;
        error = "line:" + std::to_string(rule->id.line) + "col:" + std::to_string(rule->id.col)
            + " node create failed:" + error;
        return nullptr;
    }

    // 如果遇到分号表示结束
    if (offset >= token_list.size())
    {
        if (rule != nullptr) delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }
        
    if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL || token_list[offset].value != ";")
    {
        if (rule != nullptr) delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + " expect; but get:" + token_list[offset].value;
        return rule;
    }
    ++offset;

    return rule;
}

ABnfRuleNodeInfo* ABnfRule::CalcABnfNode(const std::vector<ABnfRuleTokenInfo>& token_list, size_t& offset, std::string& error)
{
    auto node = new ABnfRuleNodeInfo();

    while (offset < token_list.size())
    {
        const ABnfRuleTokenInfo& token = token_list[offset];

        // 如果是注释，那么就跳过
        if (token.type == ABnfRuleTokenType::TT_LINE_COMMENT || token.type == ABnfRuleTokenType::TT_BLOCK_COMMENT)
        {
            ++offset;
            continue;
        }

        // 检查ID
        if (token.type == ABnfRuleTokenType::TT_ID)
        {
            // 正则表达式匹配
            std::smatch result;
            static std::regex pattern("^[_a-zA-Z][_a-zA-Z0-9]*$");
            if (!std::regex_match(token.value, result, pattern))
            {
                if (node != nullptr) delete node;
                error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                    + "ID must be alpha, number, _, and not start with number, but get:" + token.value;
                return nullptr;
            }

            if (node->node_list.size() == 0)
                node->node_list.push_back(std::vector<ABnfRuleNodeInfo*>());
            node->node_list[node->node_list.size() - 1].push_back(new ABnfRuleNodeInfo(token));

            ++offset;
            continue;
        }

        // 检查字符串
        if (token.type == ABnfRuleTokenType::TT_STRING
            || token.type == ABnfRuleTokenType::TT_KEY
            || token.type == ABnfRuleTokenType::TT_REGEX)
        {
            if (node->node_list.size() == 0)
                node->node_list.push_back(std::vector<ABnfRuleNodeInfo*>());
            node->node_list[node->node_list.size() - 1].push_back(new ABnfRuleNodeInfo(token));

            ++offset;
            continue;
        }

        // 最后检查符号
        if (token.type == ABnfRuleTokenType::TT_SYMBOL)
        {
            if (token.value == "(")
            {
                ++offset;

                if (node->node_list.size() == 0)
                    node->node_list.push_back(std::vector<ABnfRuleNodeInfo*>());
                auto sub_node = CalcABnfNode(token_list, offset, error);
                if (sub_node == nullptr)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " node create failed:" + error;
                    return nullptr;
                }
                node->node_list[node->node_list.size() - 1].push_back(sub_node);

                if (offset >= token_list.size() || token_list[offset].value != ")")
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " expect ), but get :" + token.value;
                    return nullptr;
                }

                ++offset;
                continue;
            }
            else if (token.value == "*")
            {
                if (node->node_list.size() == 0 || node->node_list[node->node_list.size() - 1].size() == 0)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col) + " is nothing before *";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->repeat != ABnfRuleNodeRepeatType::NRT_NONE)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " repeat * rule";
                    return nullptr;
                }

                node_list[node_list.size() - 1]->repeat = ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE;

                ++offset;
                continue;
            }
            else if (token.value == "+")
            {
                if (node->node_list.size() == 0 || node->node_list[node->node_list.size() - 1].size() == 0)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before +";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->repeat != ABnfRuleNodeRepeatType::NRT_NONE)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " repeat + rule";
                    return nullptr;
                }

                node_list[node_list.size() - 1]->repeat = ABnfRuleNodeRepeatType::NRT_AT_LEAST_ONE;

                ++offset;
                continue;
            }
            else if (token.value == "?")
            {
                if (node->node_list.size() == 0 || node->node_list[node->node_list.size() - 1].size() == 0)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before ?";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->repeat != ABnfRuleNodeRepeatType::NRT_NONE)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " repeat ? rule";
                    return nullptr;
                }

                node_list[node_list.size() - 1]->repeat = ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT;

                ++offset;
                continue;
            }
            else if (token.value == "@")
            {
                if (node->node_list.size() == 0 || node->node_list[node->node_list.size() - 1].size() == 0)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before @";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->pin != ABnfRuleNodePinType::NPT_NONE)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " repeat @ rule";
                    return nullptr;
                }

                node_list[node_list.size() - 1]->pin = ABnfRuleNodePinType::NPT_TRUE;

                ++offset;
                continue;
            }
            else if (token.value == "#")
            {
                if (node->node_list.size() == 0 || node->node_list[node->node_list.size() - 1].size() == 0)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before #";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->not_key != ABnfRuleNodeNotKeyType::NNKT_NONE)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " repeated # rule";
                    return nullptr;
                }

                node_list[node_list.size() - 1]->not_key = ABnfRuleNodeNotKeyType::NNKT_TRUE;

                ++offset;
                continue;
            }
            else if (token.value == "|")
            {
                if (node->node_list.size() == 0 || node->node_list[node->node_list.size() - 1].size() == 0)
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before |";
                    return nullptr;
                }


                if (offset + 1 >= token_list.size()
                    && token_list[offset + 1].type == ABnfRuleTokenType::TT_SYMBOL
                    && token_list[offset + 1].value == ";")
                {
                    if (node != nullptr) delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing behind |";
                    return nullptr;
                }

                node->node_list.push_back(std::vector<ABnfRuleNodeInfo*>());

                ++offset;
                continue;
            }
            else if (token.value == ";" || token.value == ")")
            {
                break;
            }
            else
            {
                if (node != nullptr) delete node;
                error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                    + " now can't handle:" + token.value;
                return nullptr;
            }
        }

        if (node != nullptr) delete node;
        error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
            + " unknow token type:" + token.value;
        return nullptr;
    }

    return node;
}

void ABnfRule::CalcToken(std::vector<ABnfRuleTokenInfo>& token_list)
{
    int line = 0;        // 当前line
    int col = 0;         // 当前col

    ABnfRuleTokenInfo token;

    size_t index = 0;
    while (index < m_buffer.size())
    {
        char c = m_buffer[index];
        char next_c = '\0';
        if (index + 1 < m_buffer.size())
            next_c = m_buffer[index + 1];

        // 计算linecol
        if (c == '\n')
        {
            ++line;
            col = 0;
        }
        else
        {
            ++col;
        }

        // 如果在当引号内部
        if (token.type == ABnfRuleTokenType::TT_STRING)
        {
            if (c == '\\')
            {
                if (next_c == '\\' || next_c == '\'') { token.value += next_c; ++index; ++col; }
                else if (next_c == 'a') { token.value += '\a'; ++index; ++col; }
                else if (next_c == 'b') { token.value += '\b'; ++index; ++col; }
                else if (next_c == 'f') { token.value += '\f'; ++index; ++col; }
                else if (next_c == 'n') { token.value += '\n'; ++index; ++col; }
                else if (next_c == 'r') { token.value += '\r'; ++index; ++col; }
                else if (next_c == 't') { token.value += '\t'; ++index; ++col; }
                else if (next_c == 'v') { token.value += '\v'; ++index; ++col; }
                else token.value += c;
            }
            else if (c == '\'')
            {
                // 收集符号
                m_symbol_set.insert(token.value);
                token_list.push_back(token);
                token = ABnfRuleTokenInfo();
            }
            else
            {
                token.value += c;
            }
        }
        else if (token.type == ABnfRuleTokenType::TT_KEY)
        {
            if (c == '\\')
            {
                if (next_c == '\\' || next_c == '>') { token.value += next_c; ++index; ++col; }
                else if (next_c == 'a') { token.value += '\a'; ++index; ++col; }
                else if (next_c == 'b') { token.value += '\b'; ++index; ++col; }
                else if (next_c == 'f') { token.value += '\f'; ++index; ++col; }
                else if (next_c == 'n') { token.value += '\n'; ++index; ++col; }
                else if (next_c == 'r') { token.value += '\r'; ++index; ++col; }
                else if (next_c == 't') { token.value += '\t'; ++index; ++col; }
                else if (next_c == 'v') { token.value += '\v'; ++index; ++col; }
                else token.value += c;
            }
            else if (c == '>')
            {
                // 收集关键字
                m_key_set.insert(token.value);
                token_list.push_back(token);
                token = ABnfRuleTokenInfo();
            }
            else
            {
                token.value += c;
            }
        }
        else if (token.type == ABnfRuleTokenType::TT_REGEX)
        {
            if (c == '\\')
            {
                if (next_c == '\\' || next_c == '"') { token.value += next_c; ++index; ++col; }
                else if (next_c == 'a') { token.value += '\a'; ++index; ++col; }
                else if (next_c == 'b') { token.value += '\b'; ++index; ++col; }
                else if (next_c == 'f') { token.value += '\f'; ++index; ++col; }
                else if (next_c == 'n') { token.value += '\n'; ++index; ++col; }
                else if (next_c == 'r') { token.value += '\r'; ++index; ++col; }
                else if (next_c == 't') { token.value += '\t'; ++index; ++col; }
                else if (next_c == 'v') { token.value += '\v'; ++index; ++col; }
                else token.value += c;
            }
            else if (c == '"')
            {
                token_list.push_back(token);
                token = ABnfRuleTokenInfo();
            }
            else
            {
                token.value += c;
            }
        }
        else if (token.type == ABnfRuleTokenType::TT_LINE_COMMENT)
        {
            if (c == '\r')
            {
                if (next_c == '\n')
                {
                    ++index;
                    ++line;
                    col = 0;
                    token_list.push_back(token);
                    token = ABnfRuleTokenInfo();
                }
                else
                {
                    token.value += c;
                }
            }
            else if (c == '\n')
            {
                token_list.push_back(token);
                token = ABnfRuleTokenInfo();
            }
            else
            {
                token.value += c;
            }
        }
        else if (token.type == ABnfRuleTokenType::TT_BLOCK_COMMENT)
        {
            if (c == '*')
            {
                if (next_c == '/')
                {
                    ++index;
                    ++col;
                    token_list.push_back(token);
                    token = ABnfRuleTokenInfo();
                }
                else
                {
                    token.value += c;
                }
            }
            else
            {
                token.value += c;
            }
        }
        else
        {
            if (c == '\'')
            {
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
                token = ABnfRuleTokenInfo();
                token.type = ABnfRuleTokenType::TT_STRING;
                token.line = line;
                token.col = col;
            }
            else if (c == '<')
            {
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
                token = ABnfRuleTokenInfo();
                token.type = ABnfRuleTokenType::TT_KEY;
                token.line = line;
                token.col = col;
            }
            else if (c == '"')
            {
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
                token = ABnfRuleTokenInfo();
                token.type = ABnfRuleTokenType::TT_REGEX;
                token.line = line;
                token.col = col;
            }
            else if (c == '/' && next_c == '/')
            {
                ++index;
                ++col;
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
                token = ABnfRuleTokenInfo();
                token.type = ABnfRuleTokenType::TT_LINE_COMMENT;
                token.line = line;
                token.col = col;
            }
            else if (c == '/' && next_c == '*')
            {
                ++index;
                ++col;
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
                token = ABnfRuleTokenInfo();
                token.type = ABnfRuleTokenType::TT_BLOCK_COMMENT;
                token.line = line;
                token.col = col;
            }
            else if (c == '=' || c == '@' || c == '#' || c == ':'
                || c == '*' || c == '?' || c == '+'
                || c == '|' || c == ';'
                || c == '(' || c == ')')
            {
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);

                token = ABnfRuleTokenInfo();
                token.type = ABnfRuleTokenType::TT_SYMBOL;
                token.value += c;
                token.line = line;
                token.col = col;
                token_list.push_back(token);

                token = ABnfRuleTokenInfo();
            }
            else if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
                token = ABnfRuleTokenInfo();
            }
            else
            {
                if (token.type == ABnfRuleTokenType::TT_NONE)
                {
                    token = ABnfRuleTokenInfo();
                    token.type = ABnfRuleTokenType::TT_ID;
                    token.line = line;
                    token.col = col;
                }
                token.value += c;
            }
        }

        ++index;
    }

    if (token.type != ABnfRuleTokenType::TT_NONE) token_list.push_back(token);
}