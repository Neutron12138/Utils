#pragma once

#include "class_info_base_register.hpp"

namespace utils
{
    BASE_DECLARE_REF_TEMPLATE_TYPE(C, ClassInfoRegister);

    /// @brief 类信息注册器
    /// @tparam C 类类型
    template <typename C>
    class ClassInfoRegister : public ClassInfoBaseRegister
    {
    public:
        using ClassType = C;

    public:
        inline ClassInfoRegister() = default;
        inline ClassInfoRegister(const BaseClassArray &base_classes) : ClassInfoBaseRegister(base_classes) {}
        inline ~ClassInfoRegister() override = default;

    public:
        using ClassInfoBaseRegister::register_field;
        using ClassInfoBaseRegister::register_method;

        template <typename T>
        inline void register_field(const std::string &name, T(ClassType::*ptr))
        {
            _add_field(name, std::make_shared<MemberField<T, C>>(ptr));
        }

        template <typename T>
        inline void register_field(const std::string &name, const T(ClassType::*ptr))
        {
            _add_field(name, std::make_shared<MemberField<T, C>>(ptr));
        }

        template <typename R, typename... T>
        inline void register_method(const std::string &name, R (ClassType::*ptr)(T...))
        {
            _add_method(name, std::make_shared<MemberMethod<R, C, T...>>(ptr));
        }

        template <typename R, typename... T>
        inline void register_method(const std::string &name, R (ClassType::*ptr)(T...) const)
        {
            _add_method(name, std::make_shared<MemberMethod<R, C, T...>>(ptr));
        }
    };

} // namespace utils
