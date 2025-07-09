#pragma once

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#endif
#include <stb_image_resize2.h>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
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
        inline BaseImage() = default;
        inline BaseImage(BaseImage &&from)
            : m_width(std::exchange(from.m_width, 0)),
              m_height(std::exchange(from.m_height, 0)),
              m_format(std::exchange(from.m_format, Format::None)) {}
        inline ~BaseImage() override = default;

    public:
        BaseImage &operator=(BaseImage &&from)
        {
            m_width = std::exchange(from.m_width, 0);
            m_height = std::exchange(from.m_height, 0);
            m_format = std::exchange(from.m_format, Format::None);
            return *this;
        }

        inline base::Size get_width() const { return m_width; }
        inline base::Size get_height() const { return m_height; }
        inline Format get_format() const { return m_format; }

        /// @brief 获取原始像素数据
        /// @return 原始像素数据
        virtual const void *get_raw_pixels() const = 0;

        /// @brief 销毁图像资源
        virtual void destroy()
        {
            m_width = 0;
            m_height = 0;
            m_format = Format::None;
        }

    public:
        /// @brief 将图像保存为PNG格式
        /// @param filename 文件名
        virtual void save_as_png(const std::string &filename)
        {
            bool success = stbi_write_png(
                filename.data(), m_width, m_height, static_cast<base::Int32>(m_format), get_raw_pixels(), 0);

            if (!success)
                throw BASE_MAKE_RUNTIME_ERROR("Failed to save image as png, filename: \"", filename, "\"");
        }

        /// @brief 将图像保存为JPG格式
        /// @param filename 文件名
        /// @param quality 质量
        virtual void save_as_jpg(const std::string &filename, int quality)
        {
            bool success = stbi_write_jpg(
                filename.data(), m_width, m_height, static_cast<base::Int32>(m_format), get_raw_pixels(), quality);

            if (!success)
                throw BASE_MAKE_RUNTIME_ERROR("Failed to save image as jpg, filename: \"", filename, "\"");
        }
    };

} // namespace utils
