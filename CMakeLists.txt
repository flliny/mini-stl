cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For clang-tidy.
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 17) # Compile as C++17.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Require C++17 support.

project(MiniSTL
        DESCRIPTION "Mini STL implementation."
        LANGUAGES C CXX
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        message(STATUS "Setting build type to `Debug` as none was specified.")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

# Checks if you're running CMake from a folder that already has CMakeLists.txt.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)

if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
        message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()



enable_testing()


# #####################################################################################################################
# COMPILER SETUP
# #####################################################################################################################
if(NOT DEFINED SANITIZER)
        set(SANITIZER address)
endif()

message("Build mode: ${CMAKE_BUILD_TYPE}")
message("${SANITIZER} sanitizer will be enabled in debug mode.")

# Compiler flags.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -Wno-attributes") # TODO: remove
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fsanitize=${SANITIZER} -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

# Output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes.
include_directories(${BUSTUB_SRC_INCLUDE_DIR} ${BUSTUB_TEST_INCLUDE_DIR} ${BUSTUB_THIRD_PARTY_INCLUDE_DIR})
include_directories(BEFORE src) # This is needed for gtest.

function(disable_target_warnings NAME)
        target_compile_options(${NAME} PRIVATE "-w")
endfunction()

# #####################################################################################################################
# Other CMake modules
# MUST BE ADDED AFTER CONFIGURING COMPILER PARAMETERS
# #####################################################################################################################
add_subdirectory(src)
# add_subdirectory(test)