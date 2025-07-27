#pragma once

#include <base/misc/time.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace utils
{
    BASE_DECLARE_REF_TEMPLATE_TYPE(ClockT, TimeManager);

    /// @brief 时间管理器
    /// @tparam ClockT 时钟类型
    template <typename ClockT>
    class TimeManager : public base::Time<ClockT>,
                        virtual public base::PolymorphicObject
    {
    public:
        using Time = base::Time<ClockT>;
        using Clock = typename Time::Clock;
        using TimePoint = typename Time::TimePoint;
        using Duration = typename Time::Duration;

        static TimePoint get_current_time() { return Time::get_current_time(); }

    private:
        /// @brief 开始时间
        TimePoint m_start_time = get_current_time();

    public:
        TimeManager() = default;
        ~TimeManager() override = default;

    public:
        const TimePoint &get_start_time() const { return m_start_time; }

        /// @brief 获取自start_time以来总共经过的时间
        /// @return 经过的时间（秒）
        double get_total_elapsed() const { return (get_current_time() - m_start_time).count(); }

    public:
        /// @brief 重新开始计时
        virtual void restart() { m_start_time = get_current_time(); }
    };

    using SteadyTimeManager = TimeManager<std::chrono::steady_clock>;
    using SystemTimeManager = TimeManager<std::chrono::system_clock>;
    using HighResolutionTimeManager = TimeManager<std::chrono::high_resolution_clock>;

} // namespace utils
