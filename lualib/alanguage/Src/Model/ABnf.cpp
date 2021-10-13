#include "ABnf.h"
#include "ABnfRuleInfo.h"
#include "ABnfRuleNodeInfo.h"
#include "ABnfNodeElement.h"
#include "ABnfKeyElement.h"
#include "ABnfStringElement.h"
#include "ABnfRegexElement.h"
#include "ABnfErrorElement.h"

#include "alanguage/Src/Index/ABnfFile.h"
#include "alanguage/Src/Index/ABnfFactory.h"

// ��ʼ������
void ABnf::Clear()
{
    m_file = nullptr;
    m_factory = nullptr;
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();
    m_root = nullptr;
    m_line_comment = nullptr;
    m_block_comment = nullptr;
    m_rule.Clear();
    m_symbol_check.clear();
}

// �����ķ�
bool ABnf::Load(const std::string& buffer, ABnfFactory* factory, std::string& error)
{
    // ����
    Clear();

    // ���ýڵ㹤��������ָ�벻��Ϊ��
    m_factory = factory;
    if (m_factory == nullptr)
    {
        Clear();
        error = "m_factory == null";
        return false;
    }

    // ���������ķ�
    if (!m_rule.Load(buffer, error))
    {
        Clear();
        return false;
    }

    // ��ȡ������
    m_root = m_rule.FindRuleInfo("Root");
    // ��ȡ����ע��
    m_line_comment = m_rule.FindRuleInfo("LineComment");
    // ��ȡ����ע��
    m_block_comment = m_rule.FindRuleInfo("BlockComment");

    // �ռ����ż�飬�ڴ�������+=ʱ�������Ϊ+=��������+��=��
    const auto& symbol_set = m_rule.GetSymbolSet();
    for (const auto& symbol : symbol_set)
    {
        for (const auto& symbol_check : symbol_set)
        {
            if (symbol_check.find(symbol) == 0 && symbol_check.size() > symbol.size())
                m_symbol_check[symbol].insert(symbol_check[symbol.size()]);
        }
    }

    return true;
}

// ��ȡ������Ϣ
ABnfRuleInfo* ABnf::GetRule(const std::string& name)
{
    return m_rule.FindRuleInfo(name);
}

const std::unordered_set<std::string>& ABnf::GetKeySet() const
{
    return m_rule.GetKeySet();
}

const std::unordered_map<std::string, ABnfRuleInfo*>& ABnf::GetRuleSet() const
{
    return m_rule.GetRuleSet();
}

// ��ѯ�ؼ���
void ABnf::QueryKeyWordCompletion(const std::string& input, std::vector<ALanguageCompletionInfo>& list) const
{
    for (const auto& key : m_rule.GetKeySet())
    {
        if (key.find(input) == 0)
        {
            ALanguageCompletionInfo info;
            info.display = key;
            list.push_back(info);
        }
    }
}

// �����﷨�ڵ�
ABnfNodeElementPtr ABnf::CreateNodeElement(int line, int col, int offset, const std::string& type) const
{
    auto node = m_factory->CreateNodeElement(m_file, line, col, offset, type);
    if (node == nullptr) node = std::make_shared<ABnfNodeElement>(m_factory, m_file, line, col, offset, type);
    return node;
}

// �����ؼ��ֽڵ�
ABnfKeyElementPtr ABnf::CreateKeyElement(int line, int col, int offset, const std::string& value) const
{
    auto node = m_factory->CreateKeyElement(m_file, line, col, offset, value);
    if (node == nullptr) node = std::make_shared<ABnfKeyElement>(m_factory, m_file, line, col, offset, value);
    return node;
}

// �������Žڵ�
ABnfStringElementPtr ABnf::CreateStringElement(int line, int col, int offset, const std::string& value) const
{
    auto node = m_factory->CreateStringElement(m_file, line, col, offset, value);
    if (node == nullptr) node = std::make_shared<ABnfStringElement>(m_factory, m_file, line, col, offset, value);
    return node;
}

// ����������ʽ�ڵ�
ABnfRegexElementPtr ABnf::CreateRegexElement(int line, int col, int offset, const std::string& value, const std::shared_ptr<ARegex>& regex) const
{
    auto node = m_factory->CreateRegexElement(m_file, line, col, offset, value, regex);
    if (node == nullptr) node = std::make_shared<ABnfRegexElement>(m_factory, m_file, line, col, offset, value, regex);
    return node;
}

