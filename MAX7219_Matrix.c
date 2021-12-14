#include "MAX7219_Matrix.h"

#define LAST_BIT_INDEX 7
#define ASCII_SPACE_OFFSET 0x20
#define TOTAL_FONT_COUNT 3

#define BIT_READ(value, bit) (((value) >> (bit)) & 0x01)
#define BIT_SET(value, bit) ((value) |= (1UL << (bit)))
#define BIT_CLEAR(value, bit) ((value) &= ~(1UL << (bit)))
#define BIT_WRITE(value, bit, bitValue) ((bitValue) ? BIT_SET((value), (bit)) : BIT_CLEAR((value), (bit)))

static SPI_Polling spiInstance;
static bool isInvertedViewEnable = false;
static uint8_t lcdFont = MAX7219_FONT_DEFAULT;
static uint8_t rowBufferArray[MAX7219_MATRIX_DISPLAY_ROW_COUNT][MAX7219_NUMBER_OF_MATRIX_DISPLAYS];

static void shiftRowsRight();
static void shiftRowsLeft();
static void refreshDisplays();

static uint8_t getFontCharacterByte(unsigned char character, uint8_t index);
static inline uint8_t reverseByte(uint8_t byte);
static void displayRowBuffer(uint8_t row, uint8_t displayNumber);
static void sendMAX7219(uint8_t address, uint8_t value);

static inline bool isRowNumberValid(uint8_t row);
static inline bool isDisplayNumberValid(uint8_t displayNumber);


void initMAX7219DotMatrixDisplay(SPI_TypeDef *SPIx,
                                 GPIO_TypeDef *chipSelectGPIOx,
                                 uint32_t chipSelectPin,
                                 MAX7219BrightnessMode brightness) {
    spiInstance = initSPI(SPIx, chipSelectGPIOx, chipSelectPin);
    setDecodeModeMAX7219(MAX7219_NO_DECODE_FOR_ALL_DIGITS);       //  no decoding
    setScanLimitMAX7219(MAX7219_DISPLAY_DIGITS_0_1_2_3_4_5_6_7);  //  scan limit = 8 LEDs
    setShutdownMAX7219(MAX7219_NORMAL_OPERATION_MODE);            //  power down = 0，normal mode = 1
    setDisplayTestMAX7219(MAX7219_DISPLAY_TEST_DISABLED);         //  no test display
    setBrightnessMAX7219(brightness);                             //  brightness intensity
    clearMAX7219();
}

void setInvertMAX7219(bool isInverted) {
    isInvertedViewEnable = isInverted;
}

void setFontMAX7219(uint8_t font) {
    if (font <= TOTAL_FONT_COUNT) {
        lcdFont = font;
    }
}

void printCharMAX7219(char character, uint8_t displayNumber) {
    if (displayNumber > MAX7219_NUMBER_OF_MATRIX_DISPLAYS) return;
    for (uint8_t i = 0; i < MAX7219_MATRIX_DISPLAY_ROW_COUNT; i++) {
        uint8_t rowValue = getFontCharacterByte(character, i);
        setLedRowMAX7219(7 - i, displayNumber, reverseByte(rowValue));
    }
}

void scrollStringRightMAX7219(const char *string, uint32_t timeDelayMs) {
    size_t stringLength = strlen(string);
    for (size_t i = 0; i < stringLength; i++) {
        shiftCharRightMAX7219(string[stringLength - i - 1], timeDelayMs);
    }
}

void scrollStringLeftMAX7219(const char *string, uint32_t timeDelayMs) {
    for (size_t i = 0; i < strlen(string); i++) {
        shiftCharLeftMAX7219(string[i], timeDelayMs);
    }
}

void shiftCharRightMAX7219(char character, uint32_t timeDelayMs) {
    for (uint8_t column = 0; column < MAX7219_MATRIX_DISPLAY_COLUMN_COUNT; column++) {
        for (uint8_t row = 0; row < MAX7219_MATRIX_DISPLAY_ROW_COUNT; row++) {
            uint8_t charRowValue = reverseByte(getFontCharacterByte(character, 7 - row));
            uint8_t currentRowValue = rowBufferArray[row][0];

            uint8_t charDotBit = BIT_READ(charRowValue, LAST_BIT_INDEX - column);
            BIT_WRITE(currentRowValue, 0, charDotBit);
            rowBufferArray[row][0] = currentRowValue;
        }
        refreshDisplays();
        shiftRowsRight();
        LL_mDelay(timeDelayMs);
    }
}

