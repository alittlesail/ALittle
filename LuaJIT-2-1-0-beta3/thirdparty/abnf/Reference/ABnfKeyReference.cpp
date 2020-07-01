
#include "ABnfKeyReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfNodeElement.h"
#include "../../alanguage/Model/ABnf.h"
#include "../Index/ABnfFileClass.h"

#include <unordered_set>

ABnfKeyReference::ABnfKeyReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

bool ABnfKeyReference::CheckError(ABnfGuessError& error)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    if (element->GetLength() <= 2)
    {
        error.element = element;
        error.error = "key can't not be empty";
        return true;
    }
    return false;
}

void ABnfKeyReference::QueryQuickInfo(std::string& info)
{
    info = "key word: Any regular expression encounters a keyword, even if the match is successful, it is considered a failure, to ensure that the keyword has a high resolution priority";
}
