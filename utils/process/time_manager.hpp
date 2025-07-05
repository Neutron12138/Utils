#pragma once

#include <chrono>
#include <base/core/time.hpp>
#include <base/core/polymorphic_object.hpp>

namespace utils
{
    template <typename ClockType>
    class TimeManager;
    template <typename ClockType>
    using TimeManagerRef = ::base::Ref<TimeManager<ClockType>>;
    template <typename ClockType>
    using TimeManagerWeakRef = ::base::WeakRef<TimeManager<ClockType>>;

    /// @brief 时间管理器
    /// @tparam ClockType 时钟类型
    template <typename ClockType>
    class TimeManager : public ::base::Time<ClockType>,
                        virtual public ::base::PolymorphicObject
    {
    public:
        using Clock = typename ::base::Time<ClockType>::Clock;
        using TimePoint = typename ::base::Time<ClockType>::TimePoint;
        using Duration = typename ::base::Time<ClockType>::Duration;

        static inline TimePoint get_current_time() { return ::base::Time<ClockType>::get_current_time(); }

    private:
        /// @brief 开始时间
        TimePoint m_start_time = get_current_time();

    public:
        inline TimeManager() = default;
        inline ~TimeManager() override = default;

    public:
        inline const TimePoint &get_start_time() const { return m_start_time; }

        /// @brief 获取自start_time以来总共经过的时间
        /// @return 经过的时间（秒）
        inline double get_total_elapsed() const { return Duration(get_current_time() - m_start_time).count(); }

    public:
        /// @brief 重新开始计时
        virtual void restart() { m_start_time = get_current_time(); }
    };

} // namespace utils
