add_executable(hello-world hello-world.c)

add_executable(random-test
    ${CMAKE_SOURCE_DIR}/utils/random.cpp
    random-test.c
)