// ��ʼ�����ļ�
ABnfNodeElementPtr ABnf::Analysis(ABnfFile* file)
{
    if (m_root == nullptr) return nullptr;

    // ��ջ���
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();

    // �����ַ���
    m_file = file;

    // ��ʼ��λ��
    int line = 0;
    int col = 0;
    int offset = 0;
    int pin_offset = -1;
    const bool not_key = false;
    m_stop_stack.clear();

    // �������ڵ�
    auto node = CreateNodeElement(line, col, offset, m_root->id.value);

    // �����ָ���
    AnalysisSkip(line, col, offset);
    // ����ע��
    AnalysisABnfCommentMatch(m_root, node, not_key, line, col, offset);
    // �����ָ���
    AnalysisSkip(line, col, offset);

    // ��������ļ�β������ô����������
    if (offset < m_file->GetLength())
    {
        // ��ʼ����
        while (true)
        {
            // ���ݸ��ڵ���ķ���ʼ�����ı�
            if (!AnalysisABnfNode(m_root, m_root->node, node, not_key
                , line, col, offset, pin_offset, false))
            {
                // ���offset���ļ�β������ô��ǰ��һ���ַ����������ڴ�������ڵ�
                if (offset >= m_file->GetLength() && m_file->GetLength() > 0)
                    --offset;
            }
            else
            {
                // �����ָ��ַ�
                AnalysisSkip(line, col, offset);

                // ��������ļ�β������ô����������
                if (offset >= m_file->GetLength()) break;
            }

            // ��offset��Ϊ����ڵ�λ��
            node->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "syntax error", nullptr));

            // ������һ�У�Ȼ���������
            if (!JumpToNextLine(line, col, offset)) break;
        }
    }

    // ��ջ���
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();
    m_stop_stack.clear();
    m_file = nullptr;

    // ���ؽ��
    return node;
}

// �����������
bool ABnf::AnalysisABnfNode(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent
    , bool not_key, int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // ���� �����ҽ���һ����
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_NONE || node->repeat == ABnfRuleNodeRepeatType::NRT_ONE)
    {
        // ƥ���һ��
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, ignore_error))
        {
            // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
            if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

            // ����ƥ��ʧ��
            return false;
        }

        // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // ����ƥ��ɹ�
        return true;
    }

    // ���� ������һ����
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_AT_LEAST_ONE)
    {
        // ƥ���һ��
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, ignore_error))
        {
            // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
            if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

            // ����ƥ��ʧ��
            return false;
        }

        // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // ƥ��ʣ�µģ����Դ�����ƥ�䵽�����ƥ�䵽����
        return AnalysisABnfNodeMore(rule, node, parent, not_key
            , line, col, offset
            , pin_offset, true);
    }

    // ���� ��û�л���һ����
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT)
    {
        // ���Դ��������ƥ�䵽��ƥ�䣬���ƥ�䲻��������
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, true))
        {
            // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
            // ������Ϊƥ��ʧ��
            if (temp_pin_offset >= 0)
            {
                pin_offset = temp_pin_offset;
                return false;
            }

            // �ڲ�û��pin�����Ա��Ϊ��ǰƥ��ɹ�������ʧ�ܵĲ���
            return true;
        }

        // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // ����ƥ��ɹ�
        return true;
    }

    // ���� ��û�л�����������
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE)
    {
        // ���Դ�����ƥ����پ�ƥ�����
        return AnalysisABnfNodeMore(rule, node, parent, not_key
            , line, col, offset
            , pin_offset, true);
    }

    // ����һ�㲻�ᷢ��
    return false;
}

// ���ƥ��
bool ABnf::AnalysisABnfNodeMore(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent
    , bool not_key, int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // ѭ������
    while (offset < m_file->GetLength())
    {
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, ignore_error))
        {
            // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
            // ������Ϊƥ��ʧ��
            if (temp_pin_offset >= 0)
            {
                // ��������ʹ��offset��Ϊpin
                pin_offset = offset;
                return false;
            }

            // �ڲ�û��pin�����Ա��Ϊ��ǰƥ��ɹ�������ʧ�ܵĲ���
            return true;
        }

        // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // ����ע��
        AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
        // �����ָ��ַ�
        AnalysisSkip(line, col, offset);
    }

    return true;
}

