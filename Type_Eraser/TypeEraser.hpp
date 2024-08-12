#pragma once

#include <memory>
#include "CheckTool.hpp"
/*
    ����Ҫ��ǰ�ж��Ƿ����ĳ������������CheckTool.hpp �е� CHECKCLASSFUNCTION
    //ʹ�÷�ʽ:    Object obj1{...};
*/

//ע�ắ��
REGISTERFUNCTIONFORCHECK(is_init)

//����ӿ�
struct Command {
    virtual ~Command() {}
    virtual int get_id() const = 0;
    virtual bool is_init() const = 0;
};

// ��������ģ�壬ʵ������ӿ�
template<typename T>
struct ConcreteCommand : Command {
    ConcreteCommand(T&& obj) noexcept : object_(std::forward<T>(obj)) {};
    int get_id() const override { return object_.get_id(); };

    //���ڲ�ȷ�����޵ģ�ͨ��if constexpr�����б������������   ��CheckTool�����м��
    bool is_init() const override {
        if constexpr (CHECKCLASSFUNCTION(T,is_init,bool)) {
            return object_.is_init();
        }
        else {
            return false; // ���߷���Ĭ��ֵ
        }
    }
private:
    T object_;
};

// ���Ͳ�����������
class Object {
public:
    // ���캯��ģ�壬�����κξ���get_id()�����Ķ���
    template<typename T>
    Object(T&& obj) : concept_(std::make_unique < ConcreteCommand<T> >(std::forward<T>(obj))) {}

    // ���ô洢����������get_id()����
    int get_id() const { return concept_->get_id(); }
    bool is_init() const { return concept_->is_init(); }
private:
    std::unique_ptr<Command> concept_; // ʹ��unique_ptr�������������
};