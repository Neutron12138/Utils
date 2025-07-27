#pragma once

#include "method_base.hpp"

namespace utils
{
    template <typename, typename...>
    class GlobalMethod;
    template <typename R, typename... T>
    using GlobalMethodRef = base::Ref<GlobalMethod<R, T...>>;
    template <typename R, typename... T>
    using GlobalMethodWeakRef = base::WeakRef<GlobalMethod<R, T...>>;

    /// @brief 普通方法
    /// @tparam R 返回值类型
    /// @tparam ...T 参数类型
    template <typename R, typename... T>
    class GlobalMethod : public MethodBase
    {
    public:
        using Ret = R;
        using ArgsTuple = std::tuple<T...>;
        using Ptr = Ret (*)(T...);

    private:
        /// @brief 指针
        Ptr m_ptr;

    public:
        inline GlobalMethod(Ptr ptr) : MethodBase(false), m_ptr(ptr) {}
        inline ~GlobalMethod() override = default;

    public:
        inline Ptr get_ptr() const { return m_ptr; }

    public:
        inline std::any invoke(void *, const std::any &args) const override { return invoke_impl(args); }
        inline std::any invoke(const void *, const std::any &args) const override { return invoke_impl(args); }

        /// @brief 具体实现
        /// @param args 参数列表
        /// @return 返回值
        std::any invoke_impl(const std::any &args) const
        {
            auto tuple = std::any_cast<ArgsTuple>(args);
            auto impl = [this](auto... args) -> Ret
            {
                return std::invoke(m_ptr, args...);
            };

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
