#pragma once

#include "class_info.hpp"

namespace utils
{
    /// @brief 类数据库
    class ClassDB
    {
    public:
        using ClassInfoDict = std::unordered_map<std::string, ClassInfoRef>;
        using ClassInfoConstIterator = ClassInfoDict::const_iterator;

    private:
        /// @brief 类信息字典
        ClassInfoDict m_class_info_dict;

    public:
        ClassDB() = default;
        ~ClassDB() = default;

    public:
        inline const ClassInfoDict &get_class_info_dict() const { return m_class_info_dict; }

    public:
        inline void register_class(const std::string &name, const ClassInfoRef &class_info)
        {
            m_class_info_dict[name] = class_info;
        }

        ClassInfoConstIterator find_class(const std::string &name)
        {
            auto iter = m_class_info_dict.find(name);
            if (iter == m_class_info_dict.cend())
                throw BASE_MAKE_RUNTIME_ERROR("Unable to find class, class name: \"", name, "\"");

            return iter;
        }
    };

} // namespace utils
