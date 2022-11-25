project(AlgoLab3)

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
	AlgoLab3
	Sort.h
	SortTest.cpp
)

target_link_libraries(
  AlgoLab3
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(AlgoLab3)
