#pragma once

#include "base_image.hpp"

namespace utils
{
    BaseImage::BaseImage(BaseImage &&from)
        : m_width(std::exchange(from.m_width, 0)),
          m_height(std::exchange(from.m_height, 0)),
          m_format(std::exchange(from.m_format, Format::None)) {}

    BaseImage &BaseImage::operator=(BaseImage &&from)
    {
        m_width = std::exchange(from.m_width, 0);
        m_height = std::exchange(from.m_height, 0);
        m_format = std::exchange(from.m_format, Format::None);
        return *this;
    }

    base::Size BaseImage::get_width() const { return m_width; }
    base::Size BaseImage::get_height() const { return m_height; }
    BaseImage::Format BaseImage::get_format() const { return m_format; }

    void BaseImage::destroy()
    {
        m_width = 0;
        m_height = 0;
        m_format = Format::None;
    }

    void BaseImage::save_as_png(const std::filesystem::path &filename)
    {
        bool success = stbi_write_png(
            filename.string().data(), m_width, m_height, static_cast<base::Int32>(m_format), get_raw_pixels(), 0);

        if (!success)
            throw BASE_MAKE_RUNTIME_ERROR("Failed to save image as png, filename: \"", filename, "\"");
    }

    void BaseImage::save_as_jpg(const std::filesystem::path &filename, int quality)
    {
        bool success = stbi_write_jpg(
            filename.string().data(), m_width, m_height, static_cast<base::Int32>(m_format), get_raw_pixels(), quality);

        if (!success)
            throw BASE_MAKE_RUNTIME_ERROR("Failed to save image as jpg, filename: \"", filename, "\"");
    }

} // namespace utils
