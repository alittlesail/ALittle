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

// 初始化参数
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

// 加载文法
bool ABnf::Load(const std::string& buffer, ABnfFactory* factory, std::string& error)
{
    // 清理
    Clear();

    // 设置节点工厂，工厂指针不能为空
    m_factory = factory;
    if (m_factory == nullptr)
    {
        Clear();
        error = "m_factory == null";
        return false;
    }

    // 加载语言文法
    if (!m_rule.Load(buffer, error))
    {
        Clear();
        return false;
    }

    // 获取根规则
    m_root = m_rule.FindRuleInfo("Root");
    // 获取单行注释
    m_line_comment = m_rule.FindRuleInfo("LineComment");
    // 获取多行注释
    m_block_comment = m_rule.FindRuleInfo("BlockComment");

    // 收集符号检查，在处理类似+=时，会解析为+=，而不是+和=。
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

// 获取规则信息
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

// 查询关键字
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

// 创建语法节点
ABnfNodeElementPtr ABnf::CreateNodeElement(int line, int col, int offset, const std::string& type) const
{
    auto node = m_factory->CreateNodeElement(m_file, line, col, offset, type);
    if (node == nullptr) node = std::make_shared<ABnfNodeElement>(m_factory, m_file, line, col, offset, type);
    return node;
}

// 创建关键字节点
ABnfKeyElementPtr ABnf::CreateKeyElement(int line, int col, int offset, const std::string& value) const
{
    auto node = m_factory->CreateKeyElement(m_file, line, col, offset, value);
    if (node == nullptr) node = std::make_shared<ABnfKeyElement>(m_factory, m_file, line, col, offset, value);
    return node;
}

// 创建符号节点
ABnfStringElementPtr ABnf::CreateStringElement(int line, int col, int offset, const std::string& value) const
{
    auto node = m_factory->CreateStringElement(m_file, line, col, offset, value);
    if (node == nullptr) node = std::make_shared<ABnfStringElement>(m_factory, m_file, line, col, offset, value);
    return node;
}

// 创建曾泽表达式节点
ABnfRegexElementPtr ABnf::CreateRegexElement(int line, int col, int offset, const std::string& value, const std::shared_ptr<ARegex>& regex) const
{
    auto node = m_factory->CreateRegexElement(m_file, line, col, offset, value, regex);
    if (node == nullptr) node = std::make_shared<ABnfRegexElement>(m_factory, m_file, line, col, offset, value, regex);
    return node;
}

// 开始解析文件
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
    const bool not_key = false;
    m_stop_stack.clear();

    // 创建跟节点
    auto node = CreateNodeElement(line, col, offset, m_root->id.value);

    // 跳过分隔符
    AnalysisSkip(line, col, offset);
    // 跳过注释
    AnalysisABnfCommentMatch(m_root, node, not_key, line, col, offset);
    // 跳过分隔符
    AnalysisSkip(line, col, offset);

    // 如果到了文件尾部，那么就跳出解析
    if (offset < m_file->GetLength())
    {
        // 开始解析
        while (true)
        {
            // 根据根节点的文法开始解析文本
            if (!AnalysisABnfNode(m_root, m_root->node, node, not_key
                , line, col, offset, pin_offset, false))
            {
                // 如果offset是文件尾部，那么向前走一个字符，这样便于创建错误节点
                if (offset >= m_file->GetLength() && m_file->GetLength() > 0)
                    --offset;
            }
            else
            {
                // 跳过分割字符
                AnalysisSkip(line, col, offset);

                // 如果到了文件尾部，那么就跳出解析
                if (offset >= m_file->GetLength()) break;
            }

            // 将offset视为错误节点位置
            node->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "syntax error", nullptr));

            // 跳到下一行，然后继续解析
            if (!JumpToNextLine(line, col, offset)) break;
        }
    }

    // 清空缓存
    m_regex_skip.clear();
    m_line_comment_skip.clear();
    m_block_comment_skip.clear();
    m_stop_stack.clear();
    m_file = nullptr;

    // 返回结果
    return node;
}

