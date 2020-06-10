
---@module ALittle
module("ALittle", package.seeall)

local table = table
local tostring = tostring
local select = select
local print = print

-- 设置打印的回调函数
local log = nil
function SetLogCallback(func)
    log = func
end

LogLevel =
{
    INFO = 0,
    WARN = 1,
    ERROR = 2,
}

-- 日志函数
function Log(...)
    -- 创建列表
    local new_arg = {}
    -- 获取参数个数
    local arg_count = select("#", ...)
    -- 遍历参数
    for i = 1, arg_count do
        -- 把参数变成字符串添加到列表中
        table.insert(new_arg, tostring(select(i, ...)))
    end
    -- 打印出来
    if log == nil then
        print(table.concat(new_arg, "\t"))
    else
        log(table.concat(new_arg, "\t"), 0)
    end
end

-- 日志函数
function Warn(...)
    -- 创建列表
    local new_arg = {}
    -- 获取参数个数
    local arg_count = select("#", ...)
    -- 遍历参数
    for i = 1, arg_count do
        -- 把参数变成字符串添加到列表中
        table.insert(new_arg, tostring(select(i, ...)))
    end
    -- 打印出来
    if log == nil then
        print(table.concat(new_arg, "\t"))
    else
        log(table.concat(new_arg, "\t"), 1)
    end
end

-- 日志函数
function Error(...)
    -- 创建列表
    local new_arg = {}
    -- 获取参数个数
    local arg_count = select("#", ...)
    -- 遍历参数
    for i = 1, arg_count do
        -- 把参数变成字符串添加到列表中
        table.insert(new_arg, tostring(select(i, ...)))
    end
    -- 打印出来
    if log == nil then
        print(table.concat(new_arg, "\t"))
    else
        log(table.concat(new_arg, "\t"), 2)
    end
end