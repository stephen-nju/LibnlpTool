cmake_minimum_required(VERSION 3.15)

project(nlptool VERSION 0.1.0)
include(cmake/ProjectSettings.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(thirdparty)
add_subdirectory(src)

option(LIBNLP_ENABLE_SHARED "Builds shared libaries in addition to static libraries." OFF)
message(STATUS "LIBNLP_ENABLE_SHARED= ${LIBNLP_ENABLE_SHARED}")
option(LIBNLP_ENABLE_TEST "enable test " ON)

# if(MSVC)
#   string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG})
#   string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL     ${CMAKE_CXX_FLAGS_MINSIZEREL})
#   string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE})
#   string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
#   add_definitions("/wd4267 /wd4244 /wd4305 /Zc:strictStrings /utf-8")
#   # 添加编译选项
# endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