// 分析规则语句
bool ABnf::AnalysisABnfNode(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent
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

        // 如果匹配内部有pin，那么也要对外标记为pin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // 返回匹配成功
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

        // 如果匹配内部有pin，那么也要对外标记为pin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // 匹配剩下的，忽略错误，能匹配到哪里就匹配到哪里
        return AnalysisABnfNodeMore(rule, node, parent, not_key
            , line, col, offset
            , pin_offset, true);
    }

    // 处理 （没有或者一个）
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_ONE_OR_NOT)
    {
        // 忽略错误，如果能匹配到就匹配，如果匹配不到就算了
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

        // 如果匹配内部有pin，那么也要对外标记为pin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // 返回匹配成功
        return true;
    }

    // 处理 （没有或者任意多个）
    if (node->repeat == ABnfRuleNodeRepeatType::NRT_NOT_OR_MORE)
    {
        // 忽略错误，能匹配多少就匹配多少
        return AnalysisABnfNodeMore(rule, node, parent, not_key
            , line, col, offset
            , pin_offset, true);
    }

    // 这里一般不会发生
    return false;
}

// 多次匹配
bool ABnf::AnalysisABnfNodeMore(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent
    , bool not_key, int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 循环解析
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

        // 如果匹配内部有pin，那么也要对外标记为pin
        if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

        // 跳过注释
        AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
        // 跳过分割字符
        AnalysisSkip(line, col, offset);
    }

    return true;
}

// 规则匹配
bool ABnf::AnalysisABnfRuleMatch(ABnfRuleInfo* rule, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 跳过分割字符
    AnalysisSkip(line, col, offset);
    // 跳过注释
    AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
    // 跳过分割字符
    AnalysisSkip(line, col, offset);

    // 如果文件已经结束，那么就是匹配失败
    if (offset >= m_file->GetLength()) return false;
    // 检查下一个字符
    const char next_char = m_file->GetText()[offset];
    // 检查下一个字符是否在预测范围内
    const auto* index_list = rule->CheckNextChar(next_char);
    if (!index_list) return false;

    ABnfNodeElementPtr stop_token_element;
    // 遍历选择规则
    std::vector<ABnfNodeElementPtr> option_list;
    for (auto option_index : *index_list)
    {
        // 强规则预检查
        if (!rule->node->PreCheck(m_file->GetText(), offset)) continue;
        // 获取当前节点规则
        auto& node_list = rule->node->node_list[option_index];

        // 缓存位置，用于多轮匹配
        int temp_line = line;
        int temp_col = col;
        int temp_offset = offset;

        // 标记当前规则是否有pin
        int temp_pin_offset = -1;
        // 是否匹配成功
        bool match = true;
        // 开始处理规则序列
        ABnfNodeElementPtr element = CreateNodeElement(line, col, offset, rule->id.value);
        for (auto& node : node_list)
        {
            int sub_pin_offset = -1;
            if (!AnalysisABnfNode(rule, node, element, not_key
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
            if (node->pin == ABnfRuleNodePinType::NPT_TRUE)
                temp_pin_offset = temp_offset;
        }

        // 匹配成功
        if (match)
        {
            // 添加到节点中
            if (!element->GetChilds().empty()) parent->AddChild(element);

            // 返回结果位置
            line = temp_line;
            col = temp_col;
            offset = temp_offset;

            // 如果匹配内部有pin，那么也要对外标记为pin
            if (temp_pin_offset >= 0) pin_offset = temp_pin_offset;

            // 返回匹配成功
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
            stop_token_element = element;
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
        if (option->GetChilds().size() != 0) parent->AddChild(option);
    }

    // 如果有pin，并且有结束符
    if (pin_offset >= 0)
    {
        // 从pin_offset开始查找结束符
        int find = m_file->GetLength();
        const auto& text = m_file->GetText();
        int index = -1;
        for (int i = static_cast<int>(m_stop_stack.size()) - 1; i >= 0; --i)
        {
            const auto& stop_token = m_stop_stack[i]->GetStopToken();
            const int token_size = static_cast<int>(stop_token.size());
            if (token_size <= 0) continue;
            // 查找结束符
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
            // 如果找到了，并且比find更近，那么就是用当前这个
            if (value >= 0 && find > value)
            {
                find = value;
                index = i;
            }
        }

        // 如果有找到
        if (index >= 0)
        {
            // 如果是当前规则
            if (m_stop_stack[index] == rule)
            {
                // 跳过分隔符
                AnalysisOffset(find + static_cast<int>(m_stop_stack[index]->GetStopToken().size()) - offset, line, col, offset);
                // 添加syntax error
                const auto error_element = std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "syntax error", nullptr);
                if (stop_token_element) stop_token_element->AddChild(error_element);
                else parent->AddChild(error_element);
                // 返回匹配成功，目的是吸纳错误文本，让剩下的文本继续匹配
                return true;
            }
            // 如果是倒数第二个规则
            else if (index == static_cast<int>(m_stop_stack.size()) - 2)
            {
                // 跳过分隔符
                AnalysisOffset(find - offset, line, col, offset);
                // 添加syntax error
                parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "syntax error", nullptr));
                // 返回匹配成功，目的是吸纳错误文本，让剩下的文本继续匹配
                return true;
            }
        }
    }

    return false;
}

