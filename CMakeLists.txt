cmake_minimum_required(VERSION 3.31)
project(mandelbrot_sfml)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network System)

add_executable(mandelbrot_sfml main.cpp
        Timer.cpp
        Timer.h
)

target_link_libraries(mandelbrot_sfml PRIVATE SFML::Graphics SFML::Audio SFML::Network SFML::System)