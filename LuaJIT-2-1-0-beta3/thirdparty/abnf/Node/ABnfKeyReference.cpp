
#include "ABnfFileClass.h"
#include "ABnfCommonReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ABnfKeyReference.h"
#include "ABnfFileClass.h"

#include <unordered_set>

ABnfKeyReference::ABnfKeyReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

bool ABnfKeyReference::CheckError(ABnfGuessError& error)
{
    if (m_element->GetLength() <= 2)
    {
        error.element = m_element;
        error.error = "key can't not be empty";
        return true;
    }
    return false;
}

void ABnfKeyReference::QueryQuickInfo(std::string& info)
{
    info = "key word: Any regular expression encounters a keyword, even if the match is successful, it is considered a failure, to ensure that the keyword has a high resolution priority";
}
