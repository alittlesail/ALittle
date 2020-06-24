#include "ABnf.h"
#include "../Index/ABnfFile.h"
#include "ABnfFactory.h"
#include "ABnfRuleInfo.h"
#include "ABnfRuleNodeInfo.h"
#include "ABnfNodeElement.h"
#include "ABnfKeyElement.h"
#include "ABnfStringElement.h"
#include "ABnfRegexElement.h"
#include "ABnfErrorElement.h"

ABnf::ABnf()
{
}

// 初始化参数
void ABnf::Clear()
{
    m_file = nullptr;
    m_factory = nullptr;
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();
    m_stat = ABnfRuleStat();
    m_root = nullptr;
    m_line_comment = nullptr;
    m_block_comment = nullptr;
    m_rule.Clear();
    m_symbol_check.clear();
}

// 加载文法
bool ABnf::Load(const std::string& buffer, ABnfFactory* factory, std::string& error)
{
    // 清理
    Clear();

    // 设置节点工厂
    m_factory = factory;
    if (m_factory == nullptr)
    {
        Clear();
        error = "m_factory == null";
        return false;
    }

    // 保存字符串内容
    if (!m_rule.Load(buffer, error))
    {
        Clear();
        return false;
    }

    // 保存特殊的规则
    m_root = m_rule.FindRuleInfo("Root");
    m_line_comment = m_rule.FindRuleInfo("LineComment");
    m_block_comment = m_rule.FindRuleInfo("BlockComment");

    const auto& symbol_set = m_rule.GetSymbolSet();
    for (auto& symbol : symbol_set)
    {
        for (auto& symbol_check : symbol_set)
        {
            if (symbol_check.find(symbol) == 0 && symbol_check.size() > symbol.size())
                m_symbol_check[symbol].insert(symbol_check[symbol.size()]);
        }
    }
    return true;
}

ABnfRuleInfo* ABnf::GetRule(const std::string& name)
{
    return m_rule.FindRuleInfo(name);
}

// 查询关键字
void ABnf::QueryKeyWordCompletion(const std::string& input, std::vector<ALanguageCompletionInfo>& list)
{
    for (auto& key : m_rule.GetKeySet())
    {
        if (key.find(input) == 0)
        {
            ALanguageCompletionInfo info;
            info.display = key;
            list.push_back(info);
        }
    }
}

ABnfNodeElementPtr ABnf::CreateNodeElement(int line, int col, int offset, const std::string& type)
{
    // m_stat.CreateNode(type);
    auto node = m_factory->CreateNodeElement(m_file, line, col, offset, type);
    if (node == nullptr) node = ABnfNodeElementPtr(new ABnfNodeElement(m_factory, m_file, line, col, offset, type));
    return node;
}

ABnfKeyElementPtr ABnf::CreateKeyElement(int line, int col, int offset, const std::string& value)
{
    // m_stat.create_key_count++;
    auto node = m_factory->CreateKeyElement(m_file, line, col, offset, value);
    if (node == nullptr) node = ABnfKeyElementPtr(new ABnfKeyElement(m_factory, m_file, line, col, offset, value));
    return node;
}

ABnfStringElementPtr ABnf::CreateStringElement(int line, int col, int offset, const std::string& value)
{
    // m_stat.create_string_count++;
    auto node = m_factory->CreateStringElement(m_file, line, col, offset, value);
    if (node == nullptr) node = ABnfStringElementPtr(new ABnfStringElement(m_factory, m_file, line, col, offset, value));
    return node;
}

ABnfRegexElementPtr ABnf::CreateRegexElement(int line, int col, int offset, const std::string& value, std::shared_ptr<std::regex> regex)
{
    // m_stat.create_regex_count++;
    auto node = m_factory->CreateRegexElement(m_file, line, col, offset, value, regex);
    if (node == nullptr) node = ABnfRegexElementPtr(new ABnfRegexElement(m_factory, m_file, line, col, offset, value, regex));
    return node;
}

