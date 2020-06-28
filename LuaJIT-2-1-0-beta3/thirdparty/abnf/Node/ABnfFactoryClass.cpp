
#include "ABnfFactoryClass.h" 
#include "ABnfIdReference.h"
#include "ABnfRegexReference.h"
#include "ABnfKeyReference.h"
#include "ABnfStringReference.h"
#include "ABnfNodeReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"

ABnfReference* ABnfFactoryClass::CreateReference(ABnfElementPtr element)
{
    if (element->GetNodeType() == "Id")
        return new ABnfIdReference(element);
    else if (element->GetNodeType() == "Regex")
        return new ABnfRegexReference(element);
    else if (element->GetNodeType() == "Key")
        return new ABnfKeyReference(element);
    else if (element->GetNodeType() == "String")
        return new ABnfStringReference(element);
    else if (element->GetNodeType() == "Node")
        return new ABnfNodeReference(element);
    return new ABnfCommonReference(element);
}
