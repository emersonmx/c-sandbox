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
