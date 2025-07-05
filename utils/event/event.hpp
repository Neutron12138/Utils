#pragma once

#include <base/core/type.hpp>
#include <base/core/reference_object.hpp>

namespace utils
{
    class Event;
    using EventRef = ::base::Ref<Event>;
    using EventWeakRef = ::base::WeakRef<Event>;

    /// @brief 事件基类
    class Event : public ::base::ReferenceObject
    {
    private:
        /// @brief 该事件是否已经被处理
        bool m_is_handled = false;

    public:
        inline Event() = default;
        inline ~Event() override = default;

    public:
        inline bool is_handled() const { return m_is_handled; }
        inline void set_handled() { m_is_handled = true; }

    public:
        /// @brief 获取事件类型
        /// @return 事件类型
        inline virtual ::base::Int64 get_event_type() const = 0;
    };

} // namespace utils
