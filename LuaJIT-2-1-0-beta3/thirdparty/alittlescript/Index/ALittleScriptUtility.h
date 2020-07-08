
#ifndef _ALITTLE_ALITTLESCRIPTUTILITY_H_
#define _ALITTLE_ALITTLESCRIPTUTILITY_H_

#include <string>
#include <memory>
#include <vector>

#include "ALittleScriptDefine.h"

class ALittleScriptNumberElement;
class ALittleScriptGuessStruct;
class ALittleScriptModifierElement;
class ABnfElement;
struct ABnfGuessError;
class ABnfFile;
class ABnfGuess;
using ABnfGuessPtr = std::shared_ptr<ABnfGuess>;
class ALittleScriptNamespaceDecElement;
class ALittleScriptNamespaceNameDecElement;
class ALittleScriptClassDecElement;
class ALittleScriptTemplateDecElement;
class ALittleScriptStructDecElement;
class ALittleScriptStructVarDecElement;
class ALittleScriptEnumDecElement;
class ALittleScriptEnumVarDecElement;
class ALittleScriptVarAssignNameDecElement;
class ALittleScriptClassCtorDecElement;
class ALittleScriptMethodParamNameDecElement;
class ALittleScriptForExprElement;
class ALittleScriptForConditionElement;
class ALittleScriptAllExprElement;
class ALittleScriptValueStatElement;

class ALittleScriptUtility
{
public:
    // 删除左边的空格
    static void TrimLeft(std::string& target);

    // 删除右边的空格
    static void TrimRight(std::string& target);

	// 创建文件夹
	static void CreateFolder(const std::string& path);

	// 递归创建文件夹
	static void CreateDeepFolder(const std::string& path);

    // 判断文件是否存在
    static bool IsFileExist(const std::string& path);

    // 判断文件是否存在
    static bool IsDirExist(const std::string& path);

    // 获取文件夹下的所有文件
    static void GetNameListInFolder(const std::string& path, std::vector<std::string>& file_list, std::vector<std::string>& dir_list);

    // 改变扩展名
    static std::string ChangeFileExtByPath(const std::string& file_path, const std::string& ext);

    // 判断字符串是不是整型值
	static bool IsInt(const std::shared_ptr<ALittleScriptNumberElement>& element);

    // 计算哈希值
	static int JSHash(const std::string& content);

	// 计算结构体的哈希值
	static int StructHash(const std::shared_ptr<ALittleScriptGuessStruct>& guess);

