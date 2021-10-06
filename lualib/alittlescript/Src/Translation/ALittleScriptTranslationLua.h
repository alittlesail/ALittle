﻿
#ifndef _ALITTLE_ALITTLESCRIPTTRANSLATIONLUA_H_
#define _ALITTLE_ALITTLESCRIPTTRANSLATIONLUA_H_

#include "ALittleScriptTranslation.h"

class ALittleScriptKeyElement;
class ALittleScriptStringElement;
class ALittleScriptRegexElement;
class ALittleScriptConstModifierElement;
class ALittleScriptOp8SuffixEeElement;
class ALittleScriptRootElement;
class ALittleScriptElseIfConditionElement;
class ALittleScriptNumberElement;
class ALittleScriptProtocolModifierElement;
class ALittleScriptLineCommentElement;
class ALittleScriptMethodReturnTailDecElement;
class ALittleScriptIdElement;
class ALittleScriptBlockCommentElement;
class ALittleScriptStructOptionDecElement;
class ALittleScriptTextElement;
class ALittleScriptRegisterModifierElement;
class ALittleScriptAccessModifierElement;
class ALittleScriptMethodSetterParamDecElement;
class ALittleScriptTemplateExtendsClassDecElement;
class ALittleScriptOp7SuffixEeElement;
class ALittleScriptNamespaceElementDecElement;
class ALittleScriptModifierElement;
class ALittleScriptCoroutineModifierElement;
class ALittleScriptMethodReturnDecElement;
class ALittleScriptCommandBodyDecElement;
class ALittleScriptTemplateExtendsStructDecElement;
class ALittleScriptAllTypeConstElement;
class ALittleScriptCommandModifierElement;
class ALittleScriptOp5Element;
class ALittleScriptNullableModifierElement;
class ALittleScriptMethodParamTailDecElement;
class ALittleScriptForInConditionElement;
class ALittleScriptStructDecElement;
class ALittleScriptOpAssignExprElement;
class ALittleScriptNamespaceDecElement;
class ALittleScriptLanguageNameDecElement;
class ALittleScriptStructNameDecElement;
class ALittleScriptPropertyValueElement;
class ALittleScriptNamespaceNameDecElement;
class ALittleScriptLanguageBodyDecElement;
class ALittleScriptEnumVarNameDecElement;
class ALittleScriptLanguageModifierElement;
class ALittleScriptStructVarDecElement;
class ALittleScriptNativeModifierElement;
class ALittleScriptAttributeModifierElement;
class ALittleScriptMethodParamOneDecElement;
class ALittleScriptTemplateDecElement;
class ALittleScriptOp4SuffixEeElement;
class ALittleScriptTemplatePairDecElement;
class ALittleScriptOp6SuffixExElement;
class ALittleScriptTemplateNameDecElement;
class ALittleScriptTemplateExtendsDecElement;
class ALittleScriptClassVarNameDecElement;
class ALittleScriptClassDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptForBodyElement;
class ALittleScriptClassNameDecElement;
class ALittleScriptClassExtendsDecElement;
class ALittleScriptElseExprElement;
class ALittleScriptClassElementDecElement;
class ALittleScriptMethodParamDecElement;
class ALittleScriptOp6SuffixElement;
class ALittleScriptPropertyValueThisTypeElement;
class ALittleScriptClassBodyDecElement;
class ALittleScriptClassVarValueDecElement;
class ALittleScriptUsingNameDecElement;
class ALittleScriptClassVarDecElement;
class ALittleScriptStructExtendsDecElement;
class ALittleScriptPropertyValueMethodCallElement;
class ALittleScriptAllTypeElement;
class ALittleScriptReturnYieldElement;
class ALittleScriptStructBodyDecElement;
class ALittleScriptMethodGetterParamDecElement;
class ALittleScriptGenericTypeElement;
class ALittleScriptStructVarNameDecElement;
class ALittleScriptOp7SuffixElement;
class ALittleScriptGenericFunctorParamTypeElement;
class ALittleScriptStructOptionNameDecElement;
class ALittleScriptEnumDecElement;
class ALittleScriptEnumNameDecElement;
class ALittleScriptEnumBodyDecElement;
class ALittleScriptEnumVarDecElement;
class ALittleScriptInstanceDecElement;
class ALittleScriptUsingDecElement;
class ALittleScriptMethodParamNameDecElement;
class ALittleScriptPropertyValueDotIdElement;
class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodReturnOneDecElement;
class ALittleScriptOp3Element;
class ALittleScriptClassCtorDecElement;
class ALittleScriptClassGetterDecElement;
class ALittleScriptClassSetterDecElement;
class ALittleScriptOpNewListStatElement;
class ALittleScriptClassMethodDecElement;
class ALittleScriptClassStaticDecElement;
class ALittleScriptGlobalMethodDecElement;
class ALittleScriptAllExprElement;
class ALittleScriptEmptyExprElement;
class ALittleScriptForExprElement;
class ALittleScriptForConditionElement;
class ALittleScriptForStepConditionElement;
class ALittleScriptForStartStatElement;
class ALittleScriptForEndStatElement;
class ALittleScriptForStepStatElement;
class ALittleScriptForPairDecElement;
class ALittleScriptWhileExprElement;
class ALittleScriptWhileConditionElement;
class ALittleScriptWhileBodyElement;
class ALittleScriptOp2StatElement;
class ALittleScriptDoWhileExprElement;
class ALittleScriptDoWhileConditionElement;
class ALittleScriptDoWhileBodyElement;
class ALittleScriptIfExprElement;
class ALittleScriptIfConditionElement;
class ALittleScriptIfBodyElement;
class ALittleScriptElseBodyElement;
class ALittleScriptElseIfExprElement;
class ALittleScriptElseIfBodyElement;
class ALittleScriptWrapExprElement;
class ALittleScriptReturnExprElement;
class ALittleScriptFlowExprElement;
class ALittleScriptVarAssignExprElement;
class ALittleScriptVarAssignDecElement;
class ALittleScriptVarAssignNameDecElement;
class ALittleScriptOpAssignElement;
class ALittleScriptOp1ExprElement;
class ALittleScriptThrowExprElement;
class ALittleScriptAssertExprElement;
class ALittleScriptCustomTypeElement;
class ALittleScriptCustomTypeNameElement;
class ALittleScriptOp4StatElement;
class ALittleScriptCustomTypeDotIdElement;
class ALittleScriptCustomTypeDotIdNameElement;
class ALittleScriptCustomTypeTemplateElement;
class ALittleScriptGenericMapTypeElement;
class ALittleScriptPrimitiveTypeElement;
class ALittleScriptGenericListTypeElement;
class ALittleScriptGenericFunctorTypeElement;
class ALittleScriptGenericFunctorParamOneTypeElement;
class ALittleScriptGenericFunctorParamTailElement;
class ALittleScriptGenericFunctorReturnTailElement;
class ALittleScriptGenericFunctorReturnOneTypeElement;
class ALittleScriptGenericFunctorReturnTypeElement;
class ALittleScriptValueStatElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptValueOpStatElement;
class ALittleScriptOpNewStatElement;
class ALittleScriptBindStatElement;
class ALittleScriptTcallStatElement;
class ALittleScriptWrapValueStatElement;
class ALittleScriptConstValueElement;
class ALittleScriptCoroutineStatElement;
class ALittleScriptReflectValueElement;
class ALittleScriptReflectCustomTypeElement;
class ALittleScriptReflectValueStatElement;
class ALittleScriptPathsValueElement;
class ALittleScriptPropertyValueFirstTypeElement;
class ALittleScriptPropertyValueCastTypeElement;
class ALittleScriptPropertyValueCustomTypeElement;
class ALittleScriptPropertyValueSuffixElement;
class ALittleScriptPropertyValueDotIdNameElement;
class ALittleScriptPropertyValueBracketValueElement;
class ALittleScriptPropertyValueMethodTemplateElement;
class ALittleScriptOp12Element;
class ALittleScriptOp12StatElement;
class ALittleScriptOp12SuffixElement;
class ALittleScriptOp12SuffixEeElement;
class ALittleScriptOp12SuffixExElement;
class ALittleScriptOp11Element;
class ALittleScriptOp11StatElement;
class ALittleScriptOp11SuffixElement;
class ALittleScriptOp11SuffixEeElement;
class ALittleScriptOp11SuffixExElement;
class ALittleScriptOp10Element;
class ALittleScriptOp10StatElement;
class ALittleScriptOp10SuffixElement;
class ALittleScriptOp10SuffixEeElement;
class ALittleScriptOp10SuffixExElement;
class ALittleScriptOp9Element;
class ALittleScriptOp9StatElement;
class ALittleScriptOp9SuffixElement;
class ALittleScriptOp9SuffixEeElement;
class ALittleScriptOp9SuffixExElement;
class ALittleScriptOp8Element;
class ALittleScriptOp8StatElement;
class ALittleScriptOp8SuffixElement;
class ALittleScriptOp8SuffixExElement;
class ALittleScriptOp7Element;
class ALittleScriptOp7StatElement;
class ALittleScriptOp7SuffixExElement;
class ALittleScriptOp6Element;
class ALittleScriptOp6StatElement;
class ALittleScriptOp6SuffixEeElement;
class ALittleScriptOp5StatElement;
class ALittleScriptOp5SuffixElement;
class ALittleScriptOp5SuffixEeElement;
class ALittleScriptOp5SuffixExElement;
class ALittleScriptOp4Element;
class ALittleScriptOp4SuffixElement;
class ALittleScriptOp4SuffixExElement;
class ALittleScriptOp3StatElement;
class ALittleScriptOp3SuffixElement;
class ALittleScriptOp3SuffixExElement;
class ALittleScriptOp2Element;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp2SuffixExElement;
class ALittleScriptOp1Element;

