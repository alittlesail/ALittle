
#include "ABnfFileClass.h"
#include "ABnfCommonReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ABnfRegexReference.h"
#include "ABnfFileClass.h"

#include <unordered_set>
#include "ABnfRegexReference.h"

ABnfRegexReference::ABnfRegexReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

void ABnfRegexReference::QueryQuickInfo(std::string& info)
{
    auto parent = m_element->GetParent();
    if (parent != nullptr && parent->GetNodeType() == "Expression")
    {
        info = "The next character prediction, if the prediction fails, skip this rule to improve parsing efficiency";
        return;
    }

    info = "Regular expression matching";
}
