
#include "ABnfElement.h"
#include "ABnfReference.h"
#include "../Index/ABnfFactory.h"
#include "../Index/ABnfFile.h"
#include "../Index/ABnfProject.h"

ABnfElement::ABnfElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset)
{
    m_factory = factory;
    m_file = file;
    m_line = line;
    m_col = col;
    m_start = offset;
}

ABnfElement::~ABnfElement()
{
    if (m_reference != nullptr)
        delete m_reference;
}

// 获取引用
ABnfReference* ABnfElement::GetReference()
{
    if (m_reference != nullptr) return m_reference;

    if (m_factory != nullptr)
        m_reference = m_factory->CreateReference(shared_from_this());
    if (m_reference == nullptr)
        m_reference = new ABnfReference();
    return m_reference;
}

// 获取类型
ABnfGuessError ABnfElement::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    guess_list.resize(0);
    return m_factory->GuessTypes(shared_from_this(), guess_list);
}

// 获取第一个类型
ABnfGuessError ABnfElement::GuessType(ABnfGuessPtr& out)
{
    out = nullptr;

    std::vector<ABnfGuessPtr> guess_list;
    auto error = GuessTypes(guess_list);
    if (error) return error;

    if (guess_list.size() == 0)
    {
        error.element = shared_from_this();
        error.error = "unknown type";
        return error;
    }

    out = guess_list[0];
    return nullptr;
}

// 获取文件全路径
const std::string& ABnfElement::GetFullPath()
{
    static std::string empty;
    if (m_file == nullptr) return empty;
    return m_file->GetFullPath();
}

// 获取所在工程路径
const std::string& ABnfElement::GetProjectPath()
{
    static std::string empty;
    if (m_file == nullptr) return empty;
    auto* project = m_file->GetProject();
    if (project == nullptr) return empty;
    return project->GetProjectPath();
}

// 设置父节点
void ABnfElement::SetParent(ABnfElementPtr parent) { m_parent = parent; }
ABnfElementPtr ABnfElement::GetParent() { return m_parent.lock(); }

// 当前节点是否和指定范围有交集
bool ABnfElement::IntersectsWith(int start, int end)
{
    if (m_start >= end) return false;
    if (GetEnd() <= start) return false;
    return true;
}

// 获取类型
const std::string& ABnfElement::GetNodeType() { static std::string empty; return empty; }

const std::string& ABnfElement::GetLeafType() { static std::string empty; return empty; }

// 获取文本
const std::string& ABnfElement::GetElementText()
{
    if (m_element_text.size() > 0) return m_element_text;

    int start = GetStart();
    if (start >= m_file->GetLength())
        return m_element_text;

    int length = GetLength();
    if (length == 0) return m_element_text;

    m_element_text = m_file->Substring(start, length);
    return m_element_text;
}

// 获取去掉单引号对和双引号对之后的字符串
std::string ABnfElement::GetElementString()
{
    int length = GetLength();
    if (length <= 2) return "";
    length -= 2;
    int start = GetStart() + 1;
    if (start >= m_file->GetLength()) return "";
    return m_file->Substring(start, length);
}

// 计算indent
int ABnfElement::GetStartIndent()
{
    int start = GetStart();
    int end = start + GetStartCol();
    int count = 0;
    for (int i = start; i < end; ++i)
    {
        if (i >= m_file->GetLength()) break;

        if (m_file->GetText()[i] == '\t')
            count += s_indent_size;
        else
            ++count;
    }

    return count;
}