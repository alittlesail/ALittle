﻿
#include "ABnfFile.h"
#include "ABnfProject.h"

#include "alanguage/Src/Model/ABnf.h"
#include "alanguage/Src/Model/ABnfElement.h"
#include "alanguage/Src/Model/ABnfNodeElement.h"
#include "alanguage/Src/Model/ABnfErrorElement.h"
#include "alanguage/Src/Model/ABnfReference.h"
#include "alanguage/Src/Model/ABnfRegexElement.h"
#include "alanguage/Src/Model/ABnfStringElement.h"
#include "alanguage/Src/Model/ALanguageHelperInfo.h"
#include "alanguage/Src/Model/ABnfRuleInfo.h"
#include "alanguage/Src/Model/ABnfRuleNodeInfo.h"

ABnfFile::ABnfFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len, bool in_ui)
{
    m_project = project;
    m_module_path = module_path;
    m_full_path = full_path;
    m_in_ui = in_ui;
    SetText(text, len);
}

// 设置文本
void ABnfFile::SetText(const char* text, size_t len)
{
    if (len > 0) m_text.assign(text, len);
}

// 插入文本
// it_line 从0开始算
// it_char 从0开始算
void ABnfFile::InsertText(const char* content, size_t len, int it_line, int it_char)
{
    int cur_line = 0;
    int cur_char = 0;

    size_t index = 0;
    while (index < m_text.size())
    {
        if (cur_line == it_line && cur_char == it_char) break;

        const int byte_count = GetByteCountOfOneWord(m_text[index]);
        if (byte_count == 1 && m_text[index] == '\n')
        {
            ++cur_line;
            cur_char = 0;
        }
        else
        {
            ++cur_char;
        }

        index += byte_count;
    }

    m_text.insert(index, content, len);
}

// 删除文本
// it_line_start 从0开始算
// it_char_start 从0开始算
// it_line_end 从0开始算
// it_char_end 从0开始算
void ABnfFile::DeleteText(int it_line_start, int it_char_start, int it_line_end, int it_char_end)
{
    bool swap = false;
    if (it_line_start > it_line_end)
        swap = true;
    else if (it_line_start == it_line_end)
        swap = it_char_start > it_char_end;
    if (swap)
    {
        std::swap(it_line_start, it_line_end);
        std::swap(it_char_start, it_char_end);
    }

    int cur_line = 0;
    int cur_char = 0;

    size_t start_index = 0;
    while (start_index < m_text.size())
    {
        if (cur_line == it_line_start && cur_char == it_char_start) break;

        const int byte_count = GetByteCountOfOneWord(m_text[start_index]);
        if (byte_count == 1 && m_text[start_index] == '\n')
        {
            ++cur_line;
            cur_char = 0;
        }
        else
        {
            ++cur_char;
        }

        start_index += byte_count;
    }

    size_t end_index = start_index;
    while (end_index < m_text.size())
    {
        const int byte_count = GetByteCountOfOneWord(m_text[end_index]);

        if (cur_line == it_line_end && cur_char == it_char_end)
        {
            end_index += byte_count;
            break;
        }

        if (byte_count == 1 && m_text[end_index] == '\n')
        {
            ++cur_line;
            cur_char = 0;
        }
        else
        {
            ++cur_char;
        }

        end_index += byte_count;
    }

    m_text.erase(start_index, end_index - start_index);
}

bool ABnfFile::ContainText(const std::string& text) const
{
    return m_text.find(text) != std::string::npos;
}

const std::vector<ALanguageColorInfo>* ABnfFile::QueryColor(int version, int it_line)
{
    AnalysisText(version);
    AnalysisColor(version);

    auto it = m_color_map.find(it_line);
    if (it == m_color_map.end()) return nullptr;
    return &it->second;
}

bool ABnfFile::QueryInfo(int version, int it_line, int it_char, ALanguageQuickInfo& info)
{
    AnalysisText(version);

    if (m_root == nullptr) return false;

    auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr || element->IsError()) return false;

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr)
        element->GetReference()->QueryQuickInfo(info.info);
    else
        node->GetReference()->QueryQuickInfo(info.info);

    info.line_start = element->GetStartLine();
    info.char_start = element->GetStartCol();
    info.line_end = element->GetEndLine();
    info.char_end = element->GetEndCol();

    return !info.info.empty();
}

bool ABnfFile::QueryGoto(int version, int it_line, int it_char, ALanguageGotoInfo& info)
{
    AnalysisText(version);

    if (m_root == nullptr) return false;

    auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr || element->IsError()) return false;

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return false;
    
    auto goto_element = node->GetReference()->GotoDefinition();
    if (goto_element == nullptr) return false;

    info.file_path = goto_element->GetFullPath();
    info.line_start = goto_element->GetStartLine();
    info.char_start = goto_element->GetStartCol();
    info.line_end = goto_element->GetEndLine();
    info.char_end = goto_element->GetEndCol();

    return true;
}

