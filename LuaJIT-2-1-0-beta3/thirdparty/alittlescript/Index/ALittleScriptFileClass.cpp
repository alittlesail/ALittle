
#include "ALittleScriptFileClass.h"
#include "ALittleScriptProjectClass.h"
#include "../../alanguage/Model/ABnf.h"
#include "../../alanguage/Model/ABnfNodeElement.h"

ALittleScriptFileClass::ALittleScriptFileClass(ABnfProject* project, const std::string& full_path, const char* text, size_t len)
	: ABnfFile(project, full_path, text, len)
{
}

ALittleScriptFileClass::~ALittleScriptFileClass()
{
}

// 更新分析内容
void ALittleScriptFileClass::UpdateAnalysis()
{
    m_root = nullptr;
    
    m_root = GetProject()->RefABnf().Analysis(this);
    if (m_root == nullptr) return;
}

void ALittleScriptFileClass::UpdateError()
{
    ClearCheckError();
    ClearAnalysisError();

    if (m_root == nullptr) return;

    CollectError(m_root);
    AnalysisError(m_root);
}

