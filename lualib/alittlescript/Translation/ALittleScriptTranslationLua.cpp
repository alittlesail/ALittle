#include "ALittleScriptTranslationLua.h"

#include "../../alanguage/Index/ABnfFactory.h"

#include "../Generate/ALittleScriptKeyElement.h"
#include "../Generate/ALittleScriptStringElement.h"
#include "../Generate/ALittleScriptRegexElement.h"
#include "../Generate/ALittleScriptConstModifierElement.h"
#include "../Generate/ALittleScriptOp8SuffixEeElement.h"
#include "../Generate/ALittleScriptRootElement.h"
#include "../Generate/ALittleScriptElseIfConditionElement.h"
#include "../Generate/ALittleScriptNumberElement.h"
#include "../Generate/ALittleScriptProtocolModifierElement.h"
#include "../Generate/ALittleScriptLineCommentElement.h"
#include "../Generate/ALittleScriptMethodReturnTailDecElement.h"
#include "../Generate/ALittleScriptIdElement.h"
#include "../Generate/ALittleScriptBlockCommentElement.h"
#include "../Generate/ALittleScriptStructOptionDecElement.h"
#include "../Generate/ALittleScriptTextElement.h"
#include "../Generate/ALittleScriptRegisterModifierElement.h"
#include "../Generate/ALittleScriptAccessModifierElement.h"
#include "../Generate/ALittleScriptMethodSetterParamDecElement.h"
#include "../Generate/ALittleScriptTemplateExtendsClassDecElement.h"
#include "../Generate/ALittleScriptOp7SuffixEeElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptModifierElement.h"
#include "../Generate/ALittleScriptCoroutineModifierElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Generate/ALittleScriptCommandBodyDecElement.h"
#include "../Generate/ALittleScriptTemplateExtendsStructDecElement.h"
#include "../Generate/ALittleScriptAllTypeConstElement.h"
#include "../Generate/ALittleScriptCommandModifierElement.h"
#include "../Generate/ALittleScriptOp5Element.h"
#include "../Generate/ALittleScriptNullableModifierElement.h"
#include "../Generate/ALittleScriptMethodParamTailDecElement.h"
#include "../Generate/ALittleScriptForInConditionElement.h"
#include "../Generate/ALittleScriptStructDecElement.h"
#include "../Generate/ALittleScriptOpAssignExprElement.h"
#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptLanguageNameDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptLanguageBodyDecElement.h"
#include "../Generate/ALittleScriptEnumVarNameDecElement.h"
#include "../Generate/ALittleScriptLanguageModifierElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"
#include "../Generate/ALittleScriptNativeModifierElement.h"
#include "../Generate/ALittleScriptAttributeModifierElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptOp4SuffixEeElement.h"
#include "../Generate/ALittleScriptTemplatePairDecElement.h"
#include "../Generate/ALittleScriptOp6SuffixExElement.h"
#include "../Generate/ALittleScriptTemplateNameDecElement.h"
#include "../Generate/ALittleScriptTemplateExtendsDecElement.h"
#include "../Generate/ALittleScriptClassVarNameDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptMethodBodyDecElement.h"
#include "../Generate/ALittleScriptForBodyElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptClassExtendsDecElement.h"
#include "../Generate/ALittleScriptElseExprElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptOp6SuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueThisTypeElement.h"
#include "../Generate/ALittleScriptClassBodyDecElement.h"
#include "../Generate/ALittleScriptClassVarValueDecElement.h"
#include "../Generate/ALittleScriptUsingNameDecElement.h"
#include "../Generate/ALittleScriptClassVarDecElement.h"
#include "../Generate/ALittleScriptStructExtendsDecElement.h"
#include "../Generate/ALittleScriptPropertyValueMethodCallElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptReturnYieldElement.h"
#include "../Generate/ALittleScriptStructBodyDecElement.h"
#include "../Generate/ALittleScriptMethodGetterParamDecElement.h"
#include "../Generate/ALittleScriptGenericTypeElement.h"
#include "../Generate/ALittleScriptStructVarNameDecElement.h"
#include "../Generate/ALittleScriptOp7SuffixElement.h"
#include "../Generate/ALittleScriptGenericFunctorParamTypeElement.h"
#include "../Generate/ALittleScriptStructOptionNameDecElement.h"
#include "../Generate/ALittleScriptEnumDecElement.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptEnumBodyDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptInstanceDecElement.h"
#include "../Generate/ALittleScriptUsingDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"
#include "../Generate/ALittleScriptPropertyValueDotIdElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptMethodReturnOneDecElement.h"
#include "../Generate/ALittleScriptOp3Element.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptOpNewListStatElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptAllExprElement.h"
#include "../Generate/ALittleScriptEmptyExprElement.h"
#include "../Generate/ALittleScriptForExprElement.h"
#include "../Generate/ALittleScriptForConditionElement.h"
#include "../Generate/ALittleScriptForStepConditionElement.h"
#include "../Generate/ALittleScriptForStartStatElement.h"
#include "../Generate/ALittleScriptForEndStatElement.h"
#include "../Generate/ALittleScriptForStepStatElement.h"
#include "../Generate/ALittleScriptForPairDecElement.h"
#include "../Generate/ALittleScriptWhileExprElement.h"
#include "../Generate/ALittleScriptWhileConditionElement.h"
#include "../Generate/ALittleScriptWhileBodyElement.h"
#include "../Generate/ALittleScriptOp2StatElement.h"
#include "../Generate/ALittleScriptDoWhileExprElement.h"
#include "../Generate/ALittleScriptDoWhileConditionElement.h"
#include "../Generate/ALittleScriptDoWhileBodyElement.h"
#include "../Generate/ALittleScriptIfExprElement.h"
#include "../Generate/ALittleScriptIfConditionElement.h"
#include "../Generate/ALittleScriptIfBodyElement.h"
#include "../Generate/ALittleScriptElseBodyElement.h"
#include "../Generate/ALittleScriptElseIfExprElement.h"
#include "../Generate/ALittleScriptElseIfBodyElement.h"
#include "../Generate/ALittleScriptWrapExprElement.h"
#include "../Generate/ALittleScriptReturnExprElement.h"
#include "../Generate/ALittleScriptFlowExprElement.h"
#include "../Generate/ALittleScriptVarAssignExprElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptOpAssignElement.h"
#include "../Generate/ALittleScriptOp1ExprElement.h"
#include "../Generate/ALittleScriptThrowExprElement.h"
#include "../Generate/ALittleScriptAssertExprElement.h"
#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptCustomTypeNameElement.h"
#include "../Generate/ALittleScriptOp4StatElement.h"
#include "../Generate/ALittleScriptCustomTypeDotIdElement.h"
#include "../Generate/ALittleScriptCustomTypeDotIdNameElement.h"
#include "../Generate/ALittleScriptCustomTypeTemplateElement.h"
#include "../Generate/ALittleScriptGenericMapTypeElement.h"
#include "../Generate/ALittleScriptPrimitiveTypeElement.h"
#include "../Generate/ALittleScriptGenericListTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorParamOneTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorParamTailElement.h"
#include "../Generate/ALittleScriptGenericFunctorReturnTailElement.h"
#include "../Generate/ALittleScriptGenericFunctorReturnOneTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorReturnTypeElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptValueFactorStatElement.h"
#include "../Generate/ALittleScriptValueOpStatElement.h"
#include "../Generate/ALittleScriptOpNewStatElement.h"
#include "../Generate/ALittleScriptBindStatElement.h"
#include "../Generate/ALittleScriptTcallStatElement.h"
#include "../Generate/ALittleScriptWrapValueStatElement.h"
#include "../Generate/ALittleScriptConstValueElement.h"
#include "../Generate/ALittleScriptCoroutineStatElement.h"
#include "../Generate/ALittleScriptReflectValueElement.h"
#include "../Generate/ALittleScriptReflectCustomTypeElement.h"
#include "../Generate/ALittleScriptReflectValueStatElement.h"
#include "../Generate/ALittleScriptPathsValueElement.h"
#include "../Generate/ALittleScriptPropertyValueFirstTypeElement.h"
#include "../Generate/ALittleScriptPropertyValueCastTypeElement.h"
#include "../Generate/ALittleScriptPropertyValueCustomTypeElement.h"
#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueDotIdNameElement.h"
#include "../Generate/ALittleScriptPropertyValueBracketValueElement.h"
#include "../Generate/ALittleScriptPropertyValueMethodTemplateElement.h"
#include "../Generate/ALittleScriptOp12Element.h"
#include "../Generate/ALittleScriptOp12StatElement.h"
#include "../Generate/ALittleScriptOp12SuffixElement.h"
#include "../Generate/ALittleScriptOp12SuffixExElement.h"
#include "../Generate/ALittleScriptOp11Element.h"
#include "../Generate/ALittleScriptOp11StatElement.h"
#include "../Generate/ALittleScriptOp11SuffixElement.h"
#include "../Generate/ALittleScriptOp11SuffixExElement.h"
#include "../Generate/ALittleScriptOp10Element.h"
#include "../Generate/ALittleScriptOp10StatElement.h"
#include "../Generate/ALittleScriptOp10SuffixElement.h"
#include "../Generate/ALittleScriptOp10SuffixExElement.h"
#include "../Generate/ALittleScriptOp9Element.h"
#include "../Generate/ALittleScriptOp9StatElement.h"
#include "../Generate/ALittleScriptOp9SuffixElement.h"
#include "../Generate/ALittleScriptOp9SuffixExElement.h"
#include "../Generate/ALittleScriptOp8Element.h"
#include "../Generate/ALittleScriptOp8StatElement.h"
#include "../Generate/ALittleScriptOp8SuffixElement.h"
#include "../Generate/ALittleScriptOp8SuffixExElement.h"
#include "../Generate/ALittleScriptOp7Element.h"
#include "../Generate/ALittleScriptOp7StatElement.h"
#include "../Generate/ALittleScriptOp7SuffixExElement.h"
#include "../Generate/ALittleScriptOp6Element.h"
#include "../Generate/ALittleScriptOp6StatElement.h"
#include "../Generate/ALittleScriptOp6SuffixEeElement.h"
#include "../Generate/ALittleScriptOp5StatElement.h"
#include "../Generate/ALittleScriptOp5SuffixElement.h"
#include "../Generate/ALittleScriptOp5SuffixEeElement.h"
#include "../Generate/ALittleScriptOp5SuffixExElement.h"
#include "../Generate/ALittleScriptOp4Element.h"
#include "../Generate/ALittleScriptOp4SuffixElement.h"
#include "../Generate/ALittleScriptOp4SuffixExElement.h"
#include "../Generate/ALittleScriptOp3StatElement.h"
#include "../Generate/ALittleScriptOp3SuffixElement.h"
#include "../Generate/ALittleScriptOp3SuffixExElement.h"
#include "../Generate/ALittleScriptOp2Element.h"
#include "../Generate/ALittleScriptOp2ValueElement.h"
#include "../Generate/ALittleScriptOp2SuffixExElement.h"
#include "../Generate/ALittleScriptOp1Element.h"

#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessClassName.h"
#include "../Guess/ALittleScriptGuessClassTemplate.h"
#include "../Guess/ALittleScriptGuessConst.h"
#include "../Guess/ALittleScriptGuessEnum.h"
#include "../Guess/ALittleScriptGuessEnumName.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessMethodTemplate.h"
#include "../Guess/ALittleScriptGuessNamespace.h"
#include "../Guess/ALittleScriptGuessNamespaceName.h"
#include "../Guess/ALittleScriptGuessParamTail.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessStructName.h"
#include "../Guess/ALittleScriptGuessTemplate.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptProjectClass.h"

#include "../Reference/ALittleScriptPropertyValueMethodCallReference.h"
#include "../Reference/ALittleScriptPropertyValueCustomTypeReference.h"
#include "../Reference/ALittleScriptCustomTypeReference.h"

ABnfGuessError ALittleScriptTranslationLua::GenerateBindStat(std::shared_ptr<ALittleScriptBindStatElement> bind_stat, const std::string& pre_tab, std::string& content)
{
    const auto& value_stat_list = bind_stat->GetValueStatList();

    content = "Lua.Bind(";
    std::vector<std::string> param_list;
    for (auto& value_stat : value_stat_list)
    {
        std::string sub_content;
        auto error = GenerateValueStat(value_stat, pre_tab, sub_content);
        if (error) return error;
        param_list.push_back(sub_content);
    }
    content += ABnfFactory::Join(param_list, u8", ");
    content += ")";
    return nullptr;
}

// ����tcall����

ABnfGuessError ALittleScriptTranslationLua::GenerateTcallStat(std::shared_ptr<ALittleScriptTcallStatElement> tcall_stat, const std::string& pre_tab, std::string& content)
{
    const auto& value_stat_list = tcall_stat->GetValueStatList();

    content = "Lua.TCall(";
    std::vector<std::string> param_list;
    for (auto& value_stat : value_stat_list)
    {
        std::string sub_content;
        auto error = GenerateValueStat(value_stat, pre_tab, sub_content);
        if (error) return error;
        param_list.push_back(sub_content);
    }
    content += ABnfFactory::Join(param_list, u8", ");
    content += ")";
    return nullptr;
}

// ����new List

ABnfGuessError ALittleScriptTranslationLua::GenerateOpNewListStat(std::shared_ptr<ALittleScriptOpNewListStatElement> op_new_list, const std::string& pre_tab, std::string& content)
{
    const auto& value_stat_list = op_new_list->GetValueStatList();

    content = "{";
    std::vector<std::string> param_list;
    for (auto& value_stat : value_stat_list)
    {
        std::string sub_content;
        auto error = GenerateValueStat(value_stat, pre_tab, sub_content);
        if (error) return error;
        param_list.push_back(sub_content);
    }
    content += ABnfFactory::Join(param_list, u8", ");
    content += "}";
    return nullptr;
}

// ����new