bool ABnfFile::QueryComplete(int version, int it_line, int it_char
    , std::vector<ALanguageCompletionInfo>& info_list
    , int& line_start, int& char_start, int& line_end, int& char_end)
{
    AnalysisText(version);

    if (m_root == nullptr) return false;

    auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr) return false;

    line_start = element->GetStartLine();
    char_start = element->GetStartCol();
    line_end = element->GetEndLine();
    char_end = element->GetEndCol();

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return true;

    node->GetReference()->QueryCompletion(node, info_list);
    node->GetReference()->QueryKeyWord(node, info_list);
    return true;
}

bool ABnfFile::QueryParamList(int version, int it_line, int it_char
    , std::vector<ALanguageParameterInfo>& param_list
    , int& line_start, int& char_start, int& line_end, int& char_end)
{
    AnalysisText(version);

    if (m_root == nullptr) return false;

    auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr) return false;

    line_start = element->GetStartLine();
    char_start = element->GetStartCol();
    line_end = element->GetEndLine();
    char_end = element->GetEndCol();

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return false;

    return node->GetReference()->QueryParamList(line_start, char_start, line_end, char_end, param_list);
}

int ABnfFile::QueryParamIndex(int version, int it_line, int it_char, int* start_offset)
{
    AnalysisText(version);
    if (m_root == nullptr) return 0;

    const auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr) return 0;

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return 0;

    return node->GetReference()->QueryParamIndex(it_line, it_char, element, *start_offset);
}

bool ABnfFile::QueryError(int version, bool force, std::vector<ALanguageErrorInfo>& info_list)
{
    AnalysisText(version);
    AnalysisError(version, force);

    std::unordered_set<ABnfElementPtr> filter;
    for (auto& pair : m_check_error_map)
    {
        if (filter.find(pair.first) != filter.end()) continue;
        ALanguageErrorInfo info;
        info.line_start = pair.first->GetStartLine();
        info.char_start = pair.first->GetStartCol();
        info.line_end = pair.first->GetEndLine();
        info.char_end = pair.first->GetEndCol();
        info.error = pair.second;
        info_list.push_back(info);
        filter.insert(pair.first);
    }

    for (auto& pair : m_analysis_error_map)
    {
        if (filter.find(pair.first) != filter.end()) continue;
        ALanguageErrorInfo info;
        info.line_start = pair.first->GetStartLine();
        info.char_start = pair.first->GetStartCol();
        info.line_end = pair.first->GetEndLine();
        info.char_end = pair.first->GetEndCol();
        info.error = pair.second;
        info_list.push_back(info);
        filter.insert(pair.first);
    }
    return true;
}

int ABnfFile::QueryDesiredIndent(int version, int it_line, int it_char)
{
    AnalysisText(version);
    if (m_root == nullptr) return 0;

    const auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr) return 0;

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return 0;

    return node->GetReference()->QueryDesiredIndent(it_line, it_char, element);
}

int ABnfFile::QueryFormatIndent(int version, int it_line, int it_char)
{
    AnalysisText(version);
    if (m_root == nullptr) return 0;

    const auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr) return 0;

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return 0;

    return node->GetReference()->QueryFormatIndent(it_line, it_char, element);
}

