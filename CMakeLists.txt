cmake_minimum_required(VERSION 3.14)

Project("ACreation")
set(CMAKE_POLICY_DEFAULT_CMP0079 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0002 NEW)

# include fetchcontent so that stuff
# can be pulled from git and compiled automatically
include(FetchContent)

set(SKIP_INSTALL_ALL ON) # Prevent png from trying to install stuff and fail

# add the .cpp files
file(GLOB ACREATION_SOURCE
    src/*.cpp
)

# make an executable from the C++ files
add_executable(Main ${ACREATION_SOURCE})

# get SDL2 from git, compile it and link it

FetchContent_Declare(
  SDL
  URL            https://www.libsdl.org/release/SDL2-2.0.12.zip
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/external/SDL2
)

FetchContent_Declare(
  SDL_IMAGE
  URL            https://github.com/pvallet/SDL_image/archive/release-2.0.5-mod7.zip
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/external/SDL2_image
)

# include all the headers
include_directories(
    "src/headers"
)

# make them usable
FetchContent_MakeAvailable(SDL SDL_IMAGE)

# link them
target_link_libraries(Main
    SDL2
    SDL2_image
)

# KABOOM!