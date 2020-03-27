
【Visual Studio安装步骤】
1. 安装VS2019: https://visualstudio.microsoft.com/zh-hans/vs/
2. 安装ALittleScript.vsix语言插件
3. 打开ALittle.sln工程，就可以看到代码了

【Emscripten编译说明】
1. 安装docker:https://www.docker.com/products/docker-desktop

2. 打开Windows PowerShell，执行以下指令
	拉取ubuntu镜像  docker pull ubuntu
	创建ubuntu容器  docker run -it --name alittle ubuntu /bin/bash -v D:/Software/ALittle/trunk/Emscripten:/alittle
	此时已进入ubuntu
	更新系统 apt update
	安装git  apt install git
	安装python apt install python
	安装xml2 apt install xml2
	安装gcc apt install gcc
	更新gcc apt upgrade gcc
	安装autoconf apt install autoconf
	安装cmake apt install cmake
	安装readline库 apt install libreadline-dev
	拉emsdk的代码 git clone https://github.com/emscripten-core/emsdk.git
	进入emsdk目录 cd emsdk
	安装emsdk		sh emsdk install latest
	激活emsdk		sh emsdk activate latest
	设置环境变量		source ./emsdk_env.sh

3. 编译lua5.3.5:https://www.lua.org/download.html
	a. 把lua5.3.5解压到D:/Software/ALittle/trunk/Emscripten/lua5.3.5文件夹中
	b. 进入D:/Software/ALittle/trunk/Emscripten/lua5.3.5文件夹
	c. emmake make posix CC=emcc
	d. emmake make install

5. 编译SDL2（SDL2_image，SDL2_mixer，SDL2_net，SDL2_ttf同理）
	a. 把SDL2解压到D:/Software/ALittle/trunk/Emscripten/SDL2中
	b. 进入D:/Software/ALittle/trunk/Emscripten
	c. mkdir build_SDL2
	d. cd build_SDL2
	e. emcmake cmake ../SDL2
	d. emmake make
	e. emmake make install


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