
#ifndef _ALITTLE_ABNFREGEXELEMENT_H_
#define _ALITTLE_ABNFREGEXELEMENT_H_

#include "ABnfLeafElement.h"
#include "ARegex.h"

class ABnfRegexElement : public ABnfLeafElement
{
private:
    std::shared_ptr<ARegex> m_regex;

public:
    ABnfRegexElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& value, const std::shared_ptr<ARegex>& regex)
        : ABnfLeafElement(factory, file, line, col, offset, value), m_regex(regex)
    { }
    virtual ~ABnfRegexElement() = default;

    bool IsMatch(const std::string& value) const
    {
        if (m_regex == nullptr) return false;
        int length = 0;
        return m_regex->Match(value.c_str(), length);
    }
    virtual const std::string& GetLeafType() override { static std::string type = "Regex"; return type; }
};

#endif