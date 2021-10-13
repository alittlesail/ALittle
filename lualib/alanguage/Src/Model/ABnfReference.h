
#ifndef _ALITTLE_ABNFREFERENCE_H_
#define _ALITTLE_ABNFREFERENCE_H_

#include "ABnfGuess.h"
#include "ALanguageHelperInfo.h"

#include <memory>

class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
using ABnfElementWeakPtr = std::weak_ptr<ABnfElement>;
class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;

class ABnfReference
{
public:
    ABnfReference() = default;
    virtual ~ABnfReference() = default;

    // ������
    virtual ABnfGuessError CheckError() { return nullptr; }

    // ��ȡ����
    virtual ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) { return nullptr; }

    // ���ض�����ʽ������
    virtual bool MultiGuessTypes() { return false; }

    // ��ȡ����
    virtual int QueryDesiredIndent(int it_line, int it_char, const ABnfElementPtr& select) { return 0; }

    // ��ȡ����
    virtual int QueryFormatIndent(int it_line, int it_char, const ABnfElementPtr& select) { return 0; }

    // ��������ʱ�ĺ�����ʾ
    virtual bool QueryParamList(int& line_start, int& char_start, int& line_end, int& char_end, std::vector<ALanguageParameterInfo>& param_list) { return false; }

    // ��ȡ�����±�
    virtual int QueryParamIndex(int it_line, int it_char, const ABnfElementPtr& select, int& start_offset) { return -1; }

    // �������ʱ����ʾ�Ŀ����Ϣ
    virtual void QueryQuickInfo(std::string& info) { }

    // �������ܲ�ȫ
    virtual bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) { return false; }
    virtual bool QueryKeyWord(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) { return false; }

    // ��ɫ
    virtual int QueryClassificationTag(bool& blur) { blur = false; return 0; }

    // ����ʰȡ
    virtual bool PeekHighlightWord() { return false; }

    // ���и���
    virtual void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) { }

    // ��ת
    virtual ABnfElementPtr GotoDefinition() { return nullptr; }

    // �Ƿ������ת
    virtual bool CanGotoDefinition() { return true; }
};

#endif