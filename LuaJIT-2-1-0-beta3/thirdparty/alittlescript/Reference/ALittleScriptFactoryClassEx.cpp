#include "ALittleScriptFactoryClassEx.h"

#include "ALittleScriptAllExprReference.h"
#include "ALittleScriptAllTypeReference.h"
#include "ALittleScriptAssertExprReference.h"
#include "ALittleScriptAssertExprReference.h"
#include "ALittleScriptBindStatReference.h"
#include "ALittleScriptClassCtorDecReference.h"
#include "ALittleScriptClassGetterDecReference.h"
#include "ALittleScriptClassSetterDecReference.h"
#include "ALittleScriptClassMethodDecReference.h"
#include "ALittleScriptClassStaticDecReference.h"
#include "ALittleScriptClassDecReference.h"
#include "ALittleScriptClassExtendsDecReference.h"
#include "ALittleScriptClassElementDecReference.h"
#include "ALittleScriptClassNameDecReference.h"
#include "ALittleScriptClassVarDecReference.h"
#include "ALittleScriptClassVarNameDecReference.h"
#include "ALittleScriptConstValueReference.h"
#include "ALittleScriptCoroutineStatReference.h"
#include "ALittleScriptCustomTypeDotIdNameReference.h"
#include "ALittleScriptCustomTypeDotIdReference.h"
#include "ALittleScriptCustomTypeNameReference.h"
#include "ALittleScriptCustomTypeReference.h"
#include "ALittleScriptEnumDecReference.h"
#include "ALittleScriptEnumNameDecReference.h"
#include "ALittleScriptEnumVarDecReference.h"
#include "ALittleScriptEnumVarNameDecReference.h"
#include "ALittleScriptFlowExprReference.h"
#include "ALittleScriptForExprReference.h"
#include "ALittleScriptForPairDecReference.h"
#include "ALittleScriptGenericTypeReference.h"
#include "ALittleScriptGlobalMethodDecReference.h"
#include "ALittleScriptIdReference.h"
#include "ALittleScriptIfConditionReference.h"
#include "ALittleScriptElseIfConditionReference.h"
#include "ALittleScriptWhileConditionReference.h"
#include "ALittleScriptDoWhileConditionReference.h"
#include "ALittleScriptKeyReference.h"
#include "ALittleScriptLineCommentReference.h"
#include "ALittleScriptMethodBodyDecReference.h"
#include "ALittleScriptMethodNameDecReference.h"
#include "ALittleScriptMethodParamOneDecReference.h"
#include "ALittleScriptMethodParamNameDecReference.h"
#include "ALittleScriptMethodParamTailDecReference.h"
#include "ALittleScriptMethodReturnDecReference.h"
#include "ALittleScriptMethodReturnTailDecReference.h"
#include "ALittleScriptNamespaceDecReference.h"
#include "ALittleScriptNamespaceElementDecReference.h"
#include "ALittleScriptNamespaceNameDecReference.h"
#include "ALittleScriptOp1ExprReference.h"
#include "ALittleScriptOpAssignExprReference.h"
#include "ALittleScriptOpNewListStatReference.h"
#include "ALittleScriptOpNewStatReference.h"
#include "ALittleScriptPathsValueReference.h"
#include "ALittleScriptPrimitiveTypeReference.h"
#include "ALittleScriptPropertyValueBracketValueReference.h"
#include "ALittleScriptPropertyValueCastTypeReference.h"
#include "ALittleScriptPropertyValueCustomTypeReference.h"
#include "ALittleScriptPropertyValueDotIdReference.h"
#include "ALittleScriptPropertyValueDotIdNameReference.h"
#include "ALittleScriptPropertyValueFirstTypeReference.h"
#include "ALittleScriptPropertyValueMethodCallReference.h"
#include "ALittleScriptPropertyValueReference.h"
#include "ALittleScriptPropertyValueSuffixReference.h"
#include "ALittleScriptPropertyValueThisTypeReference.h"
#include "ALittleScriptReflectValueReference.h"
#include "ALittleScriptReturnExprReference.h"
#include "ALittleScriptStructDecReference.h"
#include "ALittleScriptStructNameDecReference.h"
#include "ALittleScriptStructVarDecReference.h"
#include "ALittleScriptStructOptionNameDecReference.h"
#include "ALittleScriptTcallStatReference.h"
#include "ALittleScriptStructVarNameDecReference.h"
#include "ALittleScriptTemplateDecReference.h"
#include "ALittleScriptTemplateNameDecReference.h"
#include "ALittleScriptTemplatePairDecReference.h"
#include "ALittleScriptThrowExprReference.h"
#include "ALittleScriptUsingDecReference.h"
#include "ALittleScriptUsingNameDecReference.h"
#include "ALittleScriptValueFactorStatReference.h"
#include "ALittleScriptValueStatReference.h"
#include "ALittleScriptVarAssignDecReference.h"
#include "ALittleScriptVarAssignNameDecReference.h"
#include "ALittleScriptWrapValueStatReference.h"
#include "ALittleScriptLanguageModifierReference.h"
#include "ALittleScriptLanguageNameDecReference.h"
#include "ALittleScriptStringReference.h"
#include "ALittleScriptRegexReference.h"
#include "ALittleScriptTextReference.h"
#include "ALittleScriptNumberReference.h"
#include "ALittleScriptBlockCommentReference.h"
#include "ALittleScriptVarAssignExprReference.h"

