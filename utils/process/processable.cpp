#pragma once

#include "processable.hpp"

namespace utils
{
    void Processable::_process(double delta) {}
    void Processable::_physics_process(double delta) {}

    void Processable::set_process_mode(ProcessMode mode) { m_process_mode = mode; }
    Processable::ProcessMode Processable::get_process_mode() const { return m_process_mode; }
    void Processable::set_process(bool enabled) { m_is_process_enabled = enabled; }
    bool Processable::is_process_enabled() const { return m_is_process_enabled; }
    void Processable::set_physics_process(bool enabled) { m_is_physics_process_enabled = enabled; }
    bool Processable::is_physics_process_enabled() const { return m_is_physics_process_enabled; }

} // namespace utils
