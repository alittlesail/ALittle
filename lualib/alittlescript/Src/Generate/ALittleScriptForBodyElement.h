#ifndef _ALITTLE_ALittleScriptForBodyElement_H_
#define _ALITTLE_ALittleScriptForBodyElement_H_

#include <memory>
#include <vector>
#include <string>
#include "alanguage/Src/Model/ABnfNodeElement.h"

class ALittleScriptAllExprElement;
class ALittleScriptStringElement;

class ALittleScriptForBodyElement : public ABnfNodeElement
{
public:
    ALittleScriptForBodyElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForBodyElement() { }

private:
    bool m_flag_AllExpr = false;
    std::vector<std::shared_ptr<ALittleScriptAllExprElement>> m_list_AllExpr;
public:
    const std::vector<std::shared_ptr<ALittleScriptAllExprElement>>& GetAllExprList();
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList();
};

#endif // _ALITTLE_ALittleScriptForBodyElement_H_
