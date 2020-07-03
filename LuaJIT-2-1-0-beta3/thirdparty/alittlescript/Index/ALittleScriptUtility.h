
#ifndef _ALITTLE_ALITTLESCRIPTUTILITY_H_
#define _ALITTLE_ALITTLESCRIPTUTILITY_H_

#include <string>
#include <memory>
#include <vector>

class ALittleScriptNumberElement;
class ALittleScriptGuessStruct;
class ALittleScriptModifierElement;
class ABnfElement;
struct ABnfGuessError;
class ABnfFile;
class ALittleScriptNamespaceDecElement;
class ALittleScriptNamespaceNameDecElement;
class ALittleScriptClassDecElement;
class ALittleScriptTemplateDecElement;

// 类的属性类型
enum class ClassAttrType
{
    VAR,            // 成员变量
    FUN,            // 成员函数
    GETTER,         // getter函数
    SETTER,         // setter函数
    STATIC,         // 静态函数
    TEMPLATE,       // 模板参数
};

// 访问权限类型
enum class ClassAccessType
{
    PUBLIC,         // 全局可访问
    PROTECTED,      // 本命名域可访问
    PRIVATE,        // 本类可访问
};

// 元素类型
enum class ABnfElementType
{
    CLASS_NAME,         // 类名
    ENUM_NAME,          // 枚举名
    STRUCT_NAME,        // 结构体名
    INSTANCE_NAME,      // 单例名
    GLOBAL_METHOD,      // 全局函数
    USING_NAME,         // using名
};

class ALittleScriptUtility
{
public:
	// 创建文件夹
	static void CreateFolder(const std::string& path);

	// 递归创建文件夹
	static void CreateDeepFolder(const std::string& path);

    // 判断文件是否存在
    static bool IsFileExist(const std::string& path);

    // 判断文件是否存在
    static bool IsDirExist(const std::string& path);

    // 获取文件夹下的所有文件
    enum class NameType
    {
        NT_ALL,
        NT_FILE,
        NT_DIR,
    };
    static void GetNameListInFolder(const std::string& path, NameType type, std::vector<std::string>& out);

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
    static bool CheckInvokeAwaitError(std::shared_ptr<ABnfElement> element, ABnfGuessError& error);

    // 判断是否存在
    static bool CheckError(std::shared_ptr<ABnfElement> parent, const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, ABnfGuessError& error);

    // 获取是否是register
    static bool IsRegister(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取是否是Const
    static bool IsConst(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取是否是Nullable
    static bool IsNullable(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list);

    // 获取协程类型
    static bool GetCoroutineType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& out);

    // 获取协议类型
    static bool GetProtocolType(const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& element_list, std::string& out);

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
};

#endif // _ALITTLE_ALITTLESCRIPTUTILITY_H_
