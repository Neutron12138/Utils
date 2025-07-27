#pragma once

#include "meta_base.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(MethodBase);

    /// @brief 方法基类
    class MethodBase : public MetaBase
    {
    public:
        inline MethodBase(bool is_const) : MetaBase(is_const) {}
        inline ~MethodBase() override = default;

    public:
        /// @brief 调用方法
        /// @param object 对象
        /// @param args 参数列表
        /// @return 返回值
        virtual std::any invoke(void *object, const std::any &args) const = 0;

        /// @brief 调用方法
        /// @param object 对象
        /// @param args 参数列表
        /// @return 返回值
        virtual std::any invoke(const void *object, const std::any &args) const = 0;
    };

} // namespace utils