ABnfGuessError ALittleScriptTranslationLua::GenerateOpNewStat(std::shared_ptr<ALittleScriptOpNewStatElement> op_new_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    // �����ͨ������
    auto generic_type = op_new_stat->GetGenericType();
    if (generic_type != nullptr)
    {
        // �����Map����ôֱ�ӷ���{}
        auto map_type = generic_type->GetGenericMapType();
        if (map_type != nullptr)
        {
            content = "{}";
            return nullptr;
        }

        // �����List����ôֱ�ӷ���{}
        auto list_type = generic_type->GetGenericListType();
        if (list_type != nullptr)
        {
            content = "{}";
            return nullptr;
        }

        auto functor_type = generic_type->GetGenericFunctorType();
        if (functor_type != nullptr)
            return ABnfGuessError(generic_type, u8"Functor����ʹ��new������");
    }

    // �Զ�������
    auto custom_type = op_new_stat->GetCustomType();
    if (custom_type != nullptr)
    {
        ABnfGuessPtr guess;
        auto error = custom_type->GuessType(guess);
        if (error) return error;

        // �����Map����ôֱ�ӷ���{}
        if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
        {
            content = "{}";
            return nullptr;
        }

        // �����List����ôֱ�ӷ���{}
        if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
        {
            content = "{}";
            return nullptr;
        }

        // ����ǽṹ��
        if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            content = "{}";
            return nullptr;
        }

        // �������
        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        {
            // ����custom_type��
            error = GenerateCustomType(custom_type, pre_tab, content);
            if (error) return error;
            content += "(";
            std::vector<std::string> param_list;
            const auto& value_stat_list = op_new_stat->GetValueStatList();
            for (auto& value_stat : value_stat_list)
            {
                std::string sub_content;
                error = GenerateValueStat(value_stat, pre_tab, sub_content);
                if (error) return error;
                param_list.push_back(sub_content);
            }
            content += ABnfFactory::Join(param_list, u8", ");
            content += ")";
            return nullptr;
        }

        // ����Ǻ���ģ�����
        if (std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess);
            if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_template->template_extends.lock()) || guess_template->is_struct)
            {
                content = "{}";
                return nullptr;
            }

            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess_template->template_extends.lock()) || guess_template->is_class)
            {
                content = guess_template->GetValue() + "()";
                return nullptr;
            }
        }

        // �������ģ�����
        if (std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess);
            if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_template->template_extends.lock()) || guess_template->is_struct)
            {
                content = "{}";
                return nullptr;
            }

            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess_template->template_extends.lock()))
            {
                // ����custom_type��
                error = GenerateCustomType(custom_type, pre_tab, content);
                if (error) return error;
                content += "(";
                std::vector<std::string> param_list;
                const auto& value_stat_list = op_new_stat->GetValueStatList();
                for (auto& value_stat : value_stat_list)
                {
                    std::string sub_content;
                    error = GenerateValueStat(value_stat, pre_tab, sub_content);
                    if (error) return error;
                    param_list.push_back(sub_content);
                }
                content += ABnfFactory::Join(param_list, u8", ");
                content += ")";
                return nullptr;
            }

            if (guess_template->is_class)
            {
                return ABnfGuessError(op_new_stat, u8"��ģ��ֻ��class������ȷ�����Ĺ����������");
            }
        }
    }

    return ABnfGuessError(op_new_stat, u8"new δ֪����");
}

// ����custom_type�����е�ģ������б�
ABnfGuessError ALittleScriptTranslationLua::GenerateCustomTypeTemplateList(std::vector<ABnfGuessPtr>& guess_list, std::vector<std::string>& template_param_list, std::vector<std::string>& template_param_name_list)
{
    for (size_t index = 0; index < guess_list.size(); ++index)
    {
        auto guess = guess_list[index];
        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        {
            auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
            // �������
            AddRelay(guess_class->class_dec.lock());
            // ���û��ģ�����
            if (guess_class->template_list.size() == 0)
            {
                // ��ȡ����
                std::string name = guess_class->GetValue();
                // �������using�����������ʹ��using_name
                if (guess_class->using_name.size()) name = guess_class->using_name;
                // ������ƣ��������������뵱ǰ��ͬ��������lua����ô��ȥ��
                std::vector<std::string> split;
                ABnfFactory::Split(name, ".", split);
                if (split.size() == 2 && split[0] == "lua")
                    template_param_list.push_back(split[1]);
                else
                    template_param_list.push_back(name);
                template_param_name_list.push_back(name);
            }
            // ��ģ�����
            else
            {
                // ���ģ�����
                std::vector<ABnfGuessPtr> sub_guess_list;
                for (auto& sub_guess_w : guess_class->template_list)
                {
                    auto sub_guess = sub_guess_w.lock();
                    if (sub_guess == nullptr) return ABnfGuessError(nullptr, u8"����ģ��������ʧЧ��");

                    ABnfGuessPtr value_guess;
                    auto it = guess_class->template_map.find(sub_guess->GetValueWithoutConst());
                    if (it == guess_class->template_map.end() || !it->second.lock())
                        return ABnfGuessError(nullptr, u8"����ģ��û��������");
                    value_guess = it->second.lock();
                    if (sub_guess->is_const && !value_guess->is_const)
                    {
                        value_guess = value_guess->Clone();
                        value_guess->is_const = true;
                        value_guess->UpdateValue();
                    }
                    sub_guess_list.push_back(value_guess);
                }
                // ��ȡ��ģ�����
                std::vector<std::string> sub_template_param_list;
                std::vector<std::string> sub_template_param_name_list;
                auto error = GenerateCustomTypeTemplateList(sub_guess_list, sub_template_param_list, sub_template_param_name_list);
                if (error) return error;

                // �������������
                std::string full_class_name = guess_class->namespace_name + "." + guess_class->class_name;

                // ����ʵ������
                std::string class_name = full_class_name;
                if (guess_class->namespace_name == "lua")
                    class_name = guess_class->class_name;

                // ����ģ����
                std::string template_name = full_class_name + "<" + ABnfFactory::Join(sub_template_param_name_list, ", ") + ">";

                std::string content = "Lua.Template(" + class_name;
                content += ", \"" + template_name + "\"";
                if (sub_template_param_list.size() > 0)
                    content += ", " + ABnfFactory::Join(sub_template_param_list, ", ");

                content += ")";
                template_param_name_list.push_back(template_name);
                template_param_list.push_back(content);
            }
        }
        // ����ǽṹ��
        else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            template_param_name_list.push_back(guess->GetValue());
            m_need_all_struct = true;
            template_param_list.push_back("___all_struct[" + std::to_string(ALittleScriptUtility::StructHash(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))) + "]");
            auto error = GenerateReflectStructInfo(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess));
            if (error) return error;
        }
        // ����Ǻ���ģ�����
        else if (std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess);
            template_param_list.push_back(guess_template->GetValue());
            // ������ǽṹ�������
            if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_template->template_extends.lock()) || guess_template->is_struct)
                template_param_name_list.push_back("\".." + guess_template->GetValue() + ".name..\"");
            else
                template_param_name_list.push_back("\".." + guess_template->GetValue() + ".__name..\"");
        }
        // �������ģ�����
        else if (std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess);
            template_param_list.push_back("self.__class.__element[" + std::to_string(index + 1) + "]");
            // ������ǽṹ�������
            if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_template->template_extends.lock()) || guess_template->is_struct)
                template_param_name_list.push_back("\"..self.__class.__element[" + std::to_string(index + 1) + "].name..\"");
            else
                template_param_name_list.push_back("\"..self.__class.__element[" + std::to_string(index + 1) + "].__name..\"");
        }
        // �������ͣ�ֱ����nil
        else
        {
            template_param_name_list.push_back(guess->GetValue());
            template_param_list.push_back("nil");
        }
    }
    return nullptr;
}

// ����custom_type
ABnfGuessError ALittleScriptTranslationLua::GenerateCustomType(std::shared_ptr<ALittleScriptCustomTypeElement> custom_type, const std::string& pre_tab, std::string& content)
{
    content = "";

    ABnfGuessPtr guess;
    auto error = custom_type->GuessType(guess);
    if (error) return error;

    // ����ǽṹ��������ô�͵���������
    if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
    {
        content = "{}";
        return nullptr;
    }
    // �������
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
    {
        auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
        // �������
        AddRelay(guess_class->class_dec.lock());

        // ����custom_type������������͵�ǰ�ļ�������һ�£���������lua�������£�ȡ��������ǰ׺
        auto name_dec = custom_type->GetCustomTypeName();
        if (name_dec == nullptr) return ABnfGuessError(custom_type, u8"���ʽ������");
        std::string class_name = name_dec->GetElementText();

        auto dot_id = custom_type->GetCustomTypeDotId();
        if (dot_id != nullptr)
        {
            auto dot_id_name = dot_id->GetCustomTypeDotIdName();
            if (dot_id_name != nullptr)
            {
                if (class_name == "lua")
                    class_name = dot_id_name->GetElementText();
                else
                    class_name += "." + dot_id_name->GetElementText();
            }
            else
            {
                // �ж�custom_type����Դ
                std::string pre_namespace_name;
                error = dynamic_cast<ALittleScriptCustomTypeReference*>(custom_type->GetReference())->CalcNamespaceName(pre_namespace_name);
                if (error) return error;

                if (pre_namespace_name == "alittle" || pre_namespace_name == "lua") pre_namespace_name = "";
                if (pre_namespace_name.size() > 0) pre_namespace_name += ".";

                class_name = pre_namespace_name + class_name;
            }
        }
        else
        {
            // �ж�custom_type����Դ
            std::string pre_namespace_name;
            error = dynamic_cast<ALittleScriptCustomTypeReference*>(custom_type->GetReference())->CalcNamespaceName(pre_namespace_name);
            if (error) return error;

            if (pre_namespace_name == "alittle" || pre_namespace_name == "lua") pre_namespace_name = "";
            if (pre_namespace_name.size() > 0) pre_namespace_name += ".";

            class_name = pre_namespace_name + class_name;
        }

        // ��������ģ���������ô��ģ��ģ��
        std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> all_type_list;
        if (custom_type->GetCustomTypeTemplate() != nullptr) all_type_list = custom_type->GetCustomTypeTemplate()->GetAllTypeList();

        if (all_type_list.size() > 0)
        {
            // ��ȡ����ģ�����
            std::vector<ABnfGuessPtr> guess_list;
            for (auto& all_type : all_type_list)
            {
                ABnfGuessPtr sub_guess;
                error = all_type->GuessType(sub_guess);
                if (error) return error;
                guess_list.push_back(sub_guess);
            }
            // ����ģ����Ϣ
            std::vector<std::string> template_param_list;
            std::vector<std::string> template_param_name_list;
            error = GenerateCustomTypeTemplateList(guess_list, template_param_list, template_param_name_list);
            if (error) return error;

            std::string template_name = guess_class->namespace_name + "." + guess_class->class_name;
            template_name += "<" + ABnfFactory::Join(template_param_name_list, ", ") + ">";

            content = "Lua.Template(" + class_name;
            content += ", \"" + template_name + "\"";
            if (template_param_list.size() > 0)
                content += ", " + ABnfFactory::Join(template_param_list, ", ");
            content += ")";

            return nullptr;
        }
        else
        {
            content = class_name;
            return nullptr;
        }
    }
    // ����Ǻ���ģ�����
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess))
    {
        content = guess->GetValue();
        return nullptr;
    }
    // �������ģ��Ԫ��
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess))
    {
        auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess);
        // ����±�
        auto template_pair_dec = guess_template->template_pair_dec.lock();
        if (template_pair_dec == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
        auto template_dec = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(template_pair_dec->GetParent());
        int index = -1;
        for (size_t i = 0; i < template_dec->GetTemplatePairDecList().size(); ++i)
        {
            if (template_dec->GetTemplatePairDecList()[i] == template_pair_dec)
            {
                index = static_cast<int>(i);
                break;
            }
        }
        // ģ��Ԫ��
        content = "self.__class.__element[" + std::to_string(index + 1) + "]";
        return nullptr;
    }

    return ABnfGuessError(nullptr, u8"δ֪�ı��ʽ����");
}

