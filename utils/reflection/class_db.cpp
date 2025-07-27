#pragma once

#include "class_db.hpp"

namespace utils
{
    const ClassDB::ClassInfoDict &ClassDB::get_class_info_dict() const { return m_class_info_dict; }

    void ClassDB::register_class(const std::string &name, const ClassInfoRef &class_info)
    {
        m_class_info_dict[name] = class_info;
    }

    ClassDB::ClassInfoConstIterator ClassDB::find_class(const std::string &name)
    {
        auto iter = m_class_info_dict.find(name);
        if (iter == m_class_info_dict.cend())
            throw BASE_MAKE_RUNTIME_ERROR("Unable to find class, class name: \"", name, "\"");

        return iter;
    }

} // namespace utils
