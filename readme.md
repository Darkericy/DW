# 从零开始跟着大佬写下分布式服务器框架 #
***
### 当前进度 ###
* 2023.7.11 一切的开始
* 2023.7.14 log模块完成
* 2023.7.16 配置模块完成
* 2023.7.17 配置模块与日志模块整合完毕
* 2023.7.17 线程模块完成
* 2023.7.18 线程模块与日志模块配置模块整合完毕
* 2023.7.19 携程模块完成
* 2023.7.23 携程调度模块完成
* 2023.7.24 IO调度模块完成
* 2023.7.25 定时器模块完成
* 2023.7.26 hook模块完成
***
### 日志模块 ###
日志被细分为了LoggerManager, Logger, LogAppender, LogFormater等大类，每个类各司其职。大佬视频中的各个类耦合严重，我对结构做了些许修改，在我的版本里耦合没有那么严重了。同时对于调用日志的宏定义我也修改为了模板inline函数（为了方便，在接下来的内容中我依然描述为宏定义），这是为了响应effective c++中建议，虽然从调用上来看要复杂了一点，但是更可靠了。
    
目前存在的问题：日志输出格式的修改接口过于隐蔽，未来如果要修改或指定特定格式会比较麻烦。

### 配置模块 ###
配置模块使用boost库和yaml-cpp库开发，通过递归的模板实现完成了对yml文件的解析，同时支持大部分stl库的解析。
自定义类型的解析需要片特化LexicalCast模板，之后就可以解析自定义类型。
因为解析的过程是递归实现的，因此支持嵌套类型的解析。
与日志系统整合完毕，实现修改配置文件配置日志。

### 线程模块 ###
线程模块使用pthread里的功能，封装了互斥索，自选锁，以及锁的资源管理类。没有使用c++11的线程库是因为c++中没有提供读写互斥量和自选锁等经常用到的东西，因此大佬选择自己封装了一个。
通过这一节的学习使我对线程和锁的理解更上一层楼。

### 携程模块 ###
携程对于我来说是全新的东西，去尝试理解这个新东西非常的吃力。好在结合以前学过的知识我能勉强理解，在理解了携程及其用法之后我感叹他的方便。
自己封装携程并操控是一个有难度的事情，虽然C++20提供了无栈携程的使用，但是20标准的携程使用还是略显笨拙，我期待能在23标准推出后改善我对携程的理解和用法。

### 携程调度模块 ###
这对于我来讲是更加新颖的东西，理解学习这里的东西更是一个非常大的挑战，这个模块正好在比较忙的时候开始学习的，花费了非常久的时间，最后调整demo也花了我一个早上的时间。
不过我也确实理解了这个模块的运作机理。同时我修改了这个模块的很多代码，让他不要与携程模块过渡耦合。另外我删除了构造函数中的usecaler参数，我在不断的比对分析后决定删除他，不知道大佬是出于什么样的考量设置了这个参数，但至少在我看来，设置这个参数以后无故增加了许多维护成本，函数逻辑也变得非常混乱。所以我决定删除了。

### 定时器模块完成 ###
定时器模块与调度模块的配合让我确实大开眼界，之前在tinywebserver中实现的基于小根堆的定时器虽然也能有类似的功能，但是从使用的角度来看，这个定时器的功能要比webserver中的强过太多。通过使用epollwait的特点巧妙的管理时间，并使用tickle函数巧妙的唤醒epollwait，太巧妙了，我学到了很多。

### hook模块 ###
这个模块对我来说又是一个全新的东西，但是不难理解，而且我还获得了顿悟。在看到两个sleep函数在互不影响的前提下执行，打开了我新世界的大门。收益量多