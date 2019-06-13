pkg_search_module(SDL2 REQUIRED sdl2>=2.0.0)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

add_executable(time_test time_test.c)
target_link_libraries(time_test
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

add_executable(resize_test
    resize_test.c
    sdl2.c
    sdl2_ttf.c
    text.c
)
target_link_libraries(resize_test
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

add_executable(events
    sdl2.c
    events.c
)
target_link_libraries(events
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
