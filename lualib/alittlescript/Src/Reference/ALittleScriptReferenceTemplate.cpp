
#include "ALittleScriptReferenceTemplate.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "alanguage/Src/Model/ABnfElement.h"
#include "alanguage/Src/Model/ABnfGuess.h"
#include "alanguage/Src/Model/ABnfStringElement.h"
#include "alanguage/Src/Model/ALanguageHelperInfo.h"
#include "alanguage/Src/Index/ABnfFile.h"
#include "alanguage/Src/Index/ABnfProject.h"

#include "../Generate/ALittleScriptClassBodyDecElement.h"
#include "../Generate/ALittleScriptStructBodyDecElement.h"
#include "../Generate/ALittleScriptEnumBodyDecElement.h"
#include "../Generate/ALittleScriptMethodBodyDecElement.h"
#include "../Generate/ALittleScriptForBodyElement.h"
#include "../Generate/ALittleScriptWhileBodyElement.h"
#include "../Generate/ALittleScriptDoWhileBodyElement.h"
#include "../Generate/ALittleScriptIfBodyElement.h"
#include "../Generate/ALittleScriptElseIfBodyElement.h"
#include "../Generate/ALittleScriptElseBodyElement.h"
#include "../Generate/ALittleScriptWrapExprElement.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptOpNewListStatElement.h"
#include "../Generate/ALittleScriptLineCommentElement.h"
#include "../Generate/ALittleScriptBlockCommentElement.h"
#include "../Generate/ALittleScriptWhileExprElement.h"
#include "../Generate/ALittleScriptIfExprElement.h"
#include "../Generate/ALittleScriptAllExprElement.h"
#include "../Generate/ALittleScriptForExprElement.h"
#include "../Generate/ALittleScriptElseIfExprElement.h"
#include "../Generate/ALittleScriptElseExprElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"
#include "../Generate/ALittleScriptStructOptionDecElement.h"
#include "../Generate/ALittleScriptOp8Element.h"
#include "../Generate/ALittleScriptOp7Element.h"
#include "../Generate/ALittleScriptOp6Element.h"
#include "../Generate/ALittleScriptOp5Element.h"
#include "../Generate/ALittleScriptOp4Element.h"
#include "../Generate/ALittleScriptOp3Element.h"
#include "../Generate/ALittleScriptOp2Element.h"
#include "../Generate/ALittleScriptOp1Element.h"
#include "../Generate/ALittleScriptPropertyValueMethodCallElement.h"
#include "../Generate/ALittleScriptBindStatElement.h"
#include "../Generate/ALittleScriptTcallStatElement.h"
#include "../Generate/ALittleScriptOpNewStatElement.h"
#include "../Generate/ALittleScriptStringElement.h"
#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptMethodParamTailDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"

#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessClass.h"

#include "ALittleScriptPropertyValueMethodCallReference.h"

ALittleScriptReference::ALittleScriptReference(const ABnfElementPtr& p_element)
{
	m_ref_element = p_element;
}

// 鼠标移入时，显示的快捷信息
void ALittleScriptReference::QueryQuickInfo(std::string& info)
{
    auto element = m_ref_element.lock();
    if (element == nullptr) return;

    ABnfGuessPtr guess;
    const auto error = element->GuessType(guess);
    if (error) return;
    info = guess->GetValue();
}

int ALittleScriptReference::QueryDesiredIndent(int it_line, int it_char, const ABnfElementPtr& select)
{
    const auto element = m_ref_element.lock();
    if (element == nullptr) return 0;

    auto parent = element->GetParent();
    if (parent == nullptr)
    {
        if (m_desire_indent >= 0) return m_desire_indent;
        m_desire_indent = 0;
        return m_desire_indent;
    }

    if (std::dynamic_pointer_cast<ALittleScriptClassBodyDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptStructBodyDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptEnumBodyDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptForBodyElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptWhileBodyElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptDoWhileBodyElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptIfBodyElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptElseIfBodyElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptElseBodyElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(element))
    {
        if (m_desire_indent < 0)
            m_desire_indent = parent->GetReference()->QueryDesiredIndent(it_line, it_char, nullptr);
        if (std::dynamic_pointer_cast<ABnfStringElement>(select)
            && (select->GetElementText() == "{" || select->GetElementText() == "}"))
            return m_desire_indent;
        return m_desire_indent + s_indent_size;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptOpNewListStatElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptBindStatElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(element))
    {
        if (m_desire_indent >= 0) return m_desire_indent;

        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        const auto& childs = node->GetChilds();
        if (!childs.empty())
        {
            m_desire_indent = childs[0]->GetStartIndent();
            return m_desire_indent;
        }
    }
    else if (std::dynamic_pointer_cast<ALittleScriptOp8Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp7Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp6Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp5Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp4Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp3Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp2Element>(element))
    {
        if (m_desire_indent >= 0) return m_desire_indent;
        m_desire_indent = parent->GetReference()->QueryDesiredIndent(it_line, it_char, nullptr) + s_indent_size;
        return m_desire_indent;
    }

    if (m_desire_indent >= 0) return m_desire_indent;
    m_desire_indent = parent->GetReference()->QueryDesiredIndent(it_line, it_char, nullptr);
    return m_desire_indent;
}

