cmake_minimum_required(VERSION 3.10)
project(cpp_systems_practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# === SharedPtr ===
add_library(shared_ptr
    shared_ptr/SharedPtr.cpp
)
target_include_directories(shared_ptr PUBLIC shared_ptr)

add_executable(SharedPtrTest
    tests/SharedPtrTest.cpp
)
target_link_libraries(SharedPtrTest PRIVATE shared_ptr GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(SharedPtrTest)

# === Vector (planned) ===
# add_library(vector_impl
#     vector/Vector.cpp
# )
# target_include_directories(vector_impl PUBLIC vector)
#
# add_executable(VectorTest
#     tests/VectorTest.cpp
# )
# target_link_libraries(VectorTest PRIVATE vector_impl GTest::gtest_main)
#
# gtest_discover_tests(VectorTest)