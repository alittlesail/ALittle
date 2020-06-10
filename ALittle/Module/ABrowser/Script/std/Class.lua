
---@module ALittle
module("ALittle", package.seeall)

--[[

使Lua支持面向对象

-- 定义一个类，类名规则是首字母大写，多个单词也是首字母大写
BaseType = Class()

-- 定义构造函数
function BaseType:Ctor(x)
	print("BaseType ctor")
	self._x = x -- 成员变量的命名规则以下划线开头，小写，多个单词用下划线隔开
end

-- 定义成员函数，成员函数的命名规则是首字母大写，多个单词首也是首字母大写
function BaseType:PrintX()
	print(self._x)
end

function BaseType:Hello()
	print("hello BaseType")
end

-- 定义一个新的类，继承了BaseType
Test = Class(BaseType)

-- 定义Test的构造函数
function Test:Ctor()
	print("Test ctor")
end

function Test:Hello()
	print("hello Test")
end

-- 创建一个Test实例对象
a = Test(1)
-- 调用PrintX函数，从BaseType那边继承来的
a:PrintX()
-- 调用Hellow，Test自己定义的，它重写了BaseType的Hello函数
a:Hello()

--]]


--[[
class_type : 类型的基本属性
	-- __super : 该类型的父类
	-- Ctor : 该类的构造函数
	-- __setter : setter 函数集合
	-- __getter : getter 函数集合

注意：成员变量使用"_"开头

object : 实例对象
	-- __class : 该实例对象的类型
--]]

local setmetatable = setmetatable
local rawget = rawget
local rawset = rawset
local tostring = tostring
local pairs = pairs
local type = type
local table = table

-- 记录所有的类模版
local __all_class = {}
-- 这里设置弱引用，当某些类不在被使用之后，这个地方不会持有
setmetatable(__all_class, { __mode = "k" })

-- 从对象里面取值
local __object_index_function
__object_index_function = function(object, key)
    -- 先判断是否在class，有则查找
    local class = rawget(object, "__class")

    -- 如果没有那么判断是否有getter (比如获取属性_x，那么函数名为__getter:x)
    local getter = class.__getter[key]
    if getter then
        return getter(object)
    end

    -- 取到的值，一般情况下都是funciton
    local value = class[key]
    if value then
        -- 保存起来，便于快速查找
        rawset(object, key, value)
        -- 返回值
        return value
    end

    -- 没有的话，就是没有了
    return nil
end

-- 把值设置到对象里面
local __object_newindex_function
__object_newindex_function = function(object, key, value)
    -- 获取class
    local class = rawget(object, "__class")
    -- 判断是否有setter (比如设置属性_x，那么函数名为__setter:x)
    local setter = class.__setter[key]
    if setter then
        setter(object, value)
        return
    end

    -- 如果没有就只能设置属性
    rawset(object, key, value)
end

local __object_tostring_function
__object_tostring_function = function(object)
    local class = rawget(object, "__class")
    return "[ALittle Object:" .. tostring(class.__name or "not set class name") .. "]"
end

-- 创建所有实例对象的元表
local __object_mt = {}
__object_mt.__index = __object_index_function
__object_mt.__newindex = __object_newindex_function
__object_mt.__tostring = __object_tostring_function

-- 递归调用构造函数
local __class_create_function
__class_create_function = function(class, object, ...)
    -- 检查是否有父类，如果有则调用父类的构造函数。
    local super = rawget(class, "__super")
    if super then
        __class_create_function(super, object, ...)
    end
    -- 如果当前类有定义Ctor函数，则调用。
    local Ctor = rawget(class, "Ctor")
    if Ctor then
        Ctor(object, ...)
    end
end

-- 从类模板里面取值
local __class_index_function
__class_index_function = function(class, key)
    -- 能执行到这里，说明class本身没有，那么到父类里面找
    local super = rawget(class, "__super")
    -- 如果没有父类，那么就直接返回
    if super == nil then
        return nil
    end
    -- 获取值
    local value = super[key]
    -- 保存起来，便于快速查找
    rawset(class, key, value)
    -- 返回结果
    return value
end

local __class_call_function
__class_call_function = function(class, ...)
    -- 创建类实例对象
    local object = {}
    -- 保存类
    object.__class = class
    -- 设置实例对象的元表
    setmetatable(object, __object_mt)
    -- 向父类模版递归调用Ctor函数。这里模拟C++的构造函数。
    __class_create_function(class, object, ...)
    -- 返回创建的实例对象
    return object
end

local __class_tostring_function
__class_tostring_function = function(class)
    return "[ALittle Class:" .. tostring(class.__name or "not set class name") .. "]"
end

-- 创建所有类的元表
local __class_mt = {}
__class_mt.__index = __class_index_function
__class_mt.__call = __class_call_function
__class_mt.__tostring = __class_tostring_function

-- 定义类
-- 参数super 父类对象
-- 参数name 类名字
function Class(super, name)
    -- 定义类模版
    local class = {}
    -- 设置类模版的父类模版
    class.__super = super
    -- 设置类模版的类名
    class.__name = name
    -- 设置属性映射表函数
    local setter = {}
    local getter = {}
    if super then
        for k, v in pairs(super.__setter) do
            setter[k] = v
        end
        for k, v in pairs(super.__getter) do
            getter[k] = v
        end
    end
    class.__setter = setter
    class.__getter = getter
    -- 设置类模版的元表
    setmetatable(class, __class_mt)
    -- 保存类定义
    __all_class[class] = true
    -- 返回类模版
    return class
end

-- 检查某个对象是否是这个类
function InstanceOf(object, clazz)
    if (type(object) ~= "table") then return false end
    return object.__class == clazz
end

-- 检查是否是类
function IsClass(object)
    if (type(object) ~= "table") then return false end
    return object.__class ~= nil    
end

-- 创建对象
function NewObject(clazz, ...)
    return clazz(...);
end

-- 获取类名
function GetClassName(object)
    if (not IsClass(object)) then return nil end
    return object.__class.__name
end

-- 获取类
function GetClass(object)
    return object.__class;
end
-- 获取类的getter集合
function GetClassGetter(clazz)
    local list = {};
    local count = 0;
    for k, v in pairs(clazz.__getter) do
        count = count + 1;
        list[count] = k;
    end
    return list;
end
-- 获取类的setter集合
function GetClassSetter(clazz)
    local list = {};
    local count = 0;
    for k, v in pairs(clazz.__setter) do
        count = count + 1;
        list[count] = k;
    end
    return list;
end

-- 创建一张空表
function CreateTable()
    return {}
end

-- 设置弱引用
function SetWeak(object, key, value)
    local mode = ""
    if key then mode = "k" end
    if value then mode = mode.."v" end
    setmetatable(object, { __mode = mode })
end

-- 表尾部添加元素
function ListPush(object, value)
    table.insert(object, value)
end
