# 第0章 实验指引以及说明

## 实验目的

在计算机组成原理与体系结构这一系列的实验内容当中，将会介绍硬件设计开发相关的基础知识以及对各种硬件设计开发与验证测试的工具以及框架的使用进行熟悉。下面首先概括在这一系列的实验当中需要熟悉学习的相关知识以及设计使用到的工具。

### 硬件开发设计基础

以下是这一系列实验内容所要学习的相关知识：

1. 硬件基础知识简介
2. 组合逻辑电路入门
3. 时序逻辑电路入门
4. 电路实例介绍（运算器、RV32I处理器等）
5. 面向FPGA的算法核设计入门（流水线、数据并行、其他计算技术等）

### 硬件开发设计/验证工具

下面列举这一系列实验内容所需要使用的工具。

针对开发方面的工具有：

1. **PyHCL**；本系列实验主要使用的基于Python的硬件设计开发工具。
2. **Chisel**；由加州大学伯克利分校开发的基于Scala的硬件设计开发工具，作为参考。
3. **FIRRTL**；Flexible Internal Representation for RTL，Chisel的中间层语言，也是PyHCL的目标语言。

用于进行仿真验证测试的工具有：

1. **Cocotb**；基于Python的硬件验证平台。
2. **Verilator**；基于C++的开源仿真工具。
3. **GTKwave**；查看仿真波形文件的工具。
4. **Treadle**；FIRRTL执行器/调试器。
5. **Diagrammer**；FIRRTL代码的图形化工具，可以将FIRRTL代码的逻辑结构以及数据流转化为svg图像进行调试。

## 开发设计/验证工具使用简要说明

在这一节当中会对上述实验所需要的工具安装使用进行简要的说明。

### PyHCL

PyHCL是由笔者团队开发的基于Python的开源硬件开发设计框架，其设计思想与Chisel类似。在数字逻辑课程当中提到过目前工业上主流的硬件设计语言是Verilog和VHDL，然而这个已经有数十年寿命的过程式语言已经无法满足目前越来越庞大越来越复杂的集成电路芯片开发的需求。Chisel是将硬件设计与高层次的程序设计语言相结合的开山鼻祖，其将硬件设计嵌入到高级程序语言Scala当中，提出了硬件敏捷设计的可能性。将硬件设计框架嵌入到基于面向对象的编程语言可以使得硬件设计享受到面向对象语言本体的各种优势。然而，由于Chisel基于的是Scala语言，这种语言使用受众小，学习难度较高，而且社区活跃度也比较低，导致上手的难度高，学习的时间周期长，不利于其推广。因此本团队使用Python语言来设计开发PyHCL，提供一个更为易用、简洁的硬件设计框架。

PyHCL的Github repo：https://github.com/scutdig/PyChip-py-hcl

PyHCL的基础wiki：https://github.com/scutdig/PyChip-py-hcl/wiki

在实验的过程中将会与PyHCL相结合来熟悉这个工具的使用和开发。

#### 安装与使用

PyHCL实际上就是使用Python实现的库，因此只要使用Git将PyHCL源码克隆下来后便可以将其放置于项目根目录当中使用，只需要在使用到PyHCL的代码中导入即可：

```python
from pyhcl import *
```

然而，PyHCL需要一定的环境支持，包括：

- Python3.7及以上版本；
- FIRRTL环境，在下文中会对如何配置进行说明；

使用PyHCL来进行开发，操作系统推荐使用Linux的发行版（Ubuntu，Arch系的Manjaro）或者MacOS。

### Chisel

Chisel是较为成熟的工具，最新的版本为Chisel3。在这一系列的实验当中，都会使用PyHCL来进行开发，而Chisel仅仅提供给大家作为参考。Chisel的资料也较为详尽：

Chisel的官网：https://www.chisel-lang.org/

Chisel的Github repo：https://github.com/freechipsproject/chisel3

Chisel的wiki：https://github.com/freechipsproject/chisel3/wiki

Chisel的API文档：https://www.chisel-lang.org/api/latest/

关于Chisel的安装与使用，都可以在Chisel官方的文档中找到，在这里就不再赘述。

### FIRRTL

FIRRTL是Chisel在Chisel3版本引入的框架中间代码层语言，类似于LLVM的存在。在Chisel3版本中，框架工具的编译链条是由Scala到FIRRTL再到Verilog。FIRRTL的引入使得框架的前后端实际上都可以替换为其他的语言。PyHCL的目标语言就是FIRRTL，并调用FIRRTL编译器生成Verilog代码。因此要使用PyHCL需要配置FIRRTL环境。

