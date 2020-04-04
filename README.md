
## ALittleScript是什么
ALittleScript是一门兼顾强类型和弱类型的语言。

## ALittleScript的设计目标
* 它是以生成`Lua`为目标的强类型语言，类比`TypeScript`生成`JavaScript`。
* 它也可以生成`JavaScript`。
* 最终以生成的目标语言来运行，所以目标语言所有的已有资源和代码都可以无缝对接使用。
* `一次编写，多平台运行`。

## 安装环境

* 安装[Visual Studio](https://visualstudio.microsoft.com/zh-hans/vs/)(2015、2017、2019)
* 安装[ALittleScript.vsix](https://github.com/alittlesail/ALittle/blob/master/ALittleScript.vsix)语言插件

## Hello World
* 使用Git拉去当前项目
* 使用Visual Studio打开Module/ALittleIDE/Other/GameLibrary/ALittle.sln
* 已经内置两个工程Core和HelloWorld
* Core是语言标准库，今后的每个sln都要包含它
* HelloWorld项目只有一个文件Main.alittle，内部有一个Main函数打印了HelloWorld
* 运行nginx-1.16.1中的start.bat来打开nginx
* 打开浏览器输入localhost/Module/ALittleIDE/Other/GameLibrary/HelloWorld/HelloWorld.html
* 按F12打开浏览器调试界面，就可以看到HelloWorld
* ![HelloWorld](https://github.com/alittlesail/ALittle/blob/master/Module/ALittleIDE/Other/GameLibrary/HelloWorld/HelloWorld.png)
