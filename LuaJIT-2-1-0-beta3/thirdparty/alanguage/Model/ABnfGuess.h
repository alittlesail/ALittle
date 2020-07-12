
#ifndef _ALITTLE_ABNFGUESS_H_
#define _ALITTLE_ABNFGUESS_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <memory>

class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;
using ABnfGuessWeakPtr = std::weak_ptr<ABnfGuess>;
class ABnfFile;

class ABnfGuess : public std::enable_shared_from_this<ABnfGuess>
{
protected:
    std::string value;
    std::string value_without_const;

public:
    virtual ~ABnfGuess() {}

    bool is_const = false;

    virtual bool IsChanged() const { return true; }
    virtual const std::string& GetValue() const { return value; }
    virtual const std::string& GetValueWithoutConst() const { return value_without_const; }
    virtual void UpdateValue() { }
    virtual ABnfGuessPtr Clone() const { return nullptr; }
    virtual bool NeedReplace() const { return false; }
    virtual ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) { return nullptr; }
    virtual bool HasAny() const { return false; }
    virtual const std::string& GetTotalValue() { return value; }
};

class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
using ABnfElementWeakPtr = std::weak_ptr<ABnfElement>;

struct ABnfGuessError
{
    std::string error;
    ABnfElementPtr element;

    ABnfGuessError() {}
    ABnfGuessError(const char* p_error) : error(p_error) { }
    ABnfGuessError(std::nullptr_t t) { }
    ABnfGuessError(ABnfElementPtr p_element, const std::string& p_error) : element(p_element), error(p_error) {}
    ABnfGuessError(ABnfElementPtr p_element, const char* p_error) : element(p_element), error(p_error) {}
    operator bool() { return !error.empty(); }
};

#endif // _ALITTLE_ABNFGUESS_H_