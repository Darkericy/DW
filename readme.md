# 从零开始跟着大佬写下分布式服务器框架 #
***
### 当前进度 ###
* 2023.7.11 一切的开始
* 2023.7.14 log模块完成
* 2023.7.16 配置模块完成
***
### 日志模块 ###
日志被细分为了LoggerManager, Logger, LogAppender, LogFormater等大类，每个类各司其职。大佬视频中的各个类耦合严重，我对结构做了些许修改，在我的版本里耦合没有那么严重了。同时对于调用日志的宏定义我也修改为了模板inline函数（为了方便，在接下来的内容中我依然描述为宏定义），这是为了响应effective c++中建议，虽然从调用上来看要复杂了一点，但是更可靠了。
    
目前存在的问题：日志输出格式的修改接口过于隐蔽，未来如果要修改或指定特定格式会比较麻烦。

### 配置模块 ###
配置模块使用boost库和yaml-cpp库开发，通过递归的模板实现完成了对yml文件的解析，同时支持大部分stl库的解析。
自定义类型的解析需要片特化LexicalCast模板，之后就可以解析自定义类型。
因为解析的过程是递归实现的，因此支持嵌套类型的解析。