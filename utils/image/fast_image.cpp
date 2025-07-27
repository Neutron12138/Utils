#pragma once

#include "fast_image.hpp"

namespace utils
{
    FastImage::FastImage(FastImage &&from)
        : BaseImage(std::move(from)),
          m_pixels(std::exchange(from.m_pixels, nullptr)) {}

    FastImage::~FastImage() { destroy(); }

    FastImage &FastImage::operator=(FastImage &&from)
    {
        destroy();
        m_pixels = std::exchange(from.m_pixels, nullptr);
        BaseImage::operator=(std::move(from));
        return *this;
    }

    const void *FastImage::get_raw_pixels() const { return m_pixels.get(); }
    base::Int64 FastImage::get_resource_type() const { return static_cast<base::Int64>(ResourceType::FastImage); }
    bool FastImage::is_valid() const { return m_pixels.get(); }

    void FastImage::load_from_file(const std::filesystem::path &filename, base::Size desired_channels)
    {
        destroy();

        int width, height, channels;
        stbi_uc *data = stbi_load(filename.string().data(), &width, &height, &channels, desired_channels);
        if (!data)
            throw BASE_MAKE_RUNTIME_ERROR("Failed to load image, filename: \"", filename, "\"");

        m_width = width;
        m_height = height;
        m_format = static_cast<Format>(desired_channels ? desired_channels : channels);
        m_pixels.reset(data);
    }

    void FastImage::destroy()
    {
        if (m_pixels)
            stbi_image_free(m_pixels.release());
        BaseImage::destroy();
    }

    FastImage load_fast_image_from_file(const std::filesystem::path &filename, base::Size desired_channels)
    {
        FastImage image;
        image.load_from_file(filename, desired_channels);
        return image;
    }

} // namespace utils
