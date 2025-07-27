#pragma once

#include "class_info.hpp"

namespace utils
{
    BASE_DECLARE_REF_TYPE(ClassDB);

    /// @brief 类数据库
    class ClassDB
    {
    public:
        using ClassInfoDict = std::unordered_map<std::string, ClassInfoRef>;
        using ClassInfoConstIterator = ClassInfoDict::const_iterator;

    private:
        /// @brief 类信息字典
        ClassInfoDict m_class_info_dict = {};

    public:
        ClassDB() = default;
        ~ClassDB() = default;

    public:
        const ClassInfoDict &get_class_info_dict() const;

    public:
        void register_class(const std::string &name, const ClassInfoRef &class_info);
        ClassInfoConstIterator find_class(const std::string &name);
    };

} // namespace utils
