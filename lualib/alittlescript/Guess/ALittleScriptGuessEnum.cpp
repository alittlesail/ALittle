
#include "ALittleScriptGuessEnum.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

#include "../Generate/ALittleScriptEnumDecElement.h"

ALittleScriptGuessEnum::ALittleScriptGuessEnum(const std::string& p_namespace_name, const std::string& p_enum_name
    , const std::shared_ptr<ALittleScriptEnumDecElement>& p_enum_dec)
{
    is_register = ALittleScriptUtility::IsRegister(p_enum_dec);
    namespace_name = p_namespace_name;
    enum_name = p_enum_name;
    enum_dec = p_enum_dec;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessEnum::GetElement() { return enum_dec.lock(); }

bool ALittleScriptGuessEnum::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessEnum::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessEnum::Clone() const
{
    return std::make_shared<ALittleScriptGuessEnum>(namespace_name, enum_name, enum_dec.lock());
}

void ALittleScriptGuessEnum::UpdateValue()
{
    value = namespace_name + "." + enum_name;
    value_without_const = value;
}

bool ALittleScriptGuessEnum::IsChanged() const
{
    const auto element = enum_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}

