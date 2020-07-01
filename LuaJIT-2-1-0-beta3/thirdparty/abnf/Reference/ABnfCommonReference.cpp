
#include "ABnfCommonReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"

ABnfCommonReference::ABnfCommonReference(ABnfElementPtr element)
{
    m_element = element;
}

// ÅäÉ«
int ABnfCommonReference::QueryClassificationTag(bool& blur)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    blur = false;
    const auto& type = element->GetNodeType();
    if (type == "Id")
    {
        const auto& text = element->GetElementText();
        if (text == "Root" || text == "LineComment" || text == "BlockComment")
            return ABnfColorType::ABnfKeyWord;
        else
            return ABnfColorType::ABnfId;
    }
    
    if (type == "LineComment" || type == "BlockComment")
        return ABnfColorType::ABnfComment;
    
    if (type == "Key")
        return ABnfColorType::ABnfKey;
    
    if (type == "String")
        return ABnfColorType::ABnfString;

    if (type == "Regex")
        return ABnfColorType::ABnfRegex;

    if (type == "NodeTail")
        return ABnfColorType::ABnfNodeTail;

    return 0;
}

int ABnfCommonReference::QueryDesiredIndent(int it_line, int it_char, ABnfElementPtr select)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    const auto& type = element->GetNodeType();
    if (type == "Root" || type == "LineComment" || type == "BlockComment")
        return 0;
    return 4;
}
