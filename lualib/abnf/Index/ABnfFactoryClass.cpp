
#include "ABnfFactoryClass.h"
#include "ABnfFileClass.h"
#include "../Reference/ABnfIdReference.h"
#include "../Reference/ABnfRegexReference.h"
#include "../Reference/ABnfKeyReference.h"
#include "../Reference/ABnfStringReference.h"
#include "../Reference/ABnfNodeReference.h"
#include "../Reference/ABnfNumberReference.h"
#include "../../alanguage/Model/ABnfElement.h"

ABnfReference* ABnfFactoryClass::CreateReference(const ABnfElementPtr& element)
{
    if (element->GetNodeType() == "Id")
        return new ABnfIdReference(element);
    else if (element->GetNodeType() == "Regex")
        return new ABnfRegexReference(element);
    else if (element->GetNodeType() == "Number")
        return new ABnfNumberReference(element);
    else if (element->GetNodeType() == "Key")
        return new ABnfKeyReference(element);
    else if (element->GetNodeType() == "String")
        return new ABnfStringReference(element);
    else if (element->GetNodeType() == "Node")
        return new ABnfNodeReference(element);
    return new ABnfCommonReference(element);
}

ABnfFile* ABnfFactoryClass::CreateFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len)
{
    return new ABnfFileClass(project, full_path, text, len, false);
}
