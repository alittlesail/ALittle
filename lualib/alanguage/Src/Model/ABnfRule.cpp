
#include "ABnfRule.h"
#include "ABnfRuleInfo.h"
#include "ABnfRuleTokenInfo.h"
#include "ABnfRuleNodeInfo.h"
#include "ARegex.h"

// ��ʼ������
void ABnfRule::Clear()
{
    m_buffer = "";
    for (auto& pair : m_rule_map) delete pair.second;
    m_rule_map.clear();
    m_key_set.clear();
    m_symbol_set.clear();
}

// �����ķ�
bool ABnfRule::Load(const std::string& buffer, std::string& error)
{
    // ����
    Clear();

    // �����ַ�������
    m_buffer = buffer;

    // ����token
    std::vector<ABnfRuleTokenInfo> token_list;
    CalcToken(token_list);

    int rule_id = 0;
    // ��token col���line�﷨����
    size_t offset = 0;
    while (offset < token_list.size())
    {
        ++rule_id;
        // ��������
        ABnfRuleInfo* rule = CalcABnfRule(token_list, rule_id, offset, error);
        if (rule == nullptr)
        {
            Clear();
            return false;
        }

        // ����Ƿ��ظ�
        auto it = m_rule_map.find(rule->id.value);
        if (it != m_rule_map.end())
        {
            const std::string name = rule->id.value;
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

// �����������Ʋ��ҹ������
ABnfRuleInfo* ABnfRule::FindRuleInfo(const std::string& id)
{
    const auto it = m_rule_map.find(id);
    if (it == m_rule_map.end()) return nullptr;
    return it->second;
}

const std::unordered_map<std::string, ABnfRuleInfo*>& ABnfRule::GetRuleSet() const
{
    return m_rule_map;
}

// �����������
ABnfRuleInfo* ABnfRule::CalcABnfRule(const std::vector<ABnfRuleTokenInfo>& token_list, int rule_id, size_t& offset, std::string& error)
{
	auto* rule = new ABnfRuleInfo(this);

    rule->rule_id = rule_id;

    // ����ע��
    while (offset < token_list.size() &&
        (token_list[offset].type == ABnfRuleTokenType::TT_LINE_COMMENT
            || token_list[offset].type == ABnfRuleTokenType::TT_BLOCK_COMMENT))
        ++offset;

    // ����ID
    if (offset >= token_list.size())
    {
        delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }

    if (token_list[offset].type != ABnfRuleTokenType::TT_ID)
    {
        delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + " expect ID bug get:" + token_list[offset].value;
        return nullptr;
    }

    // ������ʽƥ��
    int result_length;
    static ARegex pattern("[_a-zA-Z][_a-zA-Z0-9]*");
    if (!pattern.Match(token_list[offset].value.c_str(), result_length))
    {
        delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + "ID must be alpha, number, _, and not start with number, but get:" + token_list[offset].value;
        return nullptr;
    }

    rule->id = token_list[offset];
    ++offset;

    // ����ð��
    if (offset >= token_list.size())
    {
        delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }

    if (token_list[offset].type == ABnfRuleTokenType::TT_SYMBOL && token_list[offset].value == ":")
    {
        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }
            
        if (token_list[offset].type != ABnfRuleTokenType::TT_REGEX)
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect regex but get:" + token_list[offset].value;
            return nullptr;
        }

        rule->prediction = token_list[offset];
        ++offset;

        // ����Ԥ��pin
        if (offset < token_list.size()
            && token_list[offset].type == ABnfRuleTokenType::TT_SYMBOL
            && token_list[offset].value == "@")
        {
            rule->prediction_pin = ABnfRuleNodePinType::NPT_TRUE;
            ++offset;
        }
    }

    if (offset >= token_list.size())
    {
        delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }

    // ������ɫ���
    if (token_list[offset].type == ABnfRuleTokenType::TT_SYMBOL && token_list[offset].value == "[")
    {
        rule->has_color = true;

        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }

        // red
        if (token_list[offset].type != ABnfRuleTokenType::TT_ID)
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect number of red but get:" + token_list[offset].value;
            return nullptr;
        }
        rule->red = std::atoi(token_list[offset].value.c_str());  // NOLINT(cert-err34-c)

        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }

        // ,
        if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL || token_list[offset].value != ",")
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect , but get:" + token_list[offset].value;
            return nullptr;
        }

        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }

        // green
        if (token_list[offset].type != ABnfRuleTokenType::TT_ID)
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect number of green but get:" + token_list[offset].value;
            return nullptr;
        }
        rule->green = std::atoi(token_list[offset].value.c_str());  // NOLINT(cert-err34-c)

        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }

        // ,
        if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL || token_list[offset].value != ",")
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect , but get:" + token_list[offset].value;
            return nullptr;
        }

        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }

        // blue
        if (token_list[offset].type != ABnfRuleTokenType::TT_ID)
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect number of blue but get:" + token_list[offset].value;
            return nullptr;
        }
        rule->blue = std::atoi(token_list[offset].value.c_str());  // NOLINT(cert-err34-c)

        ++offset;
        // ����Ԥ��������ʽ
        if (offset >= token_list.size())
        {
            delete rule;
            error = "the last rule is incomplete";
            return nullptr;
        }

        // ]
        if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL || token_list[offset].value != "]")
        {
            delete rule;
            error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
                + " expect ] but get:" + token_list[offset].value;
            return nullptr;
        }

        ++offset;
    }

    // ����Ⱥ�
    if (offset >= token_list.size())
    {
        delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }
        
    if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL && token_list[offset].value != "=")
    {
        delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + " expect = but get:" + token_list[offset].value;
        return nullptr;
    }
    rule->assign = token_list[offset];
    ++offset;

    // ��ȡ��������
    rule->node = CalcABnfNode(token_list, offset, error);
    if (rule->node == nullptr || rule->node->node_list.empty())
    {
        delete rule;
        error = "line:" + std::to_string(rule->id.line) + "col:" + std::to_string(token_list[offset].col)
            + " node create failed:" + error;
        return nullptr;
    }

    // ��������ֺű�ʾ����
    if (offset >= token_list.size())
    {
        delete rule;
        error = "the last rule is incomplete";
        return nullptr;
    }
        
    if (token_list[offset].type != ABnfRuleTokenType::TT_SYMBOL || token_list[offset].value != ";")
    {
        delete rule;
        error = "line:" + std::to_string(token_list[offset].line) + "col:" + std::to_string(token_list[offset].col)
            + " expect; but get:" + token_list[offset].value;
        return nullptr;
    }
    ++offset;

    return rule;
}

