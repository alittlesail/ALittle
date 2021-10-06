
#ifndef _ALITTLE_ABNFREGEXREFERENCE_H_
#define _ALITTLE_ABNFREGEXREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfRegexReference : public ABnfCommonReference
{
public:
    ABnfRegexReference(const ABnfElementPtr& element);
    virtual ~ABnfRegexReference() {}

    void QueryQuickInfo(std::string& info) override;
};

#endif // _ALITTLE_ABNFREGEXREFERENCE_H_
