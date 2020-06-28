
#include "ABnfFileClass.h"
#include "ABnfCommonReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ABnfNodeReference.h"
#include "ABnfFileClass.h"

#include <unordered_set>

ABnfNodeReference::ABnfNodeReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

bool ABnfNodeReference::CheckError(ABnfGuessError& error)
{
    auto parent = std::dynamic_pointer_cast<ABnfNodeElement>(m_element->GetParent());
    if (parent == nullptr) return false;

    for (auto child : parent->GetChilds())
    {
        if (child->GetNodeType() == "Id" && child->GetElementText() == "Root")
            return false;
    }

    return CheckElementError(m_element, error);
}

bool ABnfNodeReference::CheckElementError(ABnfElementPtr element, ABnfGuessError& error)
{
    if (element->GetNodeType() == "List")
    {
        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return false;

        bool has_child = false;
        for (auto child : node->GetChilds())
        {
            if (child->GetNodeType() == "Option")
            {
                auto result = CheckElementError(child, error);
                if (result) return result;
            }
            else
            {
                auto result = CheckElementError(child, error);
                if (!result)
                {
                    has_child = true;
                    break;
                }

            }
        }
        if (!has_child)
        {
            error.element = element;
            error.error = "The rule cannot guarantee that there will be child nodes";
            return true;
        }
            
    }
    else if (element->GetNodeType() == "Option" || element->GetNodeType() == "Node")
    {
        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return false;

        for (auto child : node->GetChilds())
        {
            auto result = CheckElementError(child, error);
            if (result) return result;
        }
    }
    else if (element->GetNodeType() == "Group" || element->GetNodeType() == "Leaf")
    {
        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return false;

        ABnfElementPtr tail_node = nullptr;
        for (auto child : node->GetChilds())
        {
            if (child->GetNodeType() == "NodeTail")
                tail_node = child;
        }

        if (tail_node != nullptr && (tail_node->GetElementText() == "*" | tail_node->GetElementText() == "?"))
        {
            error.element = element;
            error.error = "The rule cannot guarantee that there will be child nodes";
            return true;
        }

        for (auto child : node->GetChilds())
        {
            auto result = CheckElementError(child, error);
            if (result) return result;
        }
    }

    return false;
}
