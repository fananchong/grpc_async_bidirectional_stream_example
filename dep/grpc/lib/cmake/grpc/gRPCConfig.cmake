# Module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules)

# Depend packages


if(NOT OPENSSL_FOUND)
  find_package(OpenSSL)
endif()

if(NOT TARGET absl::strings)
  find_package(absl CONFIG)
endif()


# Targets
include(${CMAKE_CURRENT_LIST_DIR}/gRPCTargets.cmake)
