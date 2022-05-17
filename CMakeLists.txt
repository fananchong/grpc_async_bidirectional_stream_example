cmake_minimum_required (VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME test)
project(${PROJECT_NAME})

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)
message("-- CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

if (MY_CC)
    SET(CMAKE_C_COMPILER ${MY_CC})
endif()

if (MY_CXX)
    SET(CMAKE_CXX_COMPILER ${MY_CXX})
endif()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message("-- BUILD: ${CMAKE_BUILD_TYPE}")

include_directories("./src")
include_directories("./dep/grpc/include")
include_directories("./dep/openssl/include")
include_directories("./dep/absl/include")
include_directories("./dep/spdlog/include")
link_directories("./dep/grpc/lib")
link_directories("./dep/grpc/lib64/")
link_directories("./dep/openssl/lib")


set (LIB_GRPC grpc++_reflection
    grpc++
    grpc
    gpr
    protobuf
    upb
    cares
    re2
    absl_bad_optional_access
    absl_bad_variant_access
    absl_base
    absl_city
    absl_civil_time
    absl_cord
    absl_debugging_internal
    absl_demangle_internal
    absl_exponential_biased
    absl_graphcycles_internal
    absl_hash
    absl_hashtablez_sampler
    absl_int128
    absl_log_severity
    absl_malloc_internal
    absl_raw_hash_set
    absl_raw_logging_internal
    absl_spinlock_wait
    absl_stacktrace
    absl_status
    absl_statusor
    absl_str_format_internal
    absl_strings
    absl_strings_internal
    absl_symbolize
    absl_synchronization
    absl_throw_delegate
    absl_time 
    absl_time_zone 
    address_sorting
)

file(GLOB_RECURSE SRC_FILES src/*.c src/*.cc src/*.cpp src/*.h src/*.hpp src/*.ipp)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_FILES})
add_executable(${PROJECT_NAME} ${SRC_FILES})
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP")
    target_link_libraries(${PROJECT_NAME} ${LIB_GRPC} CRYPT32 Winhttp httpapi Ws2_32)
ELSE ()
    add_definitions(-g)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        add_compile_options(-O3)
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    target_link_libraries(${PROJECT_NAME} -Wl,--start-group ${LIB_GRPC} ssl crypto pthread dl stdc++ c m -Wl,--end-group)
ENDIF ()
install(TARGETS ${PROJECT_NAME} DESTINATION .)