ABnfRuleNodeInfo* ABnfRule::CalcABnfNode(const std::vector<ABnfRuleTokenInfo>& token_list, size_t& offset, std::string& error) const
{
    auto* node = new ABnfRuleNodeInfo();

    while (offset < token_list.size())
    {
        const ABnfRuleTokenInfo& token = token_list[offset];

        // �����ע�ͣ���ô������
        if (token.type == ABnfRuleTokenType::TT_LINE_COMMENT || token.type == ABnfRuleTokenType::TT_BLOCK_COMMENT)
        {
            ++offset;
            continue;
        }

        // ���ID
        if (token.type == ABnfRuleTokenType::TT_ID)
        {
            // ������ʽƥ��
            int result_length = 0;
            static ARegex pattern("[_a-zA-Z][_a-zA-Z0-9]*");
            if (!pattern.Match(token.value.c_str(), result_length))
            {
                delete node;
                error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                    + "ID must be alpha, number, _, and not start with number, but get:" + token.value;
                return nullptr;
            }

            if (node->node_list.empty())
                node->node_list.emplace_back(std::vector<ABnfRuleNodeInfo*>());
            node->node_list[node->node_list.size() - 1].push_back(new ABnfRuleNodeInfo(token));

            ++offset;
            continue;
        }

        // ����ַ���
        if (token.type == ABnfRuleTokenType::TT_STRING
            || token.type == ABnfRuleTokenType::TT_KEY
            || token.type == ABnfRuleTokenType::TT_REGEX)
        {
            if (node->node_list.empty())
                node->node_list.emplace_back(std::vector<ABnfRuleNodeInfo*>());
            node->node_list[node->node_list.size() - 1].push_back(new ABnfRuleNodeInfo(token));

            ++offset;
            continue;
        }

        // ��������
        if (token.type == ABnfRuleTokenType::TT_SYMBOL)
        {
            if (token.value == "(")
            {
                ++offset;

                if (node->node_list.empty())
                    node->node_list.emplace_back(std::vector<ABnfRuleNodeInfo*>());
                const auto sub_node = CalcABnfNode(token_list, offset, error);
                if (sub_node == nullptr)
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " node create failed:" + error;
                    return nullptr;
                }
                node->node_list[node->node_list.size() - 1].push_back(sub_node);

                if (offset >= token_list.size() || token_list[offset].value != ")")
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " expect ), but get :" + token.value;
                    return nullptr;
                }

                ++offset;
                continue;
            }
            else if (token.value == "*")
            {
                if (node->node_list.empty() || node->node_list[node->node_list.size() - 1].empty())
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col) + " is nothing before *";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->repeat != ABnfRuleNodeRepeatType::NRT_NONE)
                {
                    delete node;
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
                if (node->node_list.empty() || node->node_list[node->node_list.size() - 1].empty())
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before +";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->repeat != ABnfRuleNodeRepeatType::NRT_NONE)
                {
                    delete node;
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
                if (node->node_list.empty() || node->node_list[node->node_list.size() - 1].empty())
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before ?";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->repeat != ABnfRuleNodeRepeatType::NRT_NONE)
                {
                    delete node;
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
                if (node->node_list.empty() || node->node_list[node->node_list.size() - 1].empty())
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before @";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->pin != ABnfRuleNodePinType::NPT_NONE)
                {
                    delete node;
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
                if (node->node_list.empty() || node->node_list[node->node_list.size() - 1].empty())
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before #";
                    return nullptr;
                }

                auto& node_list = node->node_list[node->node_list.size() - 1];
                if (node_list[node_list.size() - 1]->not_key != ABnfRuleNodeNotKeyType::NNKT_NONE)
                {
                    delete node;
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
                if (node->node_list.empty() || node->node_list[node->node_list.size() - 1].empty())
                {
                    delete node;
                    error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                        + " is nothing before |";
                    return nullptr;
                }


                if (offset + 1 >= token_list.size()
                    && token_list[offset + 1].type == ABnfRuleTokenType::TT_SYMBOL
                    && token_list[offset + 1].value == ";")
                {
                    delete node;
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
				delete node;
                error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
                    + " now can't handle:" + token.value;
                return nullptr;
            }
        }

        delete node;
        error = "line:" + std::to_string(token.line) + "col:" + std::to_string(token.col)
            + " unknown token type:" + token.value;
        return nullptr;
    }

    return node;
}

void ABnfRule::CalcToken(std::vector<ABnfRuleTokenInfo>& token_list)
{
    int line = 0;        // ��ǰline
    int col = 0;         // ��ǰcol

    ABnfRuleTokenInfo token;

    size_t index = 0;
    while (index < m_buffer.size())
    {
        char c = m_buffer[index];
        char next_c = '\0';
        if (index + 1 < m_buffer.size())
            next_c = m_buffer[index + 1];

        // ����line col
        if (c == '\n')
        {
            ++line;
            col = 0;
        }
        else
        {
            ++col;
        }

        // ����ڵ������ڲ�
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
                // �ռ�����
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
                // �ռ��ؼ���
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
                || c == '|' || c == ';' || c == ','
                || c == '(' || c == ')'
                || c == '[' || c == ']')
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