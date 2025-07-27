#pragma once

#include "frame_manager.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(PhysicsFrameManager);

    /// @brief 物理帧管理器
    class PhysicsFrameManager : public FrameManager
    {
    private:
        /// @brief 上次物理帧更新时间
        TimePoint m_last_physics_update_time = get_current_time();
        /// @brief 物理更新间隔，用来限制物理帧帧率
        double m_physics_update_interval = 1.0 / 60.0;
        /// @brief 上次物理更新的时间间隔
        double m_last_physics_update_delta = 0.0;
        /// @brief 总物理帧数
        base::Size m_physics_frame_count = 0;

    public:
        PhysicsFrameManager() = default;
        ~PhysicsFrameManager() override = default;

    protected:
        /// @brief 自启动以来的第一帧
        virtual void _on_first_physics_frame();

        /// @brief 当物理帧更新时
        /// @param delta 时间间隔
        virtual void _on_physics_frame_updated(double delta);

    public:
        const TimePoint &get_last_physics_update_time() const;
        double get_physics_update_interval() const;
        void set_physics_update_interval(double physics_update_interval);
        double get_last_physics_update_delta() const;
        base::Size get_physics_frame_count() const;

    protected:
        /// @brief 增加一帧
        virtual void _add_physics_frame_count();

    public:
        /// @brief 获取当前物理帧帧率
        /// @return 当前物理帧帧率
        FPS get_current_physics_fps() const;

        /// @brief 获取目标物理帧帧率
        /// @return 目标物理帧帧率
        FPS get_target_physics_fps() const;

        /// @brief 设置目标物理帧帧率
        /// @param target_physics_fps 目标物理帧帧率
        void set_target_physics_fps(FPS target_physics_fps);

        /// @brief 关闭物理帧帧率限制
        void set_unlimited_physics_fps();

        /// @brief 获取距离上一物理帧所经过的时间
        /// @return 距离上一物理帧所经过的时间
        double get_physics_update_delta() const;

        /// @brief 请求第一物理帧
        virtual void request_first_physics_frame();

        /// @brief 请求第一帧
        void request_first_frame() override;

        /// @brief 检查是否需要更新
        void update() override;

        /// @brief 重新开始计时
        void restart() override;
    };

} // namespace utils
