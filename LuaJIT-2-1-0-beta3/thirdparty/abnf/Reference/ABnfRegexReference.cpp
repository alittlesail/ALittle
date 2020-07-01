
#include "ABnfRegexReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfNodeElement.h"
#include "../../alanguage/Model/ABnf.h"
#include "../Index/ABnfFileClass.h"

#include <unordered_set>
#include "ABnfRegexReference.h"

ABnfRegexReference::ABnfRegexReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

void ABnfRegexReference::QueryQuickInfo(std::string& info)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    auto parent = element->GetParent();
    if (parent != nullptr && parent->GetNodeType() == "Expression")
    {
        info = "The next character prediction, if the prediction fails, skip this rule to improve parsing efficiency";
        return;
    }

    info = "Regular expression matching";
}
