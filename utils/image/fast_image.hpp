#pragma once

#include <vector>
#include <string>
#include "base_image.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(FastImage);

    /// @brief 快速图像类，无法修改
    class FastImage : public BaseImage
    {
    public:
        /// @brief 像素指针
        using PixelsRef = ::base::Ref<::base::UInt8>;

        /// @brief 从文件加载
        /// @param filename 文件名
        /// @param desired_channels 期望的通道数
        /// @return 图像引用
        static FastImageRef load_from_file(const std::string &filename, ::base::Size desired_channels = 0)
        {
            int width, height, channels;
            stbi_uc *data = stbi_load(filename.data(), &width, &height, &channels, desired_channels);
            if (!data)
                throw BASE_MAKE_RUNTIME_ERROR("Failed to load image, filename: \"", filename, "\"");

            Format format = static_cast<Format>(desired_channels ? desired_channels : channels);
            PixelsRef pixels(data, stbi_image_free);

            return FastImageRef(new FastImage(width, height, format, pixels));
        }

    private:
        /// @brief 像素数据
        PixelsRef m_pixels;

    protected:
        inline FastImage(::base::Size width, ::base::Size height, Format format, const PixelsRef &pixels)
            : BaseImage(width, height, format), m_pixels(pixels) {}

    public:
        inline ~FastImage() override = default;

    public:
        inline const ::base::UInt8 *get_raw_pixels() const override { return m_pixels.get(); }
        inline ::base::Int64 get_resource_type() const override { return static_cast<::base::Int64>(ResourceType::FastImage); }

    protected:
        void _set_width(::base::Size) = delete;
        void _set_height(::base::Size) = delete;
        void _set_format(Format) = delete;
    };

} // namespace utils
