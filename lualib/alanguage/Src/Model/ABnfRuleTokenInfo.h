
#ifndef _ALITTLE_ABNFRULETOKENINFO_H_
#define _ALITTLE_ABNFRULETOKENINFO_H_

#include <string>
#include <memory>

#include "ARegex.h"

enum class ABnfRuleTokenType
{
    TT_NONE,            // ��Чö��
    TT_ID,				// ������
    TT_STRING,			// �ַ���
    TT_KEY,             // �ؼ���
    TT_REGEX,			// ������ʽ�ַ���
    TT_LINE_COMMENT,	// ��ע��
    TT_BLOCK_COMMENT,	// ��ע��
    TT_SYMBOL,			// ����
};

class ABnfRuleInfo;

struct ABnfRuleTokenInfo
{
    ABnfRuleInfo* rule = nullptr;   // ��typeʱIDʱ�����ҵ��Ĺ���

    ABnfRuleTokenType type = ABnfRuleTokenType::TT_NONE;    // ����
    std::string value;                                      // ֵ
    std::shared_ptr<ARegex> regex;                      // ������ʽ

    int line = 0;   // �����У���1��ʼ��
    int col = 0;    // �����У���1��ʼ��
};

enum class ABnfRuleNodeRepeatType
{
    NRT_NONE,		    // δ���ã������Ե�NRT_ONE����
    NRT_ONE,	        // ���ҽ���һ��
    NRT_NOT_OR_MORE,    // 0�����߶��
    NRT_AT_LEAST_ONE,   // ����һ��
    NRT_ONE_OR_NOT,	    // ���ҽ���һ�� ����û��
};

enum class ABnfRuleNodePinType
{
    NPT_NONE,		// δ���ã������Ե�NPT_FALSE����
    NPT_FALSE,		// û������
    NPT_TRUE,		// ������
};

enum class ABnfRuleNodeNotKeyType
{
    NNKT_NONE,      // δ���ã������Ե�NPT_FALSE����
    NNKT_FALSE,     // û������
    NNKT_TRUE,      // ������
};

#endif // _ALITTLE_ABNFRULETOKENINFO_H_