// ����ƥ��
bool ABnf::AnalysisABnfRuleMatch(ABnfRuleInfo* rule, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // �����ָ��ַ�
    AnalysisSkip(line, col, offset);
    // ����ע��
    AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
    // �����ָ��ַ�
    AnalysisSkip(line, col, offset);

    // ����ļ��Ѿ���������ô����ƥ��ʧ��
    if (offset >= m_file->GetLength()) return false;
    // �����һ���ַ�
    const char next_char = m_file->GetText()[offset];
    // �����һ���ַ��Ƿ���Ԥ�ⷶΧ��
    const auto* index_list = rule->CheckNextChar(next_char);
    if (!index_list) return false;

    ABnfNodeElementPtr stop_token_element;
    // ����ѡ�����
    std::vector<ABnfNodeElementPtr> option_list;
    for (auto option_index : *index_list)
    {
        // ǿ����Ԥ���
        if (!rule->node->PreCheck(m_file->GetText(), offset)) continue;
        // ��ȡ��ǰ�ڵ����
        auto& node_list = rule->node->node_list[option_index];

        // ����λ�ã����ڶ���ƥ��
        int temp_line = line;
        int temp_col = col;
        int temp_offset = offset;

        // ��ǵ�ǰ�����Ƿ���pin
        int temp_pin_offset = -1;
        // �Ƿ�ƥ��ɹ�
        bool match = true;
        // ��ʼ�����������
        ABnfNodeElementPtr element = CreateNodeElement(line, col, offset, rule->id.value);
        for (auto& node : node_list)
        {
            int sub_pin_offset = -1;
            if (!AnalysisABnfNode(rule, node, element, not_key
                , temp_line, temp_col, temp_offset
                , sub_pin_offset, false))
            {
                // ���ƥ��ʧ�ܣ������ڲ���pin����ô��ǰҲҪ����Ϊpin
                if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;
                match = false;
                break;
            }

            // ���ƥ��ʧ�ܣ������ڲ���pin����ô��ǰҲҪ����Ϊpin
            if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;

            // �����������pin����ôҲҪ����Ϊpin
            if (node->pin == ABnfRuleNodePinType::NPT_TRUE)
                temp_pin_offset = temp_offset;
        }

        // ƥ��ɹ�
        if (match)
        {
            // ��ӵ��ڵ���
            if (!element->GetChilds().empty()) parent->AddChild(element);

            // ���ؽ��λ��
            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            // ���ƥ���ڲ���pin����ôҲҪ������Ϊpin
            if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

            // ����ƥ��ɹ�
            return true;
        }

        // �������pin����ô����Ƚ�pin
        // ����֮ǰ�Ľڵ㣬����Լ�������
        if (temp_pin_offset >= 0)
        {
            pin_offset = temp_pin_offset;

            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            option_list.clear();
            option_list.push_back(element);
            stop_token_element = element;
            break;
        }
        // ���û�г���pin���Ѵ�����ӵ�option_list
        else
        {
            option_list.push_back(element);
        }
    }

    // û��pin���Һ��Դ��������£�ֱ�ӷ���false
    if (pin_offset < 0 && ignore_error) return false;

    // ����option_list
    for (auto& option : option_list)
    {
        if (option->GetChilds().size() != 0) parent->AddChild(option);
    }

    // �����pin�������н�����
    if (pin_offset >= 0)
    {
        // ��pin_offset��ʼ���ҽ�����
        int find = m_file->GetLength();
        const auto& text = m_file->GetText();
        int index = -1;
        for (int i = static_cast<int>(m_stop_stack.size()) - 1; i >= 0; --i)
        {
            const auto& stop_token = m_stop_stack[i]->GetStopToken();
            const int token_size = static_cast<int>(stop_token.size());
            if (token_size <= 0) continue;
            // ���ҽ�����
            int value = -1;
            for (int j = pin_offset; j <= find - token_size; ++j) {
                bool is_find = true;
                for (int k = 0; k < token_size; ++k) {
                    if (text[j + k] != stop_token[k]) {
                        is_find = false;
                        break;
                    }
                }
                if (is_find) {
                    value = j;
                    break;
                }
            }
            // size_t value = m_file->GetText().find(stop_token.c_str(), pin_offset, find - pin_offset);
            // ����ҵ��ˣ����ұ�find��������ô�����õ�ǰ���
            if (value >= 0 && find > value)
            {
                find = value;
                index = i;
            }
        }

        // ������ҵ�
        if (index >= 0)
        {
            // ����ǵ�ǰ����
            if (m_stop_stack[index] == rule)
            {
                // �����ָ���
                AnalysisOffset(find + static_cast<int>(m_stop_stack[index]->GetStopToken().size()) - offset, line, col, offset);
                // ���syntax error
                const auto error_element = std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "syntax error", nullptr);
                if (stop_token_element) stop_token_element->AddChild(error_element);
                else parent->AddChild(error_element);
                // ����ƥ��ɹ���Ŀ�������ɴ����ı�����ʣ�µ��ı�����ƥ��
                return true;
            }
            // ����ǵ����ڶ�������
            else if (index == static_cast<int>(m_stop_stack.size()) - 2)
            {
                // �����ָ���
                AnalysisOffset(find - offset, line, col, offset);
                // ���syntax error
                parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "syntax error", nullptr));
                // ����ƥ��ɹ���Ŀ�������ɴ����ı�����ʣ�µ��ı�����ƥ��
                return true;
            }
        }
    }

    return false;
}

