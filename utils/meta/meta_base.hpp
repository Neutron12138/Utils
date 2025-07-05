#pragma once

#include <any>
#include <tuple>
#include <base/core/ref.hpp>
#include <base/core/polymorphic_object.hpp>
#include <base/core/exception.hpp>

namespace utils
{
    BASE_DECLARE_REF_TYPE(MetaBase);

    /// @brief 元基类
    class MetaBase : public ::base::PolymorphicObject
    {
    private:
        /// @brief 是否为const
        bool m_is_const;

    public:
        inline MetaBase(bool is_const) : m_is_const(is_const) {}
        inline ~MetaBase() override = default;

    public:
        inline bool is_const() const { return m_is_const; }
    };

} // namespace utils
