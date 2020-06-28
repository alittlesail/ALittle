
#ifndef _ALITTLE_ABNFNODEREFERENCE_H_
#define _ALITTLE_ABNFNODEREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfNodeReference : public ABnfCommonReference
{
public:
    ABnfNodeReference(ABnfElementPtr element);
    virtual ~ABnfNodeReference() {}

    bool CheckError(ABnfGuessError& error)override;

private:
    bool CheckElementError(ABnfElementPtr element, ABnfGuessError& error);
};

#endif // _ALITTLE_ABNFNODEREFERENCE_H_
