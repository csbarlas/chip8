set(BINARY ${CMAKE_PROJECT_NAME})

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

add_executable(${BINARY}_bin main.cpp Machine.cpp ROM.cpp Executor.cpp Display.cpp)
add_library(${BINARY}_lib STATIC main.cpp Machine.cpp ROM.cpp Executor.cpp Display.cpp)

target_link_libraries(${BINARY}_bin ${SDL2_LIBRARIES})
target_link_libraries(${BINARY}_lib ${SDL2_LIBRARIES})