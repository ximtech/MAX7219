#pragma once

#include "SPI_Polling.h"

// MAX7219 Commands
#define MAX7219_NO_OPERATION 0x00
#define MAX7219_DECODE_MODE  0x09
#define MAX7219_INTENSITY    0x0A
#define MAX7219_SCAN_LIMIT   0x0B
#define MAX7219_SHUTDOWN     0x0C
#define MAX7219_DISPLAY_TEST 0x0F

typedef enum MAX7219DecodeMode {
    MAX7219_NO_DECODE_FOR_ALL_DIGITS = 0x00,
    MAX7219_DECODE_FOR_DIGIT_0       = 0x01,
    MAX7219_DECODE_FOR_DIGITS_3_TO_0 = 0x0F,
    MAX7219_DECODE_FOR_DIGITS_7_TO_0 = 0xFF
} MAX7219DecodeMode;

typedef enum MAX7219BrightnessMode {
    MAX7219_BRIGHTNESS_INTENSITY_0  = 0x00, // Min on
    MAX7219_BRIGHTNESS_INTENSITY_1  = 0x01,
    MAX7219_BRIGHTNESS_INTENSITY_2  = 0x02,
    MAX7219_BRIGHTNESS_INTENSITY_3  = 0x03,
    MAX7219_BRIGHTNESS_INTENSITY_4  = 0x04,
    MAX7219_BRIGHTNESS_INTENSITY_5  = 0x05,
    MAX7219_BRIGHTNESS_INTENSITY_6  = 0x06,
    MAX7219_BRIGHTNESS_INTENSITY_7  = 0x07,
    MAX7219_BRIGHTNESS_INTENSITY_8  = 0x08,
    MAX7219_BRIGHTNESS_INTENSITY_9  = 0x09,
    MAX7219_BRIGHTNESS_INTENSITY_10 = 0x0A,
    MAX7219_BRIGHTNESS_INTENSITY_11 = 0x0B,
    MAX7219_BRIGHTNESS_INTENSITY_12 = 0x0C,
    MAX7219_BRIGHTNESS_INTENSITY_13 = 0x0D,
    MAX7219_BRIGHTNESS_INTENSITY_14 = 0x0E,
    MAX7219_BRIGHTNESS_INTENSITY_15 = 0x0F // Max on,
} MAX7219BrightnessMode;

typedef enum MAX7219ScanLimitMode {
    MAX7219_DISPLAY_DIGIT_0                = 0x00,
    MAX7219_DISPLAY_DIGITS_0_1             = 0x01,
    MAX7219_DISPLAY_DIGITS_0_1_2           = 0x02,
    MAX7219_DISPLAY_DIGITS_0_1_2_3         = 0x03,
    MAX7219_DISPLAY_DIGITS_0_1_2_3_4       = 0x04,
    MAX7219_DISPLAY_DIGITS_0_1_2_3_4_5     = 0x05,
    MAX7219_DISPLAY_DIGITS_0_1_2_3_4_5_6   = 0x06,
    MAX7219_DISPLAY_DIGITS_0_1_2_3_4_5_6_7 = 0x07
} MAX7219ScanLimitMode;

typedef enum MAX7219ShutdownMode {
    MAX7219_SHUTDOWN_MODE         = 0x00,
    MAX7219_NORMAL_OPERATION_MODE = 0x01,
} MAX7219ShutdownMode;

typedef enum MAX7219DisplayTestMode {
    MAX7219_DISPLAY_TEST_DISABLED = 0x00,
    MAX7219_DISPLAY_TEST_ENABLED  = 0x01,
} MAX7219DisplayTestMode;

typedef enum MAX7219DigitAddress {
    MAX7219_DIGIT_0 = 0x01,
    MAX7219_DIGIT_1 = 0x02,
    MAX7219_DIGIT_2 = 0x03,
    MAX7219_DIGIT_3 = 0x04,
    MAX7219_DIGIT_4 = 0x05,
    MAX7219_DIGIT_5 = 0x06,
    MAX7219_DIGIT_6 = 0x07,
    MAX7219_DIGIT_7 = 0x08,
} MAX7219DigitAddress;


extern void sendCommandMAX7219(uint8_t address, uint8_t value);

static inline void setDecodeModeMAX7219(MAX7219DecodeMode decodeMode) {
    sendCommandMAX7219(MAX7219_DECODE_MODE, decodeMode);
}

static inline void setBrightnessMAX7219(MAX7219BrightnessMode brightnessMode) {
    sendCommandMAX7219(MAX7219_INTENSITY, brightnessMode);
}

static inline void setScanLimitMAX7219(MAX7219ScanLimitMode scanLimitMode) {
    sendCommandMAX7219(MAX7219_SCAN_LIMIT, scanLimitMode);
}

static inline void setShutdownMAX7219(MAX7219ShutdownMode shutdownMode) {
    sendCommandMAX7219(MAX7219_SHUTDOWN, shutdownMode);
}

static inline void setDisplayTestMAX7219(MAX7219DisplayTestMode displayTestMode) {
    sendCommandMAX7219(MAX7219_DISPLAY_TEST, displayTestMode);
}

static inline void sendNoOperationCommandMAX7219() {
    sendCommandMAX7219(MAX7219_NO_OPERATION, 0x00);
}

static inline void sendDigitValueMAX7219(MAX7219DigitAddress address, uint8_t value) {
    sendCommandMAX7219(address, value);
}