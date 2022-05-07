cmake_minimum_required(VERSION 3.0.0)

project(Demo VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(thirdparty)
add_subdirectory(src)

option(LIBNLP_ENABLE_SHARED "Builds shared libaries in addition to static libraries." OFF)

# target_link_libraries(Demo utf8proc )
# target_link_libraries(Demo absl::strings absl::base absl::synchronization)
# # 需要先链接utf8proc 再链接nlptool
# target_link_libraries(Demo nlptool)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
