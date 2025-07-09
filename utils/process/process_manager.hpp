#pragma once

#include "../frame/physics_frame_manager.hpp"
#include "processable.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(ProcessManager);

    /// @brief 逻辑处理管理器
    class ProcessManager : public PhysicsFrameManager
    {
    private:
        /// @brief 是否暂停
        bool m_paused = false;
        /// @brief 时间缩放
        double m_time_scale = 1.0;

    public:
        inline ProcessManager() = default;
        inline ~ProcessManager() override = default;

    protected:
        void _on_first_frame() override = 0;
        void _on_frame_updated(double delta) override = 0;
        void _on_first_physics_frame() override = 0;
        void _on_physics_frame_updated(double delta) override = 0;

    public:
        inline void set_paused(bool paused) { m_paused = paused; }
        inline bool is_paused() const { return m_paused; }
        inline double get_time_scale() const { return m_time_scale; }
        inline void set_time_scale(double time_scale) { m_time_scale = time_scale; }
    };

} // namespace utils
