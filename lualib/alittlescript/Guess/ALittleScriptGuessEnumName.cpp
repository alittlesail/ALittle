
#include "ALittleScriptGuessEnumName.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

#include "../Generate/ALittleScriptEnumNameDecElement.h"

ALittleScriptGuessEnumName::ALittleScriptGuessEnumName(const std::string& p_namespace_name, const std::string& p_enum_name
    , const std::shared_ptr<ALittleScriptEnumNameDecElement>& p_enum_name_dec)
{
    is_register = ALittleScriptUtility::IsRegister(p_enum_name_dec);
    namespace_name = p_namespace_name;
    enum_name = p_enum_name;
    enum_name_dec = p_enum_name_dec;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessEnumName::GetElement() { return enum_name_dec.lock(); }

bool ALittleScriptGuessEnumName::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessEnumName::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessEnumName::Clone() const
{
    return std::make_shared<ALittleScriptGuessEnumName>(namespace_name, enum_name, enum_name_dec.lock());
}

void ALittleScriptGuessEnumName::UpdateValue()
{
    value = namespace_name + "." + enum_name;
    value_without_const = value;
}

bool ALittleScriptGuessEnumName::IsChanged() const
{
    const auto element = enum_name_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}

