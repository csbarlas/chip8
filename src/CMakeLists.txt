set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}_bin main.cpp Machine.cpp ROM.cpp Executor.cpp)
add_library(${BINARY}_lib STATIC main.cpp Machine.cpp ROM.cpp Executor.cpp)