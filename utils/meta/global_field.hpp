#pragma once

#include "field_base.hpp"

namespace utils
{
    template <typename T>
    class GlobalField;
    template <typename T>
    using GlobalFieldRef = ::base::Ref<GlobalField<T>>;
    template <typename T>
    using GlobalFieldWeakRef = ::base::WeakRef<GlobalField<T>>;

    /// @brief 普通属性
    /// @tparam T 类型
    template <typename T>
    class GlobalField : public FieldBase
    {
    public:
        using Type = T;
        using Ptr = Type *;
        using ConstPtr = const Type *;

    private:
        /// @brief 指针
        Ptr m_ptr;
        /// @brief const指针
        ConstPtr m_const_ptr;

    public:
        inline GlobalField(Ptr ptr) : FieldBase(false), m_ptr(ptr) {}
        inline GlobalField(ConstPtr ptr) : FieldBase(true), m_const_ptr(ptr) {}
        inline ~GlobalField() override = default;

    public:
        inline Ptr get_ptr() const { return m_ptr; }
        inline ConstPtr get_const_ptr() const { return m_const_ptr; }

    public:
        inline std::any get(void *) const override { return get_impl(); }
        inline std::any get(const void *) const override { return get_impl(); }

        /// @brief 具体实现
        /// @return 返回值
        inline std::any get_impl() const
        {
            if (is_const())
                return *m_const_ptr;
            else
                return *m_ptr;
        }

        void set(void *object, const std::any &value) const override
        {
            if (is_const())
                throw BASE_MAKE_RUNTIME_ERROR("Cannot set a const field, pointer: ", m_const_ptr);

            *m_ptr = std::any_cast<T>(value);
        }
    };

} // namespace utils
