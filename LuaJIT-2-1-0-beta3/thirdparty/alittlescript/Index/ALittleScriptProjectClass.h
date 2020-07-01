
#ifndef _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
#define _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Index/ABnfProject.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

class ALittleScriptProjectClass : public ABnfProject
{
public:
    ALittleScriptProjectClass(const std::string& full_path);
    virtual ~ALittleScriptProjectClass();
};

#endif // _ALITTLE_ALITTLESCRIPTPROJECTCLASS_H_
