
#ifndef _ALITTLE_ABNFIDREFERENCE_H_
#define _ALITTLE_ABNFIDREFERENCE_H_

#include "ABnfCommonReference.h"

class ABnfIdReference : public ABnfCommonReference
{
public:
    ABnfIdReference(ABnfElementPtr element);
    virtual ~ABnfIdReference() {}

    // 快捷信息
    void QueryQuickInfo(std::string& info) override;
    // 输入提示
    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;
    // 检查错误
    ABnfGuessError CheckError() override;
    // 可以拾取高亮
    bool PeekHighlightWord() override { return true; }
    // 获取高亮信息
    void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) override;
    // 跳转
    ABnfElementPtr GotoDefinition() override;
};

#endif // _ALITTLE_ABNFIDREFERENCE_H_
