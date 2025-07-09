#include "class_info.hpp"

namespace utils
{
    template <typename... T>
    void *ClassInfo::construct(T... args)
    {
        if (!m_constructor)
            throw BASE_MAKE_RUNTIME_ERROR("No constructor");

        return m_constructor(std::make_tuple(args...));
    }

    void ClassInfo::destruct(void *object)
    {
        if (!m_destructor)
            throw BASE_MAKE_RUNTIME_ERROR("No destructor");

        m_destructor(object);
    }

    template <typename... T>
    base::AnyRef ClassInfo::create(T... args)
    {
        if (!m_constructor)
            throw BASE_MAKE_RUNTIME_ERROR("No constructor");
        if (!m_destructor)
            throw BASE_MAKE_RUNTIME_ERROR("No destructor");

        return base::AnyRef(m_constructor(std::make_tuple(args...)), m_destructor);
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

    template <typename... T>
    std::any ClassInfo::call(void *object, const std::string &name, T... args) const
    {
        auto iter = find_method(name);
        return iter->second->invoke(object, std::make_tuple(args...));
    }

    template <typename... T>
    std::any ClassInfo::call(const void *object, const std::string &name, T... args) const
    {
        auto iter = find_method(name);
        return iter->second->invoke(object, std::make_tuple(args...));
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

    template <typename... T>
    std::any ClassInfo::call(const std::string &name, T... args) const
    {
        auto iter = find_method(name);
        return iter->second->invoke(static_cast<void *>(nullptr), std::make_tuple(args...));
    }

} // namespace utils
