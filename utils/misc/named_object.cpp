#pragma once

#include "named_object.hpp"

namespace utils
{
    NamedObject::NamedObject(const std::string &name) : m_name(name) {}
    void NamedObject::_on_name_changed(const std::string &old_name, const std::string &new_name) {}

    const std::string &NamedObject::get_name() const { return m_name; }
    void NamedObject::set_name(const std::string &new_name)
    {
        if (m_name == new_name)
            return;

        std::string old_name = std::move(m_name);
        m_name = new_name;
        _on_name_changed(std::move(old_name), m_name);
    }

} // namespace utils
