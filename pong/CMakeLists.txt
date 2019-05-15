pkg_search_module(SDL2 REQUIRED sdl2>=2.0.0)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
include_directories(${CMAKE_SOURCE_DIR}/external/cglm/include)

add_executable(pong
    ${CMAKE_SOURCE_DIR}/utils/random.cpp
    ${CMAKE_SOURCE_DIR}/sdl2/sdl2.c
    ${CMAKE_SOURCE_DIR}/sdl2/sdl2_ttf.c
    ${CMAKE_SOURCE_DIR}/sdl2/engine.c
    ${CMAKE_SOURCE_DIR}/sdl2/timer.c
    main.c
    game.c
    action.c
    render.c
    utils.c
    player.c
    ball.c
    wall.c
    midfield.c
    score.c
    shade.c
)
target_link_libraries(pong
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
