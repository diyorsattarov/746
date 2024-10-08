cmake_minimum_required(VERSION 3.2)

project(test)

set(CMAKE_CXX_STANDARD 11)  # Set your desired C++ standard here

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/test/bin)

add_executable(test_main
    test_main.cpp
)

# Check the operating system to set appropriate libraries
if (WIN32)
    find_package(spdlog REQUIRED)
    target_link_libraries(test_main PRIVATE spdlog::spdlog ws2_32)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SPDLOG REQUIRED spdlog)
    target_link_libraries(test_main PRIVATE ${SPDLOG_LIBRARIES})
endif()

add_custom_target(clean_test
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/test/bin
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/test/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/test/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/test/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/test/cmake_install.cmake
    COMMENT "Cleaning build files"
)
