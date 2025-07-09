#include "physics_frame_manager.hpp"

namespace utils
{
    void PhysicsFrameManager::_add_physics_frame_count()
    {
        m_last_physics_update_delta = get_physics_update_delta();
        m_last_physics_update_time = get_current_time();
        m_physics_frame_count++;
    }

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
