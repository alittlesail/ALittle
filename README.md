
## ALittleScript是什么
ALittleScript是一门兼顾强类型和弱类型的语言。

## ALittleScript的设计目标
* 它是以生成`Lua`为目标的强类型语言，类比`TypeScript`生成`JavaScript`。
* 它也可以生成`JavaScript`。
* 最终以生成的目标语言来运行，所以目标语言所有的已有资源和代码都可以无缝对接使用。
* `一次编写，多平台运行`。
* 代码文件以alittle为后缀，比如`Main.alittle`。
* 满足所有现代语言的特点，并且选用最为简单直接的语法。
* 严格的类型检查，提高编写效率。

## 安装环境

* 安装[Visual Studio](https://visualstudio.microsoft.com/zh-hans/vs/)(2015、2017、2019)
* 安装[ALittleScript.vsix](https://github.com/alittlesail/ALittle/blob/master/ALittleScript.vsix)语言插件
* 选择目标语言：打开Visula Studio->工具->选项->ALittleScript->General->目标语言->Lua或者JavaScript
* 当修改某个文件后进行保存时，会生成目标语言。
* 组合键Ctrl+F7，可以对某个alittle文件进行生成目标语言
* 组合键Ctrl+B， 可以对某个alittle所在的工程中所有的alittle文件进行生成目标语言

## Hello World
* 使用Git拉去当前项目
* 使用Visual Studio打开Module/ALittleIDE/Other/GameLibrary/ALittle.sln
* 已经内置两个工程Core和HelloWorld
* Core是语言标准库，今后的每个sln都要包含它
* HelloWorld项目只有一个文件Main.alittle，内部有一个Main函数打印了Hello World
* Lua版本
  * 把目标语言设置为Lua
  * 打开Core项目的ALittle.alittle文件，然后按组合键Ctrl+B，语言插件就可以生成lua文件到Script文件夹
  * 打开HelloWorld项目Main.alittle文件，然后按组合键Ctrl+B，语言插件就可以生成lua文件到Script文件夹
  * 使用浏览器打开HelloWorld.html。按F12打开浏览器调试界面，就可以看到HelloWorld
  * ![HelloWorld](https://github.com/alittlesail/ALittle/blob/master/Module/ALittleIDE/Other/GameLibrary/HelloWorld/HelloWorld.lua.png)
* JavaScript版本
  * 把目标语言设置为JavaScript
  * 打开Core项目的ALittle.alittle文件，然后按组合键Ctrl+B，语言插件就可以生成js文件到JSScript文件夹
  * 打开HelloWorld项目Main.alittle文件，然后按组合键Ctrl+B，语言插件就可以生成js文件到JSScript文件夹
  * 运行HelloWorld.bat。就可以看到HelloWorld
  * ![HelloWorld](https://github.com/alittlesail/ALittle/blob/master/Module/ALittleIDE/Other/GameLibrary/HelloWorld/HelloWorld.js.png)
  
# 语言快速入门

## 命名域 namespace
* 每个文件开头必须定义命名域，比如namespace HelloWorld;
* 所有代码相关的定义都会在命名域内
* lua, javascript, alittle属于内置命名域，不能作为开发者使用。这些命名域内部的定义属于全局
## 基本变量类型
* any, bool, int, long, string
## 内置模板容器
* List 数组容器，因为ALittle是以生成Lua语言为主，所以`下标也是从1开始`
* Map 映射表容器
## 高级类型
* struct 结构体, 支持继承
* enum 枚举类型
* class 单继承, 多态, 封装
## 访问权限修饰符
* private(本文件范围可访问，如果修饰类成员类自己和子类可访问)
* protected(本命名域范围可访问)
* public(全局可访问)
## 流程控制
* 条件跳转  if, elseif, else
* while
* do while
* for, for in
## 基本运算符
* 加法(+), 减法(-), 乘法(\*), 除法(/), 取模(%), 字符串连接(..)
## 逻辑运算符
* ==, !=, >, <, >=, <=
## 异常处理
* 断言 assert
* 抛异常 throw
* 保护调用 tcall
## Functor, bind
* 定义函数格式，并且任意函数可以进行携带参数绑定
## setter和getter
* 类成员函数可以定义为setter和getter
## 模板类，类比Java的模板
* 定义class时可以定义一些模板参数，在实例化时要带上填充的模板参数
## 模板函数，类比Java的模板
* 对成员函数、类静态函数、全局函数可以定义模板参数
## 类型推导
* var 自动推导类型，加快代码编辑
## 反射
* reflect 对struct、class、模板可以获取反射信息
## 协程
* async 对全局函数，类静态函数，类成员函数可以使用async修饰，表示是一个协程函数
* await 对全局函数，类静态函数，类成员函数可以使用await修饰，表示需要在带async和await修饰的函数中执行。
