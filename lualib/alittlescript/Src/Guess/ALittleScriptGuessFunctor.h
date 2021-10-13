
#ifndef _ALITTLE_ALITTLESCRIPTGUESSFUNCTOR_H_
#define _ALITTLE_ALITTLESCRIPTGUESSFUNCTOR_H_

#include "ALittleScriptGuess.h"

class ALittleScriptGuessTemplate;

class ALittleScriptGuessFunctor : public ALittleScriptGuess
{
public:
    // ģ������б�
    std::vector<std::weak_ptr<ALittleScriptGuessTemplate>> template_param_list;
    // �����б�
    std::vector<ABnfGuessWeakPtr> param_list;
    // �������б�
    std::vector<std::string> param_name_list;
    // �����Ƿ����Ϊnull
    std::vector<bool> param_nullable_list;
    // ����ռλ��
    ABnfGuessWeakPtr param_tail;
    // ����ֵ�б�
    std::vector<ABnfGuessWeakPtr> return_list;
    // ����ֵռλ��
    ABnfGuessWeakPtr return_tail;
    // Э��ע��
    std::string proto;
    // �Ƿ���await
    bool await_modifier = false;
    // �Ƿ���const����
    bool const_modifier = false;
    // ������ǰFunctor�Ľڵ����
    std::weak_ptr<ABnfElement> element;

public:
    ALittleScriptGuessFunctor(const std::shared_ptr<ABnfElement>& p_element);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool HasAny() const override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSFUNCTOR_H_
