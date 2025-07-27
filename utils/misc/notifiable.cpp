#pragma once

#include "notifiable.hpp"

namespace utils
{
    void Notifiable::_on_notified(base::Int64 notification) {}

    bool Notifiable::is_notification_enabled() const { return m_is_notification_enabled; }
    void Notifiable::set_notification_enabled(bool is_notification_enabled) { m_is_notification_enabled = is_notification_enabled; }

    void Notifiable::receive_notification(base::Int64 notification)
    {
        if (m_is_notification_enabled)
            _on_notified(notification);
    }

    void send_notification(Notifiable &notifiable, base::Int64 notification)
    {
        notifiable.receive_notification(notification);
    }

} // namespace utils
