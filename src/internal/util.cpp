#include "util.hpp"

#ifdef _MSC_VER

namespace boost
{
    void throw_exception(std::exception const &e) // user defined
    {
        return;
    }
}

#endif