ABnfNodeElementPtr ABnf::Analysis(ABnfFile* file)
{
    if (m_root == nullptr) return nullptr;

    // 清空缓存
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();

    // 保存字符串
    m_file = file;

    // 初始化位置
    int line = 0;
    int col = 0;
    int offset = 0;
    int pin_offset = -1;
    bool not_key = false;
    m_stop_stack.clear();

    // 创建跟节点，然后开始解析
    auto node = CreateNodeElement(line, col, offset, m_root->id.value);

    while (true)
    {
        if (!AnalysisABnfNode(m_root, m_root->node, node, not_key
            , line, col, offset
            , pin_offset, false))
        {
            if (offset >= m_file->GetLength() && m_file->GetLength() > 0)
                --offset;
        }
        else
        {
            AnalysisSkip(line, col, offset);
            if (offset >= m_file->GetLength())
                break;
        }
        node->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, "语法错误", nullptr)));

        // 跳到下一行
        if (!JumpToNextLine(line, col, offset))
            break;
    }

    // StatElement(node);
    // m_stat.CalcRate();

    // 清空缓存
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();
    m_file = nullptr;

    // 返回结果
    return node;
}

void ABnf::StatElement(ABnfElementPtr element)
{
    if (std::dynamic_pointer_cast<ABnfKeyElement>(element))
    {
        m_stat.use_key_count++;
        return;
    }

    if (std::dynamic_pointer_cast<ABnfStringElement>(element))
    {
        m_stat.use_string_count++;
        return;
    }

    if (std::dynamic_pointer_cast<ABnfRegexElement>(element))
    {
        m_stat.use_regex_count++;
        return;
    }

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node)
    {
        m_stat.use_node_count++;

        auto it = m_stat.use_node_count_map.find(node->GetNodeType());
        if (it != m_stat.use_node_count_map.end())
            it->second++;
        else
            m_stat.use_node_count_map[node->GetNodeType()] = 1;

        for (auto& child : node->GetChilds())
            StatElement(child);

        return;
    }
}

// 分析规则语句
bool ABnf::AnalysisABnfNode(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent
    , bool not_key, int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 处理 （有且仅有一个）
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_NONE || node->repeat == ABnfRuleNodeRepeatType::NRT_ONE)
    {
        // 匹配第一个
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, ignore_error))
        {
            // 如果匹配内部有pin，那么也要对外标记为pin
            if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

            // 返回匹配失败
            return false;
        }

        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        return true;
    }

    // 处理 （至少一个）
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_AT_LEAST_ONE)
    {
        // 匹配第一个
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, ignore_error))
        {
            // 如果匹配内部有pin，那么也要对外标记为pin
            if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

            // 返回匹配失败
            return false;
        }

        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // 匹配剩下的
        return AnalysisABnfNodeMore(rule, node, parent, not_key
            , line, col, offset
            , pin_offset, true);
    }

    // 处理 （没有或者一个）
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT)
    {
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, true))
        {
            // 如果匹配内部有pin，那么也要对外标记为pin
            // 并且认为匹配失败
            if (temp_pin_offset >= 0)
            {
                pin_offset = temp_pin_offset;
                return false;
            }

            // 内部没有pin，可以标记为当前匹配成功，放弃失败的部分
            return true;
        }

        if (temp_pin_offset >= 0)
            pin_offset = temp_pin_offset;

        return true;
    }

    // 处理 （没有或者任意多个）
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE)
    {
        return AnalysisABnfNodeMore(rule, node, parent, not_key
            , line, col, offset
            , pin_offset, true);
    }

    // 这里一般不会发生
    return false;
}

bool ABnf::AnalysisABnfNodeMore(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent
    , bool not_key, int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    while (offset < m_file->GetLength())
    {
        int temp_pin_offset = -1;
        if (!AnalysisABnfNodeMatch(rule, node, parent, not_key
            , line, col, offset
            , temp_pin_offset, ignore_error))
        {
            // 如果匹配内部有pin，那么也要对外标记为pin
            // 并且认为匹配失败
            if (temp_pin_offset >= 0)
            {
                // 这里特意使用offset作为pin
                pin_offset = offset;
                return false;
            }

            // 内部没有pin，可以标记为当前匹配成功，放弃失败的部分
            return true;
        }

        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // 跳过注释
        AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
        // 跳过空格，制表符，换行
        AnalysisSkip(line, col, offset);
    }

    return true;
}

