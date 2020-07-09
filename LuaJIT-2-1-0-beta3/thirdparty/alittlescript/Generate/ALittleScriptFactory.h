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
        m_create_map["ConstModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptConstModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["Op8SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp8SuffixEeElement(factory, file, line, col, offset, type)); };
        m_create_map["Root"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptRootElement(factory, file, line, col, offset, type)); };
        m_create_map["ElseIfCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptElseIfConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["Number"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptNumberElement(factory, file, line, col, offset, type)); };
        m_create_map["ProtocolModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptProtocolModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["LineComment"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptLineCommentElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodReturnTailDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodReturnTailDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Id"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptIdElement(factory, file, line, col, offset, type)); };
        m_create_map["BlockComment"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptBlockCommentElement(factory, file, line, col, offset, type)); };
        m_create_map["StructOptionDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructOptionDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Text"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTextElement(factory, file, line, col, offset, type)); };
        m_create_map["RegisterModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptRegisterModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["AccessModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptAccessModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodSetterParamDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodSetterParamDecElement(factory, file, line, col, offset, type)); };
        m_create_map["TemplateExtendsClassDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTemplateExtendsClassDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Op7SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp7SuffixEeElement(factory, file, line, col, offset, type)); };
        m_create_map["NamespaceElementDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptNamespaceElementDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Modifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["CoroutineModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCoroutineModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodReturnDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodReturnDecElement(factory, file, line, col, offset, type)); };
        m_create_map["CommandBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCommandBodyDecElement(factory, file, line, col, offset, type)); };
        m_create_map["TemplateExtendsStructDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTemplateExtendsStructDecElement(factory, file, line, col, offset, type)); };
        m_create_map["AllTypeConst"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptAllTypeConstElement(factory, file, line, col, offset, type)); };
        m_create_map["CommandModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCommandModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["Op5"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp5Element(factory, file, line, col, offset, type)); };
        m_create_map["NullableModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptNullableModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodParamTailDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodParamTailDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ForInCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForInConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["StructDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructDecElement(factory, file, line, col, offset, type)); };
        m_create_map["OpAssignExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOpAssignExprElement(factory, file, line, col, offset, type)); };
        m_create_map["NamespaceDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptNamespaceDecElement(factory, file, line, col, offset, type)); };
        m_create_map["LanguageNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptLanguageNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["StructNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueElement(factory, file, line, col, offset, type)); };
        m_create_map["NamespaceNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptNamespaceNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["LanguageBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptLanguageBodyDecElement(factory, file, line, col, offset, type)); };
        m_create_map["EnumVarNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptEnumVarNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["LanguageModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptLanguageModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["StructVarDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructVarDecElement(factory, file, line, col, offset, type)); };
        m_create_map["NativeModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptNativeModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["AttributeModifier"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptAttributeModifierElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodParamOneDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodParamOneDecElement(factory, file, line, col, offset, type)); };
        m_create_map["TemplateDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTemplateDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Op4SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp4SuffixEeElement(factory, file, line, col, offset, type)); };
        m_create_map["TemplatePairDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTemplatePairDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Op6SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp6SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["TemplateNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTemplateNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["TemplateExtendsDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTemplateExtendsDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassVarNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassVarNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassDecElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodBodyDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ForBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForBodyElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassExtendsDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassExtendsDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ElseExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptElseExprElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassElementDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassElementDecElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodParamDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodParamDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Op6Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp6SuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueThisType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueThisTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassBodyDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassVarValueDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassVarValueDecElement(factory, file, line, col, offset, type)); };
        m_create_map["UsingNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptUsingNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassVarDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassVarDecElement(factory, file, line, col, offset, type)); };
        m_create_map["StructExtendsDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructExtendsDecElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueMethodCall"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueMethodCallElement(factory, file, line, col, offset, type)); };
        m_create_map["AllType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptAllTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["ReturnYield"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptReturnYieldElement(factory, file, line, col, offset, type)); };
        m_create_map["StructBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructBodyDecElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodGetterParamDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodGetterParamDecElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["StructVarNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructVarNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Op7Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp7SuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorParamType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorParamTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["StructOptionNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptStructOptionNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["EnumDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptEnumDecElement(factory, file, line, col, offset, type)); };
        m_create_map["EnumNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptEnumNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["EnumBodyDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptEnumBodyDecElement(factory, file, line, col, offset, type)); };
        m_create_map["EnumVarDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptEnumVarDecElement(factory, file, line, col, offset, type)); };
        m_create_map["InstanceDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptInstanceDecElement(factory, file, line, col, offset, type)); };
        m_create_map["UsingDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptUsingDecElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodParamNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodParamNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueDotId"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueDotIdElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["MethodReturnOneDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptMethodReturnOneDecElement(factory, file, line, col, offset, type)); };
        m_create_map["Op3"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp3Element(factory, file, line, col, offset, type)); };
        m_create_map["ClassCtorDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassCtorDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassGetterDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassGetterDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassSetterDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassSetterDecElement(factory, file, line, col, offset, type)); };
        m_create_map["OpNewListStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOpNewListStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassMethodDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassMethodDecElement(factory, file, line, col, offset, type)); };
        m_create_map["ClassStaticDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptClassStaticDecElement(factory, file, line, col, offset, type)); };
        m_create_map["GlobalMethodDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGlobalMethodDecElement(factory, file, line, col, offset, type)); };
        m_create_map["AllExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptAllExprElement(factory, file, line, col, offset, type)); };
        m_create_map["EmptyExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptEmptyExprElement(factory, file, line, col, offset, type)); };
        m_create_map["ForExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForExprElement(factory, file, line, col, offset, type)); };
        m_create_map["ForCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["ForStepCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForStepConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["ForStartStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForStartStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ForEndStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForEndStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ForStepStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForStepStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ForPairDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptForPairDecElement(factory, file, line, col, offset, type)); };
        m_create_map["WhileExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptWhileExprElement(factory, file, line, col, offset, type)); };
        m_create_map["WhileCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptWhileConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["WhileBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptWhileBodyElement(factory, file, line, col, offset, type)); };
        m_create_map["Op2Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp2StatElement(factory, file, line, col, offset, type)); };
        m_create_map["DoWhileExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptDoWhileExprElement(factory, file, line, col, offset, type)); };
        m_create_map["DoWhileCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptDoWhileConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["DoWhileBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptDoWhileBodyElement(factory, file, line, col, offset, type)); };
        m_create_map["IfExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptIfExprElement(factory, file, line, col, offset, type)); };
        m_create_map["IfCondition"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptIfConditionElement(factory, file, line, col, offset, type)); };
        m_create_map["IfBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptIfBodyElement(factory, file, line, col, offset, type)); };
        m_create_map["ElseBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptElseBodyElement(factory, file, line, col, offset, type)); };
        m_create_map["ElseIfExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptElseIfExprElement(factory, file, line, col, offset, type)); };
        m_create_map["ElseIfBody"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptElseIfBodyElement(factory, file, line, col, offset, type)); };
        m_create_map["WrapExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptWrapExprElement(factory, file, line, col, offset, type)); };
        m_create_map["ReturnExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptReturnExprElement(factory, file, line, col, offset, type)); };
        m_create_map["FlowExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptFlowExprElement(factory, file, line, col, offset, type)); };
        m_create_map["VarAssignExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptVarAssignExprElement(factory, file, line, col, offset, type)); };
        m_create_map["VarAssignDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptVarAssignDecElement(factory, file, line, col, offset, type)); };
        m_create_map["VarAssignNameDec"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptVarAssignNameDecElement(factory, file, line, col, offset, type)); };
        m_create_map["OpAssign"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOpAssignElement(factory, file, line, col, offset, type)); };
        m_create_map["Op1Expr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp1ExprElement(factory, file, line, col, offset, type)); };
        m_create_map["ThrowExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptThrowExprElement(factory, file, line, col, offset, type)); };
        m_create_map["AssertExpr"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptAssertExprElement(factory, file, line, col, offset, type)); };
        m_create_map["CustomType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCustomTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["CustomTypeName"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCustomTypeNameElement(factory, file, line, col, offset, type)); };
        m_create_map["Op4Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp4StatElement(factory, file, line, col, offset, type)); };
        m_create_map["CustomTypeDotId"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCustomTypeDotIdElement(factory, file, line, col, offset, type)); };
        m_create_map["CustomTypeDotIdName"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCustomTypeDotIdNameElement(factory, file, line, col, offset, type)); };
        m_create_map["CustomTypeTemplate"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCustomTypeTemplateElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericMapType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericMapTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["PrimitiveType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPrimitiveTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericListType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericListTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorParamOneType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorParamOneTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorParamTail"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorParamTailElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorReturnTail"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorReturnTailElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorReturnOneType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorReturnOneTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["GenericFunctorReturnType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptGenericFunctorReturnTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["ValueStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptValueStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ValueFactorStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptValueFactorStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ValueOpStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptValueOpStatElement(factory, file, line, col, offset, type)); };
        m_create_map["OpNewStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOpNewStatElement(factory, file, line, col, offset, type)); };
        m_create_map["BindStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptBindStatElement(factory, file, line, col, offset, type)); };
        m_create_map["TcallStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptTcallStatElement(factory, file, line, col, offset, type)); };
        m_create_map["WrapValueStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptWrapValueStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ConstValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptConstValueElement(factory, file, line, col, offset, type)); };
        m_create_map["CoroutineStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptCoroutineStatElement(factory, file, line, col, offset, type)); };
        m_create_map["ReflectValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptReflectValueElement(factory, file, line, col, offset, type)); };
        m_create_map["ReflectCustomType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptReflectCustomTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["ReflectValueStat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptReflectValueStatElement(factory, file, line, col, offset, type)); };
        m_create_map["PathsValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPathsValueElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueFirstType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueFirstTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueCastType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueCastTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueCustomType"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueCustomTypeElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueSuffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueSuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueDotIdName"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueDotIdNameElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueBracketValue"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueBracketValueElement(factory, file, line, col, offset, type)); };
        m_create_map["PropertyValueMethodTemplate"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptPropertyValueMethodTemplateElement(factory, file, line, col, offset, type)); };
        m_create_map["Op8"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp8Element(factory, file, line, col, offset, type)); };
        m_create_map["Op8Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp8StatElement(factory, file, line, col, offset, type)); };
        m_create_map["Op8Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp8SuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["Op8SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp8SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["Op7"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp7Element(factory, file, line, col, offset, type)); };
        m_create_map["Op7Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp7StatElement(factory, file, line, col, offset, type)); };
        m_create_map["Op7SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp7SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["Op6"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp6Element(factory, file, line, col, offset, type)); };
        m_create_map["Op6Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp6StatElement(factory, file, line, col, offset, type)); };
        m_create_map["Op6SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp6SuffixEeElement(factory, file, line, col, offset, type)); };
        m_create_map["Op5Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp5StatElement(factory, file, line, col, offset, type)); };
        m_create_map["Op5Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp5SuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["Op5SuffixEe"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp5SuffixEeElement(factory, file, line, col, offset, type)); };
        m_create_map["Op5SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp5SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["Op4"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp4Element(factory, file, line, col, offset, type)); };
        m_create_map["Op4Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp4SuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["Op4SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp4SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["Op3Stat"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp3StatElement(factory, file, line, col, offset, type)); };
        m_create_map["Op3Suffix"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp3SuffixElement(factory, file, line, col, offset, type)); };
        m_create_map["Op3SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp3SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["Op2"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp2Element(factory, file, line, col, offset, type)); };
        m_create_map["Op2Value"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp2ValueElement(factory, file, line, col, offset, type)); };
        m_create_map["Op2SuffixEx"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp2SuffixExElement(factory, file, line, col, offset, type)); };
        m_create_map["Op1"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::shared_ptr<ABnfNodeElement>(new ALittleScriptOp1Element(factory, file, line, col, offset, type)); };

    }
    std::shared_ptr<ABnfNodeElement> CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override
    {
        auto it = m_create_map.find(type);
        if (it == m_create_map.end()) return nullptr;
        return it->second(this, file, line, col, offset, type);
    }
    std::shared_ptr<ABnfKeyElement> CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override
    {
        return std::shared_ptr<ABnfKeyElement>(new ALittleScriptKeyElement(this, file, line, col, offset, type));
    }
    std::shared_ptr<ABnfStringElement> CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override
    {
        return std::shared_ptr<ABnfStringElement>(new ALittleScriptStringElement(this, file, line, col, offset, type));
    }
    std::shared_ptr<ABnfRegexElement> CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, std::shared_ptr<ARegex> regex) override
    {
        return std::shared_ptr<ABnfRegexElement>(new ALittleScriptRegexElement(this, file, line, col, offset, type, regex));
    }
};

#endif // _ALITTLE_ALittleScriptFactory_H_
