
#include "ABnfFactoryClass.h"
#include "ABnfFileClass.h"

#include "alanguage/Src/Model/ABnfElement.h"

#include "abnf/Src/Reference/ABnfIdReference.h"
#include "abnf/Src/Reference/ABnfRegexReference.h"
#include "abnf/Src/Reference/ABnfKeyReference.h"
#include "abnf/Src/Reference/ABnfStringReference.h"
#include "abnf/Src/Reference/ABnfNodeReference.h"
#include "abnf/Src/Reference/ABnfNumberReference.h"

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
