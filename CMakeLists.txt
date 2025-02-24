cmake_minimum_required(VERSION 3.30)
project(alive_artform)

set(CMAKE_CXX_STANDARD 17)

include_directories("$ENV{USERPROFILE}/scoop/apps/sdl2/current/include/SDL2")
link_directories("$ENV{USERPROFILE}/scoop/apps/sdl2/current/lib")

include_directories("$ENV{USERPROFILE}/scoop/apps/sdl2-ttf/current/include/SDL2_ttf")
link_directories("$ENV{USERPROFILE}/scoop/apps/sdl2-ttf/current/lib")

add_executable(alive_artform main.cpp)

target_link_libraries(alive_artform -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf)