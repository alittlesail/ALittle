
#ifndef _ALITTLE_ALANGUAGECOMPLETIONINFO_H_
#define _ALITTLE_ALANGUAGECOMPLETIONINFO_H_

#include <memory>
#include <regex>

#include "alanguage/Src/Model/ABnfGuess.h"
#include "alanguage/Src/Model/ARegex.h"

class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
class ABnfKeyElement;
using ABnfKeyElementPtr = std::shared_ptr<ABnfKeyElement>;
class ABnfStringElement;
using ABnfStringElementPtr = std::shared_ptr<ABnfStringElement>;
class ABnfRegexElement;
using ABnfRegexElementPtr = std::shared_ptr<ABnfRegexElement>;
class ABnfNodeElement;
using ABnfNodeElementPtr = std::shared_ptr<ABnfNodeElement>;
class ABnfFile;
struct ABnfGuessError;
class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;
class ABnfProject;
class ABnfReference;

class ABnfFactory
{
public:
    virtual ~ABnfFactory() = default;

    virtual ABnfNodeElementPtr CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type);

    virtual ABnfKeyElementPtr CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type);

    virtual ABnfStringElementPtr CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type);

    virtual ABnfRegexElementPtr CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, const std::shared_ptr<ARegex>& regex);

    virtual ABnfReference* CreateReference(const ABnfElementPtr& element);

    virtual ABnfGuessError GuessTypes(const ABnfElementPtr& element, std::vector<ABnfGuessPtr>& guess_list) { return "no implement"; }

public:
    virtual ABnfFile* CreateFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len);

private:
    template <typename T>
    static void AddElement(T& list, const std::string& v) { list.push_back(v); }
    static void AddElement(std::list<int>& list, const std::string& v) { list.push_back(std::atoi(v.c_str())); }  // NOLINT(cert-err34-c)
    static void AddElement(std::vector<int>& list, const std::string& v) { list.push_back(std::atoi(v.c_str())); }  // NOLINT(cert-err34-c)

public:
    // �и��ַ���
    template <typename T>
    static void Split(const std::string& content, const std::string& split, T& list)
    {
        list.resize(0);
        if (content.size() == 0) return;

        size_t start_index = 0;
        while (true)
        {
            const size_t pos = content.find(split, start_index);
            if (pos != std::string::npos)
            {
                AddElement(list, content.substr(start_index, pos - start_index));
                start_index = pos + split.size();
                continue;
            }
            break;
        }

        if (start_index == 0)
            AddElement(list, content);
        else
            AddElement(list, content.substr(start_index));
    }

private:
    template <typename T>
    static void AddString(std::string& result, const T& v) { result.append(std::to_string(v)); }
    static void AddString(std::string& result, const std::string& v) { result.append(v); }

public:
    // ƴ���ַ���
    template <typename T>
    static std::string Join(const T& container, const std::string& split)
    {
        std::string result;
        size_t count = 0;
        for (auto it = container.begin(); it != container.end(); ++it)
        {
            ++count;
            AddString(result, *it);
            if (count != container.size())
                result.append(split);

        }
        return result;
    }

    // �滻�ַ���
    static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    
    // д���ļ�
    static bool WriteAllText(const std::string& file_path, const std::string& content);
};

#endif