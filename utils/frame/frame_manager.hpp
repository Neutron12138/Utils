#pragma once

#include <base/core/type.hpp>
#include "../time/time_manager.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(FrameManager);

    /// @brief 帧管理器，管理更新频率
    class FrameManager : public SteadyTimeManager
    {
    public:
        /// @brief 帧率类型
        using FPS = base::UInt32;

    private:
        /// @brief 上一帧更新时间
        TimePoint m_last_update_time = get_current_time();
        /// @brief 更新间隔，用来限制帧率
        double m_update_interval = 1.0 / 60.0;
        /// @brief 上次更新的时间间隔
        double m_last_update_delta = 0.0;
        /// @brief 总帧数
        base::Size m_frame_count = 0;

    public:
        FrameManager() = default;
        ~FrameManager() override = default;

    protected:
        /// @brief 自启动以来的第一帧
        virtual void _on_first_frame();

        /// @brief 当空闲帧更新时
        /// @param delta 时间间隔
        virtual void _on_frame_updated(double delta);

    public:
        const TimePoint &get_last_update_time() const;
        double get_update_interval() const;
        void set_update_interval(double update_interval);
        double get_last_update_delta() const;
        base::Size get_frame_count() const;

    protected:
        /// @brief 增加一帧
        virtual void _add_frame_count();

    public:
        /// @brief 获取当前帧率
        /// @return 当前帧率
        FPS get_current_fps() const;

        /// @brief 获取目标帧率
        /// @return 目标帧率
        FPS get_target_fps() const;

        /// @brief 设置目标帧率
        /// @param target_fps 目标帧率
        void set_target_fps(FPS target_fps);

        /// @brief 关闭帧率限制
        void set_unlimited_fps();

        /// @brief 获取距离上一帧所经过的时间
        /// @return 距离上一帧经过的时间
        double get_update_delta() const;

        /// @brief 请求第一帧
        virtual void request_first_frame();

        /// @brief 检查是否需要更新
        virtual void update();

        /// @brief 重新开始计时
        void restart() override;
    };

} // namespace utils
