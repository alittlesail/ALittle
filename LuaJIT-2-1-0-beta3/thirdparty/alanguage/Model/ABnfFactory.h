
#ifndef _ALITTLE_ALANGUAGECOMPLETIONINFO_H_
#define _ALITTLE_ALANGUAGECOMPLETIONINFO_H_

#include <memory>
#include <regex>
#include <unordered_map>

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
class ABnf;
using ABnfPtr = std::shared_ptr<ABnf>;

class ABnfFactory
{
public:
    virtual ~ABnfFactory() {}

    virtual ABnfNodeElementPtr CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type);

    virtual ABnfKeyElementPtr CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type);

    virtual ABnfStringElementPtr CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type);

    virtual ABnfRegexElementPtr CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, std::shared_ptr<std::regex> regex);

    virtual ABnfReference* CreateReference(ABnfElementPtr element);

    virtual bool GuessTypes(ABnfElementPtr element, std::vector<ABnfGuessPtr>& guess_list, ABnfGuessError& error) { error.error = "no implement"; return false; }

    // ÎÄ¼þºó×º
    virtual std::string GetDotExt() { return ""; }

    virtual std::string LoadABnf() { return ""; }

    virtual bool FastGoto(const std::unordered_map<std::string, ABnfProject*>& projects, const std::string& text, std::string& error) { error = "no implement FastGoto"; return false; }

    virtual ABnfFile* CreateABnfFile(const std::string& full_path, ABnfPtr abnf, const std::string& text) { return nullptr; }

    virtual ABnfProject* CreateProjectInfo(ABnfFactory* factory, ABnfPtr abnf, const std::string& path) { return nullptr; }
};

#endif // _ALITTLE_ALANGUAGECOMPLETIONINFO_H_