class ALittleScriptTranslationLua : public ALittleScriptTranslation
{
private:
    // 命名域生成前缀
    std::string m_alittle_gen_namespace_pre;
        
    // 标记是否使用rawset
    bool m_open_rawset = false;
    // 使用rawset的数量
    int m_rawset_usecount = 0;

    // 当前文件需要处理的反射信息
    std::unordered_map<std::string, StructReflectInfo> m_reflect_map;
    // 是否需要all_struct
    bool m_need_all_struct = false;

protected:
    std::string GetExt() override { return "lua"; }

    // 生成bind命令
private:
    ABnfGuessError GenerateBindStat(std::shared_ptr<ALittleScriptBindStatElement> bind_stat, const std::string& pre_tab, std::string& content);

    // 生成tcall命令
    ABnfGuessError GenerateTcallStat(std::shared_ptr<ALittleScriptTcallStatElement> tcall_stat, const std::string& pre_tab, std::string& content);

    // 生成new List
    ABnfGuessError GenerateOpNewListStat(std::shared_ptr<ALittleScriptOpNewListStatElement> op_new_list, const std::string& pre_tab, std::string& content);

    // 生成new
    ABnfGuessError GenerateOpNewStat(std::shared_ptr<ALittleScriptOpNewStatElement> op_new_stat, const std::string& pre_tab, std::string& content);

