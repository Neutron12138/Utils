#pragma once

#include "event.hpp"

namespace utils
{
    bool Event::is_handled() const { return m_is_handled; }
    void Event::set_handled() { m_is_handled = true; }

} // namespace utils
