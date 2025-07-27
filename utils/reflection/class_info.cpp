#include "class_info.hpp"

namespace utils
{
    ClassInfo::ClassInfo(const BaseClassArray &base_classes) : m_base_classes(base_classes) {}

    const ClassInfo::BaseClassArray &ClassInfo::get_base_classes() const { return m_base_classes; }
    const ClassInfo::FieldDict &ClassInfo::get_field_dict() const { return m_field_dict; }
    const ClassInfo::MethodDict &ClassInfo::get_method_dict() const { return m_method_dict; }
    const ClassInfo::Constructor &ClassInfo::get_constructor() const { return m_constructor; }
    const ClassInfo::Destructor &ClassInfo::get_destructor() const { return m_destructor; }
    void ClassInfo::set_constructor(const Constructor &constructor) { m_constructor = constructor; }
    void ClassInfo::set_destructor(const Destructor &destructor) { m_destructor = destructor; }

    void ClassInfo::_set_base_class(const ClassInfoRef &base_class)
    {
        m_base_classes = base_class->m_base_classes;
        m_base_classes.push_back(base_class);
    }

    void ClassInfo::_add_base_class(const ClassInfoRef &base_class)
    {
        m_base_classes.push_back(base_class);
    }

    void ClassInfo::_add_field(const std::string &name, const FieldBaseRef &field)
    {
        m_field_dict[name] = field;
    }

    void ClassInfo::_add_method(const std::string &name, const MethodBaseRef &method)
    {
        m_method_dict[name] = method;
    }

    //
    // 查找函数
    //

    ClassInfo::FieldConstIterator ClassInfo::find_field(const std::string &name) const
    {
        auto iter = m_field_dict.find(name);
        if (iter != m_field_dict.cend())
            return iter;

        for (auto &base_class : m_base_classes)
        {
            iter = base_class->m_field_dict.find(name);
            if (iter != base_class->m_field_dict.cend())
                return iter;
        }

        throw BASE_MAKE_RUNTIME_ERROR("Unable to find field: \"", name, "\"");
    }

    ClassInfo::MethodConstIterator ClassInfo::find_method(const std::string &name) const
    {
        auto iter = m_method_dict.find(name);
        if (iter != m_method_dict.cend())
            return iter;

        for (auto &base_class : m_base_classes)
        {
            iter = base_class->m_method_dict.find(name);
            if (iter != base_class->m_method_dict.cend())
                return iter;
        }

        throw BASE_MAKE_RUNTIME_ERROR("Unable to find method: \"", name, "\"");
    }

    //
    // 类成员
    //

    std::any ClassInfo::get(void *object, const std::string &name) const
    {
        auto iter = find_field(name);
        return iter->second->get(object);
    }

    std::any ClassInfo::get(const void *object, const std::string &name) const
    {
        auto iter = find_field(name);
        return iter->second->get(object);
    }

    void ClassInfo::set(void *object, const std::string &name, const std::any &value) const
    {
        auto iter = find_field(name);
        iter->second->set(object, value);
    }

    //
    // 静态成员
    //

    std::any ClassInfo::get(const std::string &name) const
    {
        auto iter = find_field(name);
        return iter->second->get(static_cast<void *>(nullptr));
    }

    void ClassInfo::set(const std::string &name, const std::any &value) const
    {
        auto iter = find_field(name);
        iter->second->set(nullptr, value);
    }

} // namespace utils
