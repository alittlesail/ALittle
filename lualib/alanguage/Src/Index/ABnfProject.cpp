
#include "ABnfProject.h"
#include "ABnfFactory.h"
#include "ABnfFile.h"

#include "alanguage/Src/Model/ABnfRuleInfo.h"

std::string ABnfProject::LoadABnf(const std::string& abnf_buffer)
{
    std::string error;
    m_abnf.Load(abnf_buffer, &RefFactory(), error);
    m_abnf_ui.Load(abnf_buffer, &RefFactory(), error);
    return error;
}

ABnfFile* ABnfProject::GetFile(const std::string& full_path)
{
    const auto it = m_file_map.find(full_path);
    if (it == m_file_map.end()) return nullptr;
    return it->second;
}

void ABnfProject::UpdateFile(const std::string& module_path, const std::string& full_path, int version)
{
    // 打开文件
    FILE* file = nullptr;
#ifdef _WIN32
    fopen_s(&file, full_path.c_str(), "rb");
#else
    file = fopen(full_path.c_str(), "rb");
#endif
    if (file == nullptr) return;

    std::vector<char> out;
    char buffer[1024];
    while (true)
    {
        const size_t read_size = fread(buffer, 1, sizeof(buffer), file);
        if (read_size == 0) break;
        for (size_t i = 0; i < read_size; ++i)
            out.push_back(buffer[i]);
    }

    fclose(file);

    auto it = m_file_map.find(full_path);
    if (it == m_file_map.end())
    {
        auto* abnf_file = RefFactory().CreateFile(this, module_path, full_path, out.data(), out.size());
        m_file_map[full_path] = abnf_file;
        abnf_file->AnalysisText(version);
    }
    else
    {
        it->second->SetText(out.data(), out.size());
        it->second->AnalysisText(version);
    }
}

void ABnfProject::TempFile(const std::string& module_path, const std::string& full_path, const std::string& text, int version)
{
    auto it = m_file_map.find(full_path);
    if (it == m_file_map.end())
    {
        const auto file = RefFactory().CreateFile(this, module_path, full_path, text.data(), text.size());
        m_file_map[full_path] = file;
        file->AnalysisText(version);
    }
    else
    {
        it->second->SetText(text.data(), text.size());
        it->second->AnalysisText(version);
    }
}

void ABnfProject::RemoveFile(const std::string& full_path)
{
    auto it = m_file_map.find(full_path);
    if (it == m_file_map.end()) return;

    it->second->OnRemove();
    delete it->second;
    m_file_map.erase(it);
}