// �ڵ�ƥ��
bool ABnf::AnalysisABnfNodeMatch(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // �ж��ǲ���Ҷ�ӽڵ�
    if (node->value.type != ABnfRuleTokenType::TT_NONE)
    {
        // �����ƥ���ӹ���
        if (node->value.type == ABnfRuleTokenType::TT_ID)
        {
            // �����ӹ��򣬲�����
            ABnfRuleInfo* child = node->value.rule;
            if (child == nullptr)
            {
                child = m_rule.FindRuleInfo(node->value.value);
                node->value.rule = child;
            }
            // ����û���ҵ������
            if (child == nullptr)
            {
                // ������Դ���ֱ�ӷ���false
                if (ignore_error) return false;
                // �����ָ���
                AnalysisSkip(line, col, offset);
                // ��Ӵ���ڵ�
                parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "unknown rule:" + node->value.value, nullptr));
                // ����ƥ��ʧ��
                return false;
            }

            // ��ӽ�����
            m_stop_stack.push_back(child);

            // ƥ���ӹ����ӹ����pin�ǲ��ܴ�������
            const bool result = AnalysisABnfRuleMatch(child, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key
                , line, col, offset, pin_offset, ignore_error);

            // ɾ��������
            m_stop_stack.pop_back();
            return result;
        }

        // �����������ʽ
        if (node->value.type == ABnfRuleTokenType::TT_REGEX)
            return AnalysisABnfRegexMatch(rule, node, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key, line, col, offset, pin_offset, ignore_error);

        // ����ǹؼ���
        if (node->value.type == ABnfRuleTokenType::TT_KEY)
            return AnalysisABnfKeyMatch(rule, node, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key, line, col, offset, ignore_error);

        // ʣ�µľ�����ͨ�ַ���
        return AnalysisABnfStringMatch(rule, node, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key, line, col, offset, ignore_error);
    }

    // �����һ�������

    // �����ָ���
    AnalysisSkip(line, col, offset);
    // ����ע��
    AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
    // �����ָ���
    AnalysisSkip(line, col, offset);

    // ����Ƿ�end of file
    if (offset >= m_file->GetLength()) return false;
    // �����һ���ַ��Ƿ���Ԥ�ⷶΧ��
    const char next_char = m_file->GetText()[offset];
    auto* index_list = node->CheckNextChar(&m_rule, next_char);
    if (!index_list) return false;

    // ����ѡ�����
    std::vector<ABnfNodeElementPtr> option_list;
    for (auto option_index : *index_list)
    {
        // ǿ����Ԥ���
        if (!node->PreCheck(m_file->GetText(), offset)) continue;
        // ��ȡ��ǰ�ڵ����
        auto& node_list = node->node_list[option_index];

        // ����λ�ã����ڶ���ƥ��
        int temp_line = line;
        int temp_col = col;
        int temp_offset = offset;

        // ��ǵ�ǰ�����Ƿ���pin
        int temp_pin_offset = -1;
        // �Ƿ�ƥ��ɹ�
        bool match = true;
        // ��ʼ�������
        ABnfNodeElementPtr element = std::make_shared<ABnfNodeElement>(m_factory, m_file, line, col, offset, "");
        for (auto& option_node : node_list)
        {
            int sub_pin_offset = -1;
            if (!AnalysisABnfNode(rule, option_node, element, not_key
                , temp_line, temp_col, temp_offset
                , sub_pin_offset, false))
            {
                // ���ƥ��ʧ�ܣ������ڲ���pin����ô��ǰҲҪ����Ϊpin
                if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;
                match = false;
                break;
            }

            // ���ƥ��ʧ�ܣ������ڲ���pin����ô��ǰҲҪ����Ϊpin
            if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;

            // �����������pin����ôҲҪ����Ϊpin
            if (option_node->pin == ABnfRuleNodePinType::NPT_TRUE)
                temp_pin_offset = temp_offset;
        }

        // ƥ��ɹ�
        if (match)
        {
            // ��ӵ��ڵ���
            for (auto& child : element->GetChilds())
            {
                if (child->IsLeafOrHasChildOrError())
                    parent->AddChild(child);
            }
            // ���ؽ��λ��
            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            if (temp_pin_offset >= 0)
                pin_offset = temp_pin_offset;
            return true;
        }

        // �������pin����ô����Ƚ�pin
        // ����֮ǰ�Ľڵ㣬����Լ�������
        if (temp_pin_offset >= 0)
        {
            pin_offset = temp_pin_offset;

            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            option_list.clear();
            option_list.push_back(element);
            break;
        }
        // ���û�г���pin���Ѵ�����ӵ�option_list
        else
        {
            option_list.push_back(element);
        }
    }

    // û��pin���Һ��Դ��������£�ֱ�ӷ���false
    if (pin_offset < 0 && ignore_error) return false;

    // ����option_list
    for (auto& option : option_list)
    {
        for (auto& child : option->GetChilds())
        {
            if (child->IsLeafOrHasChildOrError())
                parent->AddChild(child);
        }
    }

    return false;
}

