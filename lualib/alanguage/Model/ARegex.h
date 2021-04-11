
#ifndef _ALITTLE_AREGEX_H_
#define _ALITTLE_AREGEX_H_

#include <string>
#include <vector>
#include <unordered_set>

enum class ARegexNodeType
{
    NT_NONE,            // ��Чö��
    NT_CHAR,            // һ���ַ�
    NT_FIND_STRING,     // �����ַ���
    NT_CHARSET,         // �ַ�����
    NT_LIST,            // �ӽڵ��б� ���ƥ��
    NT_OPTION,          // �ӽڵ��б� ��֧ƥ��
};

enum class ARegexRepeatType
{
    NRT_NONE,		    // δ���ã������Ե�NRT_ONE����
    NRT_ONE,	        // ���ҽ���һ��
    NRT_NOT_OR_MORE,    // 0�����߶��
    NRT_AT_LEAST_ONE,   // ����һ��
    NRT_ONE_OR_NOT,	    // ���ҽ���һ�� ����û��
};

enum class ARegexCharSetType
{
    CST_CUSTOM,         // �Զ��壬��ȡchar_set
    CST_A,              // ��ĸ
    CST_D,              // ����
    CST_W,              // ��ĸ�����»���
    CST_DOT,            // ����\n������ַ�
    CST_ALL,            // ȫ���ַ�
};

enum class ARegexNegateType
{
    NNT_NONE,		    // δ���ã������Ե�NNT_FALSE����
    NNT_FALSE,	        // û��ȡ��
    NNT_TRUE,	        // ��ȡ��
};

struct ARegexNode
{
    // �ڵ�����
    ARegexNodeType type = ARegexNodeType::NT_NONE;
    // �ظ�ƥ�����
    ARegexRepeatType repeat = ARegexRepeatType::NRT_NONE;
    // ƥ����ȡ��
    ARegexNegateType negate = ARegexNegateType::NNT_NONE;

    // ��typeΪNT_CHARʱ����ʾҪƥ����ַ�
    char value = 0;

    // ��typeΪNT_FIND_STRINGʱ����ʾҪ���ҵ��ַ���
    std::string find;

    // ��typeΪNT_CHARSETʱ����ʾҪƥ���ַ�����
    ARegexCharSetType char_set_type = ARegexCharSetType::CST_CUSTOM;
    // ��char_set_typeΪARegexCharSetType::CST_CUSTOMʱ����ʾ�ַ�����
    std::unordered_set<char> char_set;

    // ��typeΪNT_LIST����NT_OPTIONʱ����ʾ�ӽڵ�
    std::vector<ARegexNode> childs;
};

class ARegex
{
private:
	std::string m_rule;	// ����
    std::string m_rule_error;    // ��¼����������

    // �ѱ���õĹ�������
    ARegexNode m_node;

public:
	ARegex(const std::string& rule);
    // �Ӹ�λ�ý���ƥ��
    bool Match(const char* src, int& length);

private:
    bool MatchNode(const char* src, const ARegexNode& node, int& length);
    bool MatchNodeRepeated(const char* src, const ARegexNode& node, int& length);

private:
    static bool CompileOption(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error);
    static bool CompileCustomSet(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error);
    static bool CompileFindString(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error);
};

#endif // _ALITTLE_AREGEX_H_