
#include "ARegex.h"

ARegex::ARegex(const std::string& rule) : m_rule(rule)
{
    // ��չ���������
    m_rule_error.clear();
    // ���ڵ���һ��OPTION
    size_t offset = 0;
    m_node.type = ARegexNodeType::NT_OPTION;
    // ��ʼ��������
    CompileOption(m_rule, offset, m_node, m_rule_error);
}

bool ARegex::Match(const char* src, int& length)
{
    // ��ʼ������Ϊ0
    length = 0;
    // ����repeated�ڵ�ƥ��
    return MatchNodeRepeated(src, m_node, length);
}

bool ARegex::MatchNode(const char* src, const ARegexNode& node, int& length)
{
    // ȡ����ǰ�ַ�
    const char c = src[length];
    // ����Ѿ�����β�ˣ���ô��ֱ�ӷ���
    if (c == 0) return false;

    // �������ַ�ƥ��
    if (node.type == ARegexNodeType::NT_CHAR)
    {
        // ����ַ���ȣ���ô������ƥ��ɹ�
        if (node.value == c)
        {
            ++length;
            return true;
        }
        // ����ƥ��ʧ��
        return false;
    }

    // ��������ַ���ƥ��
    if (node.type == ARegexNodeType::NT_FIND_STRING)
    {
        const auto* find = strstr(src + length, node.find.c_str());
        // ������ҵ���������ƥ��ɹ�
        if (find != nullptr)
        {
            length += static_cast<int>(find - src - length) + static_cast<int>(node.find.length());
            return true;
        }
        // ����ƥ��ʧ��
        return false;
    }

    // �����ַ�����ƥ��
    if (node.type == ARegexNodeType::NT_CHARSET)
    {
        bool check = false;
        // ȫƥ��
        if (node.char_set_type == ARegexCharSetType::CST_ALL)
        {
            check = true;
        }
        // �Զ���ƥ��
        else if (node.char_set_type == ARegexCharSetType::CST_CUSTOM)
        {
            check = node.char_set.find(c) != node.char_set.end();
        }
        // ��ĸƥ��
        else if (node.char_set_type == ARegexCharSetType::CST_A)
        {
            check = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
        }
        // ����ƥ��
        else if (node.char_set_type == ARegexCharSetType::CST_D)
        {
            check = c >= '0' && c <= '9';
        }
        // ��ĸ�����֣��»���ƥ��
        else if (node.char_set_type == ARegexCharSetType::CST_W)
        {
            check = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_';
        }
        // �ǻ��������ַ�ƥ��
        else if (node.char_set_type == ARegexCharSetType::CST_DOT)
        {
            check = c != '\n';
        }

        // ����ȡ��
        if (node.negate == ARegexNegateType::NNT_TRUE)
        {
            // �����ȡ��������checkʧ�ܣ���ô����Ϊ�ɹ�
            if (!check)
            {
                ++length;
                return true;
            }
        }
        else
        {
            // û��ȡ��������check�ɹ����ǳɹ�
            if (check)
            {
                ++length;
                return true;
            }
        }

        // �����ƥ��ʧ��
        return false;
    }

    // �����֧ƥ�䣬ֻҪĳ���ӽڵ�ƥ��ɹ����ǳɹ�
    if (node.type == ARegexNodeType::NT_OPTION)
    {
        // ���������ӽڵ�
        for (const auto& child : node.childs)
        {
            // ������ʱֵ��ÿ���ӽڵ㶼�Ǵ����λ�ÿ�ʼƥ��
            int length_temp = length;
            // ��ʼƥ��
            if (MatchNodeRepeated(src, child, length_temp))
            {
                // �����ȡ������ôֱ�ӷ���ʧ��
                if (node.negate == ARegexNegateType::NNT_TRUE)
                    return false;

                // ƥ��ɹ��ˣ���ֹͣʣ�µ��ӽڵ�ƥ�䣬���سɹ�
                length = length_temp;
                return true;
            }
        }

        // ִ�е����˵��ƥ��ʧ����

        // �����ȡ������ô�ͱ�ʾƥ��ɹ�
        if (node.negate == ARegexNegateType::NNT_TRUE)
        {
            ++length;
            return true;
        }

        // ���򷵻�ƥ��ʧ��
        return false;
    }

    // �����б�ƥ�䣬����ȫ���ɹ����ǳɹ�
    if (node.type == ARegexNodeType::NT_LIST)
    {
        // ���������ӽڵ�
        for (const auto& child : node.childs)
        {
            // ���ƥ��ʧ���ˣ�����ʧ����
            if (!MatchNodeRepeated(src, child, length))
                return false;
        }

        // ���ﲻ�ô���node.negate����Ϊ������ʽ�����ϣ�'!'���Ų��������ε���LIST

        // ִ�е��������ȫ���ɹ���
        return true;
    }

    // δ֪���͵Ľڵ�
    return false;
}

