#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <base/core/type.hpp>
#include <base/core/ref.hpp>
#include <base/misc/time.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace base
{
    BASE_DECLARE_REF_TYPE(Logger);

    /// @brief 日志输出器
    class Logger : public SystemTime,
                   public PolymorphicObject
    {
    public:
        /// @brief 日志等级
        enum class LogLevel : Int32
        {
            /// @brief 未知
            Unknown,
            /// @brief 调试
            Debug,
            /// @brief 信息
            Info,
            /// @brief 警告
            Warning,
            /// @brief 错误
            Error,
        };

        /// @brief 输出流引用包装器
        using OStreamRefWrapper = RefWrapper<std::ostream>;
        /// @brief 输出流数组
        using OStreamArray = std::vector<OStreamRefWrapper>;
        /// @brief 输出流迭代器
        using OStreamConstIterator = OStreamArray::const_iterator;

        template <typename... Ts>
        static std::string format_log(LogLevel level, Ts &&...args)
        {
            std::time_t time = Clock::to_time_t(get_current_time());
            std::tm *tm = std::localtime(&time);

            std::string str = base::to_string(
                "[time: ", std::put_time(tm, "%Y-%m-%d %H:%M:%S"), ", ",
                "level: ", level, "]\n",
                std::forward<Ts>(args)...);

            return base::to_string(
                "--------------------\n",
                str, "\n",
                "--------------------\n");
        }

    private:
        /// @brief 日志流对象，所有日志都会输入进去
        std::stringstream m_log_stream = {};
        /// @brief 是否启用标准输出（仅std::cout）
        bool m_is_standard_output_enabled = true;
        /// @brief 是否启用额外输出流
        bool m_is_extra_ostream_enabled = true;
        /// @brief 额外输出流引用数组
        OStreamArray m_extra_ostreams = {};

    public:
        Logger() = default;
        ~Logger() noexcept override = default;

    public:
        const std::stringstream &get_log_stream() const;
        void set_standard_output_enabled(bool enabled);
        bool is_standard_output_enabled() const;
        void set_extra_ostream_enabled(bool enabled);
        bool is_extra_ostream_enabled() const;
        const OStreamArray &get_extra_ostreams() const;

    protected:
        void _clear_extra_ostreams();
        void _add_extra_ostream(const OStreamRefWrapper &ostream);
        void _remove_extra_ostream(const OStreamConstIterator &iter);

        /// @brief 输出日志
        /// @param content 日志内容
        virtual void _output_log(const std::string &content);

    public:
        void add_extra_ostream(const OStreamRefWrapper &ostream);
        void clear_extra_ostreams();

    public:
        /// @brief 输出Unknown日志
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        template <typename... T>
        void logu(T... args);

        /// @brief 输出Debug日志
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        template <typename... T>
        void logd(T... args);

        /// @brief 输出Info日志
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        template <typename... T>
        void logi(T... args);

        /// @brief 输出Warning日志
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        template <typename... T>
        void logw(T... args);

        /// @brief 输出Error日志
        /// @tparam ...T 参数类型列表
        /// @param ...args 参数列表
        template <typename... T>
        void loge(T... args);
    };

    std::ostream &operator<<(std::ostream &os, Logger::LogLevel level);

} // namespace base
