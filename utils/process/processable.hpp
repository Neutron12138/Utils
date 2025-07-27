#pragma once

#include <base/core/type.hpp>
#include <base/core/ref.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace utils
{
    class ProcessManager;
    BASE_DECLARE_REF_TYPE(Processable);

    /// @brief 可进行逻辑处理的对象
    class Processable : virtual public base::PolymorphicObject
    {
    public:
        friend ProcessManager;

        /// @brief 处理模式
        enum class ProcessMode : base::Int32
        {
            /// @brief 永远不处理
            Disabled,
            /// @brief 永远处理
            Always,
            /// @brief 仅在非暂停时处理
            Pausable,
            /// @brief 仅在暂停时处理
            WhenPaused,
        };

    private:
        /// @brief 处理模式
        ProcessMode m_process_mode = ProcessMode::Pausable;
        /// @brief 启用空闲帧处理
        bool m_is_process_enabled = true;
        /// @brief 启用物理帧处理
        bool m_is_physics_process_enabled = true;

    public:
        Processable() = default;
        ~Processable() override = default;

    protected:
        /// @brief 空闲帧处理
        /// @param delta 距上一次处理经过的时间，会受到time_scale影响
        virtual void _process(double delta);

        /// @brief 物理帧处理
        /// @param delta 距上一次处理经过的时间，会受到time_scale影响
        virtual void _physics_process(double delta);

    public:
        void set_process_mode(ProcessMode mode);
        ProcessMode get_process_mode() const;
        void set_process(bool enabled);
        bool is_process_enabled() const;
        void set_physics_process(bool enabled);
        bool is_physics_process_enabled() const;
    };

} // namespace utils