// ����12�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp12Suffix(std::shared_ptr<ALittleScriptOp12SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp12()->GetElementText();
    if (op_string == "||") op_string = "or";

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp12SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string suffix_ee_result;
        auto error = GenerateOp12SuffixEe(suffix_ee, pre_tab, suffix_ee_result);
        if (error) return error;
        suffix_content_list.push_back(suffix_ee_result);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp12SuffixEe(std::shared_ptr<ALittleScriptOp12SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp12SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp12SuffixEx(std::shared_ptr<ALittleScriptOp12SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp12SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp12Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp12StatElement> op_12_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_12_stat->GetOp12Suffix();
    std::string suffix_result;
    error = GenerateOp12Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_12_stat->GetOp12SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp12SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����11�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp11Suffix(std::shared_ptr<ALittleScriptOp11SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp11()->GetElementText();
    if (op_string == "&&")
        op_string = "and";

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp11SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp11SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp11SuffixEe(std::shared_ptr<ALittleScriptOp11SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp11SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp11SuffixEx(std::shared_ptr<ALittleScriptOp11SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp11SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp11Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp11StatElement> op_11_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_11_stat->GetOp11Suffix();
    std::string suffix_result;
    error = GenerateOp11Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_11_stat->GetOp11SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp11SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����10�������

ABnfGuessError ALittleScriptTranslationLua::GenerateOp10Suffix(std::shared_ptr<ALittleScriptOp10SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp10()->GetElementText();
    if (op_string == "!=")
        op_string = "~=";

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp10SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp10SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp10SuffixEe(std::shared_ptr<ALittleScriptOp10SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp10SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp10SuffixEx(std::shared_ptr<ALittleScriptOp10SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp10SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp10Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp10StatElement> op_10_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_10_stat->GetOp10Suffix();
    std::string suffix_result;
    error = GenerateOp10Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_10_stat->GetOp10SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp10SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����9�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp9Suffix(std::shared_ptr<ALittleScriptOp9SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp9()->GetElementText();

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp9SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp9SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp9SuffixEe(std::shared_ptr<ALittleScriptOp9SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp9SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp9SuffixEx(std::shared_ptr<ALittleScriptOp9SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp9SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp9Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp9StatElement> op_9_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_9_stat->GetOp9Suffix();
    std::string suffix_result;
    error = GenerateOp9Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_9_stat->GetOp9SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp9SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����8�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp8Suffix(std::shared_ptr<ALittleScriptOp8SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp8()->GetElementText();

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp8SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp8SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = "~ " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp8SuffixEe(std::shared_ptr<ALittleScriptOp8SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp8SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp8SuffixEx(std::shared_ptr<ALittleScriptOp8SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp8SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp8Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp8StatElement> op_8_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_8_stat->GetOp8Suffix();
    std::string suffix_result;
    error = GenerateOp8Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_8_stat->GetOp8SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp8SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����7�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp7Suffix(std::shared_ptr<ALittleScriptOp7SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp7()->GetElementText();

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp7SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp7SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp7SuffixEe(std::shared_ptr<ALittleScriptOp7SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp7SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp7SuffixEx(std::shared_ptr<ALittleScriptOp7SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp7SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp7Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp7StatElement> op_7_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_7_stat->GetOp7Suffix();
    std::string suffix_result;
    error = GenerateOp7Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_7_stat->GetOp7SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp7SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����6�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp6Suffix(std::shared_ptr<ALittleScriptOp6SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp6()->GetElementText();
    if (op_string == "->>")
        op_string = ">>";
    else if (op_string == "<<-")
        op_string = "<<";

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp6SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp6SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp6SuffixEe(std::shared_ptr<ALittleScriptOp6SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp6SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp6SuffixEx(std::shared_ptr<ALittleScriptOp6SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp6SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp6Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp6StatElement> op_6_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_6_stat->GetOp6Suffix();
    std::string suffix_result;
    error = GenerateOp6Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_6_stat->GetOp6SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp6SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����5�������
ABnfGuessError ALittleScriptTranslationLua::GenerateOp5Suffix(std::shared_ptr<ALittleScriptOp5SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp5()->GetElementText();

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp5SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp5SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp5SuffixEe(std::shared_ptr<ALittleScriptOp5SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp5SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp5SuffixEx(std::shared_ptr<ALittleScriptOp5SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp5SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp5Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp5StatElement> op_5_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_5_stat->GetOp5Suffix();
    std::string suffix_result;
    error = GenerateOp5Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_5_stat->GetOp5SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp5SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����4�������

ABnfGuessError ALittleScriptTranslationLua::GenerateOp4Suffix(std::shared_ptr<ALittleScriptOp4SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp4()->GetElementText();

    std::string value_functor_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_functor_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_functor_result);
        if (error) return error;
    }

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ee_list = suffix->GetOp4SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        std::string sub_content;
        auto error = GenerateOp4SuffixEe(suffix_ee, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = op_string + " " + value_functor_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp4SuffixEe(std::shared_ptr<ALittleScriptOp4SuffixEeElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp4SuffixEe����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp4SuffixEx(std::shared_ptr<ALittleScriptOp4SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp4SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp4Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp4StatElement> op_4_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_4_stat->GetOp4Suffix();
    std::string suffix_result;
    error = GenerateOp4Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_4_stat->GetOp4SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp4SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����3�������

ABnfGuessError ALittleScriptTranslationLua::GenerateOp3Suffix(std::shared_ptr<ALittleScriptOp3SuffixElement> suffix, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string op_string = suffix->GetOp3()->GetElementText();

    std::string value_result;
    if (suffix->GetValueFactorStat() != nullptr)
    {
        auto error = GenerateValueFactorStat(suffix->GetValueFactorStat(), pre_tab, value_result);
        if (error) return error;
    }
    else if (suffix->GetOp2Value() != nullptr)
    {
        auto error = GenerateOp2Value(suffix->GetOp2Value(), pre_tab, value_result);
        if (error) return error;
    }
    else
    {
        return ABnfGuessError(nullptr, u8"GenerateOp3Suffix����δ֪�ı��ʽ");
    }

    content = op_string + " " + value_result;
    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp3SuffixEx(std::shared_ptr<ALittleScriptOp3SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp3SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateValueOpStat(std::shared_ptr<ALittleScriptValueOpStatElement> value_op_stat, const std::string& pre_tab, std::string& content)
{
    content = "";

    auto value_factor_stat = value_op_stat->GetValueFactorStat();
    if (value_factor_stat == nullptr) return ABnfGuessError(nullptr, u8"���ʽ������");

    if (value_op_stat->GetOp3Stat() != nullptr)
        return GenerateOp3Stat(value_factor_stat, value_op_stat->GetOp3Stat(), pre_tab, content);

    if (value_op_stat->GetOp4Stat() != nullptr)
        return GenerateOp4Stat(value_factor_stat, value_op_stat->GetOp4Stat(), pre_tab, content);

    if (value_op_stat->GetOp5Stat() != nullptr)
        return GenerateOp5Stat(value_factor_stat, value_op_stat->GetOp5Stat(), pre_tab, content);

    if (value_op_stat->GetOp6Stat() != nullptr)
        return GenerateOp6Stat(value_factor_stat, value_op_stat->GetOp6Stat(), pre_tab, content);

    if (value_op_stat->GetOp7Stat() != nullptr)
        return GenerateOp7Stat(value_factor_stat, value_op_stat->GetOp7Stat(), pre_tab, content);

    if (value_op_stat->GetOp8Stat() != nullptr)
        return GenerateOp8Stat(value_factor_stat, value_op_stat->GetOp8Stat(), pre_tab, content);

    if (value_op_stat->GetOp9Stat() != nullptr)
        return GenerateOp9Stat(value_factor_stat, value_op_stat->GetOp9Stat(), pre_tab, content);

    if (value_op_stat->GetOp10Stat() != nullptr)
        return GenerateOp10Stat(value_factor_stat, value_op_stat->GetOp10Stat(), pre_tab, content);

    if (value_op_stat->GetOp11Stat() != nullptr)
        return GenerateOp11Stat(value_factor_stat, value_op_stat->GetOp11Stat(), pre_tab, content);

    if (value_op_stat->GetOp12Stat() != nullptr)
        return GenerateOp12Stat(value_factor_stat, value_op_stat->GetOp12Stat(), pre_tab, content);

    return GenerateValueFactorStat(value_factor_stat, pre_tab, content);
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp3Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp3StatElement> op_3_stat, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string value_functor_result;
    auto error = GenerateValueFactorStat(value_factor_stat, pre_tab, value_functor_result);
    if (error) return error;

    auto suffix = op_3_stat->GetOp3Suffix();
    std::string suffix_result;
    error = GenerateOp3Suffix(suffix, pre_tab, suffix_result);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_3_stat->GetOp3SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp3SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    content = value_functor_result + " " + suffix_result;
    if (suffix_content_list.size() > 0) content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����2�������

ABnfGuessError ALittleScriptTranslationLua::GenerateOp2SuffixEx(std::shared_ptr<ALittleScriptOp2SuffixExElement> suffix, const std::string& pre_tab, std::string& content)
{
    if (suffix->GetOp3Suffix() != nullptr)
        return GenerateOp3Suffix(suffix->GetOp3Suffix(), pre_tab, content);
    else if (suffix->GetOp4Suffix() != nullptr)
        return GenerateOp4Suffix(suffix->GetOp4Suffix(), pre_tab, content);
    else if (suffix->GetOp5Suffix() != nullptr)
        return GenerateOp5Suffix(suffix->GetOp5Suffix(), pre_tab, content);
    else if (suffix->GetOp6Suffix() != nullptr)
        return GenerateOp6Suffix(suffix->GetOp6Suffix(), pre_tab, content);
    else if (suffix->GetOp7Suffix() != nullptr)
        return GenerateOp7Suffix(suffix->GetOp7Suffix(), pre_tab, content);
    else if (suffix->GetOp8Suffix() != nullptr)
        return GenerateOp8Suffix(suffix->GetOp8Suffix(), pre_tab, content);
    else if (suffix->GetOp9Suffix() != nullptr)
        return GenerateOp9Suffix(suffix->GetOp9Suffix(), pre_tab, content);
    else if (suffix->GetOp10Suffix() != nullptr)
        return GenerateOp10Suffix(suffix->GetOp10Suffix(), pre_tab, content);
    else if (suffix->GetOp11Suffix() != nullptr)
        return GenerateOp11Suffix(suffix->GetOp11Suffix(), pre_tab, content);
    else if (suffix->GetOp12Suffix() != nullptr)
        return GenerateOp12Suffix(suffix->GetOp12Suffix(), pre_tab, content);
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"GenerateOp2SuffixEx����δ֪�ı��ʽ");
    }
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp2Value(std::shared_ptr<ALittleScriptOp2ValueElement> op_2_value, const std::string& pre_tab, std::string& content)
{
    content = "";

    auto value_factor = op_2_value->GetValueFactorStat();
    if (value_factor == nullptr)
        return ABnfGuessError(nullptr, u8"GenerateOp2Stat��Ŀ����û�в�������");

    std::string value_stat_result;
    auto error = GenerateValueFactorStat(value_factor, pre_tab, value_stat_result);
    if (error) return error;
    std::string op_string = op_2_value->GetOp2()->GetElementText();
    if (op_string == "!")
        content += "not " + value_stat_result;
    else if (op_string == "-")
        content += "-" + value_stat_result;
    else if (op_string == "~")
        content += "~" + value_stat_result;
    else
        return ABnfGuessError(nullptr, u8"GenerateOp2Stat����δ֪����");

    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateOp2Stat(std::shared_ptr<ALittleScriptOp2StatElement> op_2_stat, const std::string& pre_tab, std::string& content)
{
    auto error = GenerateOp2Value(op_2_stat->GetOp2Value(), pre_tab, content);
    if (error) return error;

    std::vector<std::string> suffix_content_list;
    const auto& suffix_ex_list = op_2_stat->GetOp2SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        std::string sub_content;
        error = GenerateOp2SuffixEx(suffix_ex, pre_tab, sub_content);
        if (error) return error;
        suffix_content_list.push_back(sub_content);
    }
    if (suffix_content_list.size() > 0)
        content += " " + ABnfFactory::Join(suffix_content_list, " ");
    return nullptr;
}

// ����ֵ���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateValueStat(std::shared_ptr<ALittleScriptValueStatElement> root, const std::string& pre_tab, std::string& content)
{
    if (root->GetValueOpStat() != nullptr)
        return GenerateValueOpStat(root->GetValueOpStat(), pre_tab, content);

    if (root->GetOp2Stat() != nullptr)
        return GenerateOp2Stat(root->GetOp2Stat(), pre_tab, content);

    if (root->GetOpNewStat() != nullptr)
        return GenerateOpNewStat(root->GetOpNewStat(), pre_tab, content);

    if (root->GetOpNewListStat() != nullptr)
        return GenerateOpNewListStat(root->GetOpNewListStat(), pre_tab, content);

    if (root->GetBindStat() != nullptr)
        return GenerateBindStat(root->GetBindStat(), pre_tab, content);

    if (root->GetTcallStat() != nullptr)
        return GenerateTcallStat(root->GetTcallStat(), pre_tab, content);

    content = "";
    return nullptr;
}

// ����ValueFactorStat

ABnfGuessError ALittleScriptTranslationLua::GenerateValueFactorStat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor, const std::string& pre_tab, std::string& content)
{
    if (value_factor->GetConstValue() != nullptr)
        return GenerateConstValue(value_factor->GetConstValue(), pre_tab, content);

    if (value_factor->GetReflectValue() != nullptr)
        return GenerateReflectValue(value_factor->GetReflectValue(), pre_tab, content);

    if (value_factor->GetPathsValue() != nullptr)
        return GeneratePathsValue(value_factor->GetPathsValue(), pre_tab, content);

    if (value_factor->GetPropertyValue() != nullptr)
        return GeneratePropertyValue(value_factor->GetPropertyValue(), pre_tab, content);

    if (value_factor->GetCoroutineStat() != nullptr)
        return GenerateCoroutineStat(value_factor->GetCoroutineStat(), content);

    if (value_factor->GetWrapValueStat() != nullptr)
    {
        content = "";
        std::string sub_content;
        auto error = GenerateValueStat(value_factor->GetWrapValueStat()->GetValueStat(), pre_tab, sub_content);
        if (error) return error;
        content = "(" + sub_content + ")";
        return nullptr;
    }

    if (value_factor->GetMethodParamTailDec() != nullptr)
    {
        content = value_factor->GetMethodParamTailDec()->GetElementText();
        return nullptr;
    }

    content = "";
    return ABnfGuessError(nullptr, u8"GenerateValueFactor����δ֪����");
}

ABnfGuessError ALittleScriptTranslationLua::GenerateConstValue(std::shared_ptr<ALittleScriptConstValueElement> const_value, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::string const_value_string = const_value->GetElementText();
    if (const_value_string == "null")
        content += "nil";
    else
        content += const_value_string;
    return nullptr;
}

// ����·����Ϣ

ABnfGuessError ALittleScriptTranslationLua::GeneratePathsValue(std::shared_ptr<ALittleScriptPathsValueElement> paths_value, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto text = paths_value->GetText();
    if (text == nullptr) return ABnfGuessError(paths_value, u8"������·��");

    auto path = text->GetElementString();
    ALittleScriptUtility::TrimLeft(path);
    ALittleScriptUtility::TrimRight(path);
    if (!ALittleScriptUtility::IsDirExist(paths_value->GetModulePath() + path)) return ABnfGuessError(paths_value, u8"·��������:" + path);
    std::vector<std::string> path_list;

    auto* index = dynamic_cast<ALittleScriptIndex*>(paths_value->GetFile()->GetProject());
    if (index == nullptr) return ABnfGuessError(paths_value, u8"���ڹ�����");
    std::string error;
    if (!index->GetDeepFilePaths(paths_value->GetFile()->GetProject(), paths_value->GetModulePath() + path, u8"", path_list, error)) return ABnfGuessError(paths_value, error);

    content = "{";
    for (size_t i = 0; i < path_list.size(); ++i)
    {
        if (i != 0)
        {
            if (i % 3 == 0) content += "\n" + pre_tab + "\t";
            content += ", ";
        }
        content += "\"" + path_list[i] + "\"";
    }
    content += "}";
    return nullptr;
}

// ���ɷ���

ABnfGuessError ALittleScriptTranslationLua::GenerateReflectValue(std::shared_ptr<ALittleScriptReflectValueElement> reflect_value, const std::string& pre_tab, std::string& content)
{
    content = "";
    if (reflect_value->GetReflectCustomType() != nullptr)
    {
        auto custom_type = reflect_value->GetReflectCustomType()->GetCustomType();
        if (custom_type == nullptr) return ABnfGuessError(nullptr, u8"���ʽ������");

        ABnfGuessPtr guess;
        auto error = custom_type->GuessType(guess);
        if (error) return error;
        if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
            m_need_all_struct = true;
            content = "___all_struct[" + std::to_string(ALittleScriptUtility::StructHash(guess_struct)) + "]";
            return GenerateReflectStructInfo(guess_struct);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        {
            auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
            std::string name = guess_class->GetValue();
            // �����using�����������ô��ʹ��using_name
            if (guess_class->using_name.size()) name = guess_class->using_name;
            std::vector<std::string> split;
            ABnfFactory::Split(name, ".", split);
            if (split.size() == 2 && split[0] == "lua")
                content = split[1];
            else
                content = name;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess))
        {
            content = guess->GetValue();
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess);
            auto template_dec = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(guess_template->template_pair_dec.lock()->GetParent());
            int index = -1;
            for (size_t i = 0; i < template_dec->GetTemplatePairDecList().size(); ++i)
            {
                if (template_dec->GetTemplatePairDecList()[i] == guess_template->template_pair_dec.lock())
                {
                    index = static_cast<int>(i);
                    break;
                }
            }
            content = "self.__class.__element[" + std::to_string(index + 1) + "]";
            return nullptr;
        }
    }
    else if (reflect_value->GetReflectValueStat() != nullptr)
    {
        auto value_stat = reflect_value->GetReflectValueStat()->GetValueStat();
        if (value_stat == nullptr) return ABnfGuessError(nullptr, u8"���ʽ������");

        ABnfGuessPtr guess;
        auto error = value_stat->GuessType(guess);
        if (error) return error;
        if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);
            m_need_all_struct = true;
            content = "___all_struct[" + std::to_string(ALittleScriptUtility::StructHash(guess_struct)) + "]";
            return GenerateReflectStructInfo(guess_struct);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        {
            std::string sub_content;
            error = GenerateValueStat(value_stat, pre_tab, sub_content);
            if (error) return error;
            content = "(" + sub_content + ").__class";
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess_template->template_extends.lock()) || guess_template->is_class)
            {
                std::string sub_content;
                error = GenerateValueStat(value_stat, pre_tab, sub_content);
                if (error) return error;
                content = "(" + sub_content + ").__class";
                return nullptr;
            }

            return ABnfGuessError(nullptr, u8"reflect���ܷ���struct����ģ�����");
        }
    }

    return ABnfGuessError(nullptr, u8"reflectֻ�ܷ���struct����class�Լ�class����");
}

// ����struct�ķ�����Ϣ

ABnfGuessError ALittleScriptTranslationLua::GenerateReflectStructInfo(ABnfGuessPtr guess)
{
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
    {
        auto guess_list = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess);
        auto error = GenerateReflectStructInfo(guess_list->sub_type.lock());
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
    {
        auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess);
        auto error = GenerateReflectStructInfo(guess_map->key_type.lock());
        if (error) return error;

        error = GenerateReflectStructInfo(guess_map->value_type.lock());
        if (error) return error;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
    {
        auto guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess);

        if (m_reflect_map.find(guess_struct->GetValue()) != m_reflect_map.end()) return nullptr;

        auto generate = false;
        // ����Ǳ��ļ��ģ���ô������
        if (guess_struct->struct_dec.lock() != nullptr && guess_struct->struct_dec.lock()->GetFullPath() == m_file_path)
            generate = true;
        // �������ͬһ�����̣���ô������
        if (guess_struct->struct_dec.lock() != nullptr && guess_struct->struct_dec.lock()->GetModulePath() != m_module_path)
            generate = true;
        //  �����ͬһ�����̣�������register����ôҲҪ����
        else if (guess_struct->is_register)
            generate = true;

        auto struct_dec = guess_struct->struct_dec.lock();
        if (struct_dec == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
        auto body_dec = struct_dec->GetStructBodyDec();
        if (body_dec == nullptr) return nullptr;

        StructReflectInfo& info = m_reflect_map[guess_struct->GetValue()] = StructReflectInfo();
        info.generate = generate;

        // ����м̳У���ô�ͻ�ȡ�̳�
        auto extends_dec = struct_dec->GetStructExtendsDec();
        if (extends_dec != nullptr && extends_dec->GetStructNameDec() != nullptr)
        {
            ABnfGuessPtr extends_guess;
            auto error = extends_dec->GetStructNameDec()->GuessType(extends_guess);
            if (error) return error;
            if (!(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(extends_guess)))
                return ABnfGuessError(nullptr, extends_guess->GetValue() + u8"���ǽṹ��");
            error = GenerateReflectStructInfo(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(extends_guess));
            if (error) return error;

            StructReflectInfo* extends_info;
            auto it = m_reflect_map.find(extends_guess->GetValue());
            if (it == m_reflect_map.end())
                return ABnfGuessError(nullptr, extends_guess->GetValue() + u8"������Ϣ����ʧ��");
            extends_info = &it->second;
            info.name_list = extends_info->name_list;
            info.type_list = extends_info->type_list;
            for (auto& pair : extends_info->option_map)
                info.option_map[pair.first] = pair.second;
        }

        std::vector<ABnfGuessPtr> next_list;
        const auto& var_dec_list = body_dec->GetStructVarDecList();
        for (auto& var_dec : var_dec_list)
        {
            ABnfGuessPtr var_guess;
            auto error = var_dec->GuessType(var_guess);
            if (error) return error;
            auto name_dec = var_dec->GetStructVarNameDec();
            if (name_dec == nullptr) return ABnfGuessError(nullptr, guess_struct->GetValue() + u8"û�ж��������");
            info.name_list.push_back("\"" + name_dec->GetElementText() + "\"");
            info.type_list.push_back("\"" + var_guess->GetValue() + "\"");

            next_list.push_back(var_guess);
        }
        const auto& option_dec_list = body_dec->GetStructOptionDecList();
        for (auto& option_dec : option_dec_list)
        {
            auto name = option_dec->GetStructOptionNameDec();
            if (name == nullptr) return ABnfGuessError(nullptr, guess_struct->GetValue() + u8"option���岻����");
            auto value = option_dec->GetText();
            if (value == nullptr) return ABnfGuessError(nullptr, guess_struct->GetValue() + u8"option���岻����");
            info.option_map[name->GetElementText()] = value->GetElementText();
        }
        std::vector<std::string> split_list;
        ABnfFactory::Split(guess_struct->GetValue(), ".", split_list);
        if (split_list.size() != 2) return nullptr;

        info.name = guess_struct->GetValue();
        info.ns_name = split_list[0];
        info.rl_name = split_list[1];
        info.hash_code = ALittleScriptUtility::StructHash(guess_struct);

        info.content = "{\n";
        info.content += "name = \"" + info.name + "\", ";         // ȫ��
        info.content += "ns_name = \"" + info.ns_name + "\", ";          // ��������
        info.content += "rl_name = \"" + info.rl_name + "\", ";          // struct��
        info.content += "hash_code = " + std::to_string(info.hash_code) + ",\n";        // ��ϣֵ
        info.content += "name_list = {" + ABnfFactory::Join(info.name_list, ",") + "},\n";      // ��Ա���б�
        info.content += "type_list = {" + ABnfFactory::Join(info.type_list, ",") + "},\n";      // �������б�
        info.content += "option_map = {";
        int cur_count = 0;
        for (auto& pair : info.option_map)
        {
            info.content += pair.first + "=" + pair.second;
            ++cur_count;
            if (info.option_map.size() != cur_count)
                info.content += ",";
        }
        info.content += "}\n";      // �������б�
        info.content += "}";

        for (auto& guess_info : next_list)
        {
            auto error = GenerateReflectStructInfo(guess_info);
            if (error) return error;
        }
    }

    return nullptr;
}

// ���������̵�ö��ֵ�����Ż�����ֱ�����ɶ�Ӧ��ֵ
ABnfGuessError ALittleScriptTranslationLua::GenerateEnumValue(std::shared_ptr<ALittleScriptPropertyValueElement> prop_value, bool& handle, std::string& content)
{
    handle = false;
    content = "";

    auto first_type = prop_value->GetPropertyValueFirstType();
    if (first_type == nullptr) return nullptr;

    ABnfGuessPtr custom_guess;
    auto error = first_type->GuessType(custom_guess);
    if (error) return error;

    std::shared_ptr<ALittleScriptGuessEnumName> enum_name_guess;
    std::shared_ptr<ALittleScriptPropertyValueSuffixElement> suffix;

    const auto& suffix_list = prop_value->GetPropertyValueSuffixList();
    if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(custom_guess))
    {
        if (suffix_list.size() != 2) return nullptr;
        suffix = suffix_list[1];

        ABnfGuessPtr guess;
        error = suffix_list[0]->GuessType(guess);
        if (error) return error;
        enum_name_guess = std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(guess);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(custom_guess))
    {
        if (suffix_list.size() != 1) return nullptr;
        suffix = suffix_list[0];

        enum_name_guess = std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(custom_guess);
    }

    if (enum_name_guess == nullptr) return nullptr;
    if (suffix == nullptr) return nullptr;

    auto enum_name_dec = enum_name_guess->enum_name_dec.lock();
    if (enum_name_dec == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    // ����ע�͵���������ö��ȫ��ʹ�ó���ֵ
    // if (enum_name_dec->GetModulePath() == m_module_path) return nullptr;

    auto dot_id = suffix->GetPropertyValueDotId();
    if (dot_id == nullptr) return nullptr;
    auto dot_id_name = dot_id->GetPropertyValueDotIdName();
    if (dot_id_name == nullptr) return nullptr;

    auto enum_dec = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(enum_name_dec->GetParent());
    if (enum_dec == nullptr) return nullptr;

    auto body_dec = enum_dec->GetEnumBodyDec();
    if (body_dec == nullptr) return nullptr;

    const auto& var_dec_list = body_dec->GetEnumVarDecList();
    for (auto& var_dec : var_dec_list)
    {
        auto name_dec = var_dec->GetEnumVarNameDec();
        if (name_dec == nullptr) continue;
        if (name_dec->GetElementText() != dot_id_name->GetElementText())
            continue;

        if (var_dec->GetText() != nullptr)
            content = var_dec->GetText()->GetElementText();
        else if (var_dec->GetNumber() != nullptr)
            content = var_dec->GetNumber()->GetElementText();

        handle = content.size() != 0;
    }

    return nullptr;
}

// ��������ֵ���ʽ

ABnfGuessError ALittleScriptTranslationLua::GeneratePropertyValue(std::shared_ptr<ALittleScriptPropertyValueElement> prop_value, const std::string& pre_tab, std::string& content)
{
    // ����ö��ֵ�������⴦��
    bool handle = false;
    auto error = GenerateEnumValue(prop_value, handle, content);
    if (error) return error;
    if (handle) return nullptr;

    content = "";

    // ������ǵ�һ�������ǲ���lua������
    bool is_lua_namespace = false;
    
    // ��ȡ��ͷ��������Ϣ
    auto first_type = prop_value->GetPropertyValueFirstType();
    auto custom_type = first_type->GetPropertyValueCustomType();
    auto this_type = first_type->GetPropertyValueThisType();
    auto cast_type = first_type->GetPropertyValueCastType();

    ABnfGuessPtr custom_guess;
    error = first_type->GuessType(custom_guess);
    if (error) return error;
    if (custom_type != nullptr)
    {
        if ((std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(custom_guess)
            && std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(custom_guess)->element.lock()))
            || std::dynamic_pointer_cast<ALittleScriptGuessClassName>(custom_guess)
            || std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(custom_guess))
            AddRelay(std::dynamic_pointer_cast<ALittleScriptGuess>(custom_guess)->GetElement());

        if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(custom_guess) && (custom_guess->GetValue() == "lua" || custom_guess->GetValue() == "alittle"))
            is_lua_namespace = true;

        // �����lua��������ô�ͺ���
        if (!is_lua_namespace)
        {
            // ���custom_type������������ô���Զ�����������
            if (!std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(custom_guess) && std::dynamic_pointer_cast<ALittleScriptGuess>(custom_guess))
            {
                // �ж�custom_type����Դ
                std::string pre_namespace_name;
                error = dynamic_cast<ALittleScriptPropertyValueCustomTypeReference*>(custom_type->GetReference())->CalcNamespaceName(pre_namespace_name);
                if (error) return error;

                if (pre_namespace_name == "alittle" || pre_namespace_name == "lua") pre_namespace_name = "";
                if (pre_namespace_name.size() > 0)
                    content += pre_namespace_name + ".";
            }

            content += custom_type->GetElementText();
        }
    }
    // �����this����ô�ͱ�Ϊself
    else if (this_type != nullptr)
    {
        content += "self";
    }
    else if (cast_type != nullptr)
    {
        auto value_factor_stat = cast_type->GetValueFactorStat();
        if (value_factor_stat == nullptr) return ABnfGuessError(nullptr, u8"castû����дת������");
        std::string sub_content;
        error = GenerateValueFactorStat(value_factor_stat, pre_tab, sub_content);
        if (error) return error;
        content += sub_content;
    }

    std::string split = ".";
    // ������ź�׺����
    const auto& suffix_list = prop_value->GetPropertyValueSuffixList();
    for (int index = 0; index < static_cast<int>(suffix_list.size()); ++index)
    {
        // ��ȡ��ǰ��׺
        auto suffix = suffix_list[index];
        // ��ȡ��һ����׺
        std::shared_ptr<ALittleScriptPropertyValueSuffixElement> pre_suffix;
        if (index - 1 >= 0) pre_suffix = suffix_list[index - 1];
        // ��ȡ��һ����׺
        std::shared_ptr<ALittleScriptPropertyValueSuffixElement> next_suffix;
        if (index + 1 < suffix_list.size()) next_suffix = suffix_list[index + 1];

        // �����ǰ�ǵ�
        auto dot_id = suffix->GetPropertyValueDotId();
        if (dot_id != nullptr)
        {
            auto dot_id_name = dot_id->GetPropertyValueDotIdName();
            if (dot_id_name == nullptr) return ABnfGuessError(nullptr, u8"�����û�ж������Զ���");
            // ��ȡ����
            ABnfGuessPtr guess;
            error = dot_id_name->GuessType(guess);
            if (error) return error;

            split = ".";
            // ����Ǻ�����
            if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
            {
                auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
                // 1. �ǳ�Ա����
                // 2. ʹ�õ��ǵ���
                // 3. ǰһ����׺����ʵ������
                // ��ô��Ҫ�ĳ�ʹ���﷨��
                if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(guess_functor->element.lock()))
                {
                    if (next_suffix != nullptr && next_suffix->GetPropertyValueMethodCall() != nullptr)
                    {
                        // ��ȡǰһ����׺������
                        ABnfGuessPtr pre_guess = custom_guess;
                        if (pre_suffix != nullptr)
                        {
                            error = pre_suffix->GuessType(pre_guess);
                            if (error) return error;
                        }

                        // ֻҪ������������ô�϶�������ʵ�����󣬾������﷨��
                        if (!(std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_guess)))
                            split = ":";
                    }
                }
                // setter��getter��Ҫ���⴦��
                else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(guess_functor->element.lock())
                    || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(guess_functor->element.lock()))
                {
                    if (next_suffix != nullptr && next_suffix->GetPropertyValueMethodCall() != nullptr)
                    {
                        ABnfGuessPtr pre_guess = custom_guess;
                        if (pre_suffix != nullptr)
                        {
                            error = pre_suffix->GuessType(pre_guess);
                            if (error) return error;
                        }

                        // ���ǰһ����׺����������ô��ô����Ҫ��ȡsetter����getter����ȡ
                        if (std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_guess))
                        {
                            // �����getter����ôһ����һ������������ClassName.disabled(self)
                            // �����setter����ôһ������������������ClassName.width(self, 100)
                            if (next_suffix->GetPropertyValueMethodCall()->GetValueStatList().size() == 1)
                                split = ".__getter.";
                            else
                                split = ".__setter.";
                        }
                    }
                }
                // ȫ�ֺ���
                else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(guess_functor->element.lock()))
                {
                    AddRelay(guess_functor->element.lock());
                }
            }
            else if (std::dynamic_pointer_cast<ALittleScriptGuessClassName>(guess) || std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(guess))
            {
                AddRelay(std::dynamic_pointer_cast<ALittleScriptGuess>(guess)->GetElement());
            }

            if (!is_lua_namespace)
                content += split;

            if (dot_id->GetPropertyValueDotIdName() == nullptr)
                return ABnfGuessError(nullptr, u8"�����û������");

            std::string name_content = dot_id->GetPropertyValueDotIdName()->GetElementText();
            // ��Ϊlua���Դ���stringģ�����͹ؼ���stringһ�������԰�lua�Զ��ĸĳ�string����Щ��ͷ��
            // Ȼ���ٷ����ʱ�򣬰�string�ĳ�string
            if (is_lua_namespace && name_content == "String")
                name_content = "string";
            content += name_content;

            // ��Ϊfalse����ʾ����������
            is_lua_namespace = false;
            continue;
        }

        auto bracket_value = suffix->GetPropertyValueBracketValue();
        if (bracket_value != nullptr)
        {
            auto value_stat = bracket_value->GetValueStat();
            if (value_stat != nullptr)
            {
                std::string sub_content;
                error = GenerateValueStat(value_stat, pre_tab, sub_content);
                if (error) return error;
                content += "[" + sub_content + "]";
            }
            continue;
        }

        auto method_call = suffix->GetPropertyValueMethodCall();
        if (method_call != nullptr)
        {
            // �Ƿ��ǵ����˴�ע�⺯����Ҫ�������⴦��
            auto refe = method_call->GetReference();
            if (!dynamic_cast<ALittleScriptPropertyValueMethodCallReference*>(refe))
                return ABnfGuessError(nullptr, u8"ALittlePropertyValueMethodCall->GetReference()�õ��Ĳ���ALittlePropertyValueMethodCallReference");

            auto reference = dynamic_cast<ALittleScriptPropertyValueMethodCallReference*>(refe);
            ABnfGuessPtr pre_type;
            error = reference->GuessPreType(pre_type);
            if (error) return error;

            auto pre_type_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(pre_type);
            if (!pre_type_functor)
                return ABnfGuessError(nullptr, u8"ALittlePropertyValueMethodCallReference.guessPreType()�õ��Ĳ���ALittleScriptGuessFunctor");

            if (pre_type_functor->proto.size())
            {
                if (pre_type_functor->proto == "Http")
                    content = "ALittle.IHttpSender.Invoke";
                else if (pre_type_functor->proto == "HttpDownload")
                    content = "ALittle.IHttpFileSender.InvokeDownload";
                else if (pre_type_functor->proto == "HttpUpload")
                    content = "ALittle.IHttpFileSender.InvokeUpload";
                else if (pre_type_functor->proto == "Msg")
                {
                    if (pre_type_functor->return_list.size() == 0)
                        content = "ALittle.IMsgCommon.Invoke";
                    else
                        content = "ALittle.IMsgCommon.InvokeRPC";
                }

                if (pre_type_functor->param_list.size() != 2)
                    return ABnfGuessError(nullptr, u8"GeneratePropertyValue:����MethodCallʱ���ִ�ע��ĺ���������������2");
                if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type_functor->param_list[1].lock()))
                    return ABnfGuessError(nullptr, u8"GeneratePropertyValue:����MethodCallʱ���ִ�ע��ĺ����ڶ�����������struct");
                auto param_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type_functor->param_list[1].lock());
                int msg_id = ALittleScriptUtility::StructHash(param_struct);

                std::vector<std::string> param_list;
                if (pre_type_functor->proto == "Msg")
                {
                    param_list.push_back(std::to_string(msg_id));
                    // ע��Э��
                    error = GenerateReflectStructInfo(param_struct);
                    if (error) return error;

                    // ����з���ֵ����ôҲҪע�᷵��ֵ
                    if (pre_type_functor->return_list.size() == 2)
                    {
                        if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type_functor->return_list[1].lock()))
                            return ABnfGuessError(nullptr, u8"GeneratePropertyValue:����MethodCallʱ���ִ�ע��ĺ�������ֵ����struct");
                        error = GenerateReflectStructInfo(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type_functor->return_list[1].lock()));
                        if (error) return error;
                    }
                }
                else
                {
                    param_list.push_back("\"" + param_struct->GetValue() + "\"");
                }

                const auto& value_stat_list = method_call->GetValueStatList();
                for (auto& value_stat : value_stat_list)
                {
                    std::string sub_content;
                    error = GenerateValueStat(value_stat, pre_tab, sub_content);
                    if (error) return error;
                    param_list.push_back(sub_content);
                }

                content += "(" + ABnfFactory::Join(param_list, ", ") + ")";
            }
            else
            {
                std::vector<std::string> param_list;

                // ����ģ�����
                std::vector<ABnfGuessPtr> template_list;
                error = reference->GenerateTemplateParamList(template_list);
                if (error) return error;
                for (auto& guess : template_list)
                {
                    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                    {
                        auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
                        if (guess_class->namespace_name == "lua")
                            param_list.push_back(guess_class->class_name);
                        else
                            param_list.push_back(guess_class->GetValue());
                    }
                    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
                    {
                        m_need_all_struct = true;
                        param_list.push_back("___all_struct[" + std::to_string(ALittleScriptUtility::StructHash(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))) + "]");
                        error = GenerateReflectStructInfo(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess));
                        if (error) return error;
                    }
                    else if (std::dynamic_pointer_cast<ALittleScriptGuessMethodTemplate>(guess))
                    {
                        param_list.push_back(guess->GetValue());
                    }
                    else if (std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess))
                    {
                        auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessClassTemplate>(guess);
                        auto template_dec = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(guess_template->template_pair_dec.lock()->GetParent());
                        int template_index = -1;
                        for (size_t i = 0; i < template_dec->GetTemplatePairDecList().size(); ++i)
                        {
                            if (template_dec->GetTemplatePairDecList()[i] == guess_template->template_pair_dec.lock())
                            {
                                template_index = static_cast<int>(i);
                                break;
                            }
                        }
                        param_list.push_back("self.__class.__element[" + std::to_string(template_index + 1) + "]");
                    }
                    else
                    {
                        return ABnfGuessError(nullptr, u8"ALittlePropertyValueMethodCallReference.generateTemplateParamList()�ķ����б��г����������͵�ALittleScriptGuess:" + guess->GetValue());
                    }
                }

                // ����ʵ�ʲ���
                const auto& value_stat_list = method_call->GetValueStatList();
                for (size_t i = 0; i < value_stat_list.size(); ++i)
                {
                    auto value_stat = value_stat_list[i];
                    // ����ǳ�Ա��setter��getter��������һ������Ҫ������ǰ��
                    if (i == 0 && split != ":" && (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(pre_type_functor->element.lock())
                        || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(pre_type_functor->element.lock())
                        || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(pre_type_functor->element.lock())))
                    {
                        std::string sub_content;
                        error = GenerateValueStat(value_stat, pre_tab, sub_content);
                        if (error) return error;
                        param_list.insert(param_list.begin(), sub_content);
                    }
                    else
                    {
                        std::string sub_content;
                        error = GenerateValueStat(value_stat, pre_tab, sub_content);
                        if (error) return error;
                        param_list.push_back(sub_content);
                    }
                }
                content += "(" + ABnfFactory::Join(param_list, ", ") + ")";
            }
            continue;
        }

        return ABnfGuessError(nullptr, u8"GeneratePropertyValue����δ֪����");
    }

    return nullptr;
}

// ����co

ABnfGuessError ALittleScriptTranslationLua::GenerateCoroutineStat(std::shared_ptr<ALittleScriptCoroutineStatElement> root, std::string& content)
{
    content = "___COROUTINE";
    return nullptr;
}

// ����using

ABnfGuessError ALittleScriptTranslationLua::GenerateUsingDec(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& modifier, std::shared_ptr<ALittleScriptUsingDecElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto name_dec = root->GetUsingNameDec();
    if (name_dec == nullptr) return ABnfGuessError(nullptr, u8"using û�ж�������");

    auto all_type = root->GetAllType();
    if (all_type == nullptr) return nullptr;

    auto custom_type = all_type->GetCustomType();
    if (custom_type == nullptr) return nullptr;

    ABnfGuessPtr guess;
    auto error = custom_type->GuessType(guess);
    if (error) return error;
    if (!(std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))) return nullptr;

    content = pre_tab;

    if (ALittleScriptUtility::CalcAccessType(modifier) == ClassAccessType::PRIVATE)
        content += "local ";
    else
        content += m_alittle_gen_namespace_pre;

    std::string sub_content;
    error = GenerateCustomType(custom_type, pre_tab, sub_content);
    if (error) return error;
    content += name_dec->GetElementText() + " = " + sub_content + ";\n";
    return nullptr;
}

// �����쳣���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateThrowExpr(std::shared_ptr<ALittleScriptThrowExprElement> return_expr, const std::string& pre_tab, std::string& content)
{
    content = "";

    const auto& value_stat_list = return_expr->GetValueStatList();
    if (value_stat_list.size() == 0) return ABnfGuessError(nullptr, u8"throw��һ������������string����");

    ABnfGuessPtr guess_info;
    auto error = value_stat_list[0]->GuessType(guess_info);
    if (error) return error;

    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess_info))
        return ABnfGuessError(nullptr, u8"throw��һ������������string����");
    if (value_stat_list.size() != 1)
        return ABnfGuessError(nullptr, u8"throwֻ��һ������");

    content = pre_tab + "Lua.Throw(";
    std::vector<std::string> param_list;
    for (size_t i = 0; i < value_stat_list.size(); ++i)
    {
        std::string sub_content;
        error = GenerateValueStat(value_stat_list[i], pre_tab, sub_content);
        if (error) return error;
        param_list.push_back(sub_content);
    }
    content += ABnfFactory::Join(param_list, u8", ");
    content += ")\n";
    return nullptr;
}

// ���ɶ��Ա��ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateAssertExpr(std::shared_ptr<ALittleScriptAssertExprElement> assert_expr, const std::string& pre_tab, std::string& content)
{
    content = "";

    const auto& value_stat_list = assert_expr->GetValueStatList();
    if (value_stat_list.size() != 2) return ABnfGuessError(nullptr, u8"assert���ҽ���������������һ�����������ͣ��ڶ�����string����");

    ABnfGuessPtr guess_info;
    auto error = value_stat_list[1]->GuessType(guess_info);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess_info))
        return ABnfGuessError(nullptr, u8"assert�ڶ�������������string����");

    content = pre_tab + "Lua.Assert(";
    std::vector<std::string> param_list;
    for (size_t i = 0; i < value_stat_list.size(); ++i)
    {
        std::string sub_content;
        error = GenerateValueStat(value_stat_list[i], pre_tab, sub_content);
        if (error) return error;
        param_list.push_back(sub_content);
    }
    content += ABnfFactory::Join(param_list, u8", ");
    content += ")\n";
    return nullptr;
}

