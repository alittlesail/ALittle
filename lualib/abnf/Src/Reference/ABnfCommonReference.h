
#ifndef _ALITTLE_ABNFCOMMONREFERENCE_H_
#define _ALITTLE_ABNFCOMMONREFERENCE_H_

#include "alanguage/Src/Model/ABnfReference.h"

enum ABnfColorType
{
    ABnfKeyWord = 1,
    ABnfId = 2,
    ABnfComment = 3,
    ABnfKey = 4,
    ABnfString = 5,
    ABnfRegex = 6,
    ABnfNodeTail = 7,
    ABnfNumber = 8,
};

class ABnfCommonReference : public ABnfReference
{
protected:
	ABnfElementWeakPtr m_element;

public:
    ABnfCommonReference(const ABnfElementPtr& element);
    virtual ~ABnfCommonReference() {}

    // 配色
    virtual int QueryClassificationTag(bool& blur) override;

    // 获取缩进
    virtual int QueryDesiredIndent(int it_line, int it_char, const ABnfElementPtr& select) override;
};

#endif // _ALITTLE_ABNFCOMMONREFERENCE_H_
