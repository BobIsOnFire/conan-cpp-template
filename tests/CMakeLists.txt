set(CMAKE_CTEST_ARGUMENTS --output-on-failure -C $<CONFIG>)
find_package(GTest CONFIG REQUIRED)

add_executable(hello_test)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.c *.cpp)
file(GLOB_RECURSE private_headers CONFIGURE_DEPENDS *.h)

target_sources(hello_test
  PRIVATE ${sources}
  PRIVATE FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${private_headers}
)

target_link_libraries(hello_test PRIVATE
    hello
    GTest::gtest
    GTest::gmock
)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
    target_link_libraries(hello_test PRIVATE GTest::gtest_main)
endif()

add_test(NAME hello_test COMMAND hello_test)
