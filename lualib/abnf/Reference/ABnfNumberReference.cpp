
#include "ABnfNumberReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnf.h"

ABnfNumberReference::ABnfNumberReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
{
}

void ABnfNumberReference::QueryQuickInfo(std::string& info)
{
    info = "color of rule";
}
