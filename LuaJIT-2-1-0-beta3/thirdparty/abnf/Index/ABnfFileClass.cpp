
#include "ABnfFileClass.h"
#include "../../alanguage/Model/ABnf.h"
#include "../../alanguage/Index/ABnfProject.h"
#include "../../alanguage/Model/ABnfNodeElement.h"

ABnfFileClass::ABnfFileClass(ABnfProject* project, const std::string& full_path, const char* text, size_t len, bool in_ui)
	: ABnfFile(project, full_path, text, len, in_ui)
{
}

ABnfFileClass::~ABnfFileClass()
{
}

// 更新分析内容
void ABnfFileClass::UpdateAnalysis()
{
    m_root = nullptr;
    m_rule.clear();
    
    if (m_in_ui)
        m_root = GetProject()->RefABnfUI().Analysis(this);
    else
        m_root = GetProject()->RefABnf().Analysis(this);
    if (m_root == nullptr) return;

    m_index.clear();
    CollectIndex(m_root);
    CollectRule();
}

void ABnfFileClass::UpdateError()
{
    ClearCheckError();
    ClearAnalysisError();

    if (m_root == nullptr) return;

    CollectError(m_root);
    AnalysisError(m_root);
}

void ABnfFileClass::CollectIndex(ABnfNodeElementPtr node)
{
    if (node->GetNodeType() == "Id")
    {
        const auto& value = node->GetElementText();
        m_index[value].insert(node);
    }

    for (auto child : node->GetChilds())
    {
        auto node_child = std::dynamic_pointer_cast<ABnfNodeElement>(child);
        if (node_child != nullptr)
            CollectIndex(node_child);
    }
}

// 收集规则ID
void ABnfFileClass::CollectRule()
{
    std::string comment;
    for (auto element : m_root->GetChilds())
    {
        if (element->GetNodeType() == "LineComment" || element->GetNodeType() == "BlockComment")
            comment = element->GetElementText();

        if (element->GetNodeType() != "Expression") continue;

        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        ABnfElementPtr id = nullptr;
        ABnfElementPtr value = nullptr;
        for (auto child : node->GetChilds())
        {
            if (child->GetNodeType() == "Id")
                id = child;
            else if (child->GetNodeType() == "Node")
                value = child;
        }
        if (id == nullptr) continue;
        if (value == nullptr) continue;
        const auto& id_value = id->GetElementText();

        m_rule[id_value][node] = comment;
        comment.clear();
    }
}
