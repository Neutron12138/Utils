#pragma once

#include "frame_manager.hpp"

namespace utils
{
    void FrameManager::_on_first_frame() {}
    void FrameManager::_on_frame_updated(double delta) {}

    const FrameManager::TimePoint &FrameManager::get_last_update_time() const { return m_last_update_time; }
    double FrameManager::get_update_interval() const { return m_update_interval; }
    void FrameManager::set_update_interval(double update_interval) { m_update_interval = update_interval; }
    double FrameManager::get_last_update_delta() const { return m_last_update_delta; }
    base::Size FrameManager::get_frame_count() const { return m_frame_count; }

    void FrameManager::_add_frame_count()
    {
        m_last_update_delta = get_update_delta();
        m_last_update_time = get_current_time();
        m_frame_count++;
    }

    FrameManager::FPS FrameManager::get_current_fps() const { return static_cast<FPS>(1.0 / m_last_update_delta); }
    FrameManager::FPS FrameManager::get_target_fps() const { return static_cast<FPS>(1.0 / m_update_interval); }
    void FrameManager::set_target_fps(FPS target_fps) { m_update_interval = 1.0 / static_cast<double>(target_fps); }
    void FrameManager::set_unlimited_fps() { m_update_interval = 0.0; }
    double FrameManager::get_update_delta() const { return (get_current_time() - m_last_update_time).count(); }

    void FrameManager::request_first_frame()
    {
        if (m_frame_count != 0)
            return;

        _on_first_frame();
        _add_frame_count();
    }

    void FrameManager::update()
    {
        // 计算距离上一帧经过的时间
        double delta = get_update_delta();
        if (delta < m_update_interval)
            return;

        _on_frame_updated(delta);
        _add_frame_count();
    }

    void FrameManager::restart()
    {
        TimeManager::restart();
        m_last_update_time = get_current_time();
        m_last_update_delta = 0.0;
        m_frame_count = 0;
    }

} // namespace utils
