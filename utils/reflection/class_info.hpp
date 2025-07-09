#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "../meta/global_field.hpp"
#include "../meta/global_method.hpp"
#include "../meta/member_field.hpp"
#include "../meta/member_method.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(ClassInfo);

    /// @brief 类信息
    class ClassInfo : public base::PolymorphicObject
    {
    public:
        using BaseClassArray = std::vector<ClassInfoRef>;
        using FieldDict = std::unordered_map<std::string, FieldBaseRef>;
        using MethodDict = std::unordered_map<std::string, MethodBaseRef>;

        using ConstructionFunc = void *(const std::any &);
        using DestructionFunc = void(void *);
        using Constructor = std::function<ConstructionFunc>;
        using Destructor = std::function<DestructionFunc>;

        using FieldIterator = FieldDict::iterator;
        using MethodIterator = MethodDict::iterator;
        using FieldConstIterator = FieldDict::const_iterator;
        using MethodConstIterator = MethodDict::const_iterator;

    private:
        /// @brief 基类信息
        BaseClassArray m_base_classes;
        /// @brief 属性字典
        FieldDict m_field_dict;
        /// @brief 方法字典
        MethodDict m_method_dict;
        /// @brief 构造函数
        Constructor m_constructor;
        /// @brief 析构函数
        Destructor m_destructor;

    protected:
        ClassInfo() = default;
        ClassInfo(const BaseClassArray &base_classes) : m_base_classes(base_classes) {}

    public:
        ~ClassInfo() override = default;

    public:
        inline const BaseClassArray &get_base_classes() const { return m_base_classes; }
        inline const FieldDict &get_field_dict() const { return m_field_dict; }
        inline const MethodDict &get_method_dict() const { return m_method_dict; }
        inline const Constructor &get_constructor() const { return m_constructor; }
        inline const Destructor &get_destructor() const { return m_destructor; }
        inline void set_constructor(const Constructor &constructor) { m_constructor = constructor; }
        inline void set_destructor(const Destructor &destructor) { m_destructor = destructor; }

    protected:
        inline void _set_base_class(const ClassInfoRef &base_class)
        {
            m_base_classes = base_class->m_base_classes;
            m_base_classes.push_back(base_class);
        }

        inline void _add_base_class(const ClassInfoRef &base_class)
        {
            m_base_classes.push_back(base_class);
        }

        inline void _add_field(const std::string &name, const FieldBaseRef &field)
        {
            m_field_dict[name] = field;
        }

        inline void _add_method(const std::string &name, const MethodBaseRef &method)
        {
            m_method_dict[name] = method;
        }

    public:
        /// @brief 构造该类
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        /// @return 对象指针
        template <typename... T>
        void *construct(T... args);

        /// @brief 析构该类
        /// @param object 对象指针
        void destruct(void *object);

        /// @brief 创建对象
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        /// @return 对象引用
        template <typename... T>
        base::AnyRef create(T... args);

        //
        // 查找函数
        //

        FieldConstIterator find_field(const std::string &name) const;
        MethodConstIterator find_method(const std::string &name) const;

        //
        // 类成员
        //

        std::any get(void *object, const std::string &name) const;
        std::any get(const void *object, const std::string &name) const;
        void set(void *object, const std::string &name, const std::any &value) const;
        template <typename... T>
        std::any call(void *object, const std::string &name, T... args) const;
        template <typename... T>
        std::any call(const void *object, const std::string &name, T... args) const;

        //
        // 静态成员
        //

        std::any get(const std::string &name) const;
        void set(const std::string &name, const std::any &value) const;
        template <typename... T>
        std::any call(const std::string &name, T... args) const;
    };

} // namespace utils
