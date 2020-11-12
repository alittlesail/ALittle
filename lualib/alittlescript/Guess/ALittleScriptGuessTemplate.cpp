
#include "ALittleScriptGuessTemplate.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../Generate/ALittleScriptTemplatePairDecElement.h"
#include "../Generate/ALittleScriptTemplateNameDecElement.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

ALittleScriptGuessTemplate::ALittleScriptGuessTemplate(const std::shared_ptr<ALittleScriptTemplatePairDecElement>& p_template_pair_dec
    , const ABnfGuessPtr& p_template_extends
    , bool p_is_class, bool p_is_struct)
{
    is_register = ALittleScriptUtility::IsRegister(p_template_pair_dec);
    template_pair_dec = p_template_pair_dec;
    template_extends = p_template_extends;
    is_class = p_is_class;
    is_struct = p_is_struct;
    if (p_template_extends != nullptr) is_const = p_template_extends->is_const;

    auto name_dec = p_template_pair_dec->GetTemplateNameDec();
    if (name_dec != nullptr) native_value = name_dec->GetElementText();
}

std::shared_ptr<ABnfElement> ALittleScriptGuessTemplate::GetElement()
{
    return template_pair_dec.lock();
}

bool ALittleScriptGuessTemplate::NeedReplace() const
{
    return true;
}

ABnfGuessPtr ALittleScriptGuessTemplate::ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map)
{
    const auto it = fill_map.find(native_value);
    if (it != fill_map.end()) return it->second;
    return shared_from_this();
}

const std::string& ALittleScriptGuessTemplate::GetTotalValue()
{
    total_value.resize(0);
    if (is_const) total_value += "const ";
    total_value += native_value;

    const auto template_extends_e = template_extends.lock();
    if (template_extends_e != nullptr)
    {
        total_value += ":" + template_extends_e->GetValue();
        return total_value;
    }
    
    if (is_class)
    {
        total_value += ":class";
        return total_value;
    }
    
    if (is_struct)
    {
        total_value += ":struct";
        return total_value;
    }

    return total_value;
}

void ALittleScriptGuessTemplate::UpdateValue()
{
    value = "";
    value += native_value;
    value_without_const = value;
    if (is_const) value = "const " + value;
}

bool ALittleScriptGuessTemplate::IsChanged() const
{
    const auto template_extends_e = template_extends.lock();
    if (template_extends_e != nullptr && template_extends_e->IsChanged()) return true;
    const auto template_pair_dec_e = template_pair_dec.lock();
    if (template_pair_dec_e == nullptr) return true;
    return dynamic_cast<ALittleScriptIndex*>(template_pair_dec_e->GetFile()->GetProject())->GetGuessTypeList(template_pair_dec_e) == nullptr;
}
