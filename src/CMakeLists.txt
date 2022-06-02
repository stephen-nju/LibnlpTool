
list(APPEND NLPTOOL_LIBS absl::strings)
list(APPEND NLPTOOL_LIBS absl::flags)
list(APPEND NLPTOOL_LIBS absl::flags_parse)
list(APPEND NLPTOOL_LIBS utf8proc)
list(APPEND NLPTOOL_LIBS spdlog)

message(STATUS "libnlptools using libs: ${NLPTOOL_LIBS}")


if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()


# # Always use the static libs on Windows.
# if (MSVC AND WIN32)
#   # set (Boost_USE_MULTITHREADED ON)
#   set (Boost_USE_STATIC_LIBS ON)
# else ()
#   # set (Boost_USE_MULTITHREADED OFF)
#   set (Boost_USE_STATIC_LIBS OFF)
# endif () 

# if (NOT Boost_USE_STATIC_LIBS)
#   add_definitions (/DBOOST_TEST_DYN_LINK)
# endif ()
# Boost headers contain #pragma commands on Windows which causes Boost
  # libraries to be linked in automatically. Custom boost installations
  # may find that these naming conventions don't always match and can
  # cause linker errors. This option disables this feature of Boost. Note
  # -DBOOST_ALL_NO_LIB can also be provided manually.


find_package(Boost COMPONENTS filesystem REQUIRED)
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


set(THIRDPARTY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty)
message(STATUS "libnlptools include thirdparty path = ${THIRDPARTY_INCLUDE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/libnlptool)

include_directories(
    ${THIRDPARTY_INCLUDE_DIR}/utf8proc
    ${THIRDPARTY_INCLUDE_DIR}/abseil-cpp
    ${THIRDPARTY_INCLUDE_DIR}/spdlog/include
)


set(LEET_CODE_SRC
  leetcode.cc
)
# tokenizer 源文件

set(TOKENIZER_SRC
	  utils.cc
    ac_automation.cc
    tokenizer.cc
)
# set(VITERBI_SRC
#     viterbi.h
#     viterbi.cc
# )

# add_executable(viterbi ${VITERBI_SRC})

# 动态库
if (LIBNLP_ENABLE_SHARED)
  set(ORIGIN_DYNAMIC_LIB_NAME ${PROJECT_NAME}-dynamic)
  add_library(${ORIGIN_DYNAMIC_LIB_NAME} SHARED ${TOKENIZER_SRC})
  message(STATUS "building dynamic lib ${ORIGIN_DYNAMIC_LIB_NAME}")
  set_target_properties(${ORIGIN_DYNAMIC_LIB_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
  target_link_libraries(${ORIGIN_DYNAMIC_LIB_NAME} PRIVATE  ${NLPTOOL_LIBS})
  if (MSVC)
    set_target_properties(${ORIGIN_DYNAMIC_LIB_NAME} PROPERTIES IMPORT_SUFFIX "_import.lib")
  elseif (MINGW)
    set_target_properties(${ORIGIN_DYNAMIC_LIB_NAME} PROPERTIES IMPORT_SUFFIX ".dll.a")
  endif()
endif()
# 静态库



add_library(${PROJECT_NAME} STATIC ${TOKENIZER_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC ${NLPTOOL_LIBS})

set(
  TEST_SRC
  testharness.h
  tokenizer_test.cc
)


include(GoogleTest)
add_executable(DemoTest ${TEST_SRC})
target_link_libraries(DemoTest ${PROJECT_NAME} gtest_main)
target_link_libraries(DemoTest Boost::filesystem Boost::diagnostic_definitions Boost::disable_autolinking Boost::dynamic_linking)
gtest_add_tests(TARGET DemoTest)

add_subdirectory(model)