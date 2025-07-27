#pragma once

#include <fstream>
#include <base/core/exception.hpp>

namespace utils
{
    /// @brief 以文本方式从输入流中读取全部内容
    /// @param is 输入流
    /// @return 内容字符串
    std::string read_string_from_stream(std::istream &is)
    {
        if (!is)
            throw BASE_MAKE_RUNTIME_ERROR("Invalid input stream");

        return std::string(
            std::istreambuf_iterator<char>(is),
            std::istreambuf_iterator<char>());
    }

    /// @brief 以文本方式从文件中读取全部内容
    /// @param filename 文件名
    /// @return 内容字符串
    std::string read_string_from_file(const std::string &filename)
    {
        std::ifstream fin;
        fin.open(filename);
        if (!fin)
            throw BASE_MAKE_RUNTIME_ERROR("Failed to open file: \"", filename, "\"");

        return std::string(
            std::istreambuf_iterator<char>(fin),
            std::istreambuf_iterator<char>());
    }

    /// @brief 以文本方式从输入流中读取全部内容
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam A 分配器类型
    /// @param is 输入流
    /// @return 内容字符串
    template <typename C, typename T, typename A>
    std::basic_string<C, T, A> read_string_from_stream(std::basic_istream<C, T> &is)
    {
        if (!is)
            throw BASE_MAKE_RUNTIME_ERROR("Invalid input stream");

        return std::basic_string<C, T, A>(
            std::istreambuf_iterator<C, T>(is),
            std::istreambuf_iterator<C, T>());
    }

    /// @brief 以文本方式从文件中读取全部内容
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam A 分配器类型
    /// @param filename 文件名
    /// @return 内容字符串
    template <typename C, typename T, typename A>
    std::basic_string<C, T, A> read_string_from_file(const std::basic_string<C, T, A> &filename)
    {
        std::basic_ifstream<C, T> fin;
        fin.open(filename);
        if (!fin)
            throw BASE_MAKE_RUNTIME_ERROR("Failed to open file: \"", filename, "\"");

        return std::basic_string<C, T, A>(
            std::istreambuf_iterator<C, T>(fin),
            std::istreambuf_iterator<C, T>());
    }

} // namespace utils
