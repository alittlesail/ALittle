
#ifndef _ALITTLE_ALITTLESCRIPTGUESSPRIMITIVE_H_
#define _ALITTLE_ALITTLESCRIPTGUESSPRIMITIVE_H_

#include "ALittleScriptGuess.h"

#include <map>

class ALittleScriptGuessPrimitive : public ALittleScriptGuess
{
private:
    std::string native_value = "";

public:
    ALittleScriptGuessPrimitive(const std::string& p_value, bool p_is_const);

    bool HasAny() const override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue()override;
    bool IsChanged() const override { return false; }
};

class ALittleScriptGuessBool : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessBool(bool p_is_const) : ALittleScriptGuessPrimitive("bool", p_is_const) { }
    ABnfGuessPtr Clone() const override { return ABnfGuessPtr(new ALittleScriptGuessBool(is_const)); }
};

class ALittleScriptGuessInt : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessInt(bool p_is_const) : ALittleScriptGuessPrimitive("int", p_is_const) { }
    ABnfGuessPtr Clone() const override { return ABnfGuessPtr(new ALittleScriptGuessInt(is_const)); }
};

class ALittleScriptGuessLong : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessLong(bool p_is_const) : ALittleScriptGuessPrimitive("long", p_is_const) { }
    ABnfGuessPtr Clone() const override { return ABnfGuessPtr(new ALittleScriptGuessLong(is_const)); }
};

class ALittleScriptGuessDouble : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessDouble(bool p_is_const) : ALittleScriptGuessPrimitive("double", p_is_const) { }
    ABnfGuessPtr Clone() const override { return ABnfGuessPtr(new ALittleScriptGuessDouble(is_const)); }
};

class ALittleScriptGuessString : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessString(bool p_is_const) : ALittleScriptGuessPrimitive("string", p_is_const) { }
    ABnfGuessPtr Clone() const override { return ABnfGuessPtr(new ALittleScriptGuessString(is_const)); }
};

class ALittleScriptGuessAny : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessAny(bool p_is_const) : ALittleScriptGuessPrimitive("any", p_is_const) { }
    ABnfGuessPtr Clone() const override { return ABnfGuessPtr(new ALittleScriptGuessAny(is_const)); }
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSPRIMITIVE_H_