bool ARegex::MatchNodeRepeated(const char* src, const ARegexNode& node, int& length)
{
    // �������ҽ���һ������ֱ�ӵ���MatchNode
    if (node.repeat == ARegexRepeatType::NRT_NONE || node.repeat == ARegexRepeatType::NRT_ONE)
        return MatchNode(src, node, length);

    // ������һ������û��
    if (node.repeat == ARegexRepeatType::NRT_ONE_OR_NOT)
    {
        // ���浱ǰֵ
        int length_temp = length;
        // ���ƥ��ɹ�����ô�ͱ����µ�ֵ
        if (MatchNode(src, node, length_temp))
            length = length_temp;
        // ���۳ɹ�ʧ�ܣ�����Ϊ�ǳɹ�
        return true;
    }

    // ����û�л��߶��
    if (node.repeat == ARegexRepeatType::NRT_NOT_OR_MORE)
    {
        // ѭ������
        while (true)
        {
            // ���浱ǰֵ
            int length_temp = length;
            // ���ƥ��ɹ����ͱ����µ�ֵ
            if (MatchNode(src, node, length_temp))
                length = length_temp;
            // ƥ��ʧ�ܾ��˳�
            else
                break;
        }

        // ����ƥ���˶��ٸ�������Ϊ�ǳɹ�
        return true;
    }

    // ��������һ��
    if (node.repeat == ARegexRepeatType::NRT_AT_LEAST_ONE)
    {
        // ����ƥ��һ�������ʧ���˾���Ϊ��ʧ��
        if (!MatchNode(src, node, length)) return false;

        // ѭ������
        while (true)
        {
            // ���浱ǰֵ
            int length_temp = length;
            // ���ƥ��ɹ����ͱ����µ�ֵ
            if (MatchNode(src, node, length_temp))
                length = length_temp;
            // ƥ��ʧ�ܾ��˳�
            else
                break;
        }

        // ������ǳɹ�
        return true;
    }

    // δ֪���;ͷ���ʧ��
    return false;
}

