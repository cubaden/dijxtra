cmake_minimum_required(VERSION 3.0.0)
project(dijxstra VERSION 0.1.0 LANGUAGES C CXX)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_executable(dijxstra main.cpp)
target_link_libraries(dijxstra ${GTEST_LIBRARIES} pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
