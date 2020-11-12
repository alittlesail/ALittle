
#ifndef _ALITTLE_ABNFNODEREFERENCE_H_
#define _ALITTLE_ABNFNODEREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfNodeReference : public ABnfCommonReference
{
public:
    ABnfNodeReference(const ABnfElementPtr& element);
    virtual ~ABnfNodeReference() {}

    ABnfGuessError CheckError() override;

private:
    ABnfGuessError CheckElementError(const ABnfElementPtr& element) const;
};

#endif // _ALITTLE_ABNFNODEREFERENCE_H_