int ALittleScriptReference::QueryFormatIndent(int it_line, int it_char, const ABnfElementPtr& select)
{
    if (m_format_indent >= 0) return m_format_indent;

    const auto element = m_ref_element.lock();
    if (element == nullptr) return 0;

    auto parent = element->GetParent();
    if (parent == nullptr)
    {
        m_format_indent = 0;
        return m_format_indent;
    }

    if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptLineCommentElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptBlockCommentElement>(element))
    {
        m_format_indent = parent->GetReference()->QueryFormatIndent(it_line, it_char, nullptr);
        if (std::dynamic_pointer_cast<ALittleScriptForExprElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptIfExprElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptElseIfExprElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptElseExprElement>(parent)

            || std::dynamic_pointer_cast<ALittleScriptClassBodyDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptEnumBodyDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptStructBodyDecElement>(parent)

            || std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptForBodyElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptWhileBodyElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptDoWhileBodyElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptIfBodyElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptElseIfBodyElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptElseBodyElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(parent))
            m_format_indent += s_indent_size;
        return m_format_indent;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptEnumVarDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptStructVarDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptStructOptionDecElement>(element))
    {
        m_format_indent = parent->GetReference()->QueryFormatIndent(it_line, it_char, nullptr) + s_indent_size;
        return m_format_indent;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptOpNewListStatElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptBindStatElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptTcallStatElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(element))
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        const auto& childs = node->GetChilds();
        if (!childs.empty())
        {
            m_format_indent = childs[0]->GetStartIndent();
            return m_format_indent;
        }
    }
    else if (std::dynamic_pointer_cast<ALittleScriptOp8Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp7Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp6Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp5Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp4Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp3Element>(element)
        || std::dynamic_pointer_cast<ALittleScriptOp2Element>(element))
    {
        m_format_indent = parent->GetReference()->QueryFormatIndent(it_line, it_char, nullptr) + s_indent_size;
        return m_format_indent;
    }

    m_format_indent = parent->GetReference()->QueryFormatIndent(it_line, it_char, nullptr);
    return m_format_indent;
}

int ALittleScriptReference::QueryParamIndex(int it_line, int it_char, const ABnfElementPtr& select, int& start_offset)
{
    ABnfElementPtr parent = m_ref_element.lock();
    if (parent == nullptr) return -1;

    while (parent != nullptr)
    {
        const std::vector<std::shared_ptr<ALittleScriptStringElement>>* symbol_list = nullptr;
        if (std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(parent))
        {
            auto stat = std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(parent);
            symbol_list = &stat->GetStringList();
        }
        else if (std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(parent))
        {
            auto stat = std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(parent);
            symbol_list = &stat->GetStringList();
        }

        if (symbol_list != nullptr)
        {
            if (symbol_list->empty()) return -1;

            int start = 0;
            for (int i = static_cast<int>(symbol_list->size()) - 1; i >= 0; --i)
            {
                if ((*symbol_list)[i]->GetElementText() == "(")
                {
                    start_offset = (*symbol_list)[i]->GetStart();
                    start = i;
                    break;
                }
            }
            int index = 0;
            for (size_t i = start; i < symbol_list->size(); ++i)
            {
                const auto& symbol = (*symbol_list)[i];
                if (symbol->GetElementText() == "(") continue;

                if (it_line < symbol->GetEndLine()) return index;
                if (it_char < symbol->GetEndCol()) return index;

                ++index;
            }

            return index;
        }

        if (std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(parent)) return -1;
        if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent)) return -1;

        parent = parent->GetParent();
    }

    return false;
}

bool ALittleScriptReference::QueryKeyWord(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    auto& abnf = select->GetFile()->GetProject()->RefABnf();

    for (const auto& key : abnf.GetKeySet())
        list.emplace_back(key, 0, "");
    return false;
}

