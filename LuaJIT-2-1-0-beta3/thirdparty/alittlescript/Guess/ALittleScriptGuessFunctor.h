
#ifndef _ALITTLE_ALITTLESCRIPTGUESSFUNCTOR_H_
#define _ALITTLE_ALITTLESCRIPTGUESSFUNCTOR_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptGuessTemplate;

class ALittleScriptGuessFunctor : public ALittleScriptGuess
{
public:
    // 模板参数列表
    std::vector<std::weak_ptr<ALittleScriptGuessTemplate>> template_param_list;
    // 参数列表
    std::vector<ABnfGuessWeakPtr> param_list;
    // 参数名列表
    std::vector<std::string> param_name_list;
    // 参数是否可以为null
    std::vector<bool> param_nullable_list;
    // 参数占位符
    ABnfGuessWeakPtr param_tail;
    // 返回值列表
    std::vector<ABnfGuessWeakPtr> return_list;
    // 返回值占位符
    ABnfGuessWeakPtr return_tail;
    // 协议注解
    std::string proto;
    // 是否是await
    bool await_modifier = false;
    // 是否有const修饰
    bool const_modifier = false;
    // 产生当前Functor的节点对象
    std::weak_ptr<ABnfElement> element;

public:
    ALittleScriptGuessFunctor(std::shared_ptr<ABnfElement> p_element);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool HasAny() const override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSFUNCTOR_H_
