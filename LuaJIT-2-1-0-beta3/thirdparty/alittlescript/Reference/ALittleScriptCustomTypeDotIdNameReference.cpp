#include "ALittleScriptCustomTypeDotIdNameReference.h"

#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptCustomTypeNameElement.h"

ALittleScriptCustomTypeDotIdNameReference::ALittleScriptCustomTypeDotIdNameReference(ABnfElementPtr element) : ALittleScriptCustomTypeCommonReference(std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element->GetParent()->GetParent()), element)
{
    auto custom_type = std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element->GetParent()->GetParent());
    auto custom_type_name = custom_type->GetCustomTypeName();
    if (custom_type_name != nullptr)
        m_namespace_name = custom_type_name->GetElementText();
    else
        m_namespace_name = "";
    m_key = element->GetElementText();
}

int ALittleScriptCustomTypeDotIdNameReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::CUSTOM_NAME;
}
