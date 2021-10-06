
#include "ABnfStringReference.h"
#include "alanguage/Src/Model/ABnfElement.h"

ABnfStringReference::ABnfStringReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
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
