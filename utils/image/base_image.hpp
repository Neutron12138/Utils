#pragma once

#include <filesystem>
#include <stb_image.h>
#include <stb_image_resize2.h>
#include <stb_image_write.h>
#include <base/core/type.hpp>
#include <base/misc/resource.hpp>
#include <base/core/exception.hpp>
#include "pixel.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(BaseImage);

    /// @brief 基础图像类
    class BaseImage : public base::Resource
    {
    public:
        /// @brief 格式
        enum class Format : base::Int32
        {
            /// @brief 无
            None,
            /// @brief 灰度
            Grey,
            /// @brief 灰度、透明度
            GA,
            /// @brief 红、绿、蓝
            RGB,
            /// @brief 红、绿、蓝、透明度
            RGBA,
        };

        /// @brief 资源类型
        enum class ResourceType : base::Int64
        {
            /// @brief 无
            None,
            /// @brief 快速图像
            FastImage,
        };

    protected:
        /// @brief 宽度
        base::Size m_width = 0;
        /// @brief 高度
        base::Size m_height = 0;
        /// @brief 格式
        Format m_format = Format::None;

    public:
        BaseImage() = default;
        BaseImage(BaseImage &&from);
        ~BaseImage() override = default;
        BASE_DELETE_COPY_FUNCTION(BaseImage);

    public:
        BaseImage &operator=(BaseImage &&from);
        base::Size get_width() const;
        base::Size get_height() const;
        Format get_format() const;

        /// @brief 获取原始像素数据
        /// @return 原始像素数据
        virtual const void *get_raw_pixels() const = 0;

        /// @brief 销毁图像资源
        virtual void destroy();

    public:
        /// @brief 将图像保存为PNG格式
        /// @param filename 文件名
        virtual void save_as_png(const std::filesystem::path &filename);

        /// @brief 将图像保存为JPG格式
        /// @param filename 文件名
        /// @param quality 质量
        virtual void save_as_jpg(const std::filesystem::path &filename, int quality);
    };

} // namespace utils