bool ALittleScriptReference::QueryParamList(int& line_start, int& char_start, int& line_end, int& char_end, std::vector<ALanguageParameterInfo>& param_list)
{
    ABnfElementPtr parent = m_ref_element.lock();
    if (parent == nullptr) return false;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(parent))
        {
	        auto* refer = dynamic_cast<ALittleScriptPropertyValueMethodCallReference*>(parent->GetReference());
            if (refer == nullptr) return false;

            ABnfGuessPtr guess;
            auto error = refer->GuessPreType(guess);
            if (error) return false;

            auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
            if (guess_functor == nullptr) return false;

            for (size_t i = 0; i < guess_functor->param_name_list.size(); ++i)
            {
                std::string type;
                if (i < guess_functor->param_nullable_list.size() && guess_functor->param_nullable_list[i])
                    type = "[Nullable] ";
                if (i < guess_functor->param_list.size())
                {
                    auto guess_e = guess_functor->param_list[i].lock();
                    if (guess_e) type += guess_e->GetValue();
                }
                
                ALanguageParameterInfo param;
                param.name = type + " " + guess_functor->param_name_list[i];

                param_list.push_back(param);
            }
            if (guess_functor->param_tail.lock() != nullptr)
            {
                ALanguageParameterInfo param;
                param.name = guess_functor->param_tail.lock()->GetValue();
                param_list.push_back(param);
            }

            line_start = parent->GetStartLine();
            char_start = parent->GetStartCol();
            line_end = parent->GetEndLine();
            char_end = parent->GetEndCol();

            auto method_call = std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(parent);
            if (method_call == nullptr) return false;
            const auto& string_list = method_call->GetStringList();
            if (string_list.size() > 1)
            {
                line_start = string_list[0]->GetStartLine();
                char_start = string_list[0]->GetStartCol();
                line_end = parent->GetEndLine();
                char_end = parent->GetEndCol();
            }
            return true;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(parent))
        {
            auto custom_type = std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(parent)->GetCustomType();
            if (custom_type == nullptr) return false;

            ABnfGuessPtr guess;
            auto error = custom_type->GuessType(guess);
            if (error) return false;

            if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
            {
                auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
                if (guess_template->template_extends.lock() != nullptr)
                    guess = guess_template->template_extends.lock();
            }

            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
            {
                auto class_dec = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess)->class_dec.lock();
                if (class_dec == nullptr) return false;
                auto ctor = ALittleScriptUtility::FindFirstCtorDecFromExtends(class_dec, 100);
                if (ctor == nullptr) return false;

                auto param_dec = ctor->GetMethodParamDec();
                if (param_dec == nullptr) return false;

                const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
                if (param_one_dec_list.empty()) return false;

                for (size_t i = 0; i < param_one_dec_list.size(); ++i)
                {
                    auto param_one_dec = param_one_dec_list[i];
                    auto tail_dec = param_one_dec->GetMethodParamTailDec();
                    if (tail_dec != nullptr)
                    {
                        ALanguageParameterInfo param_info;
                        param_info.name = tail_dec->GetElementText();
                        param_list.push_back(param_info);
                        continue;
                    }

                    auto nullable = ALittleScriptUtility::IsNullable(param_one_dec->GetModifierList());

                    auto all_type = param_one_dec->GetAllType();
                    if (all_type == nullptr) return false;

                    ABnfGuessPtr all_type_guess;
                    error = all_type->GuessType(all_type_guess);
                    if (error) return false;

                    ALanguageParameterInfo param;
                    param.name = all_type_guess->GetValue();
                    if (param_one_dec->GetMethodParamNameDec() != nullptr)
                    {
                        if (nullable) param.name += " [Nullable]";
                        param.name += " " + param_one_dec->GetMethodParamNameDec()->GetElementText();
                    }

                    param_list.push_back(param);
                }

                line_start = parent->GetStartLine();
                char_start = parent->GetStartCol();
                line_end = parent->GetEndLine();
                char_end = parent->GetEndCol();

                auto new_stat = std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(parent);
                const auto& string_list = new_stat->GetStringList();
                if (string_list.size() > 1)
                {
                    line_start = string_list[0]->GetStartLine();
                    char_start = string_list[0]->GetStartCol();
                    line_end = parent->GetEndLine();
                    char_end = parent->GetEndCol();
                }
                return true;
            }
            return false;
        }

        if (std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(parent)) return false;
        if (std::dynamic_pointer_cast<ALittleScriptAllExprElement>(parent)) return false;

        parent = parent->GetParent();
    }

    return false;
}

ALittleScriptIndex* ALittleScriptReference::GetIndex() const
{
    const auto element = m_ref_element.lock();
    if (element == nullptr) return nullptr;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject());
}
