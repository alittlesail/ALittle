
#ifndef _ALITTLE_ABNFSTRINGREFERENCE_H_
#define _ALITTLE_ABNFSTRINGREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfStringReference : public ABnfCommonReference
{
public:
    ABnfStringReference(ABnfElementPtr element);
    virtual ~ABnfStringReference() {}

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ABNFSTRINGREFERENCE_H_
