#pragma once

#include "class_info.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(ClassInfoBaseRegister);

    /// @brief 类信息基础注册器
    class ClassInfoBaseRegister : public ClassInfo
    {
    public:
        inline ClassInfoBaseRegister() = default;
        inline ClassInfoBaseRegister(const BaseClassArray &base_classes) : ClassInfo(base_classes) {}
        inline ~ClassInfoBaseRegister() = default;

    public:
        template <typename T>
        inline void register_field(const std::string &name, T *ptr)
        {
            _add_field(name, std::make_shared<GlobalField<T>>(ptr));
        }

        template <typename T>
        inline void register_field(const std::string &name, const T *ptr)
        {
            _add_field(name, std::make_shared<GlobalField<T>>(ptr));
        }

        template <typename T, typename C>
        inline void register_field(const std::string &name, T(C::*ptr))
        {
            _add_field(name, std::make_shared<MemberField<T, C>>(ptr));
        }

        template <typename T, typename C>
        inline void register_field(const std::string &name, const T(C::*ptr))
        {
            _add_field(name, std::make_shared<MemberField<T, C>>(ptr));
        }

        template <typename R, typename... T>
        inline void register_method(const std::string &name, R (*ptr)(T...))
        {
            _add_method(name, std::make_shared<GlobalMethod<R, T...>>(ptr));
        }

        template <typename R, typename C, typename... T>
        inline void register_method(const std::string &name, R (C::*ptr)(T...))
        {
            _add_method(name, std::make_shared<MemberMethod<R, C, T...>>(ptr));
        }

        template <typename R, typename C, typename... T>
        inline void register_method(const std::string &name, R (C::*ptr)(T...) const)
        {
            _add_method(name, std::make_shared<MemberMethod<R, C, T...>>(ptr));
        }
    };

} // namespace utils