bool ARegex::CompileOption(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
    // ����ǰ�ڵ����һ��NT_LIST
    node.childs.emplace_back(ARegexNode());
    auto* list = &node.childs.back();
    list->type = ARegexNodeType::NT_LIST;

    // ѭ�����ƥ��
    while (offset < rule.size())
    {
        // ��ȡ��ǰ�ַ�
        const char c = rule[offset];
        // ��ȡ��һ���ַ�
        char next_c = 0;
        if (offset + 1 < rule.size()) next_c = rule[offset + 1];
        
        // ����'['��˵������������һ���ַ�����
        if (c == '[')
        {
            // ��list�����һ��NT_CHARSET
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_CHARSET;
            child.char_set_type = ARegexCharSetType::CST_CUSTOM;

            ++offset;
            // ��ʼ�����ַ�����
            if (!CompileCustomSet(rule, offset, child, error)) return false;
            ++offset;
        }
        else if (c == ']')
        {
            error = "error close char ] in option, offset:" + std::to_string(offset);
            return false;
        }
        // ����'{'��˵������������һ���ַ�������
        else if (c == '{')
        {
            // ��list�����һ��NT_FIND_STRING
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_FIND_STRING;

            ++offset;
            // ��ʼ�����ַ�������
            if (!CompileFindString(rule, offset, child, error)) return false;
            ++offset;
        }
        else if (c == '}')
        {
            error = "error close char } in option, offset:" + std::to_string(offset);
            return false;
        }
        // ����'|'��˵�������������һ��ͬ����NT_LIST
        else if (c == '|')
        {
            // �����ڵ����һ��NT_LIST�����ѵ�ǰ��list����Ϊ�µ�NT_LIST
            node.childs.emplace_back(ARegexNode());
            list = &node.childs.back();
            list->type = ARegexNodeType::NT_LIST;

            ++offset;
        }
        // ����'!'��˵������������һ��ȡ������
        else if (c == '!')
        {
            // ����'!'�������������'()'
            if (next_c != '(')
            {
                error = "next char must be ( after !, offset:" + std::to_string(offset);
                return false;
            }
            ++offset;
        }
        // ����'('��˵������������һ��NT_OPTION
        else if (c == '(')
        {
            // ��list�����һ��NT_OPTION
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_OPTION;
            // ���ǰ��һ���ַ���'!'��˵����һ��ȡ������
            if (offset > 0 && rule[offset - 1] == '!')
                child.negate = ARegexNegateType::NNT_TRUE;

            ++offset;
            // �ݹ鴦��Option����child��ΪOption�ĸ��ڵ�
            if (!CompileOption(rule, offset, child, error)) return false;
            ++offset;
        }
        else if (c == ')')
        {
            return true;
        }
        // ����'%'��˵����������һ���ַ�ת��
        else if (c == '%')
        {
            // �������
            if (next_c == 'w' || next_c == 'a' || next_c == 'd')
            {
                // ��list���һ��NT_CHARSET
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
            // ����ֻ���ַ�ת��
            else
            {
                // ��list���һ��NT_CHAR
                list->childs.emplace_back(ARegexNode());
                ARegexNode& child = list->childs.back();
                child.type = ARegexNodeType::NT_CHAR;

                // ��������ascii��ת��
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
        // ����'.'��˵����������һ��NT_CHARSET
        else if (c == '.')
        {
            // ��list���һ��NT_CHARSET
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_CHARSET;
            child.char_set_type = ARegexCharSetType::CST_DOT;

            ++offset;
        }
        // ʣ�µľ�����ͨ�ַ���
        else
        {
            // ��list���һ��NT_CHAR
            list->childs.emplace_back(ARegexNode());
            ARegexNode& child = list->childs.back();
            child.type = ARegexNodeType::NT_CHAR;
            child.value = c;

            ++offset;
        }

        // ��ȡ��ǰlist���ظ�����
        if (list->childs.size() > 0 && offset < rule.size())
        {
            if (rule[offset] == '*') list->childs.back().repeat = ARegexRepeatType::NRT_NOT_OR_MORE;
            if (rule[offset] == '+') list->childs.back().repeat = ARegexRepeatType::NRT_AT_LEAST_ONE;
            if (rule[offset] == '?') list->childs.back().repeat = ARegexRepeatType::NRT_ONE_OR_NOT;

            if (list->childs.back().repeat != ARegexRepeatType::NRT_NONE)
                ++offset;
        }
    }

    // ������һ���ӽڵ�Ĺ����ǿյģ���ô�Ͷ���
    if (node.childs.size() > 0 && node.childs.back().childs.empty())
        node.childs.pop_back();

    // �����ǰ�Ľڵ�����ǿյģ���ô�ͳ�����
    if (node.childs.empty())
    {
        error += "empty group";
        return false;
    }
    return true;
}

bool ARegex::CompileCustomSet(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
    // ���û���ַ��˾ͱ���
    if (offset >= rule.size())
    {
        error = "custom set not complete";
        return false;
    }

    // ����Ƿ�ȡ��
    if (rule[offset] == '^')
    {
        node.negate = ARegexNegateType::NNT_TRUE;
        ++offset;
    }

    // ���ڱ����Ƿ��о��
    bool has_dot = false;
    // ѭ�����ƥ��
    while (offset < rule.size())
    {
        // ȡ����ǰ�ַ�
        char c = rule[offset];
        // ȡ����һ���ַ�
        char next_c = 0;
        if (offset + 1 < rule.size()) next_c = rule[offset + 1];
        // ȡ�����¸��ַ�
        char next_next_c = 0;
        if (offset + 2 < rule.size()) next_next_c = rule[offset + 2];
        // �ڲ����ܳ���'['������ת��
        if (c == '[')
        {
            error = "custom set can't not nested custom set";
            return false;
        }
        // �ڲ����ܳ���'('������ת��
        else if (c == '(')
        {
            error = "custom set can't not nested group";
            return false;
        }
        // �����ǰ�Ѿ���']'��˵����ʾ���������
        else if (c == ']')
        {
            // ����о�㣬��ô��Ҫ�Ż�������
            if (has_dot)
            {
                // ������о�㣬���лس�����ô�ͱ�ʾƥ�������ַ�
                // ����ƥ����˻س�����������ַ�
                if (node.char_set.find('\n') != node.char_set.end())
                    node.char_set_type = ARegexCharSetType::CST_ALL;
                else
                    node.char_set_type = ARegexCharSetType::CST_DOT;
                // �������ַ����Ͽ����������
                node.char_set.clear();
            }
            return true;
        }
        // ����'%'��˵����������һ���ַ�ת��
        else if (c == '%')
        {
            // �����ascii��
            if (next_c == 'b') node.value += '\b';
            else if (next_c == 'f') node.value += '\f';
            else if (next_c == 'n') node.value += '\n';
            else if (next_c == 'r') node.value += '\r';
            else if (next_c == 't') node.value += '\t';
            else if (next_c == 'v') node.value += '\v';
            // ����%w
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
            // ����%d
            else if (next_c == 'd')
            {
                for (char i = '0'; i <= '9'; ++i)
                    node.char_set.insert(i);
            }
            // ����%a
            else if (next_c == 'a')
            {
                for (char i = 'a'; i <= 'z'; ++i)
                    node.char_set.insert(i);
                for (char i = 'A'; i <= 'Z'; ++i)
                    node.char_set.insert(i);
            }
            // ������ֱ�������ַ���
            else if (next_c != 0)
            {
                node.char_set.insert(next_c);
            }
            ++offset;
        }
        // ��������
        else if (c >= '0' && c <= '9')
        {
            // ����������ߣ�������һ���ַ���Ȼ�����֣���ô����ȡ���ַ�Χ
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
        // ����Сд��ĸ
        else if (c >= 'a' && c <= 'z')
        {
            // ����������ߣ�������һ���ַ���Ȼ��Сд��ĸ����ô����ȡ��ĸ��Χ
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
        // �����д��ĸ
        else if (c >= 'A' && c <= 'Z')
        {
            // ����������ߣ�������һ���ַ���Ȼ�Ǵ�д��ĸ����ô����ȡ��ĸ��Χ
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
        // ������
        else if (c == '.')
        {
            has_dot = true;
        }
        // ���������ַ�
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
    // ���û���ַ��˾ͱ���
    if (offset >= rule.size())
    {
        error = "find string not complete";
        return false;
    }

    // ѭ�����ƥ��
    while (offset < rule.size())
    {
        // ȡ����ǰ�ַ�
        const char c = rule[offset];
        // ȡ����һ���ַ�
        char next_c = 0;
        if (offset + 1 < rule.size()) next_c = rule[offset + 1];
        
        // �����ַ����ڲ������ڳ���'{'��Ҫô����%ת��
        if (c == '{')
        {
            error = "find string can't not nested find string";
            return false;
        }
        // ����'}'��˵�����������
        else if (c == '}')
        {
            return true;
        }
        // ����'%'ֻ��ת��'}'
        else if (c == '%' && next_c == '}')
        {
            node.find.push_back(next_c);
            ++offset;
        }
        // ʣ�µľ�����ͨ�ַ�
        else
        {
            node.find.push_back(c);
        }

        ++offset;
    }

    error = "find string not complete";
    return false;
}