bool ABnf::AnalysisABnfRuleMatch(ABnfRuleInfo* rule, ABnfNodeElementPtr parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);
    // 跳过注释
    AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);

    if (offset >= m_file->GetLength()) return false;
    char next_char = m_file->GetText()[offset];
    auto* index_list = rule->CheckNextChar(next_char);
    if (!index_list)
        return false;

    // 遍历选择规则
    std::vector<ABnfNodeElementPtr> option_list;
    for (auto option_index : *index_list)
    {
        if (!rule->node->PreCheck(m_file->GetText(), offset)) continue;
        auto& node_list = rule->node->node_list[option_index];

        // 缓存位置
        int temp_line = line;
        int temp_col = col;
        int temp_offset = offset;

        // 标记当前规则是否有pin
        int temp_pin_offset = -1;
        // 是否匹配成功
        bool match = true;
        // 开始处理规则
        ABnfNodeElementPtr element = CreateNodeElement(line, col, offset, rule->id.value);
        for (int index = 0; index < static_cast<int>(node_list.size()); ++index)
        {
            int sub_pin_offset = -1;
            if (!AnalysisABnfNode(rule, node_list[index], element, not_key
                , temp_line, temp_col, temp_offset
                , sub_pin_offset, false))
            {
                // 如果匹配失败，并且内部有pin，那么当前也要设置为pin
                if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;
                match = false;
                break;
            }

            // 如果匹配失败，并且内部有pin，那么当前也要设置为pin
            if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;

            // 如果规则本身有pin，那么也要设置为pin
            if (node_list[index]->pin == ABnfRuleNodePinType::NPT_TRUE)
                temp_pin_offset = temp_offset;
        }

        // 匹配成功
        if (match)
        {
            // 添加到节点中
            if (element->GetChilds().size() != 0)
                parent->AddChild(element);
            // 返回结果位置
            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            if (temp_pin_offset >= 0)
                pin_offset = temp_pin_offset;
            return true;
        }

        // 如果出现pin，那么对外比较pin
        // 清理之前的节点，添加自己并跳出
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
        // 如果没有出现pin，把错误添加到option_list
        else
        {
            option_list.push_back(element);
        }
    }

    // 没有pin并且忽略错误的情况下，直接返回false
    if (pin_offset < 0 && ignore_error) return false;

    // 处理option_list
    for (auto& option : option_list)
    {
        if (option->GetChilds().size() != 0)
            parent->AddChild(option);
    }

    // 如果有pin，并且有结束符
    if (pin_offset >= 0)
    {
        // 从pin_offset开始查找结束符
        int find = m_file->GetLength();
        int index = -1;
        for (int i = static_cast<int>(m_stop_stack.size()) - 1; i >= 0; --i)
        {
            const auto& stop_token = m_stop_stack[i]->GetStopToken();
            if (stop_token.empty()) continue;

            int value = m_file->GetText().find(stop_token, pin_offset, find - pin_offset);
            if (value >= 0 && find > value)
            {
                find = value;
                index = i;
            }
        }
        if (index >= 0)
        {
            if (m_stop_stack[index] == rule)
            {
                AnalysisOffset(find + m_stop_stack[index]->GetStopToken().size() - offset, line, col, offset);
                parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, "语法错误", nullptr)));
                return true;
            }
            else if (index == static_cast<int>(m_stop_stack.size()) - 2)
            {
                AnalysisOffset(find - offset, line, col, offset);
                parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, "语法错误", nullptr)));
                return true;
            }
        }
    }

    return false;
}