// ����1�������

ABnfGuessError ALittleScriptTranslationLua::GenerateOp1Expr(std::shared_ptr<ALittleScriptOp1ExprElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto value_stat = root->GetValueStat();
    if (value_stat == nullptr)
        return ABnfGuessError(nullptr, u8"GenerateOp1Expr û�в���ֵ:" + root->GetElementText());

    auto op_1 = root->GetOp1();

    std::string value_stat_result;
    auto error = GenerateValueStat(value_stat, pre_tab, value_stat_result);
    if (error) return error;

    std::string op_1_string = op_1->GetElementText();
    if (op_1_string == "++")
    {
        content = pre_tab + value_stat_result + " = " + value_stat_result + " + 1\n";
        return nullptr;
    }

    if (op_1_string == "--")
    {
        content = pre_tab + value_stat_result + " = " + value_stat_result + " - 1\n";
        return nullptr;
    }

    return ABnfGuessError(nullptr, u8"GenerateOp1Exprδ֪����:" + op_1_string);
}

// ���ɱ��������Լ���ֵ���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateVarAssignExpr(std::shared_ptr<ALittleScriptVarAssignExprElement> root, const std::string& pre_tab, const std::string& pre_string, std::string& content)
{
    content = "";

    const auto& pair_dec_list = root->GetVarAssignDecList();
    if (pair_dec_list.size() == 0)
        return ABnfGuessError(nullptr, u8"�ֲ�����û�б�����:" + root->GetElementText());

    content = pre_tab + pre_string;

    std::vector<std::string> name_list;
    for (auto& pair_dec : pair_dec_list)
        name_list.push_back(pair_dec->GetVarAssignNameDec()->GetElementText());
    content += ABnfFactory::Join(name_list, ", ");

    auto value_stat = root->GetValueStat();
    if (value_stat == nullptr)
    {
        content += "\n";
        return nullptr;
    }

    std::string sub_content;
    auto error = GenerateValueStat(value_stat, pre_tab, sub_content);
    if (error) return error;
    content += " = " + sub_content + "\n";
    return nullptr;
}

