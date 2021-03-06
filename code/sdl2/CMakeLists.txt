cmake_minimum_required(VERSION 3.14)
project(sdl2 VERSION 0.1.0)

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
pkg_search_module(SDL2 REQUIRED sdl2>=2.0.0)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/utils/src
    ${CMAKE_SOURCE_DIR}/external/cglm/include
)

add_subdirectory(src/sdl2)
