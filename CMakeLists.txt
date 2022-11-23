cmake_minimum_required(VERSION 3.24.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Hello LANGUAGES C CXX)

if(NOT CMAKE_C_COMPILER_ID MATCHES Clang OR NOT CMAKE_SYSTEM_NAME STREQUAL Linux)
  message(FATAL_ERROR "This project can only be built on Linux with Clang.")
endif()

# Additional compile/link flags
add_compile_options(-g -Wall -Werror)
include(cmake/Sanitizers.cmake)

# clang-tidy
find_program(CLANG_TIDY clang-tidy)
message(STATUS "Clang-Tidy: ${CLANG_TIDY}")
if(CLANG_TIDY)
  set(CMAKE_C_CLANG_TIDY   ${CLANG_TIDY})
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

# clang-format
find_program(CLANG_FORMAT clang-format)
message(STATUS "Clang-Format: ${CLANG_FORMAT}")
if(CLANG_FORMAT)
  file(GLOB_RECURSE all_sources CONFIGURE_DEPENDS
    include/*.h
    src/*.c src/*.cpp src/*.h
    tests/*.c tests/*.cpp tests/*.h
  )

  add_custom_target(format
    COMMAND
      ${CLANG_FORMAT}
      -style=file
      -i
      ${all_sources}
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
    COMMENT
      "Running clang-format on sources"
  )
endif()

add_subdirectory(src)

option(BUILD_TESTING "Enable tests" ON)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
