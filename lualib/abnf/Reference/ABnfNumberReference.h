
#ifndef _ALITTLE_ABNFNUMBERREFERENCE_H_
#define _ALITTLE_ABNFNUMBERREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfNumberReference : public ABnfCommonReference
{
public:
    ABnfNumberReference(const ABnfElementPtr& element);
    virtual ~ABnfNumberReference() = default;

    void QueryQuickInfo(std::string& info) override;
};

#endif // _ALITTLE_ABNFNUMBERREFERENCE_H_
