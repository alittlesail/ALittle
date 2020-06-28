
#include "ABnfFileClass.h"
#include "ABnfCommonReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ABnfStringReference.h"
#include "ABnfFileClass.h"

#include <unordered_set>

ABnfStringReference::ABnfStringReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

bool ABnfStringReference::CheckError(ABnfGuessError& error)
{
    if (m_element->GetLength() <= 2)
    {
        error.element = m_element;
        error.error = "symbol can't not be empty";
        return true;
    }
    return false;
}
