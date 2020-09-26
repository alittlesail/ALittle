
#ifndef _ALITTLE_ABNFNUMBERREFERENCE_H_
#define _ALITTLE_ABNFNUMBERREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfNumberReference : public ABnfCommonReference
{
public:
    ABnfNumberReference(ABnfElementPtr element);
    virtual ~ABnfNumberReference() {}

    void QueryQuickInfo(std::string& info) override;
};

#endif // _ALITTLE_ABNFNUMBERREFERENCE_H_
