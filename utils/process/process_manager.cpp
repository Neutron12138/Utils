#pragma once

#include "process_manager.hpp"

namespace utils
{
    void ProcessManager::set_paused(bool paused) { m_paused = paused; }
    bool ProcessManager::is_paused() const { return m_paused; }
    double ProcessManager::get_time_scale() const { return m_time_scale; }
    void ProcessManager::set_time_scale(double time_scale) { m_time_scale = time_scale; }

    void ProcessManager::_request_process(Processable &processable, double delta) const
    {
        if (processable.is_process_enabled())
            processable._process(delta * m_time_scale);
    }

    void ProcessManager::_request_physics_process(Processable &processable, double delta) const
    {
        if (processable.is_physics_process_enabled())
            processable._physics_process(delta * m_time_scale);
    }

} // namespace utils