#include "../Index/ALittleScriptProjectClass.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptIndex.h"

ALittleScriptFactoryClassEx::ALittleScriptFactoryClassEx()
{
    m_create_map["AllExpr"] = ALittleScriptAllExprReference::Create;
    m_create_map["AllType"] = ALittleScriptAllTypeReference::Create;
    m_create_map["AssertExpr"] = ALittleScriptAssertExprReference::Create;
    m_create_map["BindStat"] = ALittleScriptBindStatReference::Create;
    m_create_map["ClassCtorDec"] = ALittleScriptClassCtorDecReference::Create;
    m_create_map["ClassGetterDec"] = ALittleScriptClassGetterDecReference::Create;
    m_create_map["ClassSetterDec"] = ALittleScriptClassSetterDecReference::Create;
    m_create_map["ClassMethodDec"] = ALittleScriptClassMethodDecReference::Create;
    m_create_map["ClassStaticDec"] = ALittleScriptClassStaticDecReference::Create;
    m_create_map["ClassDec"] = ALittleScriptClassDecReference::Create;
    m_create_map["ClassExtendsDec"] = ALittleScriptClassExtendsDecReference::Create;
    m_create_map["ClassElementDec"] = ALittleScriptClassElementDecReference::Create;
    m_create_map["ClassNameDec"] = ALittleScriptClassNameDecReference::Create;
    m_create_map["ClassVarDec"] = ALittleScriptClassVarDecReference::Create;
    m_create_map["ClassVarNameDec"] = ALittleScriptClassVarNameDecReference::Create;
    m_create_map["ConstValue"] = ALittleScriptConstValueReference::Create;
    m_create_map["CoroutineStat"] = ALittleScriptCoroutineStatReference::Create;
    m_create_map["CustomTypeDotIdName"] = ALittleScriptCustomTypeDotIdNameReference::Create;
    m_create_map["CustomTypeDotId"] = ALittleScriptCustomTypeDotIdReference::Create;
    m_create_map["CustomTypeName"] = ALittleScriptCustomTypeNameReference::Create;
    m_create_map["CustomType"] = ALittleScriptCustomTypeReference::Create;
    m_create_map["EnumDec"] = ALittleScriptEnumDecReference::Create;
    m_create_map["EnumNameDec"] = ALittleScriptEnumNameDecReference::Create;
    m_create_map["EnumVarDec"] = ALittleScriptEnumVarDecReference::Create;
    m_create_map["EnumVarNameDec"] = ALittleScriptEnumVarNameDecReference::Create;
    m_create_map["FlowExpr"] = ALittleScriptFlowExprReference::Create;
    m_create_map["ForExpr"] = ALittleScriptForExprReference::Create;
    m_create_map["ForPairDec"] = ALittleScriptForPairDecReference::Create;
    m_create_map["GenericType"] = ALittleScriptGenericTypeReference::Create;
    m_create_map["GlobalMethodDec"] = ALittleScriptGlobalMethodDecReference::Create;
    m_create_map["Id"] = ALittleScriptIdReference::Create;
    m_create_map["IfCondition"] = ALittleScriptIfConditionReference::Create;
    m_create_map["ElseIfCondition"] = ALittleScriptElseIfConditionReference::Create;
    m_create_map["WhileCondition"] = ALittleScriptWhileConditionReference::Create;
    m_create_map["DoWhileCondition"] = ALittleScriptDoWhileConditionReference::Create;
    m_create_map["Key"] = ALittleScriptKeyReference::Create;
    m_create_map["LineComment"] = ALittleScriptLineCommentReference::Create;
    m_create_map["MethodBodyDec"] = ALittleScriptMethodBodyDecReference::Create;
    m_create_map["MethodNameDec"] = ALittleScriptMethodNameDecReference::Create;
    m_create_map["MethodParamOneDec"] = ALittleScriptMethodParamOneDecReference::Create;
    m_create_map["MethodParamNameDec"] = ALittleScriptMethodParamNameDecReference::Create;
    m_create_map["MethodParamTailDec"] = ALittleScriptMethodParamTailDecReference::Create;
    m_create_map["MethodReturnDec"] = ALittleScriptMethodReturnDecReference::Create;
    m_create_map["MethodReturnTailDec"] = ALittleScriptMethodReturnTailDecReference::Create;
    m_create_map["NamespaceDec"] = ALittleScriptNamespaceDecReference::Create;
    m_create_map["NamespaceElementDec"] = ALittleScriptNamespaceElementDecReference::Create;
    m_create_map["NamespaceNameDec"] = ALittleScriptNamespaceNameDecReference::Create;
    m_create_map["Op1Expr"] = ALittleScriptOp1ExprReference::Create;
    m_create_map["OpAssignExpr"] = ALittleScriptOpAssignExprReference::Create;
    m_create_map["OpNewListStat"] = ALittleScriptOpNewListStatReference::Create;
    m_create_map["OpNewStat"] = ALittleScriptOpNewStatReference::Create;
    m_create_map["PathsValue"] = ALittleScriptPathsValueReference::Create;
    m_create_map["PrimitiveType"] = ALittleScriptPrimitiveTypeReference::Create;
    m_create_map["PropertyValueBracketValue"] = ALittleScriptPropertyValueBracketValueReference::Create;
    m_create_map["PropertyValueCastType"] = ALittleScriptPropertyValueCastTypeReference::Create;
    m_create_map["PropertyValueCustomType"] = ALittleScriptPropertyValueCustomTypeReference::Create;
    m_create_map["PropertyValueDotIdName"] = ALittleScriptPropertyValueDotIdNameReference::Create;
    m_create_map["PropertyValueDotId"] = ALittleScriptPropertyValueDotIdReference::Create;
    m_create_map["PropertyValueFirstType"] = ALittleScriptPropertyValueFirstTypeReference::Create;
    m_create_map["PropertyValueMethodCall"] = ALittleScriptPropertyValueMethodCallReference::Create;
    m_create_map["PropertyValue"] = ALittleScriptPropertyValueReference::Create;
    m_create_map["PropertyValueSuffix"] = ALittleScriptPropertyValueSuffixReference::Create;
    m_create_map["PropertyValueThisType"] = ALittleScriptPropertyValueThisTypeReference::Create;
    m_create_map["ReflectValue"] = ALittleScriptReflectValueReference::Create;
    m_create_map["ReturnExpr"] = ALittleScriptReturnExprReference::Create;
    m_create_map["StructDec"] = ALittleScriptStructDecReference::Create;
    m_create_map["StructNameDec"] = ALittleScriptStructNameDecReference::Create;
    m_create_map["StructVarDec"] = ALittleScriptStructVarDecReference::Create;
    m_create_map["StructOptionNameDec"] = ALittleScriptStructOptionNameDecReference::Create;
    m_create_map["StructVarNameDec"] = ALittleScriptStructVarNameDecReference::Create;
    m_create_map["TcallStat"] = ALittleScriptTcallStatReference::Create;
    m_create_map["TemplateDec"] = ALittleScriptTemplateDecReference::Create;
    m_create_map["TemplateNameDec"] = ALittleScriptTemplateNameDecReference::Create;
    m_create_map["TemplatePairDec"] = ALittleScriptTemplatePairDecReference::Create;
    m_create_map["ThrowExpr"] = ALittleScriptThrowExprReference::Create;
    m_create_map["UsingDec"] = ALittleScriptUsingDecReference::Create;
    m_create_map["UsingNameDec"] = ALittleScriptUsingNameDecReference::Create;
    m_create_map["ValueFactorStat"] = ALittleScriptValueFactorStatReference::Create;
    m_create_map["ValueStat"] = ALittleScriptValueStatReference::Create;
    m_create_map["VarAssignDec"] = ALittleScriptVarAssignDecReference::Create;
    m_create_map["VarAssignExpr"] = ALittleScriptVarAssignExprReference::Create;
    m_create_map["VarAssignNameDec"] = ALittleScriptVarAssignNameDecReference::Create;
    m_create_map["WrapValueStat"] = ALittleScriptWrapValueStatReference::Create;
    m_create_map["LanguageModifier"] = ALittleScriptLanguageModifierReference::Create;
    m_create_map["LanguageNameDec"] = ALittleScriptLanguageNameDecReference::Create;

    m_create_map["String"] = ALittleScriptStringReference::Create;
    m_create_map["Regex"] = ALittleScriptRegexReference::Create;
    m_create_map["Text"] = ALittleScriptTextReference::Create;
    m_create_map["Number"] = ALittleScriptNumberReference::Create;
    m_create_map["BlockComment"] = ALittleScriptBlockCommentReference::Create;
}

