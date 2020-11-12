
#include "ABnfRegexReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnf.h"

ABnfRegexReference::ABnfRegexReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
{
}

void ABnfRegexReference::QueryQuickInfo(std::string& info)
{
    const auto element = m_element.lock();
    if (element == nullptr) return;

    auto parent = element->GetParent();
    if (parent != nullptr && parent->GetNodeType() == "Expression")
    {
        info = "The next character prediction, if the prediction fails, skip this rule to improve parsing efficiency";
        return;
    }

    info = "Regular expression matching";
}
