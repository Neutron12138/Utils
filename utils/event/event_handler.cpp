#pragma once

#include "event_handler.hpp"

namespace utils
{
    void EventHandler::_handle_event(const EventRef &event) {}

    bool EventHandler::is_event_handling_enabled() const { return m_is_event_handling_enabled; }
    void EventHandler::set_event_handling_enabled(bool enabled) { m_is_event_handling_enabled = enabled; }

    void EventHandler::receive_event(const EventRef &event)
    {
        if (m_is_event_handling_enabled)
            _handle_event(event);
    }

} // namespace utils
