
#include "ABnfNodeReference.h"
#include "alanguage/Src/Model/ABnfElement.h"
#include "alanguage/Src/Model/ABnfNodeElement.h"
#include "alanguage/Src/Model/ABnf.h"

ABnfNodeReference::ABnfNodeReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
{
}

ABnfGuessError ABnfNodeReference::CheckError()
{
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    const auto parent = std::dynamic_pointer_cast<ABnfNodeElement>(element->GetParent());
    if (parent == nullptr) return nullptr;

    for (const auto& child : parent->GetChilds())
    {
        if (child->GetNodeType() == "Id" && child->GetElementText() == "Root")
            return nullptr;
    }

    return CheckElementError(element);
}

ABnfGuessError ABnfNodeReference::CheckElementError(const ABnfElementPtr& element) const
{
    if (element->GetNodeType() == "List")
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return nullptr;

        bool has_child = false;
        for (const auto& child : node->GetChilds())
        {
            if (child->GetNodeType() == "Option")
            {
                auto error = CheckElementError(child);
                if (error) return error;
            }
            else
            {
                const auto error = CheckElementError(child);
                if (!error)
                {
                    has_child = true;
                    break;
                }

            }
        }
        if (!has_child)
            return ABnfGuessError(element, "The rule cannot guarantee that there will be child nodes");
            
    }
    else if (element->GetNodeType() == "Option" || element->GetNodeType() == "Node")
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return nullptr;

        for (const auto& child : node->GetChilds())
        {
            auto error = CheckElementError(child);
            if (error) return error;
        }
    }
    else if (element->GetNodeType() == "Group" || element->GetNodeType() == "Leaf")
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return nullptr;

        ABnfElementPtr tail_node = nullptr;
        for (const auto& child : node->GetChilds())
        {
            if (child->GetNodeType() == "NodeTail")
                tail_node = child;
        }

        if (tail_node != nullptr && (tail_node->GetElementText() == "*" | tail_node->GetElementText() == "?"))
            return ABnfGuessError(element, "The rule cannot guarantee that there will be child nodes");

        for (const auto& child : node->GetChilds())
        {
            auto error = CheckElementError(child);
            if (error) return error;
        }
    }

    return nullptr;
}
