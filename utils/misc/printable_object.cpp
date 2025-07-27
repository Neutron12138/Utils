#pragma once

#include "printable_object.hpp"

namespace utils
{
    std::string PrintableObject::to_string() const
    {
        return base::to_string("PrintableObject@", this);
    }

    std::ostream &operator<<(std::ostream &os, const PrintableObject &printable)
    {
        os << printable.to_string();
        return os;
    }

    std::string str_debug_info(const PrintableObject *object,
                               const char *file, const char *function, int line)
    {
        if (object)
            return base::to_string(
                "(", object->to_string(),
                ") in file: \"", file,
                "\", function: \"", function,
                "\", line: ", line);

        return base::to_string(
            "(object@null",
            ") in file: \"", file,
            "\", function: \"", function,
            "\", line: ", line);
    }

} // namespace utils