在FIRRTL的Github repo当中有详细说明FIRRTL的安装配置过程：https://github.com/freechipsproject/firrtl#installation-instructions；你需要依照上面的说明安装verilator、yosys以及sbt，这是FIRRTL所依赖的环境。接着需要编译安装FIRRTL，如果没有问题，则会在/firrtl/utils/bin当中生成firrtl的可执行文件。接下来你需要将它加入到系统的环境变量当中，针对不同的操作系统，添加环境变量的方法都不一样，这个需要自行上网查阅方法。最终，如果成功将firrtl加入到环境变量当中，在终端中输入`firrtl --help`就可以显示firrtl的命令的相关信息。

### Verilator

Verilator是目前速度最快的开源仿真工具，其原理是将Verilog代码编译成高度并行化的C++代码来执行。它是很多仿真平台（包括Cocotb）以及FIRRTL、Chisel必须的工具之一。Verilator的安装方法可以在官网找到：https://www.veripool.org/projects/verilator/wiki/Installing。这里简述一下安装的方法：

#### 各版本的安装方式

##### Ubuntu

Ubuntu系统的安装方式非常简单，只需要使用apt-get即可：

```Shell
apt-get install verilator
```

##### Manjaro

Manjaro可以使用pacman安装：

```shell
pacman -S verilator
```

##### MacOS

MacOS可以使用brew安装，brew不是内置的，若没安装过则需要安装：

```shell
brew install verilator
```

在终端输入`verilator --version`有版本信息生成说明安装成功。

#### 使用Verilator

要使用Verilator，你需要：你所要测试的模块dut的verilog源码、模块测试所需要的harness（C++测试文件，里面会对测试的方式进行说明）。在这里提供一个笔者在Github上公开的例子供大家参考：https://github.com/Groupsun/Verilator_Simple_Usage。要使用Verilator，需要会书写harness代码，这个C++代码用于指导Verilator如何进行仿真。下面以上述例子中的`Decoder_Sim.cpp`来进行说明。

这个例子需要仿真的模块是一个3-8译码器模块。首先，使用Verilator都需要包含头文件`verilated.h`，如果需要生成波形文件，则需要包含`verilated_vcd_c.h`：

```C++
#include <verilated.h>
#include <verilated_vcd_c.h>
```

harness文件中需要包含编译测试模块得到的头文件，如我们需要测试的模块名称为`Decoder`，那么它编译生成的头文件名称为`VDecoder.h`：

```C++
#include "VDecoder.h"
```

接着需要声明顶层测试模块的指针以及生成波形文件的`VerilatedVcdC`对象指针：

```C++
VDecoder* top;
VerilatedVcdC* tfp;
```

定义仿真时间以及仿真最大时间：

```C++
vluint64_t main_time = 0;		// 仿真时间
const vluint64_t sim_time = 1024;		// 仿真最大时间
```

`main`函数中写测试例程，首先是使用Verilator的一些固定写法，以及启用波形生成选项。同时构造顶层测试模块以及生成波形文件的对象：

```C++
Verilated::commandArgs(argc, argv);
Verilated::traceEverOn(true);
top = new VDecoder;
tfp = new VerilatedVcdC;
top->trace(tfp, 99);
tfp->open("Decoder.vcd");		// 波形文件名字为Decoder.vcd
```

`while`语句中写测试具体实现。首先语句条件就是测试的继续进行的条件：`!Verilated::gotFinish() && main_time < sim_time`。这是比较固定的写法。而语句内则是如何进行测试。在测试的过程中，对dut的输入口进行相关的激励，同时观察输出口的结果就是最基本的测试方法。在这里，IO口的名称就是顶层模块的成员，通过给它们赋值就相当于给予输入口激励：

```C++
top->reset = 0;		// reset输入为0
top->S = count;		// S输入为count的值
count++;
top->eval();			// 时钟步进一个周期
tfp->dump(main_time);		// 结果写入波形文件
main_time++;			// 仿真时间+1
```

在仿真结束后，需要释放动态分配的内存：

```C++
tfp->close();
delete top;
delete tfp;
```

这就是一个最简单的harness测试文件的写法，可以看出，其实这种测试方法有一定的局限性，而且还比较麻烦。在编写完harness文件后，只要在终端执行下列命令就可以完成整个测试过程：

```shell
verilator --cc Decoder.v --exe Decoder_Sim.cpp --trace
make -j -C ./obj_dir -f VDecoder.mk VDecoder
./obj_dir/VDecoder
```

在根目录下，会生成波形文件`Decoder.vcd`，可以使用GTKwave来查看结果。





















