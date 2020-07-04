
#ifndef _ALITTLE_ABNFNODEREFERENCE_H_
#define _ALITTLE_ABNFNODEREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfNodeReference : public ABnfCommonReference
{
public:
    ABnfNodeReference(ABnfElementPtr element);
    virtual ~ABnfNodeReference() {}

    ABnfGuessError CheckError() override;

private:
    ABnfGuessError CheckElementError(ABnfElementPtr element);
};

#endif // _ALITTLE_ABNFNODEREFERENCE_H_
