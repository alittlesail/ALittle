
#include "ALittleScriptGuessNamespaceName.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "alanguage/Src/Index/ABnfFile.h"
#include "alanguage/Src/Index/ABnfProject.h"

#include "../Generate/ALittleScriptNamespaceNameDecElement.h"

ALittleScriptGuessNamespaceName::ALittleScriptGuessNamespaceName(const std::string& p_namespace_name, const std::shared_ptr<ALittleScriptNamespaceNameDecElement>& p_namespace_name_dec)
{
    is_register = ALittleScriptUtility::IsRegister(p_namespace_name_dec);
    namespace_name = p_namespace_name;
    namespace_name_dec = p_namespace_name_dec;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessNamespaceName::GetElement() { return namespace_name_dec.lock(); }

bool ALittleScriptGuessNamespaceName::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessNamespaceName::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessNamespaceName::Clone() const
{
    return std::make_shared<ALittleScriptGuessNamespaceName>(namespace_name, namespace_name_dec.lock());
}

void ALittleScriptGuessNamespaceName::UpdateValue()
{
    value = namespace_name;
    value_without_const = value;
}

bool ALittleScriptGuessNamespaceName::IsChanged() const
{
    const auto element = namespace_name_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}

