
#ifndef _ALITTLE_ALITTLESCRIPTGUESSCLASS_H_
#define _ALITTLE_ALITTLESCRIPTGUESSCLASS_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptClassDecElement;

class ALittleScriptGuessClass : public ALittleScriptGuess
{
public:
    // 命名域和类名
    std::string namespace_name;
    std::string class_name;

    // 类本身定义的模板列表
    std::vector<ABnfGuessWeakPtr> template_list;
    // 填充后的模板实例
    std::unordered_map<std::string, ABnfGuessWeakPtr> template_map;

    // 如果是using定义出来的，那么就有这个值
    std::string using_name;
    std::weak_ptr<ALittleScriptClassDecElement> class_dec;

    // 是否是原生类
    bool is_native = false;

    ALittleScriptGuessClass(const std::string& p_namespace_name, const std::string& p_class_name
        , std::shared_ptr<ALittleScriptClassDecElement> p_class_dec, const std::string& p_using_name, bool p_is_const, bool p_is_native);

    std::shared_ptr<ABnfElement> GetElement() override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue() override;
    bool IsChanged() const override;
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSCLASS_H_
