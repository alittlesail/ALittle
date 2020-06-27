
#ifndef _ALITTLE_ABNFGUESS_H_
#define _ALITTLE_ABNFGUESS_H_

#include <string>
#include <memory>
#include <unordered_map>

class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;

class ABnfGuess
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
    virtual ABnfGuessPtr ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) const { return nullptr; }
    virtual bool HasAny() const { return false; }
    virtual const std::string& GetTotalValue() const { return value; }
};

class ABnfElement;
using ABnfElementPtr = std::shared_ptr<ABnfElement>;
using ABnfElementWeakPtr = std::weak_ptr<ABnfElement>;

struct ABnfGuessError
{
    std::string error;
    ABnfElementPtr element;
};

#endif // _ALITTLE_ABNFGUESS_H_