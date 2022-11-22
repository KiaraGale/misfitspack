# Basic CMake that uses All.c
cmake_minimum_required(VERSION 3.7)

project(MisfitsPack)
set(MOD_NAME MisfitsPack CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "Misfits" CACHE STRING "The name of the built library")

add_library(MisfitsPack SHARED
    GameAPI/C/GameAPI/Game.c
    src/Misfits/Misfits.c
    src/Misfits/Objects/All.c
)

target_include_directories(MisfitsPack PRIVATE
    src/Misfits/
    src/Misfits/Objects/
    GameAPI/C/GameAPI/
)

set_target_properties(MisfitsPack PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)