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
        ProcessManager() = default;
        ~ProcessManager() override = default;

    public:
        void set_paused(bool paused);
        bool is_paused() const;
        double get_time_scale() const;
        void set_time_scale(double time_scale);

    protected:
        /// @brief 让Processable对象进行更新
        /// @param processable 对象
        /// @param delta 时间增量
        void _request_process(Processable &processable, double delta) const;

        /// @brief 让Processable对象进行更新
        /// @param processable 对象
        /// @param delta 时间增量
        void _request_physics_process(Processable &processable, double delta) const;
    };

} // namespace utils
