
#ifndef _ALITTLE_ALITTLESCRIPTGUESSCLASS_H_
#define _ALITTLE_ALITTLESCRIPTGUESSCLASS_H_

#include "ALittleScriptGuess.h"

class ALittleScriptClassDecElement;

class ALittleScriptGuessClass : public ALittleScriptGuess
{
public:
    // �����������
    std::string namespace_name;
    std::string class_name;

    // �౾�����ģ���б�
    std::vector<ABnfGuessWeakPtr> template_list;
    // �����ģ��ʵ��
    std::unordered_map<std::string, ABnfGuessWeakPtr> template_map;

    // �����using��������ģ���ô�������ֵ
    std::string using_name;
    std::weak_ptr<ALittleScriptClassDecElement> class_dec;

    // �Ƿ���ԭ����
    bool is_native = false;

    ALittleScriptGuessClass(const std::string& p_namespace_name, const std::string& p_class_name
        , const std::shared_ptr<ALittleScriptClassDecElement>& p_class_dec, const std::string& p_using_name, bool p_is_const, bool p_is_native);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSCLASS_H_
