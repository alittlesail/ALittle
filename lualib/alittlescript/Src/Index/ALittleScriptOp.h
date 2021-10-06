﻿#ifndef _ALITTLE_ALITTLESCRIPTOP_H_
#define _ALITTLE_ALITTLESCRIPTOP_H_

#include "../Guess/ALittleScriptGuess.h"

#include <string>
#include <memory>

class ALittleScriptOp12SuffixElement;
class ALittleScriptOp11SuffixElement;
class ALittleScriptOp10SuffixElement;
class ALittleScriptOp9SuffixElement;
class ALittleScriptOp8SuffixElement;
class ALittleScriptOp7SuffixElement;
class ALittleScriptOp6SuffixElement;
class ALittleScriptOp5SuffixElement;
class ALittleScriptOp4SuffixElement;
class ALittleScriptOp3SuffixElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp12StatElement;
class ALittleScriptOp11StatElement;
class ALittleScriptOp10StatElement;
class ALittleScriptOp9StatElement;
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
    static ABnfGuessError GuessTypeForOp12Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp12SuffixElement>& op_12_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp12(const ABnfElementPtr& left_src
        , const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp12SuffixElement>& op_12_suffix
        , ABnfGuessPtr& guess);

	
    static ABnfGuessError GuessTypeForOp11Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp11SuffixElement>& op_11_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp11(const ABnfElementPtr& left_src
        , const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp11SuffixElement>& op_11_suffix
        , ABnfGuessPtr& guess);

	
    static ABnfGuessError GuessTypeForOp10Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp10SuffixElement>& op_10_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp10(const ABnfElementPtr& left_src
        , const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp10SuffixElement>& op_10_suffix
        , ABnfGuessPtr& guess);

	
    static ABnfGuessError GuessTypeForOp9Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp9SuffixElement>& op_9_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp9(const ABnfElementPtr& left_src
        , const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp9SuffixElement>& op_9_suffix
        , ABnfGuessPtr& guess);

	
    static ABnfGuessError GuessTypeForOp8Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp8SuffixElement>& op_8_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp8(const ABnfElementPtr& left_src
        , const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp8SuffixElement>& op_8_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp7Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp7SuffixElement>& op_7_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp7(const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp7SuffixElement>& op_7_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp6Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp6SuffixElement>& op_6_suffix
        , ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypeForOp6(const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp6SuffixElement>& op_6_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp5Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp5SuffixElement>& op_5_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp5(const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp5SuffixElement>& op_5_suffix, ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp4Impl(const std::string& op_string
        , const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const ABnfElementPtr& right_src, const ABnfGuessPtr& right_guess_type
        , const std::shared_ptr<ALittleScriptOp4SuffixElement>& op_4_suffix
        , ABnfGuessPtr& guess);


    static ABnfGuessError GuessTypeForOp4(const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp4SuffixElement>& op_4_suffix, ABnfGuessPtr& guess);

	
    static ABnfGuessError GuessTypeForOp3(const ABnfElementPtr& left_src, const ABnfGuessPtr& left_guess_type
        , const std::shared_ptr<ALittleScriptOp3SuffixElement>& op_3_suffix, ABnfGuessPtr& guess);

public:
    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
									const std::shared_ptr<ALittleScriptOp12StatElement>& op_12_stat, ABnfGuessPtr& guess);
	
    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
									const std::shared_ptr<ALittleScriptOp11StatElement>& op_11_stat, ABnfGuessPtr& guess);
	
    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
									const std::shared_ptr<ALittleScriptOp10StatElement>& op_10_stat, ABnfGuessPtr& guess);
	
    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
									const std::shared_ptr<ALittleScriptOp9StatElement>& op_9_stat, ABnfGuessPtr& guess);
	
    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
                                    const std::shared_ptr<ALittleScriptOp8StatElement>& op_8_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
                                    const std::shared_ptr<ALittleScriptOp7StatElement>& op_7_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
                                    const std::shared_ptr<ALittleScriptOp6StatElement>& op_6_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
                                    const std::shared_ptr<ALittleScriptOp5StatElement>& op_5_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
                                    const std::shared_ptr<ALittleScriptOp4StatElement>& op_4_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptValueFactorStatElement>& value_factor_stat,
                                    const std::shared_ptr<ALittleScriptOp3StatElement>& op_3_stat, ABnfGuessPtr& guess);

    static ABnfGuessError GuessTypes(const std::shared_ptr<ALittleScriptValueOpStatElement>& value_op_stat, std::vector<ABnfGuessPtr>& guess_list);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptOp2ValueElement>& op_2_value, ABnfGuessPtr& guess);

    static ABnfGuessError GuessType(const std::shared_ptr<ALittleScriptOp2StatElement>& op_2_stat, ABnfGuessPtr& guess);

    // assign_or_call 填true表示赋值，否则是函数调用的参数传递
    static ABnfGuessError GuessTypeEqual(const ABnfGuessPtr& left_guess, const ABnfElementPtr& right_src, ABnfGuessPtr right_guess, bool assign_or_call, bool is_return);
};

#endif // _ALITTLE_ALITTLESCRIPTOP_H_