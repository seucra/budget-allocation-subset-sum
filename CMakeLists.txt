# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(SubsetSumSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Configure Qt6 for the GUI ---
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
# --------------------------------

# --- No database libraries are needed here ---

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

# --- Core Solver Library ---
add_library(solver_lib
    src/CoreSolver/DpSolver.cpp
    src/CoreSolver/BacktrackingSolver.cpp
    src/AlgorithmSelector/SolverFactory.cpp
    src/Benchmarking/Benchmark.cpp
)
target_include_directories(solver_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
# No database linking needed for solver_lib

# --- CLI Executable ---
add_executable(solver src/main_cli.cpp)
target_link_libraries(solver PRIVATE solver_lib)
target_include_directories(solver PUBLIC ${cxxopts_SOURCE_DIR}/include)

# --- GUI Executable ---
# --- GUI Executable ---
add_executable(solver-gui
    src/main_gui.cpp
    src/GUI/MainWindow.cpp # <-- This line is critical
)
target_link_libraries(solver-gui PRIVATE solver_lib Qt6::Widgets Qt6::Gui Qt6::Core)

# --- Test Executable ---
add_executable(run_tests tests/SolverTests.cpp)
target_link_libraries(run_tests PRIVATE solver_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(run_tests)

if(NOT MSVC)
    target_compile_options(solver PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(solver-gui PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(solver_lib PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(run_tests PRIVATE -Wall -Wextra -pedantic)
endif()

