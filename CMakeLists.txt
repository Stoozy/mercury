cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()


# Install Catch2 
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
file(GLOB test_sources tests/*.cc src/util.cc src/events.cc src/data_handler.cc  src/config.cc)
list(REMOVE_ITEM test_sources src/main.cc )
add_executable(tests ${test_sources})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# Actual Project
project(mercury VERSION 1.0)
include_directories(include)
file(GLOB sources src/*.cc src/strategies/*.cc)
add_executable(mercury ${sources})
