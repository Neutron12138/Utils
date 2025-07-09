#pragma once

#include <iostream>
#include <base/core/type.hpp>

namespace utils
{
    /// @brief 灰度像素
    class PixelGrey
    {
    public:
        /// @brief 灰度
        base::UInt8 grey;

    public:
        inline PixelGrey() = default;
        constexpr PixelGrey(base::UInt8 g) : grey(g) {}
        inline ~PixelGrey() = default;
    };

    /// @brief 灰度、透明度像素
    class PixelGA : public PixelGrey
    {
    public:
        /// @brief 透明度
        base::UInt8 alpha;

    public:
        inline PixelGA() = default;
        constexpr PixelGA(const PixelGrey &g, base::UInt8 a)
            : PixelGrey(g), alpha(a) {}
        constexpr PixelGA(base::UInt8 g, base::UInt8 a)
            : PixelGrey(g), alpha(a) {}
        inline ~PixelGA() = default;
    };

    /// @brief RGB像素
    class PixelRGB
    {
    public:
        /// @brief 红色
        base::UInt8 red;
        /// @brief 绿色
        base::UInt8 green;
        /// @brief 蓝色
        base::UInt8 blue;

    public:
        inline PixelRGB() = default;
        constexpr PixelRGB(base::UInt8 r, base::UInt8 g, base::UInt8 b)
            : red(r), green(g), blue(b) {}
        inline ~PixelRGB() = default;
    };

    /// @brief RGBA像素
    class PixelRGBA : public PixelRGB
    {
    public:
        /// @brief 透明度
        base::UInt8 alpha;

    public:
        inline PixelRGBA() = default;
        constexpr PixelRGBA(const PixelRGB &rgb, base::UInt8 a)
            : PixelRGB(rgb), alpha(a) {}
        constexpr PixelRGBA(base::UInt8 r, base::UInt8 g, base::UInt8 b, base::UInt8 a)
            : PixelRGB(r, g, b), alpha(a) {}
        inline ~PixelRGBA() = default;
    };

    std::ostream &operator<<(std::ostream &os, const PixelGrey &pixel)
    {
        os << "( " << static_cast<base::Int32>(pixel.grey) << " )";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const PixelGA &pixel)
    {
        os << "( " << static_cast<base::Int32>(pixel.grey) << ", "
           << static_cast<base::Int32>(pixel.alpha) << " )";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const PixelRGB &pixel)
    {
        os << "( " << static_cast<base::Int32>(pixel.red) << ", "
           << static_cast<base::Int32>(pixel.green) << ", "
           << static_cast<base::Int32>(pixel.blue) << " )";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const PixelRGBA &pixel)
    {
        os << "( " << static_cast<base::Int32>(pixel.red) << ", "
           << static_cast<base::Int32>(pixel.green) << ", "
           << static_cast<base::Int32>(pixel.blue) << ", "
           << static_cast<base::Int32>(pixel.alpha) << " )";
        return os;
    }

} // namespace utils
