#pragma once

#include "method_base.hpp"

namespace utils
{
    template <typename, typename, typename...>
    class MemberMethod;
    template <typename R, typename C, typename... T>
    using MemberMethodRef = ::base::Ref<MemberMethod<R, C, T...>>;
    template <typename R, typename C, typename... T>
    using MemberMethodWeakRef = ::base::WeakRef<MemberMethod<R, C, T...>>;

    /// @brief 成员方法
    /// @tparam R 返回值类型
    /// @tparam C 类类型
    /// @tparam ...T 参数类型
    template <typename R, typename C, typename... T>
    class MemberMethod : public MethodBase
    {
    public:
        using Ret = R;
        using Class = C;
        using ArgsTuple = std::tuple<T...>;
        using Ptr = Ret (Class::*)(T...);
        using ConstPtr = Ret (Class::*)(T...) const;

    private:
        /// @brief 指针
        Ptr m_ptr = nullptr;
        /// @brief const指针
        ConstPtr m_const_ptr = nullptr;

    public:
        inline MemberMethod(Ptr ptr) : MethodBase(false), m_ptr(ptr) {}
        inline MemberMethod(ConstPtr ptr) : MethodBase(true), m_const_ptr(ptr) {}
        inline ~MemberMethod() override = default;

    public:
        inline Ptr get_ptr() const { return m_ptr; }
        inline ConstPtr get_const_ptr() const { return m_const_ptr; }

    public:
        std::any invoke(void *object, const std::any &args) const override
        {
            auto tuple = std::any_cast<ArgsTuple>(args);
            auto impl = [this, object](auto... args) -> Ret
            {
                if (is_const())
                    return std::invoke(m_const_ptr, reinterpret_cast<Class *>(object), args...);
                else
                    return std::invoke(m_ptr, reinterpret_cast<Class *>(object), args...);
            };

            return invoke_impl(impl, tuple);
        }

        std::any invoke(const void *object, const std::any &args) const override
        {
            auto tuple = std::any_cast<ArgsTuple>(args);
            auto impl = [this, object](auto... args) -> Ret
            {
                if (is_const())
                    return std::invoke(m_const_ptr, reinterpret_cast<const Class *>(object), args...);
                else
                    throw BASE_MAKE_RUNTIME_ERROR("Cannot call a non-const method, pointer: ", m_ptr);
            };

            return invoke_impl(impl, tuple);
        }

        /// @brief 具体实现
        /// @tparam ImplT 实现函数类型
        /// @param impl 实现函数
        /// @param tuple 参数元组
        /// @return 返回值
        template <typename ImplT>
        std::any invoke_impl(ImplT impl, const ArgsTuple &tuple) const
        {
            if constexpr (std::is_void_v<Ret>)
            {
                std::apply(impl, tuple);
                return {};
            }
            else
            {
                return std::apply(impl, tuple);
            }
        }
    };

} // namespace utils