// ƥ��ؼ���
bool ABnf::AnalysisABnfKeyMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, bool ignore_error)
{
    // �����ָ���
    AnalysisSkip(line, col, offset);

    bool succeed = true;
    // ����ַ�����ƥ��
    for (int i = 0; i < static_cast<int>(node->value.value.size()); ++i)
    {
        if (offset + i >= m_file->GetLength()
            || node->value.value[i] != m_file->GetText()[offset + i])
        {
            succeed = false;
            break;
        }
    }

    // ƥ��ɹ�֮�󣬺�����Ǹ��ַ����������֣���ĸ���»���
    // ������Ҫ��ؼ��֣����������֣���ĸ���»��߹���
    if (succeed)
    {
        const int next_offset = offset + static_cast<int>(node->value.value.size());
        if (next_offset < m_file->GetLength())
        {
            const char next_char = m_file->GetText()[next_offset];
            if (next_char >= '0' && next_char <= '9'
                || next_char >= 'a' && next_char <= 'z'
                || next_char >= 'A' && next_char <= 'Z'
                || next_char == '_')
                succeed = false;
        }
    }

    // ���ƥ��ʧ��
    if (!succeed)
    {
        // �����ע�;�����
        if (rule == m_line_comment || rule == m_block_comment) return false;
        // ������Դ��������
        if (ignore_error) return false;
        // ��Ӵ���ڵ�
        if (offset < m_file->GetLength())
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get " + m_file->GetText()[offset]
                                                                , std::make_shared<ABnfKeyElement>( m_factory, m_file, line, col, offset, node->value.value)));
        else
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get end of file"
                                                                , std::make_shared<ABnfKeyElement>(m_factory, m_file, line, col, offset, node->value.value)));
        return false;
    }

    // �����ȷ�Ľڵ�
    parent->AddChild(CreateKeyElement(line, col, offset, node->value.value));
    // �����ָ���
    AnalysisOffset(static_cast<int>(node->value.value.size()), line, col, offset);
    // ����ƥ��ɹ�
    return true;
}

