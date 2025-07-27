#pragma once

#include "event.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(EventHandler);

    /// @brief 事件处理器
    class EventHandler : virtual public base::PolymorphicObject
    {
    private:
        /// @brief 是否启用事件处理
        bool m_is_event_handling_enabled = true;

    public:
        EventHandler() = default;
        ~EventHandler() override = default;

    protected:
        /// @brief 处理事件
        /// @param event 待处理事件
        virtual void _handle_event(const EventRef &event);

    public:
        bool is_event_handling_enabled() const;
        void set_event_handling_enabled(bool enabled);

    public:
        /// @brief 收到事件
        /// @param event 待处理事件
        virtual void receive_event(const EventRef &event);
    };

} // namespace utils
