#ifndef _ALITTLE_ALittleScriptFactory_H_
#define _ALITTLE_ALittleScriptFactory_H_

#include "../../alanguage/Index/ABnfFactory.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"
#include "ALittleScriptRegexElement.h"
#include "ALittleScriptConstModifierElement.h"
#include "ALittleScriptOp8SuffixEeElement.h"
#include "ALittleScriptRootElement.h"
#include "ALittleScriptElseIfConditionElement.h"
#include "ALittleScriptNumberElement.h"
#include "ALittleScriptProtocolModifierElement.h"
#include "ALittleScriptLineCommentElement.h"
#include "ALittleScriptMethodReturnTailDecElement.h"
#include "ALittleScriptIdElement.h"
#include "ALittleScriptBlockCommentElement.h"
#include "ALittleScriptStructOptionDecElement.h"
#include "ALittleScriptTextElement.h"
#include "ALittleScriptRegisterModifierElement.h"
#include "ALittleScriptAccessModifierElement.h"
#include "ALittleScriptMethodSetterParamDecElement.h"
#include "ALittleScriptTemplateExtendsClassDecElement.h"
#include "ALittleScriptOp7SuffixEeElement.h"
#include "ALittleScriptNamespaceElementDecElement.h"
#include "ALittleScriptModifierElement.h"
#include "ALittleScriptCoroutineModifierElement.h"
#include "ALittleScriptMethodReturnDecElement.h"
#include "ALittleScriptCommandBodyDecElement.h"
#include "ALittleScriptTemplateExtendsStructDecElement.h"
#include "ALittleScriptAllTypeConstElement.h"
#include "ALittleScriptCommandModifierElement.h"
#include "ALittleScriptOp5Element.h"
#include "ALittleScriptNullableModifierElement.h"
#include "ALittleScriptMethodParamTailDecElement.h"
#include "ALittleScriptForInConditionElement.h"
#include "ALittleScriptStructDecElement.h"
#include "ALittleScriptOpAssignExprElement.h"
#include "ALittleScriptNamespaceDecElement.h"
#include "ALittleScriptLanguageNameDecElement.h"
#include "ALittleScriptStructNameDecElement.h"
#include "ALittleScriptPropertyValueElement.h"
#include "ALittleScriptNamespaceNameDecElement.h"
#include "ALittleScriptLanguageBodyDecElement.h"
#include "ALittleScriptEnumVarNameDecElement.h"
#include "ALittleScriptLanguageModifierElement.h"
#include "ALittleScriptStructVarDecElement.h"
#include "ALittleScriptNativeModifierElement.h"
#include "ALittleScriptAttributeModifierElement.h"
#include "ALittleScriptMethodParamOneDecElement.h"
#include "ALittleScriptTemplateDecElement.h"
#include "ALittleScriptOp4SuffixEeElement.h"
#include "ALittleScriptTemplatePairDecElement.h"
#include "ALittleScriptOp6SuffixExElement.h"
#include "ALittleScriptTemplateNameDecElement.h"
#include "ALittleScriptTemplateExtendsDecElement.h"
#include "ALittleScriptClassVarNameDecElement.h"
#include "ALittleScriptClassDecElement.h"
#include "ALittleScriptMethodBodyDecElement.h"
#include "ALittleScriptForBodyElement.h"
#include "ALittleScriptClassNameDecElement.h"
#include "ALittleScriptClassExtendsDecElement.h"
#include "ALittleScriptElseExprElement.h"
#include "ALittleScriptClassElementDecElement.h"
#include "ALittleScriptMethodParamDecElement.h"
#include "ALittleScriptOp6SuffixElement.h"
#include "ALittleScriptPropertyValueThisTypeElement.h"
#include "ALittleScriptClassBodyDecElement.h"
#include "ALittleScriptClassVarValueDecElement.h"
#include "ALittleScriptUsingNameDecElement.h"
#include "ALittleScriptClassVarDecElement.h"
#include "ALittleScriptStructExtendsDecElement.h"
#include "ALittleScriptPropertyValueMethodCallElement.h"
#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptReturnYieldElement.h"
#include "ALittleScriptStructBodyDecElement.h"
#include "ALittleScriptMethodGetterParamDecElement.h"
#include "ALittleScriptGenericTypeElement.h"
#include "ALittleScriptStructVarNameDecElement.h"
#include "ALittleScriptOp7SuffixElement.h"
#include "ALittleScriptGenericFunctorParamTypeElement.h"
#include "ALittleScriptStructOptionNameDecElement.h"
#include "ALittleScriptEnumDecElement.h"
#include "ALittleScriptEnumNameDecElement.h"
#include "ALittleScriptEnumBodyDecElement.h"
#include "ALittleScriptEnumVarDecElement.h"
#include "ALittleScriptInstanceDecElement.h"
#include "ALittleScriptUsingDecElement.h"
#include "ALittleScriptMethodParamNameDecElement.h"
#include "ALittleScriptPropertyValueDotIdElement.h"
#include "ALittleScriptMethodNameDecElement.h"
#include "ALittleScriptMethodReturnOneDecElement.h"
#include "ALittleScriptOp3Element.h"
#include "ALittleScriptClassCtorDecElement.h"
#include "ALittleScriptClassGetterDecElement.h"
#include "ALittleScriptClassSetterDecElement.h"
#include "ALittleScriptOpNewListStatElement.h"
#include "ALittleScriptClassMethodDecElement.h"
#include "ALittleScriptClassStaticDecElement.h"
#include "ALittleScriptGlobalMethodDecElement.h"
#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptEmptyExprElement.h"
#include "ALittleScriptForExprElement.h"
#include "ALittleScriptForConditionElement.h"
#include "ALittleScriptForStepConditionElement.h"
#include "ALittleScriptForStartStatElement.h"
#include "ALittleScriptForEndStatElement.h"
#include "ALittleScriptForStepStatElement.h"
#include "ALittleScriptForPairDecElement.h"
#include "ALittleScriptWhileExprElement.h"
#include "ALittleScriptWhileConditionElement.h"
#include "ALittleScriptWhileBodyElement.h"
#include "ALittleScriptOp2StatElement.h"
#include "ALittleScriptDoWhileExprElement.h"
#include "ALittleScriptDoWhileConditionElement.h"
#include "ALittleScriptDoWhileBodyElement.h"
#include "ALittleScriptIfExprElement.h"
#include "ALittleScriptIfConditionElement.h"
#include "ALittleScriptIfBodyElement.h"
#include "ALittleScriptElseBodyElement.h"
#include "ALittleScriptElseIfExprElement.h"
#include "ALittleScriptElseIfBodyElement.h"
#include "ALittleScriptWrapExprElement.h"
#include "ALittleScriptReturnExprElement.h"
#include "ALittleScriptFlowExprElement.h"
#include "ALittleScriptVarAssignExprElement.h"
#include "ALittleScriptVarAssignDecElement.h"
#include "ALittleScriptVarAssignNameDecElement.h"
#include "ALittleScriptOpAssignElement.h"
#include "ALittleScriptOp1ExprElement.h"
#include "ALittleScriptThrowExprElement.h"
#include "ALittleScriptAssertExprElement.h"
#include "ALittleScriptCustomTypeElement.h"
#include "ALittleScriptCustomTypeNameElement.h"
#include "ALittleScriptOp4StatElement.h"
#include "ALittleScriptCustomTypeDotIdElement.h"
#include "ALittleScriptCustomTypeDotIdNameElement.h"
#include "ALittleScriptCustomTypeTemplateElement.h"
#include "ALittleScriptGenericMapTypeElement.h"
#include "ALittleScriptPrimitiveTypeElement.h"
#include "ALittleScriptGenericListTypeElement.h"
#include "ALittleScriptGenericFunctorTypeElement.h"
#include "ALittleScriptGenericFunctorParamOneTypeElement.h"
#include "ALittleScriptGenericFunctorParamTailElement.h"
#include "ALittleScriptGenericFunctorReturnTailElement.h"
#include "ALittleScriptGenericFunctorReturnOneTypeElement.h"
#include "ALittleScriptGenericFunctorReturnTypeElement.h"
#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptValueOpStatElement.h"
#include "ALittleScriptOpNewStatElement.h"
#include "ALittleScriptBindStatElement.h"
#include "ALittleScriptTcallStatElement.h"
#include "ALittleScriptWrapValueStatElement.h"
#include "ALittleScriptConstValueElement.h"
#include "ALittleScriptCoroutineStatElement.h"
#include "ALittleScriptReflectValueElement.h"
#include "ALittleScriptReflectCustomTypeElement.h"
#include "ALittleScriptReflectValueStatElement.h"
#include "ALittleScriptPathsValueElement.h"
#include "ALittleScriptPropertyValueFirstTypeElement.h"
#include "ALittleScriptPropertyValueCastTypeElement.h"
#include "ALittleScriptPropertyValueCustomTypeElement.h"
#include "ALittleScriptPropertyValueSuffixElement.h"
#include "ALittleScriptPropertyValueDotIdNameElement.h"
#include "ALittleScriptPropertyValueBracketValueElement.h"
#include "ALittleScriptPropertyValueMethodTemplateElement.h"
#include "ALittleScriptOp8Element.h"
#include "ALittleScriptOp8StatElement.h"
#include "ALittleScriptOp8SuffixElement.h"
#include "ALittleScriptOp8SuffixExElement.h"
#include "ALittleScriptOp7Element.h"
#include "ALittleScriptOp7StatElement.h"
#include "ALittleScriptOp7SuffixExElement.h"
#include "ALittleScriptOp6Element.h"
#include "ALittleScriptOp6StatElement.h"
#include "ALittleScriptOp6SuffixEeElement.h"
#include "ALittleScriptOp5StatElement.h"
#include "ALittleScriptOp5SuffixElement.h"
#include "ALittleScriptOp5SuffixEeElement.h"
#include "ALittleScriptOp5SuffixExElement.h"
#include "ALittleScriptOp4Element.h"
#include "ALittleScriptOp4SuffixElement.h"
#include "ALittleScriptOp4SuffixExElement.h"
#include "ALittleScriptOp3StatElement.h"
#include "ALittleScriptOp3SuffixElement.h"
#include "ALittleScriptOp3SuffixExElement.h"
#include "ALittleScriptOp2Element.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp2SuffixExElement.h"
#include "ALittleScriptOp1Element.h"