void shiftCharLeftMAX7219(char character, uint32_t timeDelayMs) {
    for (uint8_t column = 0; column < MAX7219_MATRIX_DISPLAY_COLUMN_COUNT; column++) {
        for (int row = 0; row < MAX7219_MATRIX_DISPLAY_ROW_COUNT; row++) {
            uint8_t charRowValue = reverseByte(getFontCharacterByte(character, 7 - row));
            uint8_t currentRowValue = rowBufferArray[row][MAX7219_NUMBER_OF_MATRIX_DISPLAYS - 1];

            uint8_t charDotBit = BIT_READ(charRowValue, column);
            BIT_WRITE(currentRowValue, LAST_BIT_INDEX, charDotBit);
            rowBufferArray[row][MAX7219_NUMBER_OF_MATRIX_DISPLAYS - 1] = currentRowValue;
        }
        refreshDisplays();
        shiftRowsLeft();
        LL_mDelay(timeDelayMs);
    }
}

void scrollCharRightMAX7219(char character, uint32_t timeDelayMs) {
    shiftCharRightMAX7219(character, timeDelayMs);
    for (int i = 0; i < (MAX7219_NUMBER_OF_MATRIX_DISPLAYS * 8); i++) {
        shiftRightMAX7219();
        LL_mDelay(timeDelayMs);
    }
}

void scrollCharLeftMAX7219(char character, uint32_t timeDelayMs) {
    shiftCharLeftMAX7219(character, timeDelayMs);
    for (int i = 0; i < (MAX7219_NUMBER_OF_MATRIX_DISPLAYS * 8); i++) {
        shiftLeftMAX7219();
        LL_mDelay(timeDelayMs);
    }
}

void shiftRightMAX7219() {
    shiftRowsRight();
    refreshDisplays();
}

void shiftLeftMAX7219() {
    shiftRowsLeft();
    refreshDisplays();
}

static void shiftRowsRight() {
    for (uint8_t i = 0; i < MAX7219_MATRIX_DISPLAY_ROW_COUNT; i++) {
        uint8_t previousCarrierBit = 0;
        uint8_t currentCarrierBit;

        for (uint8_t j = 0; j < MAX7219_NUMBER_OF_MATRIX_DISPLAYS; j++) {
            displayRowBuffer(i, j);
            uint8_t value = rowBufferArray[i][j];
            currentCarrierBit = BIT_READ(value, 7);                     // get current value MSB and set as carry for next value
            rowBufferArray[i][j] = (value << 1) | previousCarrierBit;   // shift bits and add bit from previous value
            previousCarrierBit = currentCarrierBit;                     // save current bit for next value
        }
    }
}

static void shiftRowsLeft() {
    for (uint8_t row = 0; row < MAX7219_MATRIX_DISPLAY_ROW_COUNT; row++) {
        uint8_t previousCarrierBit = 0;
        uint8_t currentCarrierBit;

        for (int16_t displayNumber = MAX7219_NUMBER_OF_MATRIX_DISPLAYS - 1; displayNumber >= 0; displayNumber--) {
            uint8_t value = rowBufferArray[row][displayNumber];
            currentCarrierBit = (value << 7) & 0x80;                                  // get current value LSB and set as carry for next value
            rowBufferArray[row][displayNumber] = (value >> 1) | previousCarrierBit;   // shift bits and add carrier bit from previous value
            previousCarrierBit = currentCarrierBit;                                   // save current bit for next value
        }
    }
}

void sendCommandMAX7219(uint8_t address, uint8_t command) {
    chipSelectSet(&spiInstance);
    for (uint8_t i = 0; i < MAX7219_NUMBER_OF_MATRIX_DISPLAYS; i++) {
        sendMAX7219(address, command);
    }
    chipSelectReset(&spiInstance);
}