// ���ɸ�ֵ���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateOpAssignExpr(std::shared_ptr<ALittleScriptOpAssignExprElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";
    const auto& prop_value_list = root->GetPropertyValueList();

    // �����б�
    std::vector<std::string> content_list;
    for (auto& prop_value : prop_value_list)
    {
        std::string sub_content;
        auto guess_error = GeneratePropertyValue(prop_value, pre_tab, sub_content);
        if (guess_error) return guess_error;
        content_list.push_back(sub_content);
    }
    std::string prop_value_result = ABnfFactory::Join(content_list, ", ");

    // ���û�и�ֵ������ֱ�ӷ��ض���
    auto op_assign = root->GetOpAssign();
    auto value_stat = root->GetValueStat();
    if (op_assign == nullptr || value_stat == nullptr)
    {
        content = pre_tab + prop_value_result + "\n";
        return nullptr;
    }

    // ��ȡ��ֵ���ʽ
    std::string value_stat_result;
    auto error = GenerateValueStat(value_stat, pre_tab, value_stat_result);
    if (error) return error;

    // ����Ⱥ�
    if (op_assign->GetElementText() == "=")
    {
        // �������Ż�
        // �� self._attr = value �Ż�Ϊ  rawset(self, u8"_attr", value)
        if (m_open_rawset && prop_value_list.size() == 1)
        {
            auto prop_value = prop_value_list[0];
            auto this_type = prop_value->GetPropertyValueFirstType()->GetPropertyValueThisType();
            if (this_type != nullptr && prop_value->GetPropertyValueSuffixList().size() == 1)
            {
                auto suffix = prop_value->GetPropertyValueSuffixList()[0];
                if (suffix->GetPropertyValueDotId() != nullptr)
                {
                    auto dot_id = suffix->GetPropertyValueDotId();
                    if (dot_id != nullptr && dot_id->GetPropertyValueDotIdName() != nullptr)
                    {
                        std::string attr_name = dot_id->GetPropertyValueDotIdName()->GetElementText();
                        ABnfGuessPtr this_guess;
                        error = this_type->GuessType(this_guess);
                        if (error) return error;

                        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(this_guess))
                        {
                            auto this_guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(this_guess);
                            std::vector<ABnfElementPtr> var_name_list;
                            ALittleScriptUtility::FindClassAttrList(this_guess_class->class_dec.lock()
                                , ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic
                                , ClassAttrType::VAR
                                , attr_name
                                , var_name_list, 100);
                            if (var_name_list.size() > 0)
                            {
                                ++m_rawset_usecount;
                                content = pre_tab + "___rawset(self, \"" + attr_name + "\", " + value_stat_result + ")\n";
                                return nullptr;
                            }
                        }
                    }
                }
            }
        }

        content = pre_tab + prop_value_result + " = " + value_stat_result + "\n";
        return nullptr;
    }

    std::string op_assign_string = op_assign->GetElementText();

    // ������ֶ��ǰ׺��ֵ����ôֻ����=��
    if (content_list.size() > 1)
        return ABnfGuessError(nullptr, u8"�Ⱥ���߳��ֶ��ֵ��ʱ��ֻ��ʹ��=��ֵ����:" + root->GetElementText());

    content = "";
    if (op_assign_string == "+="
        || op_assign_string == "-="
        || op_assign_string == "*="
        || op_assign_string == "/="
        || op_assign_string == "%=")
    {
        std::string op_string = op_assign_string.substr(0, 1);
        content = pre_tab + prop_value_result + " = " + prop_value_result + " " + op_string + " (" + value_stat_result + ")\n";
        return nullptr;
    }
    
    return ABnfGuessError(nullptr, u8"δ֪�ĸ�ֵ��������:" + op_assign_string);
}

