
#ifndef _ALITTLE_ALITTLESCRIPTGUESSTEMPLATE_H_
#define _ALITTLE_ALITTLESCRIPTGUESSTEMPLATE_H_

#include "ALittleScriptGuess.h"

class ALittleScriptTemplatePairDecElement;

class ALittleScriptGuessTemplate : public ALittleScriptGuess
{
public:
    // ģ�巶Χ�޶�
    ABnfGuessWeakPtr template_extends;
    bool is_class;
    bool is_struct;

    // Ԫ�ض���
    std::weak_ptr<ALittleScriptTemplatePairDecElement> template_pair_dec;
    std::string native_value;
    
private:
    std::string total_value;

public:
    ALittleScriptGuessTemplate(const std::shared_ptr<ALittleScriptTemplatePairDecElement>& p_template_pair_dec
        , const ABnfGuessPtr& p_template_extends
        , bool p_is_class, bool p_is_struct);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    const std::string& GetTotalValue() override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSTEMPLATE_H_
