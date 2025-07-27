#pragma once

#include <base/core/type.hpp>
#include <base/core/ref.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace utils
{
    BASE_DECLARE_REF_TYPE(Notifiable);

    /// @brief 可通知对象
    class Notifiable : virtual public base::PolymorphicObject
    {
    private:
        /// @brief 是否启用通知处理
        bool m_is_notification_enabled = true;

    public:
        Notifiable() = default;
        ~Notifiable() noexcept override = default;

    protected:
        /// @brief 被通知时
        /// @param notification 具体通知
        virtual void _on_notified(base::Int64 notification);

    public:
        bool is_notification_enabled() const;
        void set_notification_enabled(bool is_notification_enabled);

    public:
        /// @brief 该对象收到通知
        /// @param notification 具体通知
        virtual void receive_notification(base::Int64 notification);
    };

    /// @brief 对对象发送一个通知
    /// @param notifiable 待通知对象
    /// @param notification 具体通知
    void send_notification(Notifiable &notifiable, base::Int64 notification);

} // namespace utils
