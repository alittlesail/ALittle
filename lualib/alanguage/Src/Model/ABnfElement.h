
#ifndef _ALITTLE_ABNFELEMENT_H_
#define _ALITTLE_ABNFELEMENT_H_

#include <memory>
#include <string>
#include <vector>

#include "ABnfGuess.h"

class ABnfFactory;
class ABnfFile;
class ABnfReference;
class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
using ABnfElementWeakPtr = std::weak_ptr<ABnfElement>;

class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;

class ABnfElement : public std::enable_shared_from_this<ABnfElement>
{
protected:
    ABnfFactory* m_factory = nullptr;     // ���󹤳�
    ABnfFile* m_file = nullptr;           // ���ڵĽ���
    ABnfElementWeakPtr m_parent;          // ���ڵ�
    ABnfReference* m_reference = nullptr;         // ����

    std::string m_element_text;         // �ı�����    
    int m_start = 0;                       // �ı�ƫ��
    int m_line = 1;                        // ������
    int m_col = 1;                         // ������

    std::string m_descriptor;           // �ڵ�������Ϣ

public:
    ABnfElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset);
    virtual ~ABnfElement();

    virtual bool IsLeafOrHasChildOrError() { return false; }
    virtual bool IsError() { return false; }
    virtual bool IsNode() { return false; }

    // ��ȡ����
    ABnfReference* GetReference();
    // ��ȡ����
    virtual ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list);

    // ��ȡ��һ������
    virtual ABnfGuessError GuessType(ABnfGuessPtr& out);

    // ��ȡ����ϸ��
    inline ABnfFile* GetFile() const { return m_file; }
    // ��ȡ�ļ�ȫ·��
    const std::string& GetFullPath() const;
    // ��ȡ����ģ��·��
    const std::string& GetModulePath() const;

    // ���ø��ڵ�
    void SetParent(const ABnfElementPtr& parent);
    ABnfElementPtr GetParent() const;

    // ��ǰ�ڵ��Ƿ��ָ����Χ�н���
    bool IntersectsWith(int start, int end);

    // ���úͻ�ȡ����
    inline void SetDescriptor(const std::string& value) { m_descriptor = value; }
    inline const std::string& GetDescriptor() const { return m_descriptor; }

    // ����ƫ��λ�ã���ȡ������Ԫ��
    virtual ABnfElementPtr GetException(int offset) { return nullptr; }
    // �������У���ȡ������Ԫ��
    virtual ABnfElementPtr GetException(int it_line, int it_char) { return nullptr; }

    // ��ȡ�ڵ�ƫ��
    virtual int GetStart() { return m_start; }

    // ��ȡ�ڵ㳤��
    virtual int GetEnd() { return m_start; }

    // ��ȡ�ڵ㳤��
    virtual int GetLength() { return GetEnd() - GetStart(); }

    virtual int GetLengthWithoutError() { return GetEnd() - GetStart(); }

    // ��ȡ֧�ڵ�����
    virtual const std::string& GetNodeType();
    // ��ȡҶ�������
    virtual const std::string& GetLeafType();

    // ��ȡ�ı�
    virtual const std::string& GetElementText();

    // ��ȡȥ�������ŶԺ�˫���Ŷ�֮����ַ���
    virtual std::string GetElementString();

    // ��ȡ��ǰ�ǵڼ��У���1��ʼ��
    virtual int GetStartLine() { return m_line; }

    // ��ȡ��ǰ�ǵڼ��У���1��ʼ��
    virtual int GetStartCol() { return m_col; }
    // ����indent
    virtual int GetStartIndent();

    // ��ȡ����λ���ǵڼ��У���1��ʼ��
    virtual int GetEndLine() { return m_line; }
    // ��ȡ����λ���ǵڼ��У���1��ʼ��
    virtual int GetEndCol() { return m_col; }
};

#endif