// 分析节点
bool ABnf::AnalysisABnfNodeMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 判断是不是叶子节点
    if (node->value.type != ABnfRuleTokenType::TT_NONE)
    {
        // 如果是匹配子规则
        if (node->value.type == ABnfRuleTokenType::TT_ID)
        {
            // 如果没有找到子规则
            ABnfRuleInfo* child = node->value.rule;
            if (child == nullptr)
            {
                child = m_rule.FindRuleInfo(node->value.value);
                node->value.rule = child;
            }
            if (child == nullptr)
            {
                // 如果忽略错误，直接返回false
                if (ignore_error) return false;
                // 跳过空格，tab，换行
                AnalysisSkip(line, col, offset);
                // 添加错误节点
                parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, "未知规则:" + node->value.value, nullptr)));
                return false;
            }

            // 添加结束符
            m_stop_stack.push_back(child);

            // 匹配子规则，子规则的pin是不能传出来的
            bool result = AnalysisABnfRuleMatch(child, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key
                , line, col, offset
                , pin_offset, ignore_error);

            // 删除结束符
            m_stop_stack.pop_back();
            return result;
        }

        // 如果是正则表达式
        if (node->value.type == ABnfRuleTokenType::TT_REGEX)
            return AnalysisABnfRegexMatch(rule, node, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key, line, col, offset, pin_offset, ignore_error);

        // 如果是关键字
        if (node->value.type == ABnfRuleTokenType::TT_KEY)
            return AnalysisABnfKeyMatch(rule, node, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key, line, col, offset, ignore_error);

        // 剩下的就是普通字符串
        return AnalysisABnfStringMatch(rule, node, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key, line, col, offset, ignore_error);
    }

    // 如果是一个组规则

    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);
    // 跳过注释
    AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);

    if (offset >= m_file->GetLength()) return false;
    char next_char = m_file->GetText()[offset];
    const std::vector<int>* index_list = node->CheckNextChar(&m_rule, next_char);
    if (index_list) return false;

    // 遍历选择规则
    std::vector<ABnfNodeElementPtr> option_list;
    for (auto option_index : *index_list)
    {
        if (!node->PreCheck(m_file->GetText(), offset)) continue;
        auto& node_list = node->node_list[option_index];

        // 缓存位置
        int temp_line = line;
        int temp_col = col;
        int temp_offset = offset;

        // 标记当前规则是否有pin
        int temp_pin_offset = -1;
        // 是否匹配成功
        bool match = true;
        // 开始处理规则
        ABnfNodeElementPtr element = ABnfNodeElementPtr(new ABnfNodeElement(m_factory, m_file, line, col, offset, ""));
        for (int index = 0; index < static_cast<int>(node_list.size()); ++index)
        {
            int sub_pin_offset = -1;
            if (!AnalysisABnfNode(rule, node_list[index], element, not_key
                , temp_line, temp_col, temp_offset
                , sub_pin_offset, false))
            {
                // 如果匹配失败，并且内部有pin，那么当前也要设置为pin
                if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;
                match = false;
                break;
            }

            // 如果匹配失败，并且内部有pin，那么当前也要设置为pin
            if (sub_pin_offset >= 0) temp_pin_offset = sub_pin_offset;

            // 如果规则本身有pin，那么也要设置为pin
            if (node_list[index]->pin == ABnfRuleNodePinType::NPT_TRUE)
                temp_pin_offset = temp_offset;
        }

        // 匹配成功
        if (match)
        {
            // 添加到节点中
            for (auto& child : element->GetChilds())
            {
                if (child->IsLeafOrHasChildOrError())
                    parent->AddChild(child);
            }
            // 返回结果位置
            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            if (temp_pin_offset >= 0)
                pin_offset = temp_pin_offset;
            return true;
        }

        // 如果出现pin，那么对外比较pin
        // 清理之前的节点，添加自己并跳出
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
        // 如果没有出现pin，把错误添加到option_list
        else
        {
            option_list.push_back(element);
        }
    }

    // 没有pin并且忽略错误的情况下，直接返回false
    if (pin_offset < 0 && ignore_error) return false;

    // 处理option_list
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

