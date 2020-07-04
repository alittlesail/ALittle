
#ifndef _ALITTLE_ALITTLESCRIPTGUESS_H_
#define _ALITTLE_ALITTLESCRIPTGUESS_H_

#include "../../alanguage/Model/ABnfGuess.h"

class ALittleScriptGuess : public ABnfGuess
{
public:
    bool is_register = false;

    ALittleScriptGuess() { }
    virtual ~ALittleScriptGuess() {}
    virtual std::shared_ptr<ABnfElement> GetElement() { return nullptr; }
};

#endif // _ALITTLE_ALITTLESCRIPTGUESS_H_
