
#include "ABnfFactoryClass.h" 
#include "../Reference/ABnfIdReference.h"
#include "../Reference/ABnfRegexReference.h"
#include "../Reference/ABnfKeyReference.h"
#include "../Reference/ABnfStringReference.h"
#include "../Reference/ABnfNodeReference.h"
#include "../../alanguage/Model/ABnfElement.h"

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
