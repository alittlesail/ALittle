
#ifndef _ALITTLE_ABNFIDREFERENCE_H_
#define _ALITTLE_ABNFIDREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfIdReference : public ABnfCommonReference
{
public:
    ABnfIdReference(const ABnfElementPtr& element);
    virtual ~ABnfIdReference() {}

    // �����Ϣ
    void QueryQuickInfo(std::string& info) override;
    // ������ʾ
    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;
    // ������
    ABnfGuessError CheckError() override;
    // ����ʰȡ����
    bool PeekHighlightWord() override { return true; }
    // ��ȡ������Ϣ
    void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) override;
    // ��ת
    ABnfElementPtr GotoDefinition() override;
};

#endif // _ALITTLE_ABNFIDREFERENCE_H_
