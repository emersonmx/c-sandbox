cmake_minimum_required(VERSION 3.14)
project(misc VERSION 0.1.0)

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
    -g -Wall -Wextra -Wpedantic \
    -Wformat=2 -Wno-unused-parameter -Wshadow \
    -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
    -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
    -DDEBUG \
")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -g -Wall -Wextra -Wpedantic \
    -Wformat=2 -Wno-unused-parameter -Wshadow \
    -Wwrite-strings -Wredundant-decls -Wmissing-include-dirs \
    -DDEBUG \
")

add_subdirectory(src/misc)
