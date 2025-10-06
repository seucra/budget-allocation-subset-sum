# CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(SubsetSumSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- libpqxx via pkg-config ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED IMPORTED_TARGET libpqxx)

# --- Fetch dependencies ---
include(FetchContent)

FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(cxxopts)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# --- Solver library ---
add_library(solver_lib
    src/CoreSolver/DpSolver.cpp
    src/CoreSolver/BacktrackingSolver.cpp
    src/AlgorithmSelector/SolverFactory.cpp
    src/Benchmarking/Benchmark.cpp
    src/DBLayer/DatabaseManager.cpp
)
target_include_directories(solver_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(solver_lib PRIVATE PkgConfig::LIBPQXX)

# --- Main executable ---
add_executable(solver src/main.cpp)
target_include_directories(solver PRIVATE ${cxxopts_SOURCE_DIR}/include)
target_link_libraries(solver PRIVATE solver_lib)

# --- Unit tests ---
add_executable(run_tests tests/SolverTests.cpp)
target_link_libraries(run_tests PRIVATE solver_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)

# --- Compiler warnings ---
if(NOT MSVC)
    foreach(target solver solver_lib run_tests)
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic)
    endforeach()
endif()
