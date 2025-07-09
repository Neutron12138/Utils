#pragma once

#include "meta_base.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(FieldBase);

    /// @brief 属性基类
    class FieldBase : public MetaBase
    {
    public:
        inline FieldBase(bool is_const) : MetaBase(is_const) {}
        inline ~FieldBase() override = default;

    public:
        /// @brief 获取属性
        /// @param object 对象
        /// @return 结果
        virtual std::any get(void *object) const = 0;

        /// @brief 获取属性
        /// @param object 对象
        /// @return 结果
        virtual std::any get(const void *object) const = 0;

        /// @brief 设置属性
        /// @param object 对象
        /// @param value 值
        virtual void set(void *object, const std::any &value) const = 0;
    };

} // namespace utils
