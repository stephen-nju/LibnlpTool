cmake_minimum_required(VERSION 3.15)

project(nlptool VERSION 0.1.0)
include(cmake/Common.cmake)

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(test)

option(LIBNLP_ENABLE_SHARED "Builds shared libaries in addition to static libraries." OFF)
message(STATUS "LIBNLP_ENABLE_SHARED= ${LIBNLP_ENABLE_SHARED}")
option(LIBNLP_ENABLE_TEST "enable test " ON)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
