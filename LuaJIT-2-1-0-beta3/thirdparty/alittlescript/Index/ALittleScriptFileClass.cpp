
#include "ALittleScriptFileClass.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"

ALittleScriptFileClass::ALittleScriptFileClass(ABnfProject* project, const std::string& full_path, ABnf* abnf, const char* text, size_t len)
	: ABnfFile(project, full_path, abnf, text, len)
{
}

ALittleScriptFileClass::~ALittleScriptFileClass()
{
}

// 更新分析内容
void ALittleScriptFileClass::UpdateAnalysis()
{
    m_root = nullptr;
    if (m_abnf == nullptr) return;

    m_root = m_abnf->Analysis(this);
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

