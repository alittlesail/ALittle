#include "ALittleScriptAllTypeReference.h"

#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptGenericTypeElement.h"
#include "../Generate/ALittleScriptPrimitiveTypeElement.h"

#include "../Guess/ALittleScriptGuessPrimitive.h"

#include "../Index/ALittleScriptIndex.h"
#include "alanguage/Src/Index/ABnfFile.h"

ABnfGuessError ALittleScriptAllTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    guess_list.resize(0);

    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ㶪ʧ");

    ABnfGuessError error;
    const bool is_const = element->GetAllTypeConst() != nullptr;

    if (element->GetCustomType() != nullptr)
        error = element->GetCustomType()->GuessTypes(guess_list);
    else if (element->GetGenericType() != nullptr)
        error = element->GetGenericType()->GuessTypes(guess_list);
    else if (element->GetPrimitiveType() != nullptr)
        error = element->GetPrimitiveType()->GuessTypes(guess_list);

    if (error) return error;

    if (!guess_list.empty())
    {
        if (!is_const) return nullptr;

        for (size_t i = 0; i < guess_list.size(); ++i)
        {
            auto guess = guess_list[i];
            if (guess->is_const) continue;

            if (std::dynamic_pointer_cast<ALittleScriptGuessPrimitive>(guess))
            {
                const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("const " + guess->GetValue());
                if (it == ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end())
                    return ABnfGuessError(element, u8"�Ҳ���const " + guess->GetValue());
                guess_list = it->second;
                break;
            }
            else
            {
                guess = guess->Clone();
                element->GetFile()->AddGuessType(guess);
                guess->is_const = true;
                guess->UpdateValue();
            }

            guess_list[i] = guess;
        }
        return nullptr;
    }

    return ABnfGuessError(element, u8"AllType����δ֪���ӽڵ�");
}
