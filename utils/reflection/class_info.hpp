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
        BaseClassArray m_base_classes = {};
        /// @brief 属性字典
        FieldDict m_field_dict = {};
        /// @brief 方法字典
        MethodDict m_method_dict = {};
        /// @brief 构造函数
        Constructor m_constructor = {};
        /// @brief 析构函数
        Destructor m_destructor = {};

    protected:
        ClassInfo() = default;
        ClassInfo(const BaseClassArray &base_classes);

    public:
        ~ClassInfo() override = default;

    public:
        const BaseClassArray &get_base_classes() const;
        const FieldDict &get_field_dict() const;
        const MethodDict &get_method_dict() const;
        const Constructor &get_constructor() const;
        const Destructor &get_destructor() const;
        void set_constructor(const Constructor &constructor);
        void set_destructor(const Destructor &destructor);

    protected:
        void _set_base_class(const ClassInfoRef &base_class);
        void _add_base_class(const ClassInfoRef &base_class);
        void _add_field(const std::string &name, const FieldBaseRef &field);
        void _add_method(const std::string &name, const MethodBaseRef &method);

    public:
        /// @brief 构造该类
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        /// @return 对象指针
        template <typename... T>
        void *construct(T... args)
        {
            if (!m_constructor)
                throw BASE_MAKE_RUNTIME_ERROR("No constructor");

            return m_constructor(std::make_tuple(args...));
        }

        /// @brief 析构该类
        /// @param object 对象指针
        void destruct(void *object)
        {
            if (!m_destructor)
                throw BASE_MAKE_RUNTIME_ERROR("No destructor");

            m_destructor(object);
        }

        /// @brief 创建对象
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        /// @return 对象引用
        template <typename... T>
        base::AnyRef create(T... args)
        {
            if (!m_constructor)
                throw BASE_MAKE_RUNTIME_ERROR("No constructor");
            if (!m_destructor)
                throw BASE_MAKE_RUNTIME_ERROR("No destructor");

            return base::AnyRef(m_constructor(std::make_tuple(args...)), m_destructor);
        }

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
        std::any call(void *object, const std::string &name, T... args) const
        {
            auto iter = find_method(name);
            return iter->second->invoke(object, std::make_tuple(args...));
        }

        template <typename... T>
        std::any call(const void *object, const std::string &name, T... args) const
        {
            auto iter = find_method(name);
            return iter->second->invoke(object, std::make_tuple(args...));
        }

        //
        // 静态成员
        //

        std::any get(const std::string &name) const;
        void set(const std::string &name, const std::any &value) const;

        template <typename... T>
        std::any call(const std::string &name, T... args) const
        {
            auto iter = find_method(name);
            return iter->second->invoke(static_cast<void *>(nullptr), std::make_tuple(args...));
        }
    };

} // namespace utils
