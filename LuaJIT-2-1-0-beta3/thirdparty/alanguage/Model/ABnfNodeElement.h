
#ifndef _ALITTLE_ABNFNODEELEMENT_H_
#define _ALITTLE_ABNFNODEELEMENT_H_

#include <string>
#include <vector>

#include "ABnfElement.h"
 
class ABnfNodeElement : public ABnfElement
{
private:
    int m_end = -1;                        // 缓存节点长度
    int m_end_line = -1;
    int m_end_col = -1;
    std::string m_type;                    // 节点类型

protected:
    std::vector<ABnfElementPtr> m_childs; // 节点列表

public:
    ABnfNodeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type);
    virtual ~ABnfNodeElement() {}

    bool IsLeafOrHasChildOrError() override;

    // 添加元素
    void AddChild(ABnfElementPtr child);

    // 获取所有元素
    inline const std::vector<ABnfElementPtr>& GetChilds() { return m_childs; }

    inline void ResizeChild(int count) { m_childs.resize(count); }

    // 根据偏移位置，获取期望的元素
    ABnfElementPtr GetException(int offset) override;

    // 获取节点类型
    const std::string& GetNodeType() override { return m_type; }

    int GetLengthWithoutError() override;

    // 获取节点长度
    int GetEnd() override;

    // 获取结束位置是第几行
    int GetEndLine() override;

    // 获取结束位置是第几列
    int GetEndCol() override;

private:
    void CalcEnd();
};

#endif // _ALITTLE_ABNFNODEELEMENT_H_