    // 生成custom_type定义中的模板参数列表
    ABnfGuessError GenerateCustomTypeTemplateList(std::vector<ABnfGuessPtr>& guess_list,
                                        std::vector<std::string>& template_param_list,
        std::vector<std::string>& template_param_name_list);

    // 生成custom_type
    ABnfGuessError GenerateCustomType(std::shared_ptr<ALittleScriptCustomTypeElement> custom_type, const std::string& pre_tab, std::string& content);

	// 生成12级运算符
    ABnfGuessError GenerateOp12Suffix(std::shared_ptr<ALittleScriptOp12SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp12SuffixEe(std::shared_ptr<ALittleScriptOp12SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp12SuffixEx(std::shared_ptr<ALittleScriptOp12SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp12Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp12StatElement> op_12_stat, const std::string& pre_tab, std::string& content);

    // 生成11级运算符
    ABnfGuessError GenerateOp11Suffix(std::shared_ptr<ALittleScriptOp11SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp11SuffixEe(std::shared_ptr<ALittleScriptOp11SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp11SuffixEx(std::shared_ptr<ALittleScriptOp11SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp11Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp11StatElement> op_11_stat, const std::string& pre_tab, std::string& content);

    // 生成10级运算符
    ABnfGuessError GenerateOp10Suffix(std::shared_ptr<ALittleScriptOp10SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp10SuffixEe(std::shared_ptr<ALittleScriptOp10SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp10SuffixEx(std::shared_ptr<ALittleScriptOp10SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp10Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp10StatElement> op_10_stat, const std::string& pre_tab, std::string& content);

    // 生成9级运算符
    ABnfGuessError GenerateOp9Suffix(std::shared_ptr<ALittleScriptOp9SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp9SuffixEe(std::shared_ptr<ALittleScriptOp9SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp9SuffixEx(std::shared_ptr<ALittleScriptOp9SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp9Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp9StatElement> op_9_stat, const std::string& pre_tab, std::string& content);

    // 生成8级运算符
    ABnfGuessError GenerateOp8Suffix(std::shared_ptr<ALittleScriptOp8SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp8SuffixEe(std::shared_ptr<ALittleScriptOp8SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp8SuffixEx(std::shared_ptr<ALittleScriptOp8SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp8Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp8StatElement> op_8_stat, const std::string& pre_tab, std::string& content);

    // 生成7级运算符
    ABnfGuessError GenerateOp7Suffix(std::shared_ptr<ALittleScriptOp7SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp7SuffixEe(std::shared_ptr<ALittleScriptOp7SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp7SuffixEx(std::shared_ptr<ALittleScriptOp7SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp7Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp7StatElement> op_7_stat, const std::string& pre_tab, std::string& content);

    // 生成6级运算符
    ABnfGuessError GenerateOp6Suffix(std::shared_ptr<ALittleScriptOp6SuffixElement> suffix, const std::string& pre_tab, std::string& content);


    ABnfGuessError GenerateOp6SuffixEe(std::shared_ptr<ALittleScriptOp6SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);


    ABnfGuessError GenerateOp6SuffixEx(std::shared_ptr<ALittleScriptOp6SuffixExElement> suffix, const std::string& pre_tab, std::string& content);


    ABnfGuessError GenerateOp6Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp6StatElement> op_6_tat, const std::string& pre_tab, std::string& content);

    // 生成5级运算符

    ABnfGuessError GenerateOp5Suffix(std::shared_ptr<ALittleScriptOp5SuffixElement> suffix, const std::string& pre_tab, std::string& content);


    ABnfGuessError GenerateOp5SuffixEe(std::shared_ptr<ALittleScriptOp5SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);


    ABnfGuessError GenerateOp5SuffixEx(std::shared_ptr<ALittleScriptOp5SuffixExElement> suffix, const std::string& pre_tab, std::string& content);
        
    ABnfGuessError GenerateOp5Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp5StatElement> op_5_stat, const std::string& pre_tab, std::string& content);

    // 生成4级运算符
    ABnfGuessError GenerateOp4Suffix(std::shared_ptr<ALittleScriptOp4SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp4SuffixEe(std::shared_ptr<ALittleScriptOp4SuffixEeElement> suffix, const std::string& pre_tab, std::string& content);


    ABnfGuessError GenerateOp4SuffixEx(std::shared_ptr<ALittleScriptOp4SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp4Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp4StatElement> op_4_stat, const std::string& pre_tab, std::string& content);

    // 生成3级运算符
    ABnfGuessError GenerateOp3Suffix(std::shared_ptr<ALittleScriptOp3SuffixElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp3SuffixEx(std::shared_ptr<ALittleScriptOp3SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateValueOpStat(std::shared_ptr<ALittleScriptValueOpStatElement> value_op_stat, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp3Stat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp3StatElement> op_3_stat, const std::string& pre_tab, std::string& content);

    // 生成2级运算符
    ABnfGuessError GenerateOp2SuffixEx(std::shared_ptr<ALittleScriptOp2SuffixExElement> suffix, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp2Value(std::shared_ptr<ALittleScriptOp2ValueElement> op_2_value, const std::string& pre_tab, std::string& content);

    ABnfGuessError GenerateOp2Stat(std::shared_ptr<ALittleScriptOp2StatElement> op_2_stat, const std::string& pre_tab, std::string& content);

    // 生成值表达式
    ABnfGuessError GenerateValueStat(std::shared_ptr<ALittleScriptValueStatElement> root, const std::string& pre_tab, std::string& content);
        
    // 生成ValueFactorStat
    ABnfGuessError GenerateValueFactorStat(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor, const std::string& pre_tab, std::string& content);

    // 生成常量

    ABnfGuessError GenerateConstValue(std::shared_ptr<ALittleScriptConstValueElement> const_value, const std::string& pre_tab, std::string& content);

    // 生成路径信息
    ABnfGuessError GeneratePathsValue(std::shared_ptr<ALittleScriptPathsValueElement> paths_value, const std::string& pre_tab, std::string& content);

    // 生成反射
    ABnfGuessError GenerateReflectValue(std::shared_ptr<ALittleScriptReflectValueElement> reflect_value, const std::string& pre_tab, std::string& content);

    // 生成struct的反射信息
    ABnfGuessError GenerateReflectStructInfo(ABnfGuessPtr guess);

    // 对其他工程的枚举值进行优化处理，直接生成对应的值
    ABnfGuessError GenerateEnumValue(std::shared_ptr<ALittleScriptPropertyValueElement> prop_value, bool& handle, std::string& content);

    // 生成属性值表达式
    ABnfGuessError GeneratePropertyValue(std::shared_ptr<ALittleScriptPropertyValueElement> prop_value, const std::string& pre_tab, std::string& content);

    // 生成co
    ABnfGuessError GenerateCoroutineStat(std::shared_ptr<ALittleScriptCoroutineStatElement> root, std::string& content);

    // 生成using
    ABnfGuessError GenerateUsingDec(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& modifier, std::shared_ptr<ALittleScriptUsingDecElement> root, const std::string& pre_tab, std::string& content);

    // 生成异常表达式
    ABnfGuessError GenerateThrowExpr(std::shared_ptr<ALittleScriptThrowExprElement> return_expr, const std::string& pre_tab, std::string& content);

    // 生成断言表达式
    ABnfGuessError GenerateAssertExpr(std::shared_ptr<ALittleScriptAssertExprElement> assert_expr, const std::string& pre_tab, std::string& content);

    // 生成1级运算符
    ABnfGuessError GenerateOp1Expr(std::shared_ptr<ALittleScriptOp1ExprElement> root, const std::string& pre_tab, std::string& content);

    // 生成变量定义以及赋值表达式
    ABnfGuessError GenerateVarAssignExpr(std::shared_ptr<ALittleScriptVarAssignExprElement> root, const std::string& pre_tab, const std::string& pre_string, std::string& content);

    // 生成赋值表达式
    ABnfGuessError GenerateOpAssignExpr(std::shared_ptr<ALittleScriptOpAssignExprElement> root, const std::string& pre_tab, std::string& content);

    // 生成else表达式
    ABnfGuessError GenerateElseExpr(std::shared_ptr<ALittleScriptElseExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content);

    // 生成elseif表达式
    ABnfGuessError GenerateElseIfExpr(std::shared_ptr<ALittleScriptElseIfExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content);

    // 生成if表达式
    ABnfGuessError GenerateIfExpr(std::shared_ptr<ALittleScriptIfExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content);

    // 生成for表达式
    ABnfGuessError GenerateForExpr(std::shared_ptr<ALittleScriptForExprElement> root, int continue_num, const std::string& pre_tab, std::string& content);

    // 生成while表达式
    ABnfGuessError GenerateWhileExpr(std::shared_ptr<ALittleScriptWhileExprElement> root, int continue_num, const std::string& pre_tab, std::string& content);

    // 生成do while表达式
    ABnfGuessError GenerateDoWhileExpr(std::shared_ptr<ALittleScriptDoWhileExprElement> root, int continue_num, const std::string& pre_tab, std::string& content);

    // 生成子表达式组
    ABnfGuessError GenerateWrapExpr(std::shared_ptr<ALittleScriptWrapExprElement> root, int continue_num, bool& has_continue_expr, const std::string& pre_tab, std::string& content);

    // 生成return表达式
    ABnfGuessError GenerateReturnExpr(std::shared_ptr<ALittleScriptReturnExprElement> root, const std::string& pre_tab, std::string& content);

    // 生成break表达式
    ABnfGuessError GenerateFlowExpr(std::shared_ptr<ALittleScriptFlowExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content);

    // 生成任意表达式
    ABnfGuessError GenerateAllExpr(std::shared_ptr<ALittleScriptAllExprElement> root, int continue_num, bool& has_continue, const std::string& pre_tab, std::string& content);

    // 生成枚举
    ABnfGuessError GenerateEnum(std::shared_ptr<ALittleScriptEnumDecElement> root, const std::string& pre_tab, std::string& content);

    // 生成类
    ABnfGuessError GenerateClass(std::shared_ptr<ALittleScriptClassDecElement> root, const std::string& pre_tab, std::string& content);

    // 生成单例
    ABnfGuessError GenerateInstance(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& modifier, std::shared_ptr<ALittleScriptInstanceDecElement> root, const std::string& pre_tab, std::string& content);

    // 生成全局函数
    ABnfGuessError GenerateGlobalMethod(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& modifier, std::shared_ptr<ALittleScriptGlobalMethodDecElement> root, const std::string& pre_tab, std::string& content);

    // 生成根节点
protected:
    ABnfGuessError GenerateRoot(const std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>>& element_dec_list, std::string& content) override;
};

#endif // _ALITTLE_ALITTLESCRIPTTRANSLATIONLUA_H_