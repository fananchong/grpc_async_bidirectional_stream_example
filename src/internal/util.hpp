#pragma once

#include <inttypes.h>
#include <chrono>
#include "log.hpp"

#define FMTI64 PRId64

#define PRINT_CONSTRUCTOR(CLASS) \
    assert(context_ != nullptr); \
    DEBUG("{}, id={}", #CLASS, id_);

#define PRINT_DESTRUCTOR(CLASS)  \
    assert(context_ != nullptr); \
    DEBUG("~{}, id={}", #CLASS, id_);

inline int64_t get_current_time_nanos()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::system_clock::now() -
               std::chrono::system_clock::from_time_t(0))
        .count();
}
