
list(APPEND NLPTOOL_LIBS absl::strings)
list(APPEND NLPTOOL_LIBS absl::flags)
list(APPEND NLPTOOL_LIBS absl::flags_parse)
list(APPEND NLPTOOL_LIBS utf8proc)
list(APPEND NLPTOOL_LIBS spdlog)


message(STATUS "libnlptools using libs: ${NLPTOOL_LIBS}")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(THIRDPARTY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty)
message(STATUS "libnlptools include thirdparty path :${THIRDPARTY_INCLUDE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/libnlptool)

include_directories(
	${THIRDPARTY_INCLUDE_DIR}/utf8proc
  ${THIRDPARTY_INCLUDE_DIR}/abseil-cpp
  ${THIRDPARTY_INCLUDE_DIR}/spdlog/include

)

set(TOOL_SRC
	  utils.cc
    ac_automation.cc
    leetcode.cc
    tokenizer.cc
)
set(VITERBI_SRC
    viterbi.h
    viterbi.cc
)

add_executable(viterbi ${VITERBI_SRC})

add_library(nlptool STATIC ${TOOL_SRC})
target_link_libraries(nlptool PRIVATE ${NLPTOOL_LIBS})

if (LIBNLP_ENABLE_SHARED)
  add_library(nlptool SHARED ${TOOL_SRC})
endif()

# add_executable(Demo main.cc)
# target_link_libraries(Demo nlptool)