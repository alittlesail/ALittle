
#ifndef _ALITTLE_ABNFSTRINGREFERENCE_H_
#define _ALITTLE_ABNFSTRINGREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfStringReference : public ABnfCommonReference
{
public:
    ABnfStringReference(const ABnfElementPtr& element);
    virtual ~ABnfStringReference() = default;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ABNFSTRINGREFERENCE_H_
