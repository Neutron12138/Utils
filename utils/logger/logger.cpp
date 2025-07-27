#pragma once

#include <iomanip>
#include <base/core/to_string.hpp>
#include "logger.hpp"

namespace base
{
    const std::stringstream &Logger::get_log_stream() const { return m_log_stream; }
    void Logger::set_standard_output_enabled(bool enabled) { m_is_standard_output_enabled = enabled; }
    bool Logger::is_standard_output_enabled() const { return m_is_standard_output_enabled; }
    void Logger::set_extra_ostream_enabled(bool enabled) { m_is_extra_ostream_enabled = enabled; }
    bool Logger::is_extra_ostream_enabled() const { return m_is_extra_ostream_enabled; }
    const Logger::OStreamArray &Logger::get_extra_ostreams() const { return m_extra_ostreams; }

    void Logger::_clear_extra_ostreams() { m_extra_ostreams.clear(); }
    void Logger::_add_extra_ostream(const OStreamRefWrapper &ostream) { m_extra_ostreams.push_back(ostream); }
    void Logger::_remove_extra_ostream(const OStreamConstIterator &iter) { m_extra_ostreams.erase(iter); }

    void Logger::_output_log(const std::string &content)
    {
        m_log_stream << content;

        if (m_is_standard_output_enabled)
            std::cout << content;

        if (!m_is_extra_ostream_enabled)
            return;

        for (auto &os : m_extra_ostreams)
            if (os.get().good())
                os.get() << content;
    }

    void Logger::add_extra_ostream(const OStreamRefWrapper &ostream) { _add_extra_ostream(ostream); }
    void Logger::clear_extra_ostreams() { _clear_extra_ostreams(); }

    template <typename... T>
    void Logger::logu(T... args) { _output_log(format_log(LogLevel::Unknown, args...)); }

    template <typename... T>
    void Logger::logd(T... args) { _output_log(format_log(LogLevel::Debug, args...)); }

    template <typename... T>
    void Logger::logi(T... args) { _output_log(format_log(LogLevel::Info, args...)); }

    template <typename... T>
    void Logger::logw(T... args) { _output_log(format_log(LogLevel::Warning, args...)); }

    template <typename... T>
    void Logger::loge(T... args) { _output_log(format_log(LogLevel::Error, args...)); }

    std::ostream &operator<<(std::ostream &os, Logger::LogLevel level)
    {
        switch (level)
        {
        case Logger::LogLevel::Debug:
            os << "Debug";
            break;

        case Logger::LogLevel::Info:
            os << "Info";
            break;

        case Logger::LogLevel::Warning:
            os << "Warning";
            break;

        case Logger::LogLevel::Error:
            os << "Error";
            break;

        default:
            os << "Unknown";
            break;
        }
        return os;
    }

} // namespace base
