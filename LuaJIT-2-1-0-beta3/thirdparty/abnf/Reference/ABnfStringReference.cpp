
#include "ABnfStringReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfNodeElement.h"
#include "../../alanguage/Model/ABnf.h"
#include "../Index/ABnfFileClass.h"

#include <unordered_set>

ABnfStringReference::ABnfStringReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

bool ABnfStringReference::CheckError(ABnfGuessError& error)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    if (element->GetLength() <= 2)
    {
        error.element = element;
        error.error = "symbol can't not be empty";
        return true;
    }
    return false;
}
