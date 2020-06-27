
#ifndef _ALITTLE_ABNFREGEXELEMENT_H_
#define _ALITTLE_ABNFREGEXELEMENT_H_

#include "ABnfLeafElement.h"
#include <regex>

class ABnfRegexElement : public ABnfLeafElement
{
private:
    std::shared_ptr<std::regex> m_regex;

public:
    ABnfRegexElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value, std::shared_ptr<std::regex> regex)
        : ABnfLeafElement(factory, file, line, col, offset, value), m_regex(regex)
    { }
    virtual ~ABnfRegexElement() {}

    bool IsMatch(const std::string& value)
    {
        if (m_regex == nullptr) return false;
        std::smatch result;
        return std::regex_match(value, result, *m_regex);
    }
};

#endif // _ALITTLE_ABNFREGEXELEMENT_H_