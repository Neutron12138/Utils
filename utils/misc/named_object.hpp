#pragma once

#include <string>
#include <base/core/ref.hpp>
#include <base/misc/polymorphic_object.hpp>

namespace utils
{
    BASE_DECLARE_REF_TYPE(NamedObject);

    /// @brief 带名字的对象
    /// @tparam StringT 名称字符串类型
    class NamedObject : virtual public base::PolymorphicObject
    {
    private:
        /// @brief 对象名
        std::string m_name = {};

    public:
        NamedObject() = default;
        NamedObject(const std::string &name);
        ~NamedObject() noexcept override = default;

    protected:
        /// @brief 当对象名更改时
        /// @param old_name 旧名字
        /// @param new_name 新名字
        virtual void _on_name_changed(const std::string &old_name, const std::string &new_name);

    public:
        const std::string &get_name() const;
        void set_name(const std::string &new_name);
    };

} // namespace utils
