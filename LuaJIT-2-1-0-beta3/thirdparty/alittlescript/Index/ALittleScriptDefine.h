
#ifndef _ALITTLE_ALITTLESCRIPTDEFINE_H_
#define _ALITTLE_ALITTLESCRIPTDEFINE_H_

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

#endif // _ALITTLE_ALITTLESCRIPTDEFINE_H_
