cmake_minimum_required(VERSION 3.14)
project(utils VERSION 0.1.0)

# Configs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
    -Wall -Wextra -Wpedantic \
    -Wformat=2 -Wno-unused-parameter -Werror -Wshadow \
    -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
    -Wstrict-overflow -fno-strict-aliasing \
    -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
    -Wno-missing-field-initializers \
    -DDEBUG \
")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -Wall -Wextra -Wpedantic \
    -Wformat=2 -Wno-unused-parameter -Wshadow -Werror \
    -Wwrite-strings -Wredundant-decls -Wmissing-include-dirs \
    -DDEBUG \
")

# Libs
include(FindPkgConfig)

# Build settings
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src/utils)