// ����else���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateElseExpr(std::shared_ptr<ALittleScriptElseExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content)
{
    content = pre_tab;
    content += "else\n";
    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;
    if (root->GetAllExpr() != nullptr)
    {
        all_expr_list.push_back(root->GetAllExpr());
    }
    else if (root->GetElseBody() != nullptr)
    {
        all_expr_list = root->GetElseBody()->GetAllExprList();
    }
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"���ʽ������");
    }
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        std::string sub_content;
        auto error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
    }
    return nullptr;
}

// ����elseif���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateElseIfExpr(std::shared_ptr<ALittleScriptElseIfExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto condition = root->GetElseIfCondition();
    if (condition == nullptr || condition->GetValueStat() == nullptr)
        return ABnfGuessError(nullptr, u8"elseif (?) elseifû������ֵ:" + root->GetElementText());

    std::string value_stat_result;
    auto error = GenerateValueStat(condition->GetValueStat(), pre_tab, value_stat_result);
    if (error) return error;

    content = pre_tab;
    content += "elseif " + value_stat_result + " then\n";

    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;
    if (root->GetAllExpr() != nullptr)
    {
        all_expr_list.push_back(root->GetAllExpr());
    }
    else if (root->GetElseIfBody() != nullptr)
    {
        all_expr_list = root->GetElseIfBody()->GetAllExprList();
    }
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"���ʽ������");
    }
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        std::string sub_content;
        error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
    }
    return nullptr;
}

// ����if���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateIfExpr(std::shared_ptr<ALittleScriptIfExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content)
{
    content = "";

    auto condition = root->GetIfCondition();
    if (condition == nullptr || condition->GetValueStat() == nullptr)
        return ABnfGuessError(nullptr, u8"if (?) ifû������ֵ:" + root->GetElementText());

    std::string value_stat_result;
    auto error = GenerateValueStat(condition->GetValueStat(), pre_tab, value_stat_result);
    if (error) return error;

    content = pre_tab;
    content += "if " + value_stat_result + " then\n";

    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;
    if (root->GetAllExpr() != nullptr)
    {
        all_expr_list.push_back(root->GetAllExpr());
    }
    else if (root->GetIfBody() != nullptr)
    {
        all_expr_list = root->GetIfBody()->GetAllExprList();
    }
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"���ʽ������");
    }
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        std::string sub_content;
        error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
    }

    const auto& elseIfExprList = root->GetElseIfExprList();
    for (auto& elseIfExpr : elseIfExprList)
    {
        std::string sub_content;
        error = GenerateElseIfExpr(elseIfExpr, continue_num, has_continue, pre_tab, sub_content);
        if (error) return error;
        content += sub_content;
    }

    auto elseExpr = root->GetElseExpr();
    if (elseExpr != nullptr)
    {
        std::string sub_content;
        error = GenerateElseExpr(elseExpr, continue_num, has_continue, pre_tab, sub_content);
        if (error) return error;
        content += sub_content;
    }
    content += pre_tab + "end\n";
    return nullptr;
}

// ����for���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateForExpr(std::shared_ptr<ALittleScriptForExprElement> root, int continue_num, const std::string& pre_tab, std::string& content)
{
    content = "";

    auto for_condition = root->GetForCondition();
    if (for_condition == nullptr) return ABnfGuessError(nullptr, u8"���ʽ������");

    auto for_pair_dec = for_condition->GetForPairDec();
    if (for_pair_dec == nullptr) return ABnfGuessError(nullptr, u8"���ʽ������");

    content = pre_tab;

    std::string for_step_content;

    auto for_step_condition = for_condition->GetForStepCondition();
    auto for_in_condition = for_condition->GetForInCondition();
    if (for_step_condition != nullptr)
    {
        auto for_start_stat = for_step_condition->GetForStartStat();

        auto start_value_stat = for_start_stat->GetValueStat();
        if (start_value_stat == nullptr)
            return ABnfGuessError(nullptr, u8"for û�г�ʼ���ʽ:" + root->GetElementText());

        std::string start_value_stat_result;
        auto error = GenerateValueStat(start_value_stat, pre_tab, start_value_stat_result);
        if (error) return error;

        auto name_dec = for_pair_dec->GetVarAssignNameDec();
        if (name_dec == nullptr)
            return ABnfGuessError(nullptr, u8"for ��ʼ���ʽû�б�����:" + root->GetElementText());

        std::string start_var_name = name_dec->GetElementText();

        content += "local " + start_var_name + " = " + start_value_stat_result + "\n";
        content += pre_tab + "while true do\n";

        auto for_end_stat = for_step_condition->GetForEndStat();
        if (for_end_stat == nullptr)
            return ABnfGuessError(nullptr, u8"for û�н������ʽ:" + root->GetElementText());

        auto end_value_stat = for_end_stat->GetValueStat();
        std::string sub_content;
        error = GenerateValueStat(end_value_stat, pre_tab, sub_content);
        if (error) return error;
        content += pre_tab + "\tif not(" + sub_content + ") then break end\n";

        auto for_step_stat = for_step_condition->GetForStepStat();
        if (for_step_stat == nullptr)
            return ABnfGuessError(nullptr, u8"for û�в������ʽ");

        auto step_value_stat = for_step_stat->GetValueStat();
        error = GenerateValueStat(step_value_stat, pre_tab, sub_content);
        if (error) return error;

        for_step_content = pre_tab + "\t" + start_var_name + " = " + start_var_name + "+(" + sub_content + ")\n";
    }
    else if (for_in_condition != nullptr)
    {
        auto value_stat = for_in_condition->GetValueStat();
        if (value_stat == nullptr)
            return ABnfGuessError(nullptr, u8"for : û�б����Ķ���:" + root->GetElementText());

        std::string value_stat_result;
        auto error = GenerateValueStat(value_stat, pre_tab, value_stat_result);
        if (error) return error;

        auto pair_list = for_in_condition->GetForPairDecList();
        pair_list.insert(pair_list.begin(), for_pair_dec);
        std::vector<std::string> pair_string_list;
        for (auto& pair : pair_list)
        {
            auto name_dec = pair->GetVarAssignNameDec();
            if (name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"for : û�б�����");
            pair_string_list.push_back(name_dec->GetElementText());
        }

        std::string pair_type;
        error = ALittleScriptUtility::CalcPairsTypeForLua(value_stat, pair_type);
        if (error) return error;

        // ���for : ����������������ô�Ͳ���pair_type
        if (pair_type.size() == 0)
            content += "for " + ABnfFactory::Join(pair_string_list, ", ") + " in " + value_stat_result + " do\n";
        else
            content += "for " + ABnfFactory::Join(pair_string_list, ", ") + " in " + pair_type + "(" + value_stat_result + ") do\n";
    }
    else
    {
        return ABnfGuessError(nullptr, u8"for(?) ��Ч��for���:" + root->GetElementText());
    }

    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;
    if (root->GetAllExpr() != nullptr)
    {
        all_expr_list.push_back(root->GetAllExpr());
    }
    else if (root->GetForBody() != nullptr)
    {
        all_expr_list = root->GetForBody()->GetAllExprList();
    }
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"���ʽ������");
    }

    bool has_continue_expr = false;
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        bool has_continue = false;
        std::string sub_content;
        auto error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
        if (has_continue) has_continue_expr = true;
    }

    if (has_continue_expr)
        content += pre_tab + "\t::continue_" + std::to_string(continue_num) + "::\n";

    if (for_step_content.size())
        content += for_step_content;
    content += pre_tab + "end\n";
    return nullptr;
}

// ����while���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateWhileExpr(std::shared_ptr<ALittleScriptWhileExprElement> root, int continue_num, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto condition = root->GetWhileCondition();
    if (condition == nullptr || condition->GetValueStat() == nullptr)
        return ABnfGuessError(nullptr, u8"while (?) { ... } while��û������ֵ");

    std::string value_stat_result;
    auto error = GenerateValueStat(condition->GetValueStat(), pre_tab, value_stat_result);
    if (error) return error;

    content = pre_tab + "while " + value_stat_result + " do\n";

    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;
    if (root->GetAllExpr() != nullptr)
    {
        all_expr_list.push_back(root->GetAllExpr());
    }
    else if (root->GetWhileBody() != nullptr)
    {
        all_expr_list = root->GetWhileBody()->GetAllExprList();
    }
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"���ʽ������");
    }

    bool has_continue_expr = false;
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        bool has_continue = false;
        std::string sub_content;
        error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
        if (has_continue) has_continue_expr = true;
    }

    if (has_continue_expr)
        content += pre_tab + "::continue_" + std::to_string(continue_num) + "::\n";
    content += pre_tab + "end\n";
    return nullptr;
}

// ����do while���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateDoWhileExpr(std::shared_ptr<ALittleScriptDoWhileExprElement> root, int continue_num, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto condition = root->GetDoWhileCondition();
    if (condition == nullptr || condition->GetValueStat() == nullptr)
        return ABnfGuessError(nullptr, u8"do { ... } while(?) while��û������ֵ");

    std::string value_stat_result;
    auto error = GenerateValueStat(condition->GetValueStat(), pre_tab, value_stat_result);
    if (error) return error;

    content = pre_tab + "repeat\n";

    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list;
    if (root->GetDoWhileBody() != nullptr)
    {
        all_expr_list = root->GetDoWhileBody()->GetAllExprList();
    }
    else
    {
        content = "";
        return ABnfGuessError(nullptr, u8"���ʽ������");
    }

    bool has_continue_expr = false;
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        bool has_continue = false;
        std::string sub_content;
        error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
        if (has_continue) has_continue_expr = true;
    }

    if (has_continue_expr)
        content += pre_tab + "::continue_" + std::to_string(continue_num) + "::\n";
    content += pre_tab + "until not(" + value_stat_result + ")\n";
    return nullptr;
}

// �����ӱ��ʽ��

ABnfGuessError ALittleScriptTranslationLua::GenerateWrapExpr(std::shared_ptr<ALittleScriptWrapExprElement> root, int continue_num, bool& has_continue_expr, const std::string& pre_tab, std::string& content)
{
    content = pre_tab + "do\n";

    has_continue_expr = false;
    const auto& all_expr_list = root->GetAllExprList();
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        bool has_continue = false;
        std::string sub_content;
        auto error = GenerateAllExpr(all_expr, continue_num, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
        if (has_continue) has_continue_expr = true;
    }

    content += pre_tab + "end\n";
    return nullptr;
}

// ����return���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateReturnExpr(std::shared_ptr<ALittleScriptReturnExprElement> root, const std::string& pre_tab, std::string& content)
{
    if (root->GetReturnYield() != nullptr)
    {
        content = pre_tab + "return coroutine.yield()\n";
        return nullptr;
    }

    content = "";

    const auto& value_stat_list = root->GetValueStatList();
    std::vector<std::string> content_list;
    for (auto& value_stat : value_stat_list)
    {
        std::string sub_content;
        auto error = GenerateValueStat(value_stat, pre_tab, sub_content);
        if (error) return error;
        content_list.push_back(sub_content);
    }

    std::string value_stat_result = "";
    if (content_list.size() > 0)
        value_stat_result = " " + ABnfFactory::Join(content_list, ", ");

    content = pre_tab + "return" + value_stat_result + "\n";
    return nullptr;
}

// ����break���ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateFlowExpr(std::shared_ptr<ALittleScriptFlowExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content)
{
    content = root->GetElementText();
    if (content.find("break") == 0)
    {
        content = pre_tab + "break\n";
        return nullptr;
    }
    else if (content.find("continue") == 0)
    {
        content = pre_tab + "goto continue_" + std::to_string(continue_num) + "\n";
        has_continue = true;
        return nullptr;
    }

    return ABnfGuessError(nullptr, u8"δ֪�Ĳ������:" + content);
}

// ����������ʽ

