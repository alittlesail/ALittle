
#ifndef _ALITTLE_ABNFKEYREFERENCE_H_
#define _ALITTLE_ABNFKEYREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfKeyReference : public ABnfCommonReference
{
public:
    ABnfKeyReference(ABnfElementPtr element);
    virtual ~ABnfKeyReference() {}

    ABnfGuessError CheckError() override;

    void QueryQuickInfo(std::string& info) override;
};

#endif // _ALITTLE_ABNFKEYREFERENCE_H_