bool ABnfFile::QueryAutoPair(int version, int it_line, int it_char, const std::string& left_pair, const std::string& right_pair)
{
    AnalysisText(version);

    if (m_root == nullptr) return "";

    // 获取元素
    auto element = m_root->GetException(it_line, it_char);
    if (element == nullptr) return "";

    // 如果是错误元素，那么就以目标元素来判定
    if (element->IsError())
    {
        const auto error_element = std::dynamic_pointer_cast<ABnfErrorElement>(element);
        if (std::dynamic_pointer_cast<ABnfRegexElement>(error_element->GetTargetElement()))
            return std::dynamic_pointer_cast<ABnfRegexElement>(error_element->GetTargetElement())->IsMatch(left_pair + right_pair);
        else if (std::dynamic_pointer_cast<ABnfStringElement>(error_element->GetTargetElement())) // 如果节点文本正是期望值，那么就可以返回true
            return std::dynamic_pointer_cast<ABnfStringElement>(error_element->GetTargetElement())->GetValue() == right_pair;
        return false;
    }

    // 如果是正则表达式，那么就直接匹配
    if (std::dynamic_pointer_cast<ABnfRegexElement>(element))
        return std::dynamic_pointer_cast<ABnfRegexElement>(element)->IsMatch(left_pair + right_pair);

    // 获取类型
    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node == nullptr) node = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (node == nullptr) return false;

    // 查找规则 
    const auto rule = m_project->RefABnfUI().GetRule(node->GetNodeType());
    if (rule == nullptr || rule->node == nullptr) return false;
    for (auto& node_list : rule->node->node_list)
    {
        // 如果还有一个子规则，那么就跳过
        if (node_list.size() <= 1) continue;

        // 如果找到规则并且和left_pair一致，那么就找到left_pair对应的规则
        int index = -1;
        for (size_t i = 0; i < node_list.size(); ++i)
        {
            auto& node_token = node_list[i];
            if (node_token->value.type == ABnfRuleTokenType::TT_NONE) continue;

            if (node_token->value.type == ABnfRuleTokenType::TT_STRING)
            {
                if (node_token->value.value.size() == 1
                    && node_token->value.value == left_pair)
                {
                    index = static_cast<int>(i);
                    break;
                }
            }
        }
        // 如果没有找到就跳过当前规则组
        if (index == -1) continue;
        // 从后面往前找，找到与right_pair配对的子规则，如果有，那么就返回true
        for (int i = static_cast<int>(node_list.size()) - 1; i >= index + 1; --i)
        {
            auto& node_token = node_list[i];
            if (node_token->value.type == ABnfRuleTokenType::TT_NONE) continue;

            if (node_token->value.type == ABnfRuleTokenType::TT_STRING)
            {
                if (node_token->value.value == right_pair)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int ABnfFile::GetByteCountOfOneWord(unsigned char first_char)
{
    unsigned char temp = 0x80;
    int num = 0;

    const unsigned char char_value = first_char;

    if (char_value < 0x80) // ascii code.(0-127)
        return 1;
    while (temp & char_value)
    {
        ++num;
        temp = temp >> 1;
    }

    return num;
}

void ABnfFile::AnalysisText(int version)
{
    if (m_analysis_version == version) return;
    m_analysis_version = version;
    UpdateAnalysis();
}

void ABnfFile::AnalysisError(int version, bool force)
{
    if (!force && m_error_version == version) return;
    m_error_version = version;

    if (force) OnForceAnalysisError();

    ClearCheckError();
    ClearAnalysisError();
    if (m_root == nullptr) return;
    CollectError(m_root);
    AnalysisError(m_root);
}

void ABnfFile::AnalysisColor(int version)
{
    if (m_color_version == version) return;
    m_color_version = version;

    m_color_map.clear();
    if (m_root == nullptr) return;
    const auto& rule_set = GetProject()->RefABnf().GetRuleSet();
    CollectColor(m_root, rule_set, false);
}

// 更新解析
void ABnfFile::UpdateAnalysis()
{
    m_root = nullptr;

    if (m_in_ui)
        m_root = GetProject()->RefABnfUI().Analysis(this);
    else
        m_root = GetProject()->RefABnf().Analysis(this);
}

void ABnfFile::CollectColor(const ABnfElementPtr& element, const std::unordered_map<std::string, ABnfRuleInfo*>& rule_set, bool blur)
{
    if (element->IsError()) return;

    bool blur_temp = false;
    int tag = 0;

    const auto rule_it = rule_set.find(element->GetNodeType());
    if (rule_it != rule_set.end() && rule_it->second->has_color)
        tag = rule_it->second->rule_id;
    else
        tag = element->GetReference()->QueryClassificationTag(blur_temp);
    
    if (tag > 0)
    {
        for (int line = element->GetStartLine(); line <= element->GetEndLine(); ++line)
        {
            ALanguageColorInfo info;
            info.line_start = element->GetStartLine();
            info.char_start = element->GetStartCol();
            info.line_end = element->GetEndLine();
            info.char_end = element->GetEndCol();
            info.blur = (blur || blur_temp) ? 1 : 0;
            info.tag = tag;
            m_color_map[line].push_back(info);
        }
        return;
    }

    const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node != nullptr)
    {
        for (auto& child : node->GetChilds())
            CollectColor(child, rule_set, blur || blur_temp);
    }
}

// 收集语法错误
void ABnfFile::CollectError(const ABnfElementPtr& element)
{
    const auto error_element = std::dynamic_pointer_cast<ABnfErrorElement>(element);
    if (error_element != nullptr)
    {
        AddCheckErrorInfo(element, error_element->GetValue());
        return;
    }

    const auto node_element = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node_element == nullptr) return;

    for (auto& child : node_element->GetChilds())
        CollectError(child);
}

void ABnfFile::AnalysisError(const ABnfElementPtr& element)
{
    if (element->IsError()) return;

    const auto error = element->GetReference()->CheckError();
    if (error)
    {
        if (error.element != nullptr && error.element->GetFile() == this)
            AddAnalysisErrorInfo(error.element, error.error);
    }

    const auto node_element = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node_element == nullptr) return;

    for (auto& child : node_element->GetChilds())
        AnalysisError(child);
}

