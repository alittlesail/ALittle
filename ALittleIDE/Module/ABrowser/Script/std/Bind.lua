
---@module ALittle
module("ALittle", package.seeall)

--[[
委托

local func = Functor(全局函数, 参数1, 参数2, 参数3, ...)
-- 执行
func(...)
local func = Functor(类实例对象.成员函数, 类实例对象, 参数1, 参数2, 参数3, ...)
-- 执行
func(...)
--]]

local select = select
local coroutine = coroutine
local assert = assert
local unpack = unpack
local tostring = tostring
local setmetatable = setmetatable
local pcall = pcall

local __functor_mt = {}
-- 设置call函数。这样创建类实例对象时，可以使用A()这样的书写方式。
__functor_mt.__call = function(caller, ...)
    -- 创建新的参数列表
    local new_arg_list = {}
    -- 获取携带参数列表
    local arg_list = caller._arg
    -- 获取携带参数个数
    local arg_count = caller._arg_count
    -- 遍历参数列表，添加到新的列表中
    for i = 1, arg_count do
        new_arg_list[i] = arg_list[i]
    end
    -- 获取调用参数个数
    local add_count = select("#", ...)
    -- 遍历调用参数列表，添加到携带参数列表中
    for i = 1, add_count do
        new_arg_list[arg_count + i] = select(i, ...)
    end
    -- 把参数列表解包，调用回调函数
    return caller._func(unpack(new_arg_list, 1, arg_count + add_count))
end

-- 设置tostring函数
__functor_mt.__tostring = function(caller)
    return "[ALittle Functor:" .. tostring(caller) .. "]"
end

function Bind(func, ...)
    -- 如果没有携带参数，那么就直接返回func
    if select("#", ...) == 0 then
        return func
    end
    -- 委托对象
    local object = {}
    -- 保存func
    object._func = func
    -- 保存参数列表
    object._arg = { ... }
    -- 保存参数个数
    object._arg_count = select("#", ...)
    -- 委托对象的metatable
    setmetatable(object, __functor_mt)
    -- 返回委托对象
    return object
end