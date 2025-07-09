#pragma once

#include "field_base.hpp"

namespace utils
{
    template <typename T>
    class MemberFieldOffset;
    template <typename T>
    using MemberFieldOffsetRef = base::Ref<MemberFieldOffset<T>>;
    template <typename T>
    using MemberFieldOffsetWeakRef = base::WeakRef<MemberFieldOffset<T>>;

    /// @brief 成员属性偏移量
    /// @tparam T 类型
    template <typename T>
    class MemberFieldOffset : public FieldBase
    {
    public:
        using Type = T;
        using Ptr = void *;

    private:
        /// @brief 偏移量
        base::Size m_offset;

    public:
        inline MemberFieldOffset(base::Size offset, bool is_const) : FieldBase(is_const), m_offset(offset) {}
        inline ~MemberFieldOffset() override = default;

    public:
        inline base::Size get_offset() const { return m_offset; }

    public:
        inline std::any get(void *object) const override
        {
            return *reinterpret_cast<T *>((char *)object + m_offset);
        }

        inline std::any get(const void *object) const override
        {
            return *reinterpret_cast<const T *>((const char *)object + m_offset);
        }

        void set(void *object, const std::any &value) const override
        {
            if (is_const())
                throw BASE_MAKE_RUNTIME_ERROR("Cannot set a const field, offset: ", m_offset);

            *reinterpret_cast<T *>((char *)object + m_offset) = std::any_cast<T>(value);
        }
    };

} // namespace utils
