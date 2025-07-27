#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <base/core/exception.hpp>

namespace utils
{
    template <typename C, typename T, typename E, std::size_t N>
    std::basic_ostream<C, T> &operator<<(std::basic_ostream<C, T> &os, const std::array<E, N> &array)
    {
        if (!os)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to print to invalid stream");

        os << "{ ";
        for (const auto &elem : array)
            os << elem << ", ";
        os << "}";
        return os;
    }

    template <typename C, typename T, typename E>
    std::basic_ostream<C, T> &operator<<(std::basic_ostream<C, T> &os, const std::vector<E> &array)
    {
        if (!os)
            throw BASE_MAKE_INVALID_ARGUMENT_ERROR("Unable to print to invalid stream");

        os << "{ ";
        for (const auto &elem : array)
            os << elem << ", ";
        os << "}";
        return os;
    }

} // namespace utils
