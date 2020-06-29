
#ifndef _ALITTLE_ABNFCOMMONREFERENCE_H_
#define _ALITTLE_ABNFCOMMONREFERENCE_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfReference.h"

enum ABnfColorType
{
    ABnfKeyWord = 1,
    ABnfId = 2,
    ABnfComment = 3,
    ABnfKey = 4,
    ABnfString = 5,
    ABnfRegex = 6,
};

class ABnfCommonReference : public ABnfReference
{
protected:
	ABnfElementWeakPtr m_element;

public:
    ABnfCommonReference(ABnfElementPtr element);
    virtual ~ABnfCommonReference() {}

    // ÅäÉ«
    virtual int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ABNFCOMMONREFERENCE_H_
