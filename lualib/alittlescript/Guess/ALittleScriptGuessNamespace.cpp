
#include "ALittleScriptGuessNamespace.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

#include "../Generate/ALittleScriptNamespaceDecElement.h"

ALittleScriptGuessNamespace::ALittleScriptGuessNamespace(const std::string& p_namespace_name, const std::shared_ptr<ALittleScriptNamespaceDecElement>& p_namespace_dec)
{
    is_register = ALittleScriptUtility::IsRegister(p_namespace_dec);
    namespace_name = p_namespace_name;
    namespace_dec = p_namespace_dec;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessNamespace::GetElement() { return namespace_dec.lock(); }

bool ALittleScriptGuessNamespace::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessNamespace::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessNamespace::Clone() const
{
    return std::make_shared<ALittleScriptGuessNamespace>(namespace_name, namespace_dec.lock());
}

void ALittleScriptGuessNamespace::UpdateValue()
{
    value = namespace_name;
    value_without_const = value;
}

bool ALittleScriptGuessNamespace::IsChanged() const
{
    const auto element = namespace_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}

