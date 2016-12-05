project(ffffff)

cmake_minimum_required(VERSION 3.5)

set(SOURCES
main.c
)

add_executable(${PROJECT_NAME} src/main.c)

INCLUDE(FindPkgConfig)
INCLUDE(ExternalProject)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

if (not ${SDL2})
    ExternalProject_Add(SDL2 HG_REPOSITORY https://hg.libsdl.org/SDL)
    ExternalProject_Get_Property(SDL2 SDL_DIR)
    INCLUDE_DIRECTORIES(${SDL_DIR}/include)
else()
   INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
endif ()
