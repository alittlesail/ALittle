
#include "ALittleScriptFileClass.h"
#include "ALittleScriptProjectClass.h"
#include "../../alanguage/Model/ABnf.h"
#include "../../alanguage/Model/ABnfNodeElement.h"

ALittleScriptFileClass::ALittleScriptFileClass(ABnfProject* project, const std::string& full_path, const char* text, size_t len, bool in_ui)
	: ABnfFile(project, full_path, text, len, in_ui)
{
}

ALittleScriptFileClass::~ALittleScriptFileClass()
{
}

// 更新分析内容
void ALittleScriptFileClass::UpdateAnalysis()
{
    m_root = nullptr;
    
    if (m_in_ui)
        m_root = GetProject()->RefABnfUI().Analysis(this);
    else
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

