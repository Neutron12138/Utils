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
        FastImage() = default;
        FastImage(FastImage &&from);
        ~FastImage() override;

    public:
        FastImage &operator=(FastImage &&from);
        const void *get_raw_pixels() const override;
        base::Int64 get_resource_type() const override;
        bool is_valid() const override;

    public:
        void load_from_file(const std::filesystem::path &filename, base::Size desired_channels = 0);
        void destroy() override;
    };

    FastImage load_fast_image_from_file(const std::filesystem::path &filename, base::Size desired_channels = 0);

} // namespace utils
