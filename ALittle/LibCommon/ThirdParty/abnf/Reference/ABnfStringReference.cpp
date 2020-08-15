
#include "ABnfStringReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfNodeElement.h"
#include "../../alanguage/Model/ABnf.h"
#include "../Index/ABnfFileClass.h"

#include <unordered_set>

ABnfStringReference::ABnfStringReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

ABnfGuessError ABnfStringReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    if (element->GetLength() <= 2)
        return ABnfGuessError(element, "symbol can't not be empty");

    return nullptr;
}