//��ƥ�����
bool ABnf::AnalysisABnfStringMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, bool ignore_error)
{
    // �����ָ���
    AnalysisSkip(line, col, offset);

    bool succeed = true;
    // ����ַ�����ƥ��
    for (int i = 0; i < static_cast<int>(node->value.value.size()); ++i)
    {
        if (offset + i >= m_file->GetLength()
            || node->value.value[i] != m_file->GetText()[offset + i])
        {
            succeed = false;
            break;
        }
    }

    // ƥ��ɹ�֮�󣬽�������ƥ�䣬���з��ż��
    if (succeed)
    {
        const int next = offset + static_cast<int>(node->value.value.size());
        if (next < m_file->GetLength())
        {
            auto it = m_symbol_check.find(node->value.value);
            if (it != m_symbol_check.end() && it->second.find(m_file->GetText()[next]) != it->second.end())
                succeed = false;
        }
    }

    // ����ƥ��ʧ��
    if (!succeed)
    {
        // �����ע�;�����
        if (rule == m_line_comment || rule == m_block_comment) return false;
        // ������Դ��������
        if (ignore_error) return false;
        // ��Ӵ���ڵ�
        if (offset < m_file->GetLength())
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get " + m_file->GetText()[offset]
                                                                , std::make_shared<ABnfStringElement>(m_factory, m_file, line, col, offset, node->value.value)));
        else
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get end of file"
                                                                , std::make_shared<ABnfStringElement>(m_factory, m_file, line, col, offset, node->value.value)));
        return false;
    }

    // �����ȷ�Ľڵ�
    parent->AddChild(CreateStringElement(line, col, offset, node->value.value));
    // �����ָ���
    AnalysisOffset(static_cast<int>(node->value.value.size()), line, col, offset);
    // ����ƥ��ɹ�
    return true;
}

// ƥ��������ʽ
bool ABnf::AnalysisABnfRegexMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // �����ָ���
    AnalysisSkip(line, col, offset);

    // ��ȡ���棬���ڱܿ���Ч���ظ�ƥ��
    int length = 0;
    bool cache = false;
    // ���ҵ�ǰƫ��
    auto it = m_regex_skip.find(offset);
    if (it != m_regex_skip.end())
    {
        // ���ҽڵ�ƥ��
        const auto length_it = it->second.find(node);
        if (length_it != it->second.end())
        {
            // ���Ϊ�ҵ�
            cache = true;
            length = length_it->second;
        }
    }
    // ���û���ҵ�����ô�ͽ���ƥ��
    if (!cache)
    {
        // ������ʽƥ��
        if (node->value.regex == nullptr)
            node->value.regex = std::make_shared<ARegex>(node->value.value);
        // ��ʼƥ��
        int match_length = 0;
        if (node->value.regex->Match(m_file->GetText().c_str() + offset, match_length))
            length = match_length;
        // ���û��ƥ�䵽�����ҹ����Ԥ��ֵ��pin
        if (length == 0 && rule->prediction.type != ABnfRuleTokenType::TT_NONE && rule->prediction_pin == ABnfRuleNodePinType::NPT_TRUE)
        {
            // ������ʽƥ��
            if (rule->prediction.regex == nullptr)
                rule->prediction.regex = std::make_shared<ARegex>(rule->prediction.value);
            // Ԥ��ƥ�䣬���ƥ��ɹ�����ô�ͱ��Ϊ��������ʾ����
            int pre_match_length = 0;
            if (rule->prediction.regex->Match(m_file->GetText().c_str() + offset, pre_match_length))
                length = - pre_match_length;
        }
        // ��ӻ���
        m_regex_skip[offset][node] = length;
    }

    // ������ҵ�����ô�������ȷ�ڵ�
    if (length > 0)
    {
        // ��ȡ�ڵ�����
        const std::string value = m_file->Substring(offset, length);
        // ������ʽƥ��Ľ�������ǹؼ���
        if (not_key || m_rule.GetKeySet().find(value) == m_rule.GetKeySet().end())
        {
            // ��ӵ����ڵ�
            parent->AddChild(CreateRegexElement(line, col, offset, value, node->value.regex));
            // �����ָ���
            AnalysisOffset(length, line, col, offset);
            // ����ƥ��ɹ�
            return true;
        }
    }

    // �����ע����ô����Ӵ���ڵ�
    if (rule == m_line_comment || rule == m_block_comment) return false;
    // ������Դ���Ҳ����Ӵ���ڵ�
    if (ignore_error) return false;

    // ��Ӵ���ڵ�
    if (offset < m_file->GetLength())
    {
        // ���length������
        if (length > 0)
        {
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get keyword" + m_file->Substring(offset, length)
                                                                , std::make_shared<ABnfRegexElement>(m_factory, m_file, line, col, offset, "", node->value.regex)));
        }
        else if (length < 0)
        {
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get " + m_file->Substring(offset, -length)
                                                                , std::make_shared<ABnfRegexElement>(m_factory, m_file, line, col, offset, "", node->value.regex)));
            AnalysisOffset(-length, line, col, offset);
            pin_offset = offset - length;
        }
        else
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get " + m_file->GetText()[offset]
                                                                , std::make_shared<ABnfRegexElement>(m_factory, m_file, line, col, offset, "", node->value.regex)));
    }
    else
        parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get end of file"
                                                            , std::make_shared<ABnfRegexElement>(m_factory, m_file, line, col, offset, "", node->value.regex)));
    return false;
}

