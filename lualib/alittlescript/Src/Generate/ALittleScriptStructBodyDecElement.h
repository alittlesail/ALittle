#ifndef _ALITTLE_ALittleScriptStructBodyDecElement_H_
#define _ALITTLE_ALittleScriptStructBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptStructOptionDecElement;
class ALittleScriptStructVarDecElement;
class ALittleScriptStringElement;

class ALittleScriptStructBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructBodyDecElement() { }

private:
    bool m_flag_StructOptionDec = false;
    std::vector<std::shared_ptr<ALittleScriptStructOptionDecElement>> m_list_StructOptionDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptStructOptionDecElement>>& GetStructOptionDecList();
private:
    bool m_flag_StructVarDec = false;
    std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> m_list_StructVarDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& GetStructVarDecList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptStructBodyDecElement_H_
