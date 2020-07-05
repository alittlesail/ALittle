
#include "ALittleScriptGuessStructName.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

#include "../Generate/ALittleScriptStructNameDecElement.h"

ALittleScriptGuessStructName::ALittleScriptGuessStructName(const std::string& p_namespace_name, const std::string& p_struct_name
    , std::shared_ptr<ALittleScriptStructNameDecElement> p_struct_name_dec)
{
    is_register = ALittleScriptUtility::IsRegister(p_struct_name_dec);
    namespace_name = p_namespace_name;
    struct_name = p_struct_name;
    struct_name_dec = p_struct_name_dec;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessStructName::GetElement() { return struct_name_dec.lock(); }

bool ALittleScriptGuessStructName::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessStructName::ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessStructName::Clone() const
{
    return ABnfGuessPtr(new ALittleScriptGuessStructName(namespace_name, struct_name, struct_name_dec.lock()));
}

void ALittleScriptGuessStructName::UpdateValue()
{
    value = namespace_name + "." + struct_name;
    value_without_const = value;
}

bool ALittleScriptGuessStructName::IsChanged() const
{
    auto element = struct_name_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}

