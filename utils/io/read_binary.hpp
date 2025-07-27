#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <base/core/exception.hpp>

namespace utils
{
    /// @brief 从输入流中以二进制形式读取数据
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam R 返回数据类型
    /// @param is 输入流
    /// @param result 输出结果
    template <typename C, typename T, typename R>
    void read_binary_from_stream(std::basic_istream<C, T> &is, R &result)
    {
        static_assert(std::is_trivial_v<R>, "Cannot read a non-trivial type in binary form");

        if (!is)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to read binary from invalid stream");

        if (!is.read(reinterpret_cast<char *>(&result), sizeof(R)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");
    }

    /// @brief 从输入流中以二进制形式读取数据
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam E 数组元素类型
    /// @tparam N 数组长度
    /// @param is 输入流
    /// @param result 输出结果
    template <typename C, typename T, typename E, std::size_t N>
    void read_binary_from_stream(std::basic_istream<C, T> &is, std::array<E, N> &result)
    {
        static_assert(std::is_trivial_v<E>, "Cannot read a non-trivial type in binary form");

        if (!is)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to read binary from invalid stream");

        typename std::array<E, N>::size_type size = 0;
        if (!is.read(reinterpret_cast<char *>(&size), sizeof(typename std::array<E, N>::size_type)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");

        if (size != N)
            throw BASE_MAKE_RUNTIME_ERROR(
                "The actual size of the array does not match the expected size",
                ", actual: ", size,
                ", expected: ", N);

        if (!is.read(reinterpret_cast<char *>(result.data()), sizeof(E) * size))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");
    }

    /// @brief 从输入流中以二进制形式读取数据
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam E 数组元素类型
    /// @tparam A 分配器类型
    /// @param is 输入流
    /// @param result 输出结果
    template <typename C, typename T, typename E, typename A>
    void read_binary_from_stream(std::basic_istream<C, T> &is, std::vector<E, A> &result)
    {
        static_assert(std::is_trivial_v<E>, "Cannot read a non-trivial type in binary form");

        if (!is)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to read binary from invalid stream");

        typename std::vector<E, A>::size_type size = 0;
        if (!is.read(reinterpret_cast<char *>(&size), sizeof(typename std::vector<E, A>::size_type)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");

        if (size == 0)
        {
            result.clear();
            return;
        }

        result.resize(size);
        if (!is.read(reinterpret_cast<char *>(result.data()), sizeof(E) * size))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");
    }

    /// @brief 从输入流中以二进制形式读取数据
    /// @tparam SC 输入流字符类型
    /// @tparam StrA 字符串分配器类型
    /// @tparam ST 输入流字符特征
    /// @tparam StrC 字符串字符类型
    /// @tparam StrT 字符串字符特征
    /// @param is 输入流
    /// @param result 输出结果
    template <typename SC, typename ST, typename StrC, typename StrT, typename StrA>
    void read_binary_from_stream(std::basic_istream<SC, ST> &is, std::basic_string<StrC, StrT, StrA> &result)
    {
        static_assert(std::is_trivial_v<StrC>, "Cannot read a non-trivial type in binary form");

        if (!is)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to read binary from invalid stream");

        typename std::basic_string<StrC, StrT, StrA>::size_type length = 0;
        if (!is.read(reinterpret_cast<char *>(&length), sizeof(typename std::basic_string<StrC, StrT, StrA>::size_type)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");

        if (length == 0)
        {
            result.clear();
            return;
        }

        result.resize(length);
        if (!is.read(reinterpret_cast<char *>(result.data()), sizeof(StrC) * length))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to read binary from stream");
    }

} // namespace utils
