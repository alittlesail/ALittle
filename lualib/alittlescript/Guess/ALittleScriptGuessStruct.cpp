
#include "ALittleScriptGuessStruct.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

#include "../Generate/ALittleScriptStructDecElement.h"

ALittleScriptGuessStruct::ALittleScriptGuessStruct(const std::string& p_namespace_name, const std::string& p_struct_name
    , std::shared_ptr<ALittleScriptStructDecElement> p_struct_dec, bool p_is_const)
{
    is_register = ALittleScriptUtility::IsRegister(p_struct_dec);
    namespace_name = p_namespace_name;
    struct_name = p_struct_name;
    struct_dec = p_struct_dec;
    is_const = p_is_const;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessStruct::GetElement() { return struct_dec.lock(); }

bool ALittleScriptGuessStruct::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessStruct::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessStruct::Clone() const
{
    return ABnfGuessPtr(new ALittleScriptGuessStruct(namespace_name, struct_name, struct_dec.lock(), is_const));
}

void ALittleScriptGuessStruct::UpdateValue()
{
    value = namespace_name + "." + struct_name;
    value_without_const = value;
}

bool ALittleScriptGuessStruct::IsChanged() const
{
    auto element = struct_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}