bool ABnf::AnalysisABnfKeyMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
    , int& line, int& col, int& offset
    , bool ignore_error)
{
    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);

    bool succeed = true;
    for (int i = 0; i < static_cast<int>(node->value.value.size()); ++i)
    {
        // 匹配失败
        if (offset + i >= m_file->GetLength()
            || node->value.value[i] != m_file->GetText()[offset + i])
        {
            succeed = false;
            break;
        }
    }

    if (succeed)
    {
        int next_offset = offset + static_cast<int>(node->value.value.size());
        if (next_offset < m_file->GetLength())
        {
            char next_char = m_file->GetText()[next_offset];
            if (next_char >= '0' && next_char <= '9'
                || next_char >= 'a' && next_char <= 'z'
                || next_char >= 'A' && next_char <= 'Z'
                || next_char == '_')
                succeed = false;
        }
    }

    if (!succeed)
    {
        // 如果是注释就跳过
        if (rule == m_line_comment || rule == m_block_comment)
            return false;
        // 如果忽略错误就跳过
        if (ignore_error) return false;
        // 添加错误节点
        if (offset < m_file->GetLength())
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到" + m_file->GetText()[offset], new ABnfKeyElement(m_factory, m_file, line, col, offset, node->value.value))));
        else
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到文件结尾", new ABnfKeyElement(m_factory, m_file, line, col, offset, node->value.value))));
        return false;
    }

    // 添加正确的节点
    parent->AddChild(CreateKeyElement(line, col, offset, node->value.value));
    AnalysisOffset(static_cast<int>(node->value.value.size()), line, col, offset);
    return true;
}

bool ABnf::AnalysisABnfStringMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
    , int& line, int& col, int& offset, bool ignore_error)
{
    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);
    bool succeed = true;
    for (int i = 0; i < static_cast<int>(node->value.value.size()); ++i)
    {
        // 匹配失败
        if (offset + i >= m_file->GetLength()
            || node->value.value[i] != m_file->GetText()[offset + i])
        {
            succeed = false;
            break;
        }
    }

    // 检查
    if (succeed)
    {
        int next = offset + static_cast<int>(node->value.value.size());
        if (next < m_file->GetLength())
        {
            auto it = m_symbol_check.find(node->value.value);
            if (it != m_symbol_check.end() && it->second.find(m_file->GetText()[next]) != it->second.end())
                succeed = false;
        }
    }

    if (!succeed)
    {
        // 如果是注释就跳过
        if (rule == m_line_comment || rule == m_block_comment)
            return false;
        // 如果忽略错误就跳过
        if (ignore_error) return false;
        // 添加错误节点
        if (offset < m_file->GetLength())
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到" + m_file->GetText()[offset], new ABnfStringElement(m_factory, m_file, line, col, offset, node->value.value))));
        else
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到文件结尾", new ABnfStringElement(m_factory, m_file, line, col, offset, node->value.value))));
        return false;
    }

    // 添加正确的节点
    parent->AddChild(CreateStringElement(line, col, offset, node->value.value));
    AnalysisOffset(static_cast<int>(node->value.value.size()), line, col, offset);
    return true;
}

