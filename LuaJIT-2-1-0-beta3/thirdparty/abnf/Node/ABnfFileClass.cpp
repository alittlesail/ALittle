
#include "ABnfFileClass.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"

ABnfFileClass::ABnfFileClass(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len)
	: ABnfFile(project, full_path, abnf, text, len)
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
    if (m_abnf == nullptr) return;

    m_root = m_abnf->Analysis(this);
    if (m_root == nullptr) return;

    m_index.clear();
    CollectIndex(m_root);
    CollectRule();
}

void ABnfFileClass::UpdateError()
{
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
    for (auto element : m_root->GetChilds())
    {
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

        m_rule[id_value].insert(node);
    }
}
