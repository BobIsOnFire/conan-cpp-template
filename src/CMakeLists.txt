add_library(hello)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.c *.cpp)
list(FILTER sources EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

file(GLOB_RECURSE private_headers CONFIGURE_DEPENDS *.h)
file(GLOB_RECURSE public_headers CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include/*.h)

target_sources(hello
  PRIVATE ${sources}
  PRIVATE FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${private_headers}
  PUBLIC FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}/include
    FILES ${public_headers}
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
  add_executable(hello_exe)

  target_sources(hello_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
  target_link_libraries(hello_exe PRIVATE hello)
  set_target_properties(hello_exe PROPERTIES OUTPUT_NAME hello)
endif()