// 节点匹配
bool ABnf::AnalysisABnfNodeMatch(ABnfRuleInfo* rule, ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 判断是不是叶子节点
    if (node->value.type != ABnfRuleTokenType::TT_NONE)
    {
        // 如果是匹配子规则
        if (node->value.type == ABnfRuleTokenType::TT_ID)
        {
            // 查找子规则，并缓存
            ABnfRuleInfo* child = node->value.rule;
            if (child == nullptr)
            {
                child = m_rule.FindRuleInfo(node->value.value);
                node->value.rule = child;
            }
            // 处理没有找到的情况
            if (child == nullptr)
            {
                // 如果忽略错误，直接返回false
                if (ignore_error) return false;
                // 跳过分隔符
                AnalysisSkip(line, col, offset);
                // 添加错误节点
                parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, "unknown rule:" + node->value.value, nullptr));
                // 返回匹配失败
                return false;
            }

            // 添加结束符
            m_stop_stack.push_back(child);

            // 匹配子规则，子规则的pin是不能传出来的
            const bool result = AnalysisABnfRuleMatch(child, parent, node->not_key == ABnfRuleNodeNotKeyType::NNKT_TRUE || not_key
                , line, col, offset, pin_offset, ignore_error);

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

    // 跳过分隔符
    AnalysisSkip(line, col, offset);
    // 跳过注释
    AnalysisABnfCommentMatch(rule, parent, not_key, line, col, offset);
    // 跳过分隔符
    AnalysisSkip(line, col, offset);

    // 检查是否到end of file
    if (offset >= m_file->GetLength()) return false;
    // 检查下一个字符是否在预测范围内
    const char next_char = m_file->GetText()[offset];
    auto* index_list = node->CheckNextChar(&m_rule, next_char);
    if (!index_list) return false;

    // 遍历选择规则
    std::vector<ABnfNodeElementPtr> option_list;
    for (auto option_index : *index_list)
    {
        // 强规则预检查
        if (!node->PreCheck(m_file->GetText(), offset)) continue;
        // 获取当前节点规则
        auto& node_list = node->node_list[option_index];

        // 缓存位置，用于多轮匹配
        int temp_line = line;
        int temp_col = col;
        int temp_offset = offset;

        // 标记当前规则是否有pin
        int temp_pin_offset = -1;
        // 是否匹配成功
        bool match = true;
        // 开始处理规则
        ABnfNodeElementPtr element = std::make_shared<ABnfNodeElement>(m_factory, m_file, line, col, offset, "");
        for (auto& option_node : node_list)
        {
            int sub_pin_offset = -1;
            if (!AnalysisABnfNode(rule, option_node, element, not_key
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
            if (option_node->pin == ABnfRuleNodePinType::NPT_TRUE)
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

// 匹配关键字
bool ABnf::AnalysisABnfKeyMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, bool ignore_error)
{
    // 跳过分隔符
    AnalysisSkip(line, col, offset);

    bool succeed = true;
    // 逐个字符进行匹配
    for (int i = 0; i < static_cast<int>(node->value.value.size()); ++i)
    {
        if (offset + i >= m_file->GetLength()
            || node->value.value[i] != m_file->GetText()[offset + i])
        {
            succeed = false;
            break;
        }
    }

    // 匹配成功之后，后面的那个字符不能是数字，字母，下划线
    // 这样就要求关键字，必须是数字，字母，下划线构成
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

    // 如果匹配失败
    if (!succeed)
    {
        // 如果是注释就跳过
        if (rule == m_line_comment || rule == m_block_comment) return false;
        // 如果忽略错误就跳过
        if (ignore_error) return false;
        // 添加错误节点
        if (offset < m_file->GetLength())
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get " + m_file->GetText()[offset]
                                                                , std::make_shared<ABnfKeyElement>( m_factory, m_file, line, col, offset, node->value.value)));
        else
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get end of file"
                                                                , std::make_shared<ABnfKeyElement>(m_factory, m_file, line, col, offset, node->value.value)));
        return false;
    }

    // 添加正确的节点
    parent->AddChild(CreateKeyElement(line, col, offset, node->value.value));
    // 跳过分隔符
    AnalysisOffset(static_cast<int>(node->value.value.size()), line, col, offset);
    // 返回匹配成功
    return true;
}

