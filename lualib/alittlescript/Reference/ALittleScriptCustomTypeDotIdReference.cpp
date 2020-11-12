#include "ALittleScriptCustomTypeDotIdReference.h"

#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptCustomTypeNameElement.h"

ALittleScriptCustomTypeDotIdReference::ALittleScriptCustomTypeDotIdReference(const ABnfElementPtr& element) : ALittleScriptCustomTypeCommonReference(std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element->GetParent()), element)
{
    auto custom_type = std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element->GetParent());
    auto custom_type_name = custom_type->GetCustomTypeName();
    if (custom_type_name != nullptr)
        m_namespace_name = custom_type_name->GetElementText();
    else
        m_namespace_name = "";
    m_key = element->GetElementText();
}