bool ABnf::AnalysisABnfRegexMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, ABnfNodeElementPtr parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 跳过空格，制表符，换行
    AnalysisSkip(line, col, offset);

    // 获取缓存
    int length = 0;
    bool cache = false;
    auto it = m_regex_skip.find(offset);
    if (it != m_regex_skip.end())
    {
        auto length_it = it->second.find(node);
        if (length_it != it->second.end())
        {
            cache = true;
            length = length_it->second;
        }
    }
    if (!cache)
    {
        // 正则表达式匹配
        if (node->value.regex == nullptr)
            node->value.regex = std::shared_ptr<std::regex>(new std::regex(node->value.value));
        // 开始匹配
        std::smatch match;
        if (std::regex_match(m_file->GetText(), offset, m_file->GetLength() - offset, match, std::regex_constants::match_continuous))
            length = match.size();
        // 如果没有匹配到，并且规则的预测值有pin
        if (length == 0 && rule->prediction.type != ABnfRuleTokenType::TT_NONE && rule->prediction_pin == ABnfRuleNodePinType::NPT_TRUE)
        {
            // 正则表达式匹配
            if (rule->prediction.regex == nullptr)
                rule->prediction.regex = std::shared_ptr<std::regex>(new std::regex(rule->prediction.value));
            // 预测匹配
            std::smatch pre_math;
            if (std::regex_match(m_file->GetText(), offset, m_file->GetLength() - offset, pre_math, std::regex_constants::match_continuous))
                length = -pre_match.size();
        }
        // 添加缓存
        m_regex_skip[offset][node] = length;
    }

    // 如果有找到，那么就添加正确节点
    if (length > 0)
    {
        std::string value = m_file->Substring(offset, length);
        // 正则表达式匹配的结果不能是关键字
        if (not_key || m_rule.GetKeySet().find(value) == m_rule.GetKeySet().end())
        {
            parent->AddChild(CreateRegexElement(line, col, offset, value, node->value.regex));
            AnalysisOffset(length, line, col, offset);
            return true;
        }
    }

    // 如果是注释那么不添加错误节点
    if (rule == m_line_comment || rule == m_block_comment) return false;
    // 如果忽略错误，也不添加错误节点
    if (ignore_error) return false;

    // 添加错误节点
    if (offset < m_file->GetLength())
    {
        if (length > 0)
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到关键字" + m_file->Substring(offset, length), new ABnfRegexElement(m_factory, m_file, line, col, offset, "", node->value.regex))));
        else if (length < 0)
        {
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却只得到" + m_file->Substring(offset, -length), new ABnfRegexElement(m_factory, m_file, line, col, offset, "", node->value.regex))));
            AnalysisOffset(-length, line, col, offset);
            pin_offset = offset - length;
        }
        else
            parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到" + m_file->GetText()[offset], new ABnfRegexElement(m_factory, m_file, line, col, offset, "", node->value.regex))));
    }
    else
        parent->AddChild(ABnfErrorElementPtr(new ABnfErrorElement(m_factory, m_file, line, col, offset, rule->id.value + "期望匹配" + node->value.value + " 却得到文件结尾", new ABnfRegexElement(m_factory, m_file, line, col, offset, "", node->value.regex))));
    return false;
}

bool ABnf::AnalysisABnfCommentMatch(ABnfRuleInfo* rule, ABnfNodeElementPtr parent, bool not_key, int& line, int& col, int& offset)
{
    // 如果是注释，那么直接返回
    if (m_line_comment == rule || m_block_comment == rule)
        return true;

    // 循环匹配，直至行注释和多行注释一起匹配失败
    while (true)
    {
        bool match = false;
        int pin_offset = -1;
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

        if (m_block_comment != nullptr)
        {
            if (m_block_comment_skip.find(offset) == m_block_comment_skip.end())
            {
                if (AnalysisABnfRuleMatch(m_block_comment, parent, not_key
                    , line, col, offset
                    , pin_offset, true))
                    match = true;
                else
                    m_block_comment_skip.insert(offset);
            }
        }

        if (!match) return true;
    }
}

void ABnf::AnalysisOffset(int value_len, int& line, int& col, int& offset)
{
    while (true)
    {
        if (value_len == 0) break;
        if (offset >= m_file->GetLength()) break;

        if (m_file->GetText()[offset] == '\n')
        {
            ++line;
            col = 0;
        }
        else
        {
            ++col;
        }
        --value_len;
        ++offset;
    }
}

// 跳到另一行
bool ABnf::JumpToNextLine(int& line, int& col, int& offset)
{
    while (true)
    {
        if (offset >= m_file->GetLength()) break;

        if (m_file->GetText()[offset] == '\n')
        {
            ++line;
            col = 0;
            ++offset;

            return offset < m_file->GetLength();
        }
        else
        {
            ++col;
            ++offset;
        }
    }

    return false;
}

// 对切割字符进行跳跃
void ABnf::AnalysisSkip(int& line, int& col, int& offset)
{
    while (offset < m_file->GetLength())
    {
        char c = m_file->GetText()[offset];
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
            return;

        if (c == '\r')
        {

        }
        else if (c == '\n')
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