    // 语言判定
    static bool IsLanguageEnable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 是否使用原生
    static bool IsNative(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 检查await
    static ABnfGuessError CheckInvokeAwait(std::shared_ptr<ABnfElement> element);

    // 判断是否存在
    static ABnfGuessError CheckError(std::shared_ptr<ABnfElement> parent, const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取是否是register
    static bool IsRegister(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取是否是Const
    static bool IsConst(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取是否是Nullable
    static bool IsNullable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取协程类型
    static std::string GetCoroutineType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取协议类型
    static std::string GetProtocolType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取命令类型
    static bool GetCommandDetail(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& cmd, std::string& desc);

    // 获取访问权限类型
    static ClassAccessType CalcAccessType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 访问权限等级
    static const int sAccessOnlyPublic = 1;                    // 可以访问public的属性和方法
    static const int sAccessProtectedAndPublic = 2;            // 可以访问public protected的属性和方法
    static const int sAccessPrivateAndProtectedAndPublic = 3;  // 可以public protected private的属性和方法

    // 获取某个元素的命名域对象
    static std::shared_ptr<ALittleScriptNamespaceDecElement> GetNamespaceDec(ABnfFile* file);

    // 获取某个元素的命名域名对象
    static std::shared_ptr<ALittleScriptNamespaceNameDecElement> GetNamespaceNameDec(ABnfFile* file);

    // 判断某个是不是register
    static bool IsRegister(std::shared_ptr<ABnfElement> element);

    // 获取某个元素的命名域名
    static const std::string& GetNamespaceName(std::shared_ptr<ABnfElement> element);

    // 获取命名域名
    static const std::string& GetNamespaceName(ABnfFile* file);

    // 获取这个元素所在的类
    static std::shared_ptr<ALittleScriptClassDecElement> FindClassDecFromParent(std::shared_ptr<ABnfElement> dec);

    // 获取这个元素所在的函数模板
    static std::shared_ptr<ALittleScriptTemplateDecElement> FindMethodTemplateDecFromParent(std::shared_ptr<ABnfElement> dec);

    // 检查是否在静态函数中
    static bool IsInClassStaticMethod(std::shared_ptr<ABnfElement> dec);

    // 根据名称，获取这个结构体的成员列表
    static void FindStructVarDecList(std::shared_ptr<ALittleScriptStructDecElement> dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& result, int deep);

    // 根据名称，获取这个枚举中的成员
    static void FindEnumVarDecList(std::shared_ptr<ALittleScriptEnumDecElement> dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& result);

    // 计算struct的父类
    static std::shared_ptr<ALittleScriptStructDecElement> FindStructExtends(std::shared_ptr<ALittleScriptStructDecElement> dec);

    // 计算class的父类
    static std::shared_ptr<ALittleScriptClassDecElement> FindClassExtends(std::shared_ptr<ALittleScriptClassDecElement> dec);

    // 过滤名称相同的元素
    static void FilterSameName(const std::vector<std::shared_ptr<ABnfElement>>& list, std::vector<std::shared_ptr<ABnfElement>>& out);


    // 计算在dec这个类中，对targetDec成员的访问权限
    static int CalcAccessLevelByTargetClassDec(int access_level, std::shared_ptr<ALittleScriptClassDecElement> dec, std::shared_ptr<ALittleScriptClassDecElement> target_dec);

    // 计算任意元素访问targetDec的访问权限
    static int CalcAccessLevelByTargetClassDecForElement(std::shared_ptr<ABnfElement> element, std::shared_ptr<ALittleScriptClassDecElement> target_dec);

    // 根据名称，获取函数列表
    static void FindClassMethodNameDecList(std::shared_ptr<ALittleScriptClassDecElement> dec, int access_level, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result, int deep);

    // 根据名称，获取类的属性列表
    static void FindClassAttrList(std::shared_ptr<ALittleScriptClassDecElement> dec
        , int access_level, ClassAttrType attr_type, const std::string& name, std::vector<std::shared_ptr<ABnfElement>>& result, int deep);

    // 根据名称，获取继承的构造函数
    static std::shared_ptr<ALittleScriptClassCtorDecElement> FindFirstCtorDecFromExtends(std::shared_ptr<ALittleScriptClassDecElement> dec, int deep);

    // 根据名称，获取继承的属性
    static std::shared_ptr<ABnfElement> FindFirstClassAttrFromExtends(std::shared_ptr<ALittleScriptClassDecElement> dec, ClassAttrType attr_type, const std::string& name, int deep);

    // 根据名称，查找函数的参数列表
    static void FindMethodParamNameDecList(std::shared_ptr<ABnfElement> method_dec, const std::string& name, std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>>& result);

    // 根据名称，查找变量名所在的定义元素
    static void FindVarAssignNameDecList(std::shared_ptr<ABnfElement> element, const std::string& name, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result);

    static void FindVarAssignNameDecList(std::shared_ptr<ALittleScriptForExprElement> for_expr, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name);
    
    static void FindVarAssignNameDecList(std::shared_ptr<ALittleScriptForConditionElement> for_condition, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name);

    // 根据名称，查找定义表达式名列表
    static void FindVarAssignNameDecList(std::shared_ptr<ALittleScriptAllExprElement> all_expr, std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>>& result, const std::string& name);

    // 检查迭代函数
    static bool IsPairsFunction(const std::vector<ABnfGuessPtr>& guess_list);

    // 计算表达式需要使用什么样的变量方式
    static ABnfGuessError CalcPairsTypeForLua(std::shared_ptr<ALittleScriptValueStatElement> value_stat, std::string& result);

    // 计算表达式在for中使用in还是of
    static ABnfGuessError CalcPairsTypeForJavaScript(std::shared_ptr<ALittleScriptValueStatElement> value_stat, std::string& result, bool& is_native);

    // 判断 parent是否是child的父类
    static ABnfGuessError IsClassSuper(std::shared_ptr<ALittleScriptClassDecElement> child, const std::string& parent, bool& result);

    // 判断 parent是否是child的父类
    static ABnfGuessError IsStructSuper(std::shared_ptr<ABnfElement> child, const std::string& parent, bool& result);

    // 获取目标根路径
    static std::string CalcRootFullPath(const std::string& project_path, const std::string& ext);

    // 获取目标文件路径
    static std::string CalcTargetFullPath(const std::string& project_path, const std::string& ali_full_path, const std::string& ext, std::string& error);

    // 判断ValueStat
    static ABnfGuessError CalcReturnCount(std::shared_ptr<ALittleScriptValueStatElement> value_stat, int& count, std::vector<ABnfGuessPtr>& guess_list);
};

#endif // _ALITTLE_ALITTLESCRIPTUTILITY_H_
