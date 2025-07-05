#include <iostream>
#include "../utils/utils.hpp"

struct A
{
    int val = 0;
    void output() { std::cout << "val: " << val << std::endl; }
    void set(int v) { val = v; }
    int get() const { return val; }
};

int val = 0;
void output() { std::cout << "val: " << val << std::endl; }
void set(int v) { val = v; }
int get() { return val; }

struct MyClass
{
    int a;
    static int b;
    void f1() {}
    static void f2() {}

    MyClass() { std::cout << "MyClass()" << std::endl; }
    ~MyClass() { std::cout << "~MyClass()" << std::endl; }
};

int MyClass::b = 0;

void my_func(void *object) { std::cout << *(int *)(object + sizeof(MyClass)) << std::endl; }

void test1();
void test2();
void test3();

utils::ClassDB class_db;

int main()
{
    test1();
    test2();
    test3();

    return 0;
}

void test1()
{
    utils::MemberField<int, A> A_val(&A::val);
    utils::MemberMethod<void, A> A_output(&A::output);
    utils::MemberMethod<void, A, int> A_set(&A::set);
    utils::MemberMethod<int, A> A_get(&A::get);
    A a;
    A_val.set(&a, 123);
    A_output.invoke(&a, std::make_tuple());
    A_set.invoke(&a, std::make_tuple(456));
    std::cout << std::any_cast<int>(A_get.invoke(&a, std::make_tuple())) << std::endl;

    std::cout << std::endl;

    utils::GlobalField<int> _val(&val);
    utils::GlobalMethod<void> _output(&output);
    utils::GlobalMethod<void, int> _set(&set);
    utils::GlobalMethod<int> _get(&get);
    _val.set(nullptr, 123);
    _output.invoke((const void *)nullptr, std::make_tuple());
    _set.invoke((const void *)nullptr, std::make_tuple(456));
    std::cout << std::any_cast<int>(_get.invoke((const void *)nullptr, std::make_tuple())) << std::endl;

    std::cout << std::endl;
}

void test2()
{
    auto class_info = std::make_shared<utils::ClassInfoRegister<MyClass>>();
    class_info->set_constructor([](const std::any &)
                                { return new MyClass; });
    class_info->set_destructor([](void *object)
                               { delete reinterpret_cast<MyClass *>(object); });
    class_info->register_field("a", &MyClass::a);
    class_info->register_field("b", &MyClass::b);
    class_info->register_method("f1", &MyClass::f1);
    class_info->register_method("f2", &MyClass::f2);

    utils::ClassInfo::BaseClassArray utils_classes = {class_info};
    auto class_info2 = std::make_shared<utils::DynamicClassInfoRegister>(utils_classes);
    class_info2->set_constructor([](const std::any &args)
                                 { 
        char* mem=new char[sizeof(MyClass) + sizeof(int)];
        new (mem)MyClass();
        *(int*)(mem+sizeof(MyClass))=666;
        return mem; });
    class_info2->set_destructor([](void *object)
                                {
            ((MyClass*)object)->~MyClass();
            delete [](char*)object;
            std::cout << "Dynamic Class destructed" << std::endl; });
    class_info2->register_dynamic_field<int>("my_var", sizeof(MyClass), false);
    class_info2->register_dynamic_method("my_func", &my_func);

    class_db.register_class("MyClass", class_info);
    class_db.register_class("DynamicClass", class_info2);
}

void test3()
{
    auto class_info = class_db.find_class("DynamicClass")->second;
    auto object = class_info->create();
    class_info->set(object.get(), "my_var", 999);
    class_info->call(object.get(), "my_func", object.get());
}
