#pragma once

#include "../meta/member_field_offset.hpp"
#include "class_info_base_register.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(DynamicClassInfoRegister);

    /// @brief 动态类信息注册器
    class DynamicClassInfoRegister : public ClassInfoBaseRegister
    {
    public:
        inline DynamicClassInfoRegister() = default;
        inline DynamicClassInfoRegister(const BaseClassArray &base_classes) : ClassInfoBaseRegister(base_classes) {}
        inline ~DynamicClassInfoRegister() override = default;

    public:
        template <typename T>
        inline void register_dynamic_field(const std::string &name, base::Size offset, bool is_const)
        {
            _add_field(name, std::make_shared<MemberFieldOffset<T>>(offset, is_const));
        }

        template <typename R, typename... T>
        inline void register_dynamic_method(const std::string &name, R (*ptr)(void *, T...))
        {
            _add_method(name, std::make_shared<GlobalMethod<R, void *, T...>>(ptr));
        }
    };

} // namespace utils
