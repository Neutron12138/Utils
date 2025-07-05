#include <iostream>
#include "../utils/utils.hpp"

int main()
{
    std::cout << (sizeof(utils::PixelGrey) == sizeof(base::UInt8)) << std::endl
              << (sizeof(utils::PixelGA) == 2 * sizeof(base::UInt8)) << std::endl
              << (sizeof(utils::PixelRGB) == 3 * sizeof(base::UInt8)) << std::endl
              << (sizeof(utils::PixelRGBA) == 4 * sizeof(base::UInt8)) << std::endl
              << std::is_trivial_v<utils::PixelGrey> << std::endl
              << std::is_trivial_v<utils::PixelGA> << std::endl
              << std::is_trivial_v<utils::PixelRGB> << std::endl
              << std::is_trivial_v<utils::PixelRGBA> << std::endl
              << std::endl;

    constexpr utils::PixelGrey p1(1);
    constexpr utils::PixelGA p2(1, 2);
    constexpr utils::PixelRGB p3(1, 2, 3);
    constexpr utils::PixelRGBA p4(1, 2, 3, 4);

    std::cout << p1 << std::endl
              << p2 << std::endl
              << p3 << std::endl
              << p4 << std::endl
              << std::endl;

    try
    {
        utils::FastImage::load_from_file("114.jpg");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    utils::FastImageRef image = utils::FastImage::load_from_file("wall.jpg");
    std::cout << "width: " << image->get_width() << std::endl
              << "height: " << image->get_height() << std::endl
              << "format: " << static_cast<base::Int32>(image->get_format()) << std::endl;
    base::UInt8 *data = const_cast<base::UInt8 *>(image->get_raw_pixels());
    utils::PixelRGB *pixels = reinterpret_cast<utils::PixelRGB *>(data);
    std::cout << pixels[0] << ", " << pixels[1] << std::endl;
    image->save_as_png("wall_2.png");
    std::cout << std::endl;

    try
    {
        image->save_as_png("");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
