
#include "ABnfNumberReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfNodeElement.h"
#include "../../alanguage/Model/ABnf.h"
#include "../Index/ABnfFileClass.h"

#include <unordered_set>
#include "ABnfNumberReference.h"

ABnfNumberReference::ABnfNumberReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

void ABnfNumberReference::QueryQuickInfo(std::string& info)
{
    info = "color of rule";
}
