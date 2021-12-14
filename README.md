# MAX7219

**STM32** Low Layer(LL) library. MAX7219 are compact, serial input/output common-cathode display drivers that interface
microprocessors (µPs) to 7-segment numeric LED displays of up to 8 digits, bar-graph displays, or 64 individual LEDs.

<img src="https://github.com/ximtech/MAX7219/blob/main/example/max7219.PNG" alt="image" width="300"/>

### Features

- Dot LED Matrix library
  - Text shift and scroll
  - Custom text font and image print
  - Predefined text fonts and sprints

### Add as CPM project dependency

How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)

```cmake
CPMAddPackage(
        NAME MAX7219
        GITHUB_REPOSITORY ximtech/MAX7219
        GIT_TAG origin/main)
```

### Project configuration

1. Start project with STM32CubeMX:
    * [SPI configuration](https://github.com/ximtech/MAX7219/blob/main/example/config.PNG)
2. Select: Project Manager -> Advanced Settings -> SPI -> LL
3. Generate Code
4. Add sources to project:

```cmake
add_subdirectory(${STM32_CORE_SOURCE_DIR}/SPI/Polling)  # add SPI dependency

include_directories(${includes}
        ${MAX7219_MATRIX_DIRECTORY})   # matrix display source directories

file(GLOB_RECURSE SOURCES ${sources}
        ${MAX7219_MATRIX_SOURCES})    # matrix display source files
```

3. Then Build -> Clean -> Rebuild Project

## Wiring

- Single module
    - <img src="https://github.com/ximtech/MAX7219/blob/main/example/pinout1.PNG" alt="image" width="300"/>
- Multi modules
    - <img src="https://github.com/ximtech/MAX7219/blob/main/example/pinout2.PNG" alt="image" width="300"/>

### Usage

In `main.h` set configuration defines

```c
#define MAX7219_NUMBER_OF_MATRIX_DISPLAYS  4    // by default 4 led matrix modules selected

// Define fonts. Comment unused.
#define MAX7219_FONT_DEFAULT  1
#define MAX7219_FONT_SPRITES  2
#define MAX7219_FONT_REGULAR  3
```
- Usage example: [link](https://github.com/ximtech/MAX7219/blob/main/example/example.c)