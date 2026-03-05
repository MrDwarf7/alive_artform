cmake_minimum_required(VERSION 3.30)
project(alive_artform)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(Dependencies)

add_subdirectory(src)

target_include_directories(alive_artform PRIVATE
  ${CMAKE_SOURCE_DIR}/assets
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
  "."
)


#####
#####
#####
##### # include_directories("$ENV{USERPROFILE}/scoop/apps/sdl2/2.32.8/include/SDL2")
##### # link_directories("$ENV{USERPROFILE}/scoop/apps/sdl2/current/lib")
#####
##### # include_directories("$ENV{USERPROFILE}/scoop/apps/sdl2-ttf/2.24.0/include/SDL2_ttf")
##### # link_directories("$ENV{USERPROFILE}/scoop/apps/sdl2-ttf/current/lib")
#####
##### # include_directories("${CMAKE_SOURCE_DIR}/include/sdl2_2.30.12/include/SDL2")
##### # link_directories("${CMAKE_SOURCE_DIR}/include/sdl2_2.30.12/include/SDL2/lib")
#####
##### # include_directories("${CMAKE_SOURCE_DIR}/include/sdl2-ttf_2.24.0/include/SDL2_ttf")
##### # link_directories("${CMAKE_SOURCE_DIR}/include/sdl2-ttf_2.24.0/include/lib")
#####
##### target_include_directories(alive_artform PRIVATE /usr/include/SDL2)
##### find_package(PkgConfig REQUIRED)
#####
##### pkg_check_modules(SDL2 REQUIRED sdl2)
##### pkg_check_modules(SDL2_TTF REQUIRED sdl2_ttf)
#####
##### add_executable(alive_artform main.cpp)
#####
##### # target_link_libraries(alive_artform -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf)
##### # target_link_libraries(alive_artform -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf)
#####
#####
#####
##### target_include_directories(alive_artform PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
##### target_link_libraries(alive_artform PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
##### target_compile_options(alive_artform PRIVATE ${SDL2_CFLAGS_OTHER} ${SDL2_TTF_CFLAGS_OTHER})
