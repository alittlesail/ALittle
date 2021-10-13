
#include "ABnfNodeElement.h"

ABnfNodeElement::ABnfNodeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
    : ABnfElement(factory, file, line, col, offset)
{
    m_type = type;
}

bool ABnfNodeElement::IsLeafOrHasChildOrError()
{
    return m_childs.size() > 0;
}

// ���Ԫ��
void ABnfNodeElement::AddChild(ABnfElementPtr child)
{
    child->SetParent(shared_from_this());
    m_childs.push_back(child);
}

// ����ƫ��λ�ã���ȡ������Ԫ��
ABnfElementPtr ABnfNodeElement::GetException(int offset)
{
    for (auto& child : m_childs)
    {
        auto element = child->GetException(offset);
        if (element != nullptr) return element;
    }

    if (offset < GetStart()) return nullptr;
    if (offset >= GetEnd()) return nullptr;

    return shared_from_this();
}

// �������У���ȡ������Ԫ��
ABnfElementPtr ABnfNodeElement::GetException(int it_line, int it_char)
{
    for (auto& child : m_childs)
    {
        auto element = child->GetException(it_line, it_char);
        if (element != nullptr) return element;
    }

    const auto start_line = GetStartLine();
    const auto end_line = GetEndLine();

    if (start_line > it_line) return nullptr;
    if (end_line < it_line) return nullptr;

    if (start_line == it_line && GetStartCol() > it_char) return nullptr;
    if (end_line == it_line && GetEndCol() <= it_char) return nullptr;

    return shared_from_this();
}

int ABnfNodeElement::GetLengthWithoutError()
{
    for (int i = static_cast<int>(m_childs.size()) - 1; i >= 0; --i)
    {
        if (m_childs[i]->IsError())
            continue;
        return m_childs[i]->GetStart() + m_childs[i]->GetLengthWithoutError() - GetStart();
    }

    return GetLength();
}

// ��ȡ�ڵ㳤��
int ABnfNodeElement::GetEnd()
{
    if (m_end >= 0) return m_end;

    if (m_childs.empty())
    {
        m_end = m_start;
        return m_end;
    }

    m_end = m_childs[m_childs.size() - 1]->GetEnd();
    return m_end;
}

// ��ȡ����λ���ǵڼ���
int ABnfNodeElement::GetEndLine()
{
    if (m_end_line < 0) CalcEnd();
    return m_end_line;
}

// ��ȡ����λ���ǵڼ���
int ABnfNodeElement::GetEndCol()
{
    if (m_end_col < 0) CalcEnd();
    return m_end_col;
}

void ABnfNodeElement::CalcEnd()
{
    m_end_line = m_line;
    m_end_col = m_col;

    if (m_childs.empty()) return;

    m_end_line = m_childs[m_childs.size() - 1]->GetEndLine();
    m_end_col = m_childs[m_childs.size() - 1]->GetEndCol();
}
