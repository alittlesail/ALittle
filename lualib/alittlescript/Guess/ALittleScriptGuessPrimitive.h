
#ifndef _ALITTLE_ALITTLESCRIPTGUESSPRIMITIVE_H_
#define _ALITTLE_ALITTLESCRIPTGUESSPRIMITIVE_H_

#include "ALittleScriptGuess.h"

class ALittleScriptGuessPrimitive : public ALittleScriptGuess
{
private:
    std::string native_value = "";

public:
    ALittleScriptGuessPrimitive(const std::string& p_value, bool p_is_const);

    bool HasAny() const override;
    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    void UpdateValue()override;
    bool IsChanged() const override { return false; }
};

class ALittleScriptGuessBool : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessBool(bool p_is_const) : ALittleScriptGuessPrimitive("bool", p_is_const) { }
    ABnfGuessPtr Clone() const override { return std::make_shared<ALittleScriptGuessBool>(is_const); }
};

class ALittleScriptGuessInt : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessInt(bool p_is_const) : ALittleScriptGuessPrimitive("int", p_is_const) { }
    ABnfGuessPtr Clone() const override { return std::make_shared<ALittleScriptGuessInt>(is_const); }
};

class ALittleScriptGuessLong : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessLong(bool p_is_const) : ALittleScriptGuessPrimitive("long", p_is_const) { }
    ABnfGuessPtr Clone() const override { return std::make_shared<ALittleScriptGuessLong>(is_const); }
};

class ALittleScriptGuessDouble : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessDouble(bool p_is_const) : ALittleScriptGuessPrimitive("double", p_is_const) { }
    ABnfGuessPtr Clone() const override { return std::make_shared<ALittleScriptGuessDouble>(is_const); }
};

class ALittleScriptGuessString : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessString(bool p_is_const) : ALittleScriptGuessPrimitive("string", p_is_const) { }
    ABnfGuessPtr Clone() const override { return std::make_shared<ALittleScriptGuessString>(is_const); }
};

class ALittleScriptGuessAny : public ALittleScriptGuessPrimitive
{
public:
    ALittleScriptGuessAny(bool p_is_const) : ALittleScriptGuessPrimitive("any", p_is_const) { }
    ABnfGuessPtr Clone() const override { return std::make_shared<ALittleScriptGuessAny>(is_const); }
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSPRIMITIVE_H_
