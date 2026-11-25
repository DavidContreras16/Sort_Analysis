cmake_minimum_required(VERSION 3.20)

project(SortAnalysis LANGUAGES CXX)

add_library(sort_analysis INTERFACE)
target_include_directories(sort_analysis INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sort_analysis INTERFACE cxx_std_17)
