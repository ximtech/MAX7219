cmake_minimum_required(VERSION 3.20)
project(MAX7219 C)

set(CMAKE_C_STANDARD 99)

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME STM32Core
        GITHUB_REPOSITORY ximtech/STM32Core
        GIT_TAG origin/main)

set(MAX7219_MATRIX_DIRECTORY
        ${SPI_POLLING_DIRECTORY}
        ${MAX7219_SOURCE_DIR}
        ${MAX7219_SOURCE_DIR}/include
        CACHE STRING "MAX7219 Matrix directories include to the main project" FORCE)

set(MAX7219_MATRIX_SOURCES
        ${SPI_POLLING_SOURCES}
        ${MAX7219_SOURCE_DIR}/MAX7219_Matrix.c
        ${MAX7219_SOURCE_DIR}/include/MAX7219.h
        ${MAX7219_SOURCE_DIR}/include/MAX7219_Matrix.h
        CACHE STRING "MAX7219 Matrix source files include to the main project" FORCE)