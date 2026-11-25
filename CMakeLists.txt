cmake_minimum_required(VERSION 3.20)

project(SortAnalysis LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_library(sorts INTERFACE)
target_include_directories(sorts INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sorts INTERFACE cxx_std_17)

add_executable(sort_analysis src/main.cpp)
target_link_libraries(sort_analysis PRIVATE sorts)