#include <unordered_map>
#include <functional>
#include <string>

class ALittleScriptFactory : public ABnfFactory
{
    std::unordered_map<std::string, std::function<std::shared_ptr<ABnfNodeElement>(ABnfFactory*, ABnfFile*, int, int, int, const std::string&)>> m_create_map;
public:
    ALittleScriptFactory()
    {
        m_create_map["ConstModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptConstModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["Op8SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp8SuffixEeElement>(factory, file, line, col, offset, type); };
        m_create_map["Root"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptRootElement>(factory, file, line, col, offset, type); };
        m_create_map["ElseIfCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptElseIfConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["Number"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptNumberElement>(factory, file, line, col, offset, type); };
        m_create_map["ProtocolModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptProtocolModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["LineComment"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptLineCommentElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodReturnTailDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodReturnTailDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Id"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptIdElement>(factory, file, line, col, offset, type); };
        m_create_map["BlockComment"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptBlockCommentElement>(factory, file, line, col, offset, type); };
        m_create_map["StructOptionDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructOptionDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Text"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTextElement>(factory, file, line, col, offset, type); };
        m_create_map["RegisterModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptRegisterModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["AccessModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptAccessModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodSetterParamDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodSetterParamDecElement>(factory, file, line, col, offset, type); };
        m_create_map["TemplateExtendsClassDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTemplateExtendsClassDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Op7SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp7SuffixEeElement>(factory, file, line, col, offset, type); };
        m_create_map["NamespaceElementDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptNamespaceElementDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Modifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["CoroutineModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptCoroutineModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodReturnDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodReturnDecElement>(factory, file, line, col, offset, type); };
        m_create_map["CommandBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptCommandBodyDecElement>(factory, file, line, col, offset, type); };
        m_create_map["TemplateExtendsStructDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTemplateExtendsStructDecElement>(factory, file, line, col, offset, type); };
        m_create_map["AllTypeConst"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptAllTypeConstElement>(factory, file, line, col, offset, type); };
        m_create_map["CommandModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptCommandModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["Op5"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp5Element>(factory, file, line, col, offset, type); };
        m_create_map["NullableModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptNullableModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodParamTailDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodParamTailDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ForInCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptForInConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["StructDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructDecElement>(factory, file, line, col, offset, type); };
        m_create_map["OpAssignExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOpAssignExprElement>(factory, file, line, col, offset, type); };
        m_create_map["NamespaceDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptNamespaceDecElement>(factory, file, line, col, offset, type); };
        m_create_map["LanguageNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptLanguageNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["StructNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptPropertyValueElement>(factory, file, line, col, offset, type); };
        m_create_map["NamespaceNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptNamespaceNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["LanguageBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptLanguageBodyDecElement>(factory, file, line, col, offset, type); };
        m_create_map["EnumVarNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptEnumVarNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["LanguageModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptLanguageModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["StructVarDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructVarDecElement>(factory, file, line, col, offset, type); };
        m_create_map["NativeModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptNativeModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["AttributeModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptAttributeModifierElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodParamOneDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodParamOneDecElement>(factory, file, line, col, offset, type); };
        m_create_map["TemplateDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTemplateDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Op4SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp4SuffixEeElement>(factory, file, line, col, offset, type); };
        m_create_map["TemplatePairDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTemplatePairDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Op6SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp6SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["TemplateNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTemplateNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["TemplateExtendsDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptTemplateExtendsDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassVarNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassVarNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassDecElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodBodyDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ForBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptForBodyElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassExtendsDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassExtendsDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ElseExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptElseExprElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassElementDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassElementDecElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodParamDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodParamDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Op6Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp6SuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueThisType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptPropertyValueThisTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassBodyDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassVarValueDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassVarValueDecElement>(factory, file, line, col, offset, type); };
        m_create_map["UsingNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptUsingNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassVarDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassVarDecElement>(factory, file, line, col, offset, type); };
        m_create_map["StructExtendsDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructExtendsDecElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueMethodCall"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptPropertyValueMethodCallElement>(factory, file, line, col, offset, type); };
        m_create_map["AllType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptAllTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["ReturnYield"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptReturnYieldElement>(factory, file, line, col, offset, type); };
        m_create_map["StructBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructBodyDecElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodGetterParamDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodGetterParamDecElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptGenericTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["StructVarNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructVarNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Op7Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp7SuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorParamType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptGenericFunctorParamTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["StructOptionNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptStructOptionNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["EnumDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptEnumDecElement>(factory, file, line, col, offset, type); };
        m_create_map["EnumNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptEnumNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["EnumBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptEnumBodyDecElement>(factory, file, line, col, offset, type); };
        m_create_map["EnumVarDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptEnumVarDecElement>(factory, file, line, col, offset, type); };
        m_create_map["InstanceDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptInstanceDecElement>(factory, file, line, col, offset, type); };
        m_create_map["UsingDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptUsingDecElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodParamNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodParamNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueDotId"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptPropertyValueDotIdElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["MethodReturnOneDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptMethodReturnOneDecElement>(factory, file, line, col, offset, type); };
        m_create_map["Op3"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOp3Element>(factory, file, line, col, offset, type); };
        m_create_map["ClassCtorDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassCtorDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassGetterDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassGetterDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassSetterDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassSetterDecElement>(factory, file, line, col, offset, type); };
        m_create_map["OpNewListStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptOpNewListStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassMethodDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return
	        std::make_shared<ALittleScriptClassMethodDecElement>(factory, file, line, col, offset, type); };
        m_create_map["ClassStaticDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptClassStaticDecElement>(factory, file, line, col, offset, type); };
        m_create_map["GlobalMethodDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGlobalMethodDecElement>(factory, file, line, col, offset, type); };
        m_create_map["AllExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptAllExprElement>(factory, file, line, col, offset, type); };
        m_create_map["EmptyExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptEmptyExprElement>(factory, file, line, col, offset, type); };
        m_create_map["ForExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForExprElement>(factory, file, line, col, offset, type); };
        m_create_map["ForCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["ForStepCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForStepConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["ForStartStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForStartStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ForEndStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForEndStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ForStepStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForStepStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ForPairDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptForPairDecElement>(factory, file, line, col, offset, type); };
        m_create_map["WhileExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptWhileExprElement>(factory, file, line, col, offset, type); };
        m_create_map["WhileCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptWhileConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["WhileBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptWhileBodyElement>(factory, file, line, col, offset, type); };
        m_create_map["Op2Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp2StatElement>(factory, file, line, col, offset, type); };
        m_create_map["DoWhileExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptDoWhileExprElement>(factory, file, line, col, offset, type); };
        m_create_map["DoWhileCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptDoWhileConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["DoWhileBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptDoWhileBodyElement>(factory, file, line, col, offset, type); };
        m_create_map["IfExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptIfExprElement>(factory, file, line, col, offset, type); };
        m_create_map["IfCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptIfConditionElement>(factory, file, line, col, offset, type); };
        m_create_map["IfBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptIfBodyElement>(factory, file, line, col, offset, type); };
        m_create_map["ElseBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptElseBodyElement>(factory, file, line, col, offset, type); };
        m_create_map["ElseIfExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptElseIfExprElement>(factory, file, line, col, offset, type); };
        m_create_map["ElseIfBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptElseIfBodyElement>(factory, file, line, col, offset, type); };
        m_create_map["WrapExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptWrapExprElement>(factory, file, line, col, offset, type); };
        m_create_map["ReturnExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptReturnExprElement>(factory, file, line, col, offset, type); };
        m_create_map["FlowExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptFlowExprElement>(factory, file, line, col, offset, type); };
        m_create_map["VarAssignExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptVarAssignExprElement>(factory, file, line, col, offset, type); };
        m_create_map["VarAssignDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptVarAssignDecElement>(factory, file, line, col, offset, type); };
        m_create_map["VarAssignNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptVarAssignNameDecElement>(factory, file, line, col, offset, type); };
        m_create_map["OpAssign"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOpAssignElement>(factory, file, line, col, offset, type); };
        m_create_map["Op1Expr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp1ExprElement>(factory, file, line, col, offset, type); };
        m_create_map["ThrowExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptThrowExprElement>(factory, file, line, col, offset, type); };
        m_create_map["AssertExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptAssertExprElement>(factory, file, line, col, offset, type); };
        m_create_map["CustomType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptCustomTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["CustomTypeName"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptCustomTypeNameElement>(factory, file, line, col, offset, type); };
        m_create_map["Op4Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp4StatElement>(factory, file, line, col, offset, type); };
        m_create_map["CustomTypeDotId"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptCustomTypeDotIdElement>(factory, file, line, col, offset, type); };
        m_create_map["CustomTypeDotIdName"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptCustomTypeDotIdNameElement>(factory, file, line, col, offset, type); };
        m_create_map["CustomTypeTemplate"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptCustomTypeTemplateElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericMapType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericMapTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["PrimitiveType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPrimitiveTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericListType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericListTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericFunctorTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorParamOneType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericFunctorParamOneTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorParamTail"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericFunctorParamTailElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorReturnTail"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericFunctorReturnTailElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorReturnOneType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericFunctorReturnOneTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["GenericFunctorReturnType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptGenericFunctorReturnTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["ValueStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptValueStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ValueFactorStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptValueFactorStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ValueOpStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptValueOpStatElement>(factory, file, line, col, offset, type); };
        m_create_map["OpNewStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOpNewStatElement>(factory, file, line, col, offset, type); };
        m_create_map["BindStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptBindStatElement>(factory, file, line, col, offset, type); };
        m_create_map["TcallStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptTcallStatElement>(factory, file, line, col, offset, type); };
        m_create_map["WrapValueStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptWrapValueStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ConstValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptConstValueElement>(factory, file, line, col, offset, type); };
        m_create_map["CoroutineStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptCoroutineStatElement>(factory, file, line, col, offset, type); };
        m_create_map["ReflectValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptReflectValueElement>(factory, file, line, col, offset, type); };
        m_create_map["ReflectCustomType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptReflectCustomTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["ReflectValueStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptReflectValueStatElement>(factory, file, line, col, offset, type); };
        m_create_map["PathsValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPathsValueElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueFirstType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueFirstTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueCastType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueCastTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueCustomType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueCustomTypeElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueSuffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueSuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueDotIdName"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueDotIdNameElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueBracketValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueBracketValueElement>(factory, file, line, col, offset, type); };
        m_create_map["PropertyValueMethodTemplate"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptPropertyValueMethodTemplateElement>(factory, file, line, col, offset, type); };
        m_create_map["Op8"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp8Element>(factory, file, line, col, offset, type); };
        m_create_map["Op8Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp8StatElement>(factory, file, line, col, offset, type); };
        m_create_map["Op8Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp8SuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["Op8SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp8SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["Op7"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp7Element>(factory, file, line, col, offset, type); };
        m_create_map["Op7Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp7StatElement>(factory, file, line, col, offset, type); };
        m_create_map["Op7SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp7SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["Op6"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp6Element>(factory, file, line, col, offset, type); };
        m_create_map["Op6Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp6StatElement>(factory, file, line, col, offset, type); };
        m_create_map["Op6SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp6SuffixEeElement>(factory, file, line, col, offset, type); };
        m_create_map["Op5Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp5StatElement>(factory, file, line, col, offset, type); };
        m_create_map["Op5Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp5SuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["Op5SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp5SuffixEeElement>(factory, file, line, col, offset, type); };
        m_create_map["Op5SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp5SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["Op4"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp4Element>(factory, file, line, col, offset, type); };
        m_create_map["Op4Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp4SuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["Op4SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp4SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["Op3Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp3StatElement>(factory, file, line, col, offset, type); };
        m_create_map["Op3Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp3SuffixElement>(factory, file, line, col, offset, type); };
        m_create_map["Op3SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp3SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["Op2"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp2Element>(factory, file, line, col, offset, type); };
        m_create_map["Op2Value"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp2ValueElement>(factory, file, line, col, offset, type); };
        m_create_map["Op2SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp2SuffixExElement>(factory, file, line, col, offset, type); };
        m_create_map["Op1"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<ALittleScriptOp1Element>(factory, file, line, col, offset, type); };

    }
    std::shared_ptr<ABnfNodeElement> CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override
    {
        const auto it = m_create_map.find(type);
        if (it == m_create_map.end()) return nullptr;
        return it->second(this, file, line, col, offset, type);
    }
    std::shared_ptr<ABnfKeyElement> CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override
    {
        return std::make_shared<ALittleScriptKeyElement>(this, file, line, col, offset, type);
    }
    std::shared_ptr<ABnfStringElement> CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override
    {
        return std::make_shared<ALittleScriptStringElement>(this, file, line, col, offset, type);
    }
    std::shared_ptr<ABnfRegexElement> CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, const std::shared_ptr<ARegex>& regex) override
    {
        return std::make_shared<ALittleScriptRegexElement>(this, file, line, col, offset, type, regex);
    }
};

#endif // _ALITTLE_ALittleScriptFactory_H_
