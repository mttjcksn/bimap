cmake_minimum_required(VERSION 3.10)
project(bimap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  serialiser 
  GIT_REPOSITORY https://www.github.com/mttjcksn/serialiser
  GIT_TAG  main
)
FetchContent_MakeAvailable(serialiser)

# Add the header-only library
add_library(bimap-lib INTERFACE)
target_include_directories(bimap-lib INTERFACE src)
target_link_libraries(bimap-lib INTERFACE serialiser-lib)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Define option for building tests, defaulting to ON if the project is the top-level project
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)    
    enable_testing()
    add_subdirectory(test)
else()
    option(BUILD_TESTS "Build tests" OFF)
endif()


