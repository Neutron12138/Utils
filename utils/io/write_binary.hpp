#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <base/core/exception.hpp>

namespace utils
{
    /// @brief 向输出流中以二进制形式储存数据
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam R 返回数据类型
    /// @param os 输出流
    /// @param value  输入数据
    template <typename C, typename T, typename R>
    void write_binary_to_stream(std::basic_ostream<C, T> &os, const R &value)
    {
        static_assert(std::is_trivial_v<R>, "Cannot write a non-trivial type in binary form");

        if (!os)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to write binary to invalid stream");

        if (!os.write(reinterpret_cast<const char *>(&value), sizeof(R)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");
    }

    /// @brief 向输出流中以二进制形式储存数据
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam E 数组元素类型
    /// @tparam N 数组长度
    /// @param os 输出流
    /// @param value  输入数据
    template <typename C, typename T, typename E, std::size_t N>
    void write_binary_to_stream(std::basic_ostream<C, T> &os, const std::array<E, N> &value)
    {
        static_assert(std::is_trivial_v<E>, "Cannot write a non-trivial type in binary form");

        if (!os)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to write binary to invalid stream");

        constexpr typename std::array<E, N>::size_type size = N;
        if (!os.write(reinterpret_cast<const char *>(&size), sizeof(typename std::array<E, N>::size_type)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");

        if (size == 0)
            return;

        if (!os.write(reinterpret_cast<const char *>(value.data()), sizeof(E) * size))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");
    }

    /// @brief 向输出流中以二进制形式储存数据
    /// @tparam C 字符类型
    /// @tparam T 字符特征
    /// @tparam E 数组元素类型
    /// @tparam A 分配器类型
    /// @param os 输出流
    /// @param value  输入数据
    template <typename C, typename T, typename E, typename A>
    void write_binary_to_stream(std::basic_ostream<C, T> &os, const std::vector<E, A> &value)
    {
        static_assert(std::is_trivial_v<E>, "Cannot write a non-trivial type in binary form");

        if (!os)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to write binary to invalid stream");

        const typename std::vector<E, A>::size_type size = value.size();
        if (!os.write(reinterpret_cast<const char *>(&size), sizeof(typename std::vector<E, A>::size_type)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");

        if (size == 0)
            return;

        if (!os.write(reinterpret_cast<const char *>(value.data()), sizeof(E) * size))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");
    }

    /// @brief 向输出流中以二进制形式储存数据
    /// @tparam SC 输出流字符类型
    /// @tparam StrA 字符串分配器类型
    /// @tparam ST 输出流字符特征
    /// @tparam StrC 字符串字符类型
    /// @tparam StrT 字符串字符特征
    /// @param os 输出流
    /// @param value 输入数据
    template <typename SC, typename ST, typename StrC, typename StrT, typename StrA>
    void write_binary_to_stream(std::basic_ostream<SC, ST> &os, const std::basic_string<StrC, StrT, StrA> &value)
    {
        static_assert(std::is_trivial_v<StrC>, "Cannot write a non-trivial type in binary form");

        if (!os)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to write binary to invalid stream");

        const typename std::basic_string<StrC, StrT, StrA>::size_type length = value.length();
        if (!os.write(reinterpret_cast<const char *>(&length), sizeof(typename std::basic_string<StrC, StrT, StrA>::size_type)))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");

        if (length == 0)
            return;

        if (!os.write(reinterpret_cast<const char *>(value.data()), sizeof(StrC) * length))
            throw BASE_MAKE_RUNTIME_ERROR("Failed to write binary to stream");
    }

} // namespace utils
