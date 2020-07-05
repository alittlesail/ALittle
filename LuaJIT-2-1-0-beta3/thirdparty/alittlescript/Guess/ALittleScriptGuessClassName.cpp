
#include "ALittleScriptGuessClassName.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"

#include "../../alanguage/Index/ABnfFactory.h"
#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

ALittleScriptGuessClassName::ALittleScriptGuessClassName(const std::string& p_namespace_name, const std::string& p_class_name, std::shared_ptr<ALittleScriptClassNameDecElement> p_class_name_dec)
{
    is_register = ALittleScriptUtility::IsRegister(p_class_name_dec);
    namespace_name = p_namespace_name;
    class_name = p_class_name;
    class_name_dec = p_class_name_dec;
}

std::shared_ptr<ABnfElement> ALittleScriptGuessClassName::GetElement() { return class_name_dec.lock(); }

bool ALittleScriptGuessClassName::NeedReplace() const
{
    return false;
}

ABnfGuessPtr ALittleScriptGuessClassName::ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    return shared_from_this();
}

ABnfGuessPtr ALittleScriptGuessClassName::Clone() const
{
    auto guess = std::shared_ptr<ALittleScriptGuessClassName>(new ALittleScriptGuessClassName(namespace_name, class_name, class_name_dec.lock()));
    guess->UpdateValue();
    return guess;
}

void ALittleScriptGuessClassName::UpdateValue()
{
    value = namespace_name + "." + class_name;
    value_without_const = value;
}

bool ALittleScriptGuessClassName::IsChanged() const
{
    auto element = class_name_dec.lock();
    if (element == nullptr) return true;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject())->GetGuessTypeList(element) == nullptr;
}
