cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Zephyr REQUIRED)

add_subdirectory(drivers/subsys/our_driver)

project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
