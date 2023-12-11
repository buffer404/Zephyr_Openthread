list(APPEND ZEPHYR_EXTRA_MODULES /home/leonid/zephyrproject/zephyr/zephyr_lmtltd_light/lmtlib_light)
cmake_minimum_required(VERSION 3.20)

set(BOARD SOVA427VI)

find_package(Zephyr REQUIRED HINTS ZEPHYR_BASE)

project(cc-app-minimal)

include_directories(Inc)

file(GLOB_RECURSE SOURCES "src/*.*")

target_sources(app PRIVATE ${SOURCES})
