#ifndef _ALITTLE_ALITTLESCRIPTOP_H_
#define _ALITTLE_ALITTLESCRIPTOP_H_

#include "../Guess/ALittleScriptGuess.h"

#include <string>
#include <memory>

class ALittleScriptOp8SuffixElement;
class ALittleScriptOp7SuffixElement;
class ALittleScriptOp6SuffixElement;
class ALittleScriptOp5SuffixElement;
class ALittleScriptOp4SuffixElement;
class ALittleScriptOp3SuffixElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp8StatElement;
class ALittleScriptOp7StatElement;
class ALittleScriptOp6StatElement;
class ALittleScriptOp5StatElement;
class ALittleScriptOp4StatElement;
class ALittleScriptOp3StatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptValueOpStatElement;
class ALittleScriptOp2StatElement;

class ALittleScriptOp
{
private:
    static ABnfGuessError GuessTypeForOp8Impl(const std::string& op_string
            , ABnfElementPtr left_src, ABnfGuessPtr left_guess_type
            , ABnfElementPtr right_src, ABnfGuessPtr right_guess_type
            , std::shared_ptr<ALittleScriptOp8SuffixElement> op_8_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp8(ABnfElementPtr left_src
            , ABnfGuessPtr left_guess_type
            , std::shared_ptr<ALittleScriptOp8SuffixElement> op_8_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp7Impl(const std::string& op_string
            , ABnfElementPtr left_src, ABnfGuessPtr left_guess_type
            , ABnfElementPtr right_src, ABnfGuessPtr right_guess_type
            , std::shared_ptr<ALittleScriptOp7SuffixElement> op_7_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp7(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp7SuffixElement> op_7_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp6Impl(const std::string& op_string
            , ABnfElementPtr left_src, ABnfGuessPtr left_guess_type
            , ABnfElementPtr right_src, ABnfGuessPtr right_guess_type
            , std::shared_ptr<ALittleScriptOp6SuffixElement> op_6_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp6(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp6SuffixElement> op_6_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp5Impl(const std::string& op_string
            , ABnfElementPtr left_src, ABnfGuessPtr left_guess_type
            , ABnfElementPtr right_src, ABnfGuessPtr right_guess_type
            , std::shared_ptr<ALittleScriptOp5SuffixElement> op_5_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp5(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp5SuffixElement> op_5_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp4Impl(const std::string& op_string
            , ABnfElementPtr left_src, ABnfGuessPtr left_guess_type
            , ABnfElementPtr right_src, ABnfGuessPtr right_guess_type
            , std::shared_ptr<ALittleScriptOp4SuffixElement> op_4_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp4(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp4SuffixElement> op_4_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp3(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp3SuffixElement> op_3_suffix, ABnfGuessPtr& guess);

public:
    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp8StatElement> op_8_stat, ABnfGuessPtr& guess);


    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp7StatElement> op_7_stat, ABnfGuessPtr& guess);


    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp6StatElement> op_6_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp5StatElement> op_5_stat, ABnfGuessPtr& guess);


    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp4StatElement> op_4_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp3StatElement> op_3_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypes(std::shared_ptr<ALittleScriptValueOpStatElement> value_op_stat, std::vector<ABnfGuessPtr>& guess_list);

    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptOp2ValueElement> op_2_value, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(std::shared_ptr<ALittleScriptOp2StatElement> op_2_stat, ABnfGuessPtr& guess);

    // assign_or_call 填true表示赋值，否则是函数调用的参数传递
    static ABnfGuessError GuessTypeEqual(ABnfGuessPtr left_guess, ABnfElementPtr right_src, ABnfGuessPtr right_guess, bool assign_or_call, bool is_return);
};

#endif // _ALITTLE_ALITTLESCRIPTOP_H_