//　匹配符号
bool ABnf::AnalysisABnfStringMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, bool ignore_error)
{
    // 跳过分隔符
    AnalysisSkip(line, col, offset);

    bool succeed = true;
    // 逐个字符进行匹配
    for (int i = 0; i < static_cast<int>(node->value.value.size()); ++i)
    {
        if (offset + i >= m_file->GetLength()
            || node->value.value[i] != m_file->GetText()[offset + i])
        {
            succeed = false;
            break;
        }
    }

    // 匹配成功之后，进行延伸匹配，进行符号检查
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

    // 处理匹配失败
    if (!succeed)
    {
        // 如果是注释就跳过
        if (rule == m_line_comment || rule == m_block_comment) return false;
        // 如果忽略错误就跳过
        if (ignore_error) return false;
        // 添加错误节点
        if (offset < m_file->GetLength())
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get " + m_file->GetText()[offset]
                                                                , std::make_shared<ABnfStringElement>(m_factory, m_file, line, col, offset, node->value.value)));
        else
            parent->AddChild(std::make_shared<ABnfErrorElement>(m_factory, m_file, line, col, offset, rule->id.value + " expect " + node->value.value + " but get end of file"
                                                                , std::make_shared<ABnfStringElement>(m_factory, m_file, line, col, offset, node->value.value)));
        return false;
    }

    // 添加正确的节点
    parent->AddChild(CreateStringElement(line, col, offset, node->value.value));
    // 跳过分隔符
    AnalysisOffset(static_cast<int>(node->value.value.size()), line, col, offset);
    // 返回匹配成功
    return true;
}

// 匹配正则表达式
bool ABnf::AnalysisABnfRegexMatch(ABnfRuleInfo* rule
    , ABnfRuleNodeInfo* node, const ABnfNodeElementPtr& parent, bool not_key
    , int& line, int& col, int& offset, int& pin_offset, bool ignore_error)
{
    // 跳过分隔符
    AnalysisSkip(line, col, offset);

    // 获取缓存，用于避开无效的重复匹配
    int length = 0;
    bool cache = false;
    // 查找当前偏移
    auto it = m_regex_skip.find(offset);
    if (it != m_regex_skip.end())
    {
        // 查找节点匹配
        const auto length_it = it->second.find(node);
        if (length_it != it->second.end())
        {
            // 标记为找到
            cache = true;
            length = length_it->second;
        }
    }
    // 如果没有找到，那么就进行匹配
    if (!cache)
    {
        // 正则表达式匹配
        if (node->value.regex == nullptr)
            node->value.regex = std::make_shared<ARegex>(node->value.value);
        // 开始匹配
        int match_length = 0;
        if (node->value.regex->Match(m_file->GetText().c_str() + offset, match_length))
            length = match_length;
        // 如果没有匹配到，并且规则的预测值有pin
        if (length == 0 && rule->prediction.type != ABnfRuleTokenType::TT_NONE && rule->prediction_pin == ABnfRuleNodePinType::NPT_TRUE)
        {
            // 正则表达式匹配
            if (rule->prediction.regex == nullptr)
                rule->prediction.regex = std::make_shared<ARegex>(rule->prediction.value);
            // 预测匹配，如果匹配成功，那么就标记为负数，以示区别
            int pre_match_length = 0;
            if (rule->prediction.regex->Match(m_file->GetText().c_str() + offset, pre_match_length))
                length = - pre_match_length;
        }
        // 添加缓存
        m_regex_skip[offset][node] = length;
    }

    // 如果有找到，那么就添加正确节点
    if (length > 0)
    {
        // 获取节点内容
        const std::string value = m_file->Substring(offset, length);
        // 正则表达式匹配的结果不能是关键字
        if (not_key || m_rule.GetKeySet().find(value) == m_rule.GetKeySet().end())
        {
            // 添加到父节点
            parent->AddChild(CreateRegexElement(line, col, offset, value, node->value.regex));
            // 跳过分隔符
            AnalysisOffset(length, line, col, offset);
            // 返回匹配成功
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
        // 如果length是正数
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

// 注释匹配
bool ABnf::AnalysisABnfCommentMatch(ABnfRuleInfo* rule, const ABnfNodeElementPtr& parent, bool not_key, int& line, int& col, int& offset)
{
    // 如果是注释，那么直接返回
    if (m_line_comment == rule || m_block_comment == rule) return true;

    // 循环匹配，直至行注释和多行注释一起匹配失败
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

// 根据value_len进行偏移
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

// 跳到另一行
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

// 对切割字符进行跳跃
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
