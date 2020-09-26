#include "ALittleScriptUsingDecReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptUsingNameDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Guess/ALittleScriptGuessClass.h"

ALittleScriptUsingDecReference::ALittleScriptUsingDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptUsingDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

inline ABnfGuessError ALittleScriptUsingDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);
    auto name_dec = element->GetUsingNameDec();
    if (name_dec == nullptr) return ABnfGuessError(element, u8"没有定义using的名称");

    if (element->GetAllType() != nullptr)
    {
        auto error = element->GetAllType()->GuessTypes(guess_list);
        if (error) return error;

        bool has_template = false;
        for (auto& guess : guess_list)
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
            {
                auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
                if (guess_class->template_list.size() > 0)
                {
                    has_template = true;
                    break;
                }
            }
        }
        if (!has_template) return nullptr;

        std::vector<ABnfGuessPtr> new_guess_list;
        for (auto& guess : guess_list)
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
            {
                auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
                if (guess_class->template_list.size() == 0)
                {
                    new_guess_list.push_back(guess);
                }
                else
                {
                    guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess_class->Clone());
                    guess_class->using_name = m_namespace_name + "." + name_dec->GetElementText();
                    element->GetFile()->AddGuessType(guess_class);
                    new_guess_list.push_back(guess_class);
                }
            }
            else
            {
                new_guess_list.push_back(guess);
            }
        }

        guess_list = new_guess_list;
    }
    return nullptr;
}
