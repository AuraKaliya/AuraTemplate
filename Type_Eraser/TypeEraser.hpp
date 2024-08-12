#pragma once

#include <memory>
#include "CheckTool.hpp"
/*
    若需要提前判断是否存在某个函数，可用CheckTool.hpp 中的 CHECKCLASSFUNCTION
    //使用方式:    Object obj1{...};
*/

//注册函数
REGISTERFUNCTIONFORCHECK(is_init)

//抽象接口
struct Command {
    virtual ~Command() {}
    virtual int get_id() const = 0;
    virtual bool is_init() const = 0;
};

// 具体命令模板，实现命令接口
template<typename T>
struct ConcreteCommand : Command {
    ConcreteCommand(T&& obj) noexcept : object_(std::forward<T>(obj)) {};
    int get_id() const override { return object_.get_id(); };

    //对于不确定有无的，通过if constexpr来进行编译器处理调用   由CheckTool来进行检查
    bool is_init() const override {
        if constexpr (CHECKCLASSFUNCTION(T,is_init,bool)) {
            return object_.is_init();
        }
        else {
            return false; // 或者返回默认值
        }
    }
private:
    T object_;
};

// 类型擦除的主体类
class Object {
public:
    // 构造函数模板，接受任何具有get_id()方法的对象
    template<typename T>
    Object(T&& obj) : concept_(std::make_unique < ConcreteCommand<T> >(std::forward<T>(obj))) {}

    // 调用存储的命令对象的get_id()方法
    int get_id() const { return concept_->get_id(); }
    bool is_init() const { return concept_->is_init(); }
private:
    std::unique_ptr<Command> concept_; // 使用unique_ptr来管理命令对象
};