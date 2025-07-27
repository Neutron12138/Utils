#pragma once

#include <fstream>
#include <vector>
#include <base/core/type.hpp>
#include <base/core/exception.hpp>

namespace utils
{
    /// @brief 以二进制方式从输入流读取全部内容
    /// @param is 输入流
    /// @return 缓冲区
    std::vector<base::Byte> read_bytes_from_stream(std::istream &is)
    {
        if (!is)
            throw BASE_MAKE_RUNTIME_ERROR("Invalid input stream");

        is.seekg(0, std::ios::end);
        std::streamsize size = is.tellg();
        if (size <= 0)
            throw BASE_MAKE_RUNTIME_ERROR("Invalid input stream size");
        is.seekg(std::ios::beg);

        std::vector<base::Byte> buffer(size);
        if (!is.read(reinterpret_cast<char *>(buffer.data()), size))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read from input stream");

        return buffer;
    }

    /// @brief 以二进制方式从文件读取全部内容
    /// @param filename 文件名
    /// @return 缓冲区
    std::vector<base::Byte> read_bytes_from_file(const std::string &filename)
    {
        std::ifstream fin;
        fin.open(filename, std::ios::binary);
        if (fin.bad())
            throw BASE_MAKE_RUNTIME_ERROR("Failed to open file: \"", filename, "\"");

        return read_bytes_from_stream(fin);
    }

    /// @brief 以二进制方式从输入流读取全部内容
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam A 分配器类型
    /// @param is 输入流
    /// @return 缓冲区
    template <typename C, typename T, typename A = std::allocator<base::Byte>>
    std::vector<base::Byte, A> read_bytes_from_stream(std::basic_istream<C, T> &is)
    {
        if (!is)
            throw BASE_MAKE_RUNTIME_ERROR("Invalid input stream");

        is.seekg(0, std::ios::end);
        std::streamsize size = is.tellg();
        if (size <= 0)
            throw BASE_MAKE_RUNTIME_ERROR("Invalid input stream size");
        is.seekg(std::ios::beg);

        std::vector<base::Byte, A> buffer(size);
        if (!is.read(reinterpret_cast<char *>(buffer.data()), size))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read from input stream");

        return buffer;
    }

    /// @brief 以二进制方式从文件读取全部内容
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam A 分配器类型
    /// @param filename 文件名
    /// @return 缓冲区
    template <typename C, typename T, typename A = std::allocator<base::Byte>>
    std::vector<base::Byte, A> read_bytes_from_file(const std::basic_string<C, T, A> &filename)
    {
        std::basic_ifstream<C, T> fin;
        fin.open(filename, std::ios::binary);
        if (fin.bad())
            throw BASE_MAKE_RUNTIME_ERROR("Failed to open file: \"", filename, "\"");

        return read_bytes_from_stream(fin);
    }

} // namespace utils