void setLedRowMAX7219(uint8_t row, uint8_t displayNumber, uint8_t rowValue) {
    if (!isRowNumberValid(row) || !isDisplayNumberValid(displayNumber)) return;
    rowBufferArray[row][displayNumber] = rowValue;
    displayRowBuffer(row, displayNumber);
}

void setLedDotMAX7219(uint8_t row, uint8_t column, uint8_t ledValue) { // zero based index
    if (!isRowNumberValid(row)) return;
    uint8_t displayToView = column / 8; // select dot matrix display
    uint8_t columnDotToView = column % 8;  // select dot matrix column
    BIT_WRITE(rowBufferArray[row][displayToView], columnDotToView, ledValue);
    displayRowBuffer(row, displayToView);
}

void clearMAX7219() {
    for (uint8_t i = 0; i < MAX7219_MATRIX_DISPLAY_ROW_COUNT; i++) {
        memset(rowBufferArray[i], 0, MAX7219_NUMBER_OF_MATRIX_DISPLAYS);
    }
    for (MAX7219DigitAddress i = MAX7219_DIGIT_0; i <= MAX7219_DIGIT_7; i++) {
        sendDigitValueMAX7219(i, 0x00);
    }
}

static void refreshDisplays() {
    for (uint8_t row = 0; row < MAX7219_MATRIX_DISPLAY_ROW_COUNT; row++) {
        for (uint8_t displayNumber = 0; displayNumber < MAX7219_NUMBER_OF_MATRIX_DISPLAYS; displayNumber++) {
            displayRowBuffer(row, displayNumber);
        }
    }
}

static uint8_t getFontCharacterByte(unsigned char character, uint8_t index) {
    switch (lcdFont) {
        #ifdef MAX7219_FONT_DEFAULT
            case MAX7219_FONT_DEFAULT:
                return MAX7219_ASCII_TABLE[character - ASCII_SPACE_OFFSET][index];
        #endif
        #ifdef MAX7219_FONT_SPRITES
            case MAX7219_FONT_SPRITES:
                return MAX7219_SPRITES_TABLE[character][index];
        #endif
        #ifdef MAX7219_FONT_REGULAR
            case MAX7219_FONT_REGULAR:
                return MAX7219_ASCII_REGULAR_TABLE[character - ASCII_SPACE_OFFSET][index];
        #endif
        default:
            return 0;
    }
}

static inline uint8_t reverseByte(uint8_t byte) {   //
    static const uint8_t BYTE_REVERSE_LOOKUP_TABLE[16] = {
            0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
            0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
    };
    return (BYTE_REVERSE_LOOKUP_TABLE[byte & 0b1111] << 4) | BYTE_REVERSE_LOOKUP_TABLE[byte >> 4];// Reverse the top and bottom nibble then swap them.
}

static void displayRowBuffer(uint8_t row, uint8_t displayNumber) {
    chipSelectSet(&spiInstance);
    for (uint8_t i = 0; i < MAX7219_NUMBER_OF_MATRIX_DISPLAYS; i++) {
        bool isCurrentDisplayToView = (i == (MAX7219_NUMBER_OF_MATRIX_DISPLAYS - (displayNumber + 1)));
        if (isCurrentDisplayToView) {
            uint8_t rowValue = isInvertedViewEnable ? ~rowBufferArray[row][displayNumber] : rowBufferArray[row][displayNumber];
            sendMAX7219(row + 1, rowValue);
        } else {    // move to next display
            sendMAX7219(MAX7219_NO_OPERATION, 0x00);
        }
    }
    chipSelectReset(&spiInstance);
}

static void sendMAX7219(uint8_t address, uint8_t value) {
    transmit8BitsSPI(&spiInstance, address);
    transmit8BitsSPI(&spiInstance, value);
}

static inline bool isRowNumberValid(uint8_t row) {
    return row < MAX7219_MATRIX_DISPLAY_ROW_COUNT;
}

static inline bool isDisplayNumberValid(uint8_t displayNumber) {
    return displayNumber < MAX7219_NUMBER_OF_MATRIX_DISPLAYS;
}