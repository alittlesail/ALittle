
#include "ALittleScriptReferenceTemplate.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfGuess.h"
#include "../../alanguage/Model/ABnfStringElement.h"
#include "../../alanguage/Model/ALanguageHelperInfo.h"
#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

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

ALittleScriptReference::ALittleScriptReference(ABnfElementPtr p_element)
{
	m_ref_element = p_element;
}

// 鼠标移入时，显示的快捷信息
void ALittleScriptReference::QueryQuickInfo(std::string& info)
{
    auto element = m_ref_element.lock();
    if (element == nullptr) return;

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return;
    info = guess->GetValue();
}

int ALittleScriptReference::QueryDesiredIndent(int it_line, int it_char, ABnfElementPtr select)
{
    auto element = m_ref_element.lock();
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
        if (std::dynamic_pointer_cast<ABnfStringElement>(select) && select->GetElementText() == "{")
            return m_desire_indent;
        // int find = element->FindForwardFirstEnterAndHaveNotSpaceOrTab();
        // if (find < 0 || offset <= find || offset > element->GetEnd()) return m_desire_indent + s_indent_size;
        return m_desire_indent;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptOpNewListStatElement>(element))
    {
        if (m_desire_indent >= 0) return m_desire_indent;

        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        const auto& childs = node->GetChilds();
        if (childs.size() > 0)
        {
            m_desire_indent = childs[0]->GetStartIndent();
            return m_desire_indent;
        }
    }

    if (m_desire_indent >= 0) return m_desire_indent;
    m_desire_indent = parent->GetReference()->QueryDesiredIndent(it_line, it_char, nullptr);
    return m_desire_indent;
}

int ALittleScriptReference::QueryFormateIndent(int it_line, int it_char, ABnfElementPtr select)
{
    if (m_format_indent >= 0) return m_format_indent;

    auto element = m_ref_element.lock();
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
        m_format_indent = parent->GetReference()->QueryFormateIndent(it_line, it_char, nullptr);
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
        m_format_indent = parent->GetReference()->QueryFormateIndent(it_line, it_char, nullptr) + s_indent_size;
        return m_format_indent;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptOpNewListStatElement>(element))
    {
        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        const auto& childs = node->GetChilds();
        if (childs.size() > 0)
        {
            m_format_indent = childs[0]->GetStartIndent();
            return m_format_indent;
        }
    }

    m_format_indent = parent->GetReference()->QueryFormateIndent(it_line, it_char, nullptr);
    return m_format_indent;
}

ALittleScriptIndex* ALittleScriptReference::GetIndex()
{
    auto element = m_ref_element.lock();
    if (element == nullptr) return nullptr;

    return dynamic_cast<ALittleScriptIndex*>(element->GetFile()->GetProject());
}
