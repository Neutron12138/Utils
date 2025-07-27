#pragma once

#include <base/core/type.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace utils
{
    BASE_DECLARE_REF_TYPE(Event);

    /// @brief 事件基类
    class Event : public base::PolymorphicObject
    {
    private:
        /// @brief 该事件是否已经被处理
        bool m_is_handled = false;

    public:
        Event() = default;
        ~Event() override = default;

    public:
        bool is_handled() const;
        void set_handled();

    public:
        /// @brief 获取事件类型
        /// @return 事件类型
        virtual base::Int64 get_event_type() const = 0;
    };

} // namespace utils
