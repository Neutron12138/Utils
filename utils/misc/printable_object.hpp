#pragma once

#include <base/core/to_string.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace utils
{
    BASE_DECLARE_REF_TYPE(PrintableObject);

    /// @brief 可打印的对象
    /// @tparam StringT 字符串类型
    class PrintableObject : virtual public base::PolymorphicObject
    {
    public:
        PrintableObject() = default;
        ~PrintableObject() noexcept override = default;

    public:
        /// @brief 转换成字符串
        /// @return 转换后的字符串
        virtual std::string to_string() const;
    };

    std::ostream &operator<<(std::ostream &os, const PrintableObject &printable);

    /// @brief 将调试信息转化为字符串
    /// @param object 对象地址
    /// @param file 文件名
    /// @param function 函数名
    /// @param line 行号
    /// @return 转化后的字符串
    std::string str_debug_info(const PrintableObject *object, const char *file, const char *function, int line);

} // namespace utils
