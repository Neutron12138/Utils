#pragma once

#include "physics_frame_manager.hpp"

namespace utils
{
    void PhysicsFrameManager::_on_first_physics_frame() {}
    void PhysicsFrameManager::_on_physics_frame_updated(double delta) {}

    const PhysicsFrameManager::TimePoint &PhysicsFrameManager::get_last_physics_update_time() const { return m_last_physics_update_time; }
    double PhysicsFrameManager::get_physics_update_interval() const { return m_physics_update_interval; }
    void PhysicsFrameManager::set_physics_update_interval(double physics_update_interval) { m_physics_update_interval = physics_update_interval; }
    double PhysicsFrameManager::get_last_physics_update_delta() const { return m_last_physics_update_delta; }
    base::Size PhysicsFrameManager::get_physics_frame_count() const { return m_physics_frame_count; }

    void PhysicsFrameManager::_add_physics_frame_count()
    {
        m_last_physics_update_delta = get_physics_update_delta();
        m_last_physics_update_time = get_current_time();
        m_physics_frame_count++;
    }

    PhysicsFrameManager::FPS PhysicsFrameManager::get_current_physics_fps() const { return static_cast<FPS>(1.0 / m_last_physics_update_delta); }
    PhysicsFrameManager::FPS PhysicsFrameManager::get_target_physics_fps() const { return static_cast<FPS>(1.0 / m_physics_update_interval); }
    void PhysicsFrameManager::set_target_physics_fps(FPS target_physics_fps) { m_physics_update_interval = 1.0 / static_cast<double>(target_physics_fps); }
    void PhysicsFrameManager::set_unlimited_physics_fps() { m_physics_update_interval = 0.0; }
    double PhysicsFrameManager::get_physics_update_delta() const { return (get_current_time() - m_last_physics_update_time).count(); }

    void PhysicsFrameManager::request_first_physics_frame()
    {
        if (m_physics_frame_count != 0)
            return;

        _on_first_physics_frame();
        _add_physics_frame_count();
    }

    void PhysicsFrameManager::request_first_frame()
    {
        request_first_physics_frame();
        FrameManager::request_first_frame();
    }

    void PhysicsFrameManager::update()
    {
        // 计算距离上一物理帧经过的时间
        double delta = get_physics_update_delta();
        if (delta >= m_physics_update_interval)
        {
            _on_physics_frame_updated(delta);
            _add_physics_frame_count();
        }

        FrameManager::update();
    }

    void PhysicsFrameManager::restart()
    {
        FrameManager::restart();
        m_last_physics_update_time = get_current_time();
        m_last_physics_update_delta = 0.0;
        m_physics_frame_count = 0;
    }

} // namespace utils
