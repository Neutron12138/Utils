#pragma once

#include <vector>
#include <string>
#include "base_image.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(FastImage);

    /// @brief 快速图像类，无拷贝开销
    class FastImage : public BaseImage
    {
    public:
        /// @brief 像素指针
        using PixelsRef = base::UniqueRef<stbi_uc[]>;

    private:
        /// @brief 像素数据
        PixelsRef m_pixels = nullptr;

    public:
        inline FastImage() = default;
        inline FastImage(const std::string &filename) { load_from_file(filename); }
        inline FastImage(FastImage &&from) : BaseImage(std::move(from)),
                                             m_pixels(std::exchange(from.m_pixels, nullptr)) {}
        inline ~FastImage() override { destroy(); }

    public:
        FastImage &operator=(FastImage &&from)
        {
            destroy();
            m_pixels = std::exchange(from.m_pixels, nullptr);
            BaseImage::operator=(std::move(from));
            return *this;
        }

        inline const void *get_raw_pixels() const override { return m_pixels.get(); }
        inline base::Int64 get_resource_type() const override { return static_cast<base::Int64>(ResourceType::FastImage); }
        inline bool is_valid() const override { return m_pixels.get(); }

    public:
        void load_from_file(const std::string &filename, base::Size desired_channels = 0)
        {
            destroy();

            int width, height, channels;
            stbi_uc *data = stbi_load(filename.data(), &width, &height, &channels, desired_channels);
            if (!data)
                throw BASE_MAKE_RUNTIME_ERROR("Failed to load image, filename: \"", filename, "\"");

            m_width = width;
            m_height = height;
            m_format = static_cast<Format>(desired_channels ? desired_channels : channels);
            m_pixels.reset(data);
        }

        void destroy() override
        {
            if (m_pixels)
                stbi_image_free(m_pixels.release());
            BaseImage::destroy();
        }
    };

} // namespace utils
