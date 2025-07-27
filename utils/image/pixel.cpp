#pragma once

#include "pixel.hpp"

namespace utils
{
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
