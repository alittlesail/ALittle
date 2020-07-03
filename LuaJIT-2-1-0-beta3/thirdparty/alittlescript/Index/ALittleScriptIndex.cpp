
#include "ALittleScriptIndex.h"
#include "../../alanguage/Model/ABnfElement.h"

ALittleScriptIndex::ALittleScriptIndex()
{
    // 基础变量
    std::vector<std::shared_ptr<ABnfGuess>> tmp;
    tmp.resize(0); sIntGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessInt(false)); tmp.push_back(sIntGuess); sPrimitiveGuessListMap[sIntGuess->GetValue()] = tmp; sPrimitiveGuessMap[sIntGuess->GetValue()] = sIntGuess;
    tmp.resize(0); sDoubleGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessDouble(false)); tmp.push_back(sDoubleGuess); sPrimitiveGuessListMap[sDoubleGuess->GetValue()] = tmp; sPrimitiveGuessMap[sDoubleGuess->GetValue()] = sDoubleGuess;
    tmp.resize(0); sStringGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessString(false)); tmp.push_back(sStringGuess); sPrimitiveGuessListMap[sStringGuess->GetValue()] = tmp; sPrimitiveGuessMap[sStringGuess->GetValue()] = sStringGuess;
    tmp.resize(0); sBoolGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessBool(false)); tmp.push_back(sBoolGuess); sPrimitiveGuessListMap[sBoolGuess->GetValue()] = tmp; sPrimitiveGuessMap[sBoolGuess->GetValue()] = sBoolGuess;
    tmp.resize(0); sLongGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessLong(false)); tmp.push_back(sLongGuess); sPrimitiveGuessListMap[sLongGuess->GetValue()] = tmp; sPrimitiveGuessMap[sLongGuess->GetValue()] = sLongGuess;
    tmp.resize(0); sAnyGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessAny(false)); tmp.push_back(sAnyGuess); sPrimitiveGuessListMap[sAnyGuess->GetValue()] = tmp; sPrimitiveGuessMap[sAnyGuess->GetValue()] = sAnyGuess;

    tmp.resize(0); sConstIntGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessInt(true)); tmp.push_back(sConstIntGuess); sPrimitiveGuessListMap[sConstIntGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstIntGuess->GetValue()] = sConstIntGuess;
    tmp.resize(0); sConstDoubleGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessDouble(true)); tmp.push_back(sConstDoubleGuess); sPrimitiveGuessListMap[sConstDoubleGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstDoubleGuess->GetValue()] = sConstDoubleGuess;
    tmp.resize(0); sConstStringGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessString(true)); tmp.push_back(sConstStringGuess); sPrimitiveGuessListMap[sConstStringGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstStringGuess->GetValue()] = sConstStringGuess;
    tmp.resize(0); sConstBoolGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessBool(true)); tmp.push_back(sConstBoolGuess); sPrimitiveGuessListMap[sConstBoolGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstBoolGuess->GetValue()] = sConstBoolGuess;
    tmp.resize(0); sConstLongGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessLong(true)); tmp.push_back(sConstLongGuess); sPrimitiveGuessListMap[sConstLongGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstLongGuess->GetValue()] = sConstLongGuess;
    tmp.resize(0); sConstAnyGuess = std::shared_ptr<ABnfGuess>(new ALittleScriptGuessAny(true)); tmp.push_back(sConstAnyGuess); sPrimitiveGuessListMap[sConstAnyGuess->GetValue()] = tmp; sPrimitiveGuessMap[sConstAnyGuess->GetValue()] = sConstAnyGuess;

    // null常量
    sConstNullGuess.push_back(std::shared_ptr<ABnfGuess>(new ALittleScriptGuessConst("null")));

    // 控制关键字
    sCtrlKeyWord.insert("if");
    sCtrlKeyWord.insert("elseif");
    sCtrlKeyWord.insert("else");
    sCtrlKeyWord.insert("do");
    sCtrlKeyWord.insert("while");
    sCtrlKeyWord.insert("return");
    sCtrlKeyWord.insert("break");
    sCtrlKeyWord.insert("continue");
    sCtrlKeyWord.insert("for");
    sCtrlKeyWord.insert("in");
    sCtrlKeyWord.insert("throw");
    sCtrlKeyWord.insert("assert");
}

const std::vector<std::shared_ptr<ABnfGuess>>* ALittleScriptIndex::GetGuessTypeList(std::shared_ptr<ABnfElement> element)
{
    auto it = m_guess_type_map.find(element->GetFile());
    if (it == m_guess_type_map.end()) return nullptr;
    auto sub_it = it->second.find(element);
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

void ALittleScriptIndex::AddGuessTypeList(std::shared_ptr<ABnfElement> element, const std::vector<std::shared_ptr<ABnfGuess>>& guess_type_list)
{
    m_guess_type_map[element->GetFile()][element] = guess_type_list;
    auto it = m_guess_error_map.find(element->GetFile());
    if (it != m_guess_error_map.end()) it->second.erase(element);
}

ABnfGuessError* ALittleScriptIndex::GetGuessError(std::shared_ptr<ABnfElement> element)
{
    auto it = m_guess_error_map.find(element->GetFile());
    if (it == m_guess_error_map.end()) return nullptr;
    auto sub_it = it->second.find(element);
    if (sub_it == it->second.end()) return nullptr;
    return &sub_it->second;
}

void ALittleScriptIndex::AddGuessError(std::shared_ptr<ABnfElement> element, const ABnfGuessError& error)
{
    m_guess_error_map[element->GetFile()][element] = error;
    auto it = m_guess_type_map.find(element->GetFile());
    if (it != m_guess_type_map.end()) it->second.erase(element);
}
