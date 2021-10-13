
#include "ABnfKeyReference.h"
#include "alanguage/Src/Model/ABnfElement.h"
#include "alanguage/Src/Model/ABnf.h"

ABnfKeyReference::ABnfKeyReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
{
}

ABnfGuessError ABnfKeyReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    if (element->GetLength() <= 2)
        return ABnfGuessError(element, "key can't not be empty");

    return nullptr;
}

void ABnfKeyReference::QueryQuickInfo(std::string& info)
{
    info = "key word: Any regular expression encounters a keyword, even if the match is successful, it is considered a failure, to ensure that the keyword has a high resolution priority";
}
