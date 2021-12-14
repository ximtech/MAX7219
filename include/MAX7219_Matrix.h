#pragma once

#include <string.h>
#include "MAX7219.h"
#include "main.h"

#ifndef MAX7219_NUMBER_OF_MATRIX_DISPLAYS
    #define MAX7219_NUMBER_OF_MATRIX_DISPLAYS   4
#endif

#define MAX7219_MATRIX_DISPLAY_ROW_COUNT    8
#define MAX7219_MATRIX_DISPLAY_COLUMN_COUNT 8

// Font define section. Uncomment fonts what you want to use
// #define MAX7219_FONT_DEFAULT  1
//#define MAX7219_FONT_SPRITES  2
//#define MAX7219_FONT_REGULAR  3

#ifdef MAX7219_FONT_DEFAULT
#include "Fonts/MAX7219_Font_Default.h"
#endif
#ifdef MAX7219_FONT_SPRITES
#include "Fonts/MAX7219_Font_Sprites.h" // Images
#endif
#ifdef MAX7219_FONT_REGULAR
#include "Fonts/MAX7219_Font_Regular.h"
#endif


void initMAX7219DotMatrixDisplay(SPI_TypeDef *SPIx, GPIO_TypeDef *chipSelectGPIOx, uint32_t chipSelectPin, MAX7219BrightnessMode brightness);
void setInvertMAX7219(bool isInverted);
void setFontMAX7219(uint8_t font);
void printCharMAX7219(char character, uint8_t displayNumber);

void scrollStringRightMAX7219(const char *string, uint32_t timeDelayMs);
void scrollStringLeftMAX7219(const char *string, uint32_t timeDelayMs);

void shiftCharRightMAX7219(char character, uint32_t timeDelayMs);
void shiftCharLeftMAX7219(char character, uint32_t timeDelayMs);

void scrollCharRightMAX7219(char character, uint32_t timeDelayMs);
void scrollCharLeftMAX7219(char character, uint32_t timeDelayMs);

void shiftRightMAX7219();
void shiftLeftMAX7219();

void setLedDotMAX7219(uint8_t row, uint8_t column, uint8_t ledValue);
void setLedRowMAX7219(uint8_t row, uint8_t displayNumber, uint8_t rowValue);

void clearMAX7219();