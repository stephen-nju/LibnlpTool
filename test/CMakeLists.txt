# 添加ctest的头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/libnlptool)

include_directories(
    ${THIRDPARTY_INCLUDE_DIR}/utf8proc
    ${THIRDPARTY_INCLUDE_DIR}/abseil-cpp
    ${THIRDPARTY_INCLUDE_DIR}/spdlog/include
)


set(
  TEST_SRC
  testharness.h
  tokenizer_test.cc
)

if (MSVC AND WIN32)
  # set (Boost_USE_MULTITHREADED ON)
  set (Boost_USE_STATIC_LIBS ON)
else ()
  # set (Boost_USE_MULTITHREADED OFF)
  set (Boost_USE_STATIC_LIBS OFF)
endif () 

# if (NOT Boost_USE_STATIC_LIBS)
#   add_definitions (/DBOOST_TEST_DYN_LINK)
# endif ()
# Boost headers contain #pragma commands on Windows which causes Boost
  # libraries to be linked in automatically. Custom boost installations
  # may find that these naming conventions don't always match and can
  # cause linker errors. This option disables this feature of Boost. Note
  # -DBOOST_ALL_NO_LIB can also be provided manually.


find_package(Boost 1.79 REQUIRED COMPONENTS date_time filesystem)
if(Boost_FOUND)
    # add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost_LIB_DIAGNOSTIC_DEFINITIONS=${Boost_LIB_DIAGNOSTIC_DEFINITIONS}" )
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
else()
    MESSAGE( FATAL_ERROR  "BOOST NOT FOUND PLEASE install BOOST")
endif()


if(LIBNLP_ENABLE_TEST)
  enable_testing()
  include(GoogleTest)
  add_executable(DemoTest ${TEST_SRC})
  target_link_libraries(DemoTest ${PROJECT_NAME} gtest_main)  
  target_link_libraries(DemoTest Boost::filesystem)
  gtest_add_tests(TARGET DemoTest)
endif(LIBNLP_ENABLE_TEST)

add_executable(leetcode leetcode_test.cc)
target_link_libraries(leetcode ${PROJECT_NAME})
