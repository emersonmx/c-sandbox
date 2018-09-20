pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(
    ${SDL2_INCLUDE_DIRS}
)

add_executable(time-test time-test.c)
target_link_libraries(time-test
    ${SDL2_LIBRARIES}
)