ABnfReference* ALittleScriptFactoryClassEx::CreateReference(ABnfElementPtr element)
{
    auto it = m_create_map.find(element->GetNodeType());
    if (it != m_create_map.end()) return it->second(element);

    it = m_create_map.find(element->GetLeafType());
    if (it != m_create_map.end()) return it->second(element);

    return nullptr;
}

ABnfGuessError ALittleScriptFactoryClassEx::GuessTypes(ABnfElementPtr element, std::vector<ABnfGuessPtr>& guess_list)
{
    guess_list.resize(0);

    auto* index = dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject());
    if (index == nullptr) return ABnfGuessError(element, u8"不在工程内");

    auto error = index->GetGuessError(element);
    if (error) return error;

    const auto* result = index->GetGuessTypeList(element);
    if (result != nullptr) guess_list = *result;
    if (guess_list.size() > 0)
    {
        bool is_changed = false;
        for (auto& guess : guess_list)
        {
            if (guess->IsChanged())
            {
                is_changed = true;
                break;
            }
        }
        if (!is_changed) return nullptr;
    }

    auto reference = element->GetReference();
    if (reference == nullptr)
    {
        error = ABnfGuessError(element, u8"ALittleReference对象创建失败 element:" + element->GetNodeType());
        index->AddGuessError(element, error);
        return error;
    }

    error = reference->GuessTypes(guess_list);
    if (error)
    {
        index->AddGuessError(element, error);
        return error;
    }

    // 如果是两个，并且一个是register，一个不是。那么就要把register那个删掉
    if (!reference->MultiGuessTypes()
        && guess_list.size() == 2
        && guess_list[0]->GetValue() == guess_list[1]->GetValue()
        && std::dynamic_pointer_cast<ALittleScriptGuess>(guess_list[0])
        && std::dynamic_pointer_cast<ALittleScriptGuess>(guess_list[1]))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuess>(guess_list[0])->is_register && !std::dynamic_pointer_cast<ALittleScriptGuess>(guess_list[1])->is_register)
            guess_list.erase(guess_list.begin());
        else if (!std::dynamic_pointer_cast<ALittleScriptGuess>(guess_list[0])->is_register && std::dynamic_pointer_cast<ALittleScriptGuess>(guess_list[1])->is_register)
            guess_list.pop_back();
    }

    for (auto& guess : guess_list)
    {
        if (guess == nullptr)
        {
            error = ABnfGuessError(element, u8"guess列表出现null:" + element->GetNodeType());
            index->AddGuessError(element, error);
            return error;
        }
    }

    index->AddGuessTypeList(element, guess_list);
    return nullptr;
}