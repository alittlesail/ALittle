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
    m_create_map["AllExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptAllExprReference(element); };
    m_create_map["AllType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptAllTypeReference(element); };
    m_create_map["AssertExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptAssertExprReference(element); };
    m_create_map["BindStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptBindStatReference(element); };
    m_create_map["ClassCtorDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassCtorDecReference(element); };
    m_create_map["ClassGetterDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassGetterDecReference(element); };
    m_create_map["ClassSetterDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassSetterDecReference(element); };
    m_create_map["ClassMethodDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassMethodDecReference(element); };
    m_create_map["ClassStaticDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassStaticDecReference(element); };
    m_create_map["ClassDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassDecReference(element); };
    m_create_map["ClassExtendsDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassExtendsDecReference(element); };
    m_create_map["ClassElementDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassElementDecReference(element); };
    m_create_map["ClassNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassNameDecReference(element); };
    m_create_map["ClassVarDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassVarDecReference(element); };
    m_create_map["ClassVarNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptClassVarNameDecReference(element); };
    m_create_map["ConstValue"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptConstValueReference(element); };
    m_create_map["CoroutineStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptCoroutineStatReference(element); };
    m_create_map["CustomTypeDotIdName"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptCustomTypeDotIdNameReference(element); };
    m_create_map["CustomTypeDotId"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptCustomTypeDotIdReference(element); };
    m_create_map["CustomTypeName"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptCustomTypeNameReference(element); };
    m_create_map["CustomType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptCustomTypeReference(element); };
    m_create_map["EnumDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptEnumDecReference(element); };
    m_create_map["EnumNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptEnumNameDecReference(element); };
    m_create_map["EnumVarDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptEnumVarDecReference(element); };
    m_create_map["EnumVarNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptEnumVarNameDecReference(element); };
    m_create_map["FlowExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptFlowExprReference(element); };
    m_create_map["ForExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptForExprReference(element); };
    m_create_map["ForPairDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptForPairDecReference(element); };
    m_create_map["GenericType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptGenericTypeReference(element); };
    m_create_map["GlobalMethodDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptGlobalMethodDecReference(element); };
    m_create_map["Id"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptIdReference(element); };
    m_create_map["IfCondition"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptIfConditionReference(element); };
    m_create_map["ElseIfCondition"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptElseIfConditionReference(element); };
    m_create_map["WhileCondition"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptWhileConditionReference(element); };
    m_create_map["DoWhileCondition"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptDoWhileConditionReference(element); };
    m_create_map["Key"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptKeyReference(element); };
    m_create_map["LineComment"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptLineCommentReference(element); };
    m_create_map["MethodBodyDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodBodyDecReference(element); };
    m_create_map["MethodNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodNameDecReference(element); };
    m_create_map["MethodParamOneDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodParamOneDecReference(element); };
    m_create_map["MethodParamNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodParamNameDecReference(element); };
    m_create_map["MethodParamTailDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodParamTailDecReference(element); };
    m_create_map["MethodReturnDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodReturnDecReference(element); };
    m_create_map["MethodReturnTailDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptMethodReturnTailDecReference(element); };
    m_create_map["NamespaceDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptNamespaceDecReference(element); };
    m_create_map["NamespaceElementDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptNamespaceElementDecReference(element); };
    m_create_map["NamespaceNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptNamespaceNameDecReference(element); };
    m_create_map["Op1Expr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptOp1ExprReference(element); };
    m_create_map["OpAssignExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptOpAssignExprReference(element); };
    m_create_map["OpNewListStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptOpNewListStatReference(element); };
    m_create_map["OpNewStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptOpNewStatReference(element); };
    m_create_map["PathsValue"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPathsValueReference(element); };
    m_create_map["PrimitiveType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPrimitiveTypeReference(element); };
    m_create_map["PropertyValueBracketValue"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueBracketValueReference(element); };
    m_create_map["PropertyValueCastType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueCastTypeReference(element); };
    m_create_map["PropertyValueCustomType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueCustomTypeReference(element); };
    m_create_map["PropertyValueDotIdName"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueDotIdNameReference(element); };
    m_create_map["PropertyValueDotId"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueDotIdReference(element); };
    m_create_map["PropertyValueFirstType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueFirstTypeReference(element); };
    m_create_map["PropertyValueMethodCall"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueMethodCallReference(element); };
    m_create_map["PropertyValue"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueReference(element); };
    m_create_map["PropertyValueSuffix"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueSuffixReference(element); };
    m_create_map["PropertyValueThisType"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptPropertyValueThisTypeReference(element); };
    m_create_map["ReflectValue"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptReflectValueReference(element); };
    m_create_map["ReturnExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptReturnExprReference(element); };
    m_create_map["StructDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptStructDecReference(element); };
    m_create_map["StructNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptStructNameDecReference(element); };
    m_create_map["StructVarDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptStructVarDecReference(element); };
    m_create_map["StructOptionNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptStructOptionNameDecReference(element); };
    m_create_map["StructVarNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptStructVarNameDecReference(element); };
    m_create_map["TcallStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptTcallStatReference(element); };
    m_create_map["TemplateDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptTemplateDecReference(element); };
    m_create_map["TemplateNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptTemplateNameDecReference(element); };
    m_create_map["TemplatePairDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptTemplatePairDecReference(element); };
    m_create_map["ThrowExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptThrowExprReference(element); };
    m_create_map["UsingDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptUsingDecReference(element); };
    m_create_map["UsingNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptUsingNameDecReference(element); };
    m_create_map["ValueFactorStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptValueFactorStatReference(element); };
    m_create_map["ValueStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptValueStatReference(element); };
    m_create_map["VarAssignDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptVarAssignDecReference(element); };
    m_create_map["VarAssignExpr"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptVarAssignExprReference(element); };
    m_create_map["VarAssignNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptVarAssignNameDecReference(element); };
    m_create_map["WrapValueStat"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptWrapValueStatReference(element); };
    m_create_map["LanguageModifier"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptLanguageModifierReference(element); };
    m_create_map["LanguageNameDec"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptLanguageNameDecReference(element); };

    m_create_map["String"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptStringReference(element); };
    m_create_map["Regex"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptRegexReference(element); };
    m_create_map["Text"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptTextReference(element); };
    m_create_map["Number"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptNumberReference(element); };
    m_create_map["BlockComment"] = [](ABnfElementPtr element) -> ABnfReference* { return new ALittleScriptBlockCommentReference(element); };
}

ABnfReference* ALittleScriptFactoryClassEx::CreateReference(ABnfElementPtr element)
{
    auto it = m_create_map.find(element->GetNodeType());
    if (it == m_create_map.end()) return nullptr;

    return it->second(element);
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