// ע��ƥ��
bool ABnf::AnalysisABnfCommentMatch(ABnfRuleInfo* rule, const ABnfNodeElementPtr& parent, bool not_key, int& line, int& col, int& offset)
{
    // �����ע�ͣ���ôֱ�ӷ���
    if (m_line_comment == rule || m_block_comment == rule) return true;

    // ѭ��ƥ�䣬ֱ����ע�ͺͶ���ע��һ��ƥ��ʧ��
    while (true)
    {
        bool match = false;
        int pin_offset = -1;
        if (m_block_comment != nullptr)
        {
            while (true)
            {
                if (m_block_comment_skip.find(offset) == m_block_comment_skip.end())
                {
                    if (AnalysisABnfRuleMatch(m_block_comment, parent, not_key
                        , line, col, offset
                        , pin_offset, true))
                    {
                        match = true;
                    }
                    else
                    {
                        m_block_comment_skip.insert(offset);
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        if (m_line_comment != nullptr)
        {
            if (m_line_comment_skip.find(offset) == m_line_comment_skip.end())
            {
                if (AnalysisABnfRuleMatch(m_line_comment, parent, not_key
                    , line, col, offset
                    , pin_offset, true))
                    match = true;
                else
                    m_line_comment_skip.insert(offset);
            }
        }

        if (!match) return true;
    }
}

// ����value_len����ƫ��
void ABnf::AnalysisOffset(int value_len, int& line, int& col, int& offset) const
{
    while (true)
    {
        if (value_len == 0) break;
        if (offset >= m_file->GetLength()) break;

        const char c = m_file->GetText()[offset];
        if (c == '\n')
        {
            ++line;
            col = 0;
        }
        else
        {
            ++col;
        }

        const int byte_count = ABnfFile::GetByteCountOfOneWord(c);
        value_len -= byte_count;
        offset += byte_count;
    }
}

// ������һ��
bool ABnf::JumpToNextLine(int& line, int& col, int& offset) const
{
    while (true)
    {
        if (offset >= m_file->GetLength()) break;

        const char c = m_file->GetText()[offset];
        if (c == '\n')
        {
            ++line;
            col = 0;
            ++offset;

            return offset < m_file->GetLength();
        }
        else
        {
            ++col;
            offset += ABnfFile::GetByteCountOfOneWord(c);
        }
    }

    return false;
}

// ���и��ַ�������Ծ
void ABnf::AnalysisSkip(int& line, int& col, int& offset) const
{
    while (offset < m_file->GetLength())
    {
        const char c = m_file->GetText()[offset];
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
            return;

        if (c == '\n')
        {
            ++line;
            col = 0;
        }
        else
        {
            ++col;
        }
        ++offset;
    }
}
