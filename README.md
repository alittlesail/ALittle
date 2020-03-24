
【Visual Studio安装步骤】
1. 安装VS2019: https://visualstudio.microsoft.com/zh-hans/vs/
2. 安装ALittleScript.vsix语言插件
3. 打开ALittle.sln工程，就可以看到代码了

【Emscripten编译说明】
1. 安装python3:https://www.python.org/downloads/. 并把python目录加到环境变量
2. 用git拉一下代码 git clone https://github.com/emscripten-core/emsdk.git
3. 打开控制台，依次执行一下命令
	cd emsdk
	emsdk.bat install latest	（只需要执行一次）
	emsdk.bat activate latest	（只需要执行一次）
	emsdk_env.bat 				（每次打开控制台执行一次）
	将目录切换到当前git下的Emscripten目录
	执行build.bat （编译为wasm）


【插件说明】
1. ALittleScript是一门脚本语言，兼顾强类型和弱类型的语言
2. 可以翻译成Lua和JavaScript
3. 通过编写alittle为后缀的代码文件
4. 生成代码
	a. 修改代码文件时会自动生成目标代码
	b. 代码文件获得焦点时，使用组合键Ctrl+B可以生成整个工程的目标代码
	c. 代码文件获得焦点时，使用组合键Ctrl+F7可以生成当前焦点文件的目标代码

【语言特点】
1. 统一Lua和JavaScript两个脚本语言的特性
2. 通过开发ALittleScript代码可以对客户端和网页端进行一次性开发

【工程介绍】
1. Core工程：
	a. 核心库。
	b. 除了对平台语言本身，不会依赖任何第三方库。
	c. 内部有许多便捷的实现方案。已经开出的通用接口，以便于指定平台实现。
2. Std工程：
	a. 对Core便捷方案进行指定平台实现，会依赖第三方库
	b. lua方面，Std内部有对应的C/C++代码，可直接注册到lua进行使用，请自行加入C/C++工程进行编译
	c. javascript，也会提供对应的浏览器实现，不会依赖第三方库


TODO
1. 添加弱引用语法，以及相关支持
2. 完善标准库Std