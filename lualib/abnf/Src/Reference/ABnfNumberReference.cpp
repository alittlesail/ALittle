
#include "ABnfNumberReference.h"
#include "alanguage/Src/Model/ABnfElement.h"
#include "alanguage/Src/Model/ABnf.h"

ABnfNumberReference::ABnfNumberReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
{
}

void ABnfNumberReference::QueryQuickInfo(std::string& info)
{
    info = "color of rule";
}
