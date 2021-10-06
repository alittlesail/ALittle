
#ifndef _ALITTLE_ABNFNODEELEMENT_H_
#define _ALITTLE_ABNFNODEELEMENT_H_

#include <string>
#include <vector>

#include "ABnfElement.h"
 
class ABnfNodeElement : public ABnfElement
{
private:
    int m_end = -1;                        // ����ڵ㳤��
    int m_end_line = -1;
    int m_end_col = -1;
    std::string m_type;                    // �ڵ�����

protected:
    std::vector<ABnfElementPtr> m_childs; // �ڵ��б�

public:
    ABnfNodeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type);
    virtual ~ABnfNodeElement() = default;

    bool IsLeafOrHasChildOrError() override;
    bool IsNode() override { return true; }

    // ���Ԫ��
    void AddChild(ABnfElementPtr child);

    // ��ȡ����Ԫ��
    inline const std::vector<ABnfElementPtr>& GetChilds() const { return m_childs; }

    inline void ResizeChild(int count) { m_childs.resize(count); }

    // ����ƫ��λ�ã���ȡ������Ԫ��
    ABnfElementPtr GetException(int offset) override;

    // �������У���ȡ������Ԫ��
    ABnfElementPtr GetException(int it_line, int it_char) override;

    // ��ȡ�ڵ�����
    const std::string& GetNodeType() override { return m_type; }

    int GetLengthWithoutError() override;

    // ��ȡ�ڵ㳤��
    int GetEnd() override;

    // ��ȡ����λ���ǵڼ���
    int GetEndLine() override;

    // ��ȡ����λ���ǵڼ���
    int GetEndCol() override;

private:
    void CalcEnd();
};

#endif