ABnfGuessError ALittleScriptTranslationLua::GenerateAllExpr(std::shared_ptr<ALittleScriptAllExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content)
{
    content = "";
    std::vector<std::string> expr_list;
    for (auto& child : root->GetChilds())
    {
        if (std::dynamic_pointer_cast<ALittleScriptFlowExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateFlowExpr(std::dynamic_pointer_cast<ALittleScriptFlowExprElement>(child), continue_num, has_continue, pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptReturnExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateReturnExpr(std::dynamic_pointer_cast<ALittleScriptReturnExprElement>(child), pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateDoWhileExpr(std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(child), continue_num + 1, pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateWhileExpr(std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(child), continue_num + 1, pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptForExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateForExpr(std::dynamic_pointer_cast<ALittleScriptForExprElement>(child), continue_num + 1, pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptIfExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateIfExpr(std::dynamic_pointer_cast<ALittleScriptIfExprElement>(child), continue_num, has_continue, pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptOpAssignExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateOpAssignExpr(std::dynamic_pointer_cast<ALittleScriptOpAssignExprElement>(child), pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptVarAssignExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateVarAssignExpr(std::dynamic_pointer_cast<ALittleScriptVarAssignExprElement>(child), pre_tab, u8"local ", sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptOp1ExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateOp1Expr(std::dynamic_pointer_cast<ALittleScriptOp1ExprElement>(child), pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateWrapExpr(std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(child), continue_num, has_continue, pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptThrowExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateThrowExpr(std::dynamic_pointer_cast<ALittleScriptThrowExprElement>(child), pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptAssertExprElement>(child))
        {
            std::string sub_content;
            auto error = GenerateAssertExpr(std::dynamic_pointer_cast<ALittleScriptAssertExprElement>(child), pre_tab, sub_content);
            if (error) return error;
            expr_list.push_back(sub_content);
        }
    }

    content = ABnfFactory::Join(expr_list, "\n");
    return nullptr;
}

// ����ö��

ABnfGuessError ALittleScriptTranslationLua::GenerateEnum(std::shared_ptr<ALittleScriptEnumDecElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto name_dec = root->GetEnumNameDec();
    if (name_dec == nullptr) return ABnfGuessError(root, root->GetElementText() + u8"û�ж���ö����");

    content += pre_tab + m_alittle_gen_namespace_pre + name_dec->GetElementText() + " = {\n";

    int enum_value = -1;
    std::string enum_string;

    auto body_dec = root->GetEnumBodyDec();
    if (body_dec == nullptr) return ABnfGuessError(root, u8"���ʽ������");

    const auto& var_dec_list = body_dec->GetEnumVarDecList();
    for (auto& var_dec : var_dec_list)
    {
        if (var_dec->GetNumber() != nullptr)
        {
            std::string value = var_dec->GetNumber()->GetElementText();
            if (!ALittleScriptUtility::IsInt(var_dec->GetNumber()))
                return ABnfGuessError(var_dec, var_dec->GetNumber()->GetElementText() + u8"��Ӧ��ö��ֵ����������");

            if (value.find("0x") == 0)
            {
                try {
                    enum_value = std::stoi(value.substr(2), nullptr, 16);
                }
                catch (std::exception e) {
                    return ABnfGuessError(var_dec, u8"ö��ֵ��ʮ������������ʧ��");
                }
            }
            else
            {
                try {
                    enum_value = std::stoi(value, nullptr, 10);
                }
                catch (std::exception e) {
                    return ABnfGuessError(var_dec, u8"ö��ֵ��ʮ����������ʧ��");
                }
            }
            enum_string = value;
        }
        else if (var_dec->GetText() != nullptr)
        {
            enum_string = var_dec->GetText()->GetElementText();
        }
        else
        {
            ++enum_value;
            enum_string = "" + enum_value;
        }

        content += pre_tab + "\t" + var_dec->GetEnumVarNameDec()->GetElementText()
            + " = " + enum_string + ",\n";
    }

    content += pre_tab + "}\n\n";

    return nullptr;
}

// ������

ABnfGuessError ALittleScriptTranslationLua::GenerateClass(std::shared_ptr<ALittleScriptClassDecElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";

    auto name_dec = root->GetClassNameDec();
    if (name_dec == nullptr) return ABnfGuessError(root, u8"��û�ж�������");

    //������//////////////////////////////////////////////////////////////////////////////////////////
    std::string class_name = name_dec->GetElementText();

    auto extends_dec = root->GetClassExtendsDec();
    std::string extends_name = "";
    if (extends_dec != nullptr && extends_dec->GetClassNameDec() != nullptr)
    {
        ABnfGuessPtr guess;
        auto error = extends_dec->GetClassNameDec()->GuessType(guess);
        if (error) return error;

        auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
        if (guess_class == nullptr)
            return ABnfGuessError(extends_dec, u8"extends_dec->GetClassNameDec()->GuessType �õ��Ĳ���ALittleScriptGuessClass");
        extends_name = guess_class->namespace_name + "." + guess_class->class_name;

        // �̳����ڶ�������
        m_is_define_relay = true;
        AddRelay(guess_class->class_dec.lock());
        m_is_define_relay = false;
    }
    if (extends_name == "")
        extends_name = "nil";
    else
        content += pre_tab + "assert(" + extends_name + ", \" extends class:" + extends_name + " is nil\")\n";

    content += pre_tab + m_alittle_gen_namespace_pre + class_name + " = "
        + "Lua.Class(" + extends_name + ", \""
        + ALittleScriptUtility::GetNamespaceName(root) + "." + class_name + "\")\n\n";

    auto class_body_dec = root->GetClassBodyDec();
    if (class_body_dec == nullptr) return ABnfGuessError(nullptr, u8"���ʽ������");

    const auto& class_element_list = class_body_dec->GetClassElementDecList();

    // ��ȡ���г�Ա������ʼ��
    std::string var_init;
    bool has_ctor = false;
    for (auto& class_element_dec : class_element_list)
    {
        if (class_element_dec->GetClassCtorDec() != nullptr)
        {
            has_ctor = true;
            continue;
        }

        auto var_dec = class_element_dec->GetClassVarDec();
        if (var_dec == nullptr) continue;

        auto var_name_dec = var_dec->GetClassVarNameDec();
        if (var_name_dec == nullptr) continue;
        auto var_name = var_name_dec->GetElementText();

        auto var_value_dec = var_dec->GetClassVarValueDec();
        if (var_value_dec == nullptr) continue;
        {
            if (var_value_dec->GetConstValue() != nullptr)
            {
                std::string var_value_content;
                auto error = GenerateConstValue(var_value_dec->GetConstValue(), pre_tab, var_value_content);
                if (error) return nullptr;
                ++m_rawset_usecount;
                var_init += pre_tab + "\t" + "___rawset(self, \"" + var_name + "\", " + var_value_content + ")\n";
            }
            else if (var_value_dec->GetOpNewStat() != nullptr)
            {
                std::string op_new_stat_content;
                auto error = GenerateOpNewStat(var_value_dec->GetOpNewStat(), pre_tab, op_new_stat_content);
                if (error) return nullptr;
                ++m_rawset_usecount;
                var_init += pre_tab + "\t" + "___rawset(self, \"" + var_name + "\", " + op_new_stat_content + ")\n";
            }
        }
    }

    // ���û��ctor�������г�ʼ������
    if (!has_ctor && var_init.size() > 0)
    {
        content += pre_tab + "function " + m_alittle_gen_namespace_pre + class_name + ":Ctor()\n";
        content += var_init;
        content += pre_tab + "end\n";
        content += "\n";
    }

    int ctor_count = 0;
    for (auto& class_element_dec : class_element_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(class_element_dec->GetModifierList()))
            continue;

        if (class_element_dec->GetClassCtorDec() != nullptr)
        {
            ++ctor_count;
            if (ctor_count > 1)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" ���ֻ����һ�����캯��");
            //�������캯��//////////////////////////////////////////////////////////////////////////////////////////
            std::string ctor_param_list;

            auto ctor_dec = class_element_dec->GetClassCtorDec();
            std::vector<std::string> param_name_list;

            auto param_dec = ctor_dec->GetMethodParamDec();
            if (param_dec != nullptr)
            {
                const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
                for (auto& param_one_dec : param_one_dec_list)
                {
                    auto param_name_dec = param_one_dec->GetMethodParamNameDec();
                    if (param_name_dec == nullptr)
                        return ABnfGuessError(nullptr, u8"class " + class_name + u8" �Ĺ��캯��û�в�����");
                    param_name_list.push_back(param_name_dec->GetElementText());
                }
            }
            ctor_param_list = ABnfFactory::Join(param_name_list, ", ");
            content += pre_tab + "function " + m_alittle_gen_namespace_pre + class_name + ":Ctor(" + ctor_param_list + ")\n";

            m_open_rawset = true;

            auto body_dec = ctor_dec->GetMethodBodyDec();
            std::string all_expr_content;

            // ��ʼ����Ա����
            if (var_init.size() > 0)
            {
                all_expr_content += var_init;
                var_init = "";
            }

            if (body_dec != nullptr)
            {
                const auto& all_expr_list = body_dec->GetAllExprList();
                for (auto& all_expr : all_expr_list)
                {
                    if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
                        continue;
                    bool has_continue = false;
                    std::string sub_content;
                    auto error = GenerateAllExpr(all_expr, 0, has_continue, pre_tab + "\t", sub_content);
                    if (error) return error;
                    all_expr_content += sub_content;
                }
            }

            m_open_rawset = false;

            content += all_expr_content;
            content += pre_tab + "end\n";

            content += "\n";
        }
        else if (class_element_dec->GetClassGetterDec() != nullptr)
        {
            //����getter����///////////////////////////////////////////////////////////////////////////////////////
            auto class_getter_dec = class_element_dec->GetClassGetterDec();
            auto class_method_name_dec = class_getter_dec->GetMethodNameDec();
            if (class_method_name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" getter����û�к�����");

            content += pre_tab + "function " + m_alittle_gen_namespace_pre + class_name + ".__getter:" + class_method_name_dec->GetElementText() + "()\n";

            auto class_method_body_dec = class_getter_dec->GetMethodBodyDec();
            if (class_method_body_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" getter����û�к�����");
            const auto& all_expr_list = class_method_body_dec->GetAllExprList();
            for (auto& all_expr : all_expr_list)
            {
                if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
                    continue;
                bool has_continue = false;
                std::string sub_content;
                auto error = GenerateAllExpr(all_expr, 0, has_continue, pre_tab + "\t", sub_content);
                if (error) return error;
                content += sub_content;
            }
            content += pre_tab + "end\n";

            content += "\n";
        }
        else if (class_element_dec->GetClassSetterDec() != nullptr)
        {
            //����setter����///////////////////////////////////////////////////////////////////////////////////////
            auto class_setter_dec = class_element_dec->GetClassSetterDec();
            auto class_method_name_dec = class_setter_dec->GetMethodNameDec();
            if (class_method_name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" setter����û�к�����");
            auto param_dec = class_setter_dec->GetMethodSetterParamDec();
            if (param_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" setter��������Ҫ��һ������");

            auto param_one_dec = param_dec->GetMethodParamOneDec();
            if (param_one_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" setter��������Ҫ��һ������");

            auto param_name_dec = param_one_dec->GetMethodParamNameDec();
            if (param_name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" ����û�ж��庯����");

            content += pre_tab + "function " + m_alittle_gen_namespace_pre + class_name + ".__setter:"
                + class_method_name_dec->GetElementText() + "("
                + param_name_dec->GetElementText() + ")\n";

            auto class_method_body_dec = class_setter_dec->GetMethodBodyDec();
            if (class_method_body_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" setter����û�к�����");

            const auto& all_expr_list = class_method_body_dec->GetAllExprList();
            for (auto& all_expr : all_expr_list)
            {
                if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
                    continue;
                bool has_continue = false;
                std::string sub_content;
                auto error = GenerateAllExpr(all_expr, 0, has_continue, pre_tab + "\t", sub_content);
                if (error) return error;
                content += sub_content;
            }
            content += pre_tab + "end\n";

            content += "\n";
        }
        else if (class_element_dec->GetClassMethodDec() != nullptr)
        {
            //������Ա����//////////////////////////////////////////////////////////////////////////////////////////
            auto class_method_dec = class_element_dec->GetClassMethodDec();
            auto class_method_name_dec = class_method_dec->GetMethodNameDec();
            if (class_method_name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" ��Ա����û�к�����");

            std::vector<std::string> param_name_list;

            auto template_dec = class_method_dec->GetTemplateDec();
            if (template_dec != nullptr)
            {
                const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
                for (auto& pair_dec : pair_dec_list)
                {
                    ABnfGuessPtr guess;
                    auto error = pair_dec->GuessType(guess);
                    if (error) return error;

                    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
                    {
                        auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
                        if (guess_template->template_extends.lock() != nullptr || guess_template->is_class || guess_template->is_struct)
                            param_name_list.push_back(guess_template->GetValue());
                    }
                }
            }

            auto param_dec = class_method_dec->GetMethodParamDec();
            if (param_dec != nullptr)
            {
                const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
                for (auto& param_one_dec : param_one_dec_list)
                {
                    if (param_one_dec->GetMethodParamTailDec() != nullptr)
                    {
                        param_name_list.push_back(param_one_dec->GetMethodParamTailDec()->GetElementText());
                        continue;
                    }
                    auto param_name_dec = param_one_dec->GetMethodParamNameDec();
                    if (param_name_dec == nullptr)
                        return ABnfGuessError(nullptr, u8"class " + class_name + u8" ��Ա����û�в�����");
                    param_name_list.push_back(param_name_dec->GetElementText());
                }
            }
            std::string method_param_list = ABnfFactory::Join(param_name_list, ", ");
            content += pre_tab + "function " + m_alittle_gen_namespace_pre + class_name + ":"
                + class_method_name_dec->GetElementText()
                + "(" + method_param_list + ")\n";

            auto coroutine_type = ALittleScriptUtility::GetCoroutineType(class_element_dec->GetModifierList());
            if (coroutine_type == "await")
                content += pre_tab + "\tlocal ___COROUTINE = coroutine.running()\n";

            auto class_method_body_dec = class_method_dec->GetMethodBodyDec();
            if (class_method_body_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" ��Ա����û�к�����");
            const auto& all_expr_list = class_method_body_dec->GetAllExprList();
            for (auto& all_expr : all_expr_list)
            {
                if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
                    continue;
                bool has_continue = false;
                std::string sub_content;
                auto error = GenerateAllExpr(all_expr, 0, has_continue, pre_tab + "\t", sub_content);
                if (error) return error;
                content += sub_content;
            }
            content += pre_tab + "end\n";

            if (coroutine_type == "async")
            {
                content += pre_tab
                    + m_alittle_gen_namespace_pre + class_name + "." + class_method_name_dec->GetElementText()
                    + " = " + "Lua.CoWrap("
                    + m_alittle_gen_namespace_pre + class_name + "." + class_method_name_dec->GetElementText()
                    + ")\n";
            }

            content += "\n";
        }
        else if (class_element_dec->GetClassStaticDec() != nullptr)
        {
            //������̬����//////////////////////////////////////////////////////////////////////////////////////////
            auto class_static_dec = class_element_dec->GetClassStaticDec();
            auto class_method_name_dec = class_static_dec->GetMethodNameDec();
            if (class_method_name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" ��̬����û�к�����");
            std::vector<std::string> param_name_list;

            auto template_dec = class_static_dec->GetTemplateDec();
            if (template_dec != nullptr)
            {
                const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
                for (auto& pair_dec : pair_dec_list)
                {
                    ABnfGuessPtr guess;
                    auto error = pair_dec->GuessType(guess);
                    if (error) return error;
                    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
                    {
                        auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
                        if (guess_template->template_extends.lock() != nullptr || guess_template->is_class || guess_template->is_struct)
                            param_name_list.push_back(guess_template->GetValue());
                    }
                }
            }

            auto param_dec = class_static_dec->GetMethodParamDec();
            if (param_dec != nullptr)
            {
                const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
                for (auto& param_one_dec : param_one_dec_list)
                {
                    if (param_one_dec->GetMethodParamTailDec() != nullptr)
                    {
                        param_name_list.push_back(param_one_dec->GetMethodParamTailDec()->GetElementText());
                        continue;
                    }
                    auto param_name_dec = param_one_dec->GetMethodParamNameDec();
                    if (param_name_dec == nullptr)
                        return ABnfGuessError(nullptr, u8"class " + class_name + u8" ��̬����û�в�����");
                    param_name_list.push_back(param_name_dec->GetElementText());
                }
            }

            std::string method_param_list = ABnfFactory::Join(param_name_list, ", ");
            content += pre_tab + "function " + m_alittle_gen_namespace_pre + class_name + "."
                + class_method_name_dec->GetElementText()
                + "(" + method_param_list + ")\n";

            auto coroutine_type = ALittleScriptUtility::GetCoroutineType(class_element_dec->GetModifierList());
            if (coroutine_type == "await")
                content += pre_tab + "\tlocal ___COROUTINE = coroutine.running()\n";

            auto class_method_body_dec = class_static_dec->GetMethodBodyDec();
            if (class_method_body_dec == nullptr)
                return ABnfGuessError(nullptr, u8"class " + class_name + u8" ��̬����û�к�����");

            const auto& all_expr_list = class_method_body_dec->GetAllExprList();
            for (auto& all_expr : all_expr_list)
            {
                if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
                    continue;
                bool has_continue = false;
                std::string sub_content;
                auto error = GenerateAllExpr(all_expr, 0, has_continue, pre_tab + "\t", sub_content);
                if (error) return error;
                content += sub_content;
            }
            content += pre_tab + "end\n";

            if (coroutine_type == "async")
            {
                content += pre_tab
                    + m_alittle_gen_namespace_pre + class_name + "." + class_method_name_dec->GetElementText()
                    + " = " + "Lua.CoWrap("
                    + m_alittle_gen_namespace_pre + class_name + "." + class_method_name_dec->GetElementText()
                    + ")\n";
            }
            content += "\n";
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

    return nullptr;
}

// ���ɵ���

ABnfGuessError ALittleScriptTranslationLua::GenerateInstance(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& modifier, std::shared_ptr<ALittleScriptInstanceDecElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";
    auto var_assign_expr = root->GetVarAssignExpr();
    const auto& pair_dec_list = var_assign_expr->GetVarAssignDecList();
    if (pair_dec_list.size() == 0)
        return ABnfGuessError(nullptr, u8"�ֲ�����û�б�����:" + root->GetElementText());

    std::vector<std::string> name_list;
    for (auto& pair_dec : pair_dec_list)
        name_list.push_back(pair_dec->GetVarAssignNameDec()->GetElementText());

    content = pre_tab;

    auto access_type = ALittleScriptUtility::CalcAccessType(modifier);
    if (access_type == ClassAccessType::PRIVATE)
    {
        content += "local ";
        content += ABnfFactory::Join(name_list, ", ");
    }
    else if (access_type == ClassAccessType::PROTECTED)
    {
        content += m_alittle_gen_namespace_pre;
        content += ABnfFactory::Join(name_list, ", " + m_alittle_gen_namespace_pre);
    }
    else if (access_type == ClassAccessType::PUBLIC)
    {
        content += "_G.";
        content += ABnfFactory::Join(name_list, ", _G.");
    }

    auto value_stat = var_assign_expr->GetValueStat();
    if (value_stat == nullptr)
    {
        content += " = nil\n";
        return nullptr;
    }

    std::string sub_content;
    auto error = GenerateValueStat(value_stat, pre_tab, sub_content);
    if (error) return error;
    content += " = " + sub_content + "\n";
    return nullptr;
}

// ����ȫ�ֺ���
ABnfGuessError ALittleScriptTranslationLua::GenerateGlobalMethod(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& modifier, std::shared_ptr<ALittleScriptGlobalMethodDecElement> root, const std::string& pre_tab, std::string& content)
{
    content = "";

    auto global_method_name_dec = root->GetMethodNameDec();
    if (global_method_name_dec == nullptr)
        return ABnfGuessError(nullptr, u8"ȫ�ֺ���û�к�����");

    // ������
    std::string method_name = global_method_name_dec->GetElementText();

    // �������б�
    std::vector<std::string> param_name_list;

    // ģ���б�
    auto template_dec = root->GetTemplateDec();
    if (template_dec != nullptr)
    {
        const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
        for (auto& pair_dec : pair_dec_list)
        {
            ABnfGuessPtr guess;
            auto error = pair_dec->GuessType(guess);
            if (error) return error;

            // ��ģ������Ϊ������
            if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
            {
                auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
                if (guess_template->template_extends.lock() != nullptr || guess_template->is_class || guess_template->is_struct)
                    param_name_list.push_back(guess_template->GetValue());
            }
        }
    }

    // ���������б�
    auto param_dec = root->GetMethodParamDec();
    if (param_dec != nullptr)
    {
        const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
        for (auto& param_one_dec : param_one_dec_list)
        {
            if (param_one_dec->GetMethodParamTailDec() != nullptr)
            {
                param_name_list.push_back(param_one_dec->GetMethodParamTailDec()->GetElementText());
                continue;
            }
            auto param_name_dec = param_one_dec->GetMethodParamNameDec();
            if (param_name_dec == nullptr)
                return ABnfGuessError(nullptr, u8"ȫ�ֺ���" + method_name + u8"û�в�����");
            param_name_list.push_back(param_name_dec->GetElementText());
        }
    }

    // ˽���ж�
    bool isPrivate = ALittleScriptUtility::CalcAccessType(modifier) == ClassAccessType::PRIVATE;

    std::string method_param_list = ABnfFactory::Join(param_name_list, ", ");
    if (isPrivate)
    {
        content += pre_tab + "local " + method_name + "\n"
            + pre_tab + method_name + " = " + "function(" + method_param_list + ")\n";
    }
    else
    {
        content += pre_tab + "function " + m_alittle_gen_namespace_pre + method_name + "(" + method_param_list + ")\n";
    }

    auto coroutine_type = ALittleScriptUtility::GetCoroutineType(modifier);
    if (coroutine_type == "await")
        content += pre_tab + "\tlocal ___COROUTINE = coroutine.running()\n";

    auto class_method_body_dec = root->GetMethodBodyDec();
    if (class_method_body_dec == nullptr)
        return ABnfGuessError(nullptr, u8"ȫ�ֺ��� " + method_name + u8" û�к�����");

    const auto& all_expr_list = class_method_body_dec->GetAllExprList();
    for (auto& all_expr : all_expr_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        bool has_continue = false;
        std::string sub_content;
        auto error = GenerateAllExpr(all_expr, 0, has_continue, pre_tab + "\t", sub_content);
        if (error) return error;
        content += sub_content;
    }
    content += pre_tab + "end\n";

    // Э���ж�
    if (coroutine_type == "async")
    {
        content += pre_tab + m_alittle_gen_namespace_pre + method_name
            + " = " + "Lua.CoWrap("
            + m_alittle_gen_namespace_pre + method_name + ")\n";
    }

    content += "\n";

    // ע���ж�
    std::string proto_type = ALittleScriptUtility::GetProtocolType(modifier);
    std::string command_text;
    std::string command_type;
    ALittleScriptUtility::GetCommandDetail(modifier, command_type, command_text);
    if (proto_type.size())
    {
        if (param_dec == nullptr) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ�������������������");
        const auto& one_dec_list = param_dec->GetMethodParamOneDecList();
        if (one_dec_list.size() != 2 || one_dec_list[1]->GetAllType() == nullptr) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ�������������������");

        ABnfGuessPtr guess_param;
        auto error = one_dec_list[1]->GetAllType()->GuessType(guess_param);
        if (error) return error;

        auto guess_param_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_param);
        if (!guess_param_struct) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ������ڶ�������������struct");

        std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> return_list;
        auto return_dec = root->GetMethodReturnDec();
        if (return_dec != nullptr)
        {
            const auto& return_one_dec_list = return_dec->GetMethodReturnOneDecList();
            for (auto& return_one_dec : return_one_dec_list)
            {
                if (return_one_dec->GetAllType() != nullptr)
                    return_list.push_back(return_one_dec->GetAllType());
            }
        }

        ABnfGuessPtr guess_return;
        if (return_list.size() == 1)
        {
            error = return_list[0]->GuessType(guess_return);
            if (error) return error;
        }

        if (proto_type == "Http")
        {
            if (return_list.size() != 1) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ��������ҽ���һ������ֵ");
            content += pre_tab + "ALittle.RegHttpCallback(\"" + guess_param_struct->GetValue() + "\", " + m_alittle_gen_namespace_pre + method_name + ")\n";
        }
        else if (proto_type == "HttpDownload")
        {
            if (return_list.size() != 2) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ��������ҽ�����������ֵ");
            content += pre_tab
                + "ALittle.RegHttpDownloadCallback(\""
                + guess_param_struct->GetValue() + "\", " + m_alittle_gen_namespace_pre + method_name + ")\n";
        }
        else if (proto_type == "HttpUpload")
        {
            if (return_list.size() != 0) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ����������з���ֵ");
            content += pre_tab
                + "ALittle.RegHttpFileCallback(\""
                + guess_param_struct->GetValue() + "\", " + m_alittle_gen_namespace_pre + method_name + ")\n";
        }
        else if (proto_type == "Msg")
        {
            if (return_list.size() > 1) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ��������ֻ��һ������ֵ");
            error = GenerateReflectStructInfo(guess_param_struct);
            if (error) return error;

            if (guess_return == nullptr)
            {
                content += pre_tab
                    + "ALittle.RegMsgCallback(" + std::to_string(ALittleScriptUtility::StructHash(guess_param_struct))
                    + ", " + m_alittle_gen_namespace_pre + method_name + ")\n";
            }
            else
            {
                auto guess_return_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_return);
                if (!guess_return_struct) return ABnfGuessError(nullptr, u8"��" + proto_type + u8"��ȫ�ֺ���������ֵ������struct");

                content += pre_tab
                    + "ALittle.RegMsgRpcCallback(" + std::to_string(ALittleScriptUtility::StructHash(guess_param_struct))
                    + ", " + m_alittle_gen_namespace_pre + method_name + ", " + std::to_string(ALittleScriptUtility::StructHash(guess_return_struct))
                    + ")\n";

                error = GenerateReflectStructInfo(guess_return_struct);
                if (error) return error;
            }
        }
    }
    else if (command_type.size())
    {
        std::vector<std::string> var_list;
        std::vector<std::string> name_list;
        for (auto& param_name : param_name_list)
            name_list.push_back("\"" + param_name + "\"");

        if (param_dec != nullptr)
        {
            const auto& one_dec_list = param_dec->GetMethodParamOneDecList();
            for (auto& one_dec : one_dec_list)
            {
                ABnfGuessPtr all_type_guess;
                auto error = one_dec->GetAllType()->GuessType(all_type_guess);
                if (error) return error;
                var_list.push_back("\"" + all_type_guess->GetValue() + "\"");
            }
        }

        content += pre_tab
            + "ALittle.RegCmdCallback(\"" + method_name + "\", " + m_alittle_gen_namespace_pre + method_name
            + ", {" + ABnfFactory::Join(var_list, ",") + "}, {" + ABnfFactory::Join(name_list, ",")
            + "}, \"" + command_text + "\")\n";
    }

    return nullptr;
}

ABnfGuessError ALittleScriptTranslationLua::GenerateRoot(const std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>>& element_dec_list, std::string& content)
{
    content = "-- ALittle Generate Lua And Do Not Edit This Line!\n";
    m_reflect_map.clear();

    m_alittle_gen_namespace_pre = "";
    if (m_namespace_name == "lua" || m_namespace_name == "alittle")
        m_alittle_gen_namespace_pre = "_G.";
    else
        m_alittle_gen_namespace_pre = m_namespace_name + ".";

    std::string other_content = "";
    for (auto& child : element_dec_list)
    {
        if (!ALittleScriptUtility::IsLanguageEnable(child->GetModifierList()))
            continue;

        // ����ṹ��
        if (child->GetStructDec() != nullptr)
        {
            ABnfGuessPtr guess;
            auto error = child->GetStructDec()->GuessType(guess);
            if (error) return error;
            error = GenerateReflectStructInfo(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess));
            if (error) return error;
        }
        // ����enum
        else if (child->GetEnumDec() != nullptr)
        {
            std::string sub_content;
            auto error = GenerateEnum(child->GetEnumDec(), u8"", sub_content);
            if (error) return error;
            other_content += sub_content;
        }
        // ����class
        else if (child->GetClassDec() != nullptr)
        {
            std::string sub_content;
            auto error = GenerateClass(child->GetClassDec(), u8"", sub_content);
            if (error) return error;
            other_content += sub_content;
        }
        // ����instance
        else if (child->GetInstanceDec() != nullptr)
        {
            m_is_define_relay = true;
            std::string sub_content;
            auto error = GenerateInstance(child->GetModifierList(), child->GetInstanceDec(), u8"", sub_content);
            m_is_define_relay = false;
            if (error) return error;
            other_content += sub_content;
        }
        // ����ȫ�ֺ���
        else if (child->GetGlobalMethodDec() != nullptr)
        {
            m_is_define_relay = false;
            std::string sub_content;
            auto error = GenerateGlobalMethod(child->GetModifierList(), child->GetGlobalMethodDec(), u8"", sub_content);
            if (error) return error;
            other_content += sub_content;
        }
        // ����ȫ�ֲ������ʽ
        else if (child->GetOpAssignExpr() != nullptr)
        {
            m_is_define_relay = true;
            std::string sub_content;
            auto error = GenerateOpAssignExpr(child->GetOpAssignExpr(), u8"", sub_content);
            m_is_define_relay = false;
            if (error) return error;
            other_content += sub_content;
        }
        // ����using
        else if (child->GetUsingDec() != nullptr)
        {
            m_is_define_relay = true;
            std::string sub_content;
            auto error = GenerateUsingDec(child->GetModifierList(), child->GetUsingDec(), u8"", sub_content);
            m_is_define_relay = false;
            if (error) return error;
            other_content += sub_content;
        }
    }

    if (m_namespace_name == "lua" || m_namespace_name == "alittle")
        content += "do\n";
    else
    {
        content += "do\nif _G." + m_namespace_name + " == nil then _G." + m_namespace_name + " = {} end\n";
        content += "local " + m_namespace_name + " = " + m_namespace_name + "\n";
        if (m_namespace_name != "Lua") content += "local Lua = Lua\n";
        if (m_namespace_name != "ALittle") content += "local ALittle = ALittle\n";
    }

    if (m_rawset_usecount > 0) content += "local ___rawset = rawset\n";
    content += "local ___pairs = pairs\n";
    content += "local ___ipairs = ipairs\n";
    
    if (m_need_all_struct) content += "local ___all_struct = ALittle.GetAllStruct()\n";
    content += "\n";

    std::list<StructReflectInfo*> info_list;
    for (auto& pair : m_reflect_map) info_list.push_back(&pair.second);
    info_list.sort(StructReflectSort);
    for (auto& info : info_list)
    {
        if (!info->generate) continue;
        content += "ALittle.RegStruct(" + std::to_string(info->hash_code) + ", \"" + info->name + "\", " + info->content + ")\n";
    }
    content += "\n";

    content += other_content;

    content += "end";

    return nullptr;
}
