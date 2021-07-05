# Toy_complier

## 项目介绍

本项目是ZJU编译原理的大作业，内容是实现一个Simple Pascal语言的编译器

## 版本

- llvm 11.0.0
- flex 2.6. 
- bison 3.7.4

Linux 环境下安装：
```bash
    sudo apt-get install llvm
    sudo apt-get install flex bison 
```

MacOS 环境下安装：
```bash
    brew install llvm
    brew install flex bison 
```

## OS

- MacOS 
- Linux

## 编译

在`Toy_compiler`根目录下执行以下命令：
```bash
mkdir build
cd build
cmake ..
make
```
此时会生成可执行文件`toy_compiler`。在`Toy_Compiler`根目录中的`toy_compiler`是已经生成好的可执行文件。

## 运行

运行命令为`echo filename.spl | toy_compiler 2> spl.ll`，此时文件名为`filename.spl`的文件将被编译生成llvm中间代码并保存在`spl.ll`文件中。

以运行`Toy_compiler/build/toy_compiler`为例，输入命令为：

```bash
cd build
echo ../tests/Array.spl | ./toy_compiler 2> spl.ll
```

## IR执行

```bash
lli spl.ll
```
## 生成目标代码

```bash
llc --march=mips spl.ll
```

输出结果保存在`spl.s`文件中。

## AST可视化

1. 在VS Code中安装Live Server插件
2. VS Code中打开项目文件夹
3. VS Code右下角点击`Go Live`
4. 在自动加载的浏览器网页中打开`tree.html`

