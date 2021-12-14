#pragma once

#include "stdint.h"


static const unsigned char MAX7219_ASCII_TABLE[][8] = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0 - 'Empty Cell'
        {0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00}, // 33 - '!'
        {0x66, 0x66, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00}, // 34 - '"'
        {0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00}, // 35 - '#'
        {0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30, 0x00}, // 36 - '$'
        {0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00}, // 37 - '%'
        {0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00}, // 38 - '&'
        {0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00}, // 39 - '''
        {0x0c, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00}, // 40 - '('
        {0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00}, // 41 - ')'
        {0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00}, // 42 - '*'
        {0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00}, // 43 - '+'
        {0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x60}, // 44 - ','
        {0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00}, // 45 - '-'
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, // 46 - '.'
        {0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00}, // 47 - '/'
        {0x7c, 0xc6, 0xce, 0xd6, 0xe6, 0xc6, 0x7c, 0x00}, // 48 - '0'
        {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00}, // 49 - '1'
        {0x7c, 0xc6, 0x06, 0x1c, 0x30, 0x66, 0xfe, 0x00}, // 50 - '2'
        {0x7c, 0xc6, 0x06, 0x3c, 0x06, 0xc6, 0x7c, 0x00}, // 51 - '3'
        {0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00}, // 52 - '4'
        {0xfe, 0xc0, 0xc0, 0xfc, 0x06, 0xc6, 0x7c, 0x00}, // 53 - '5'
        {0x38, 0x60, 0xc0, 0xfc, 0xc6, 0xc6, 0x7c, 0x00}, // 54 - '6'
        {0xfe, 0xc6, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00}, // 55 - '7'
        {0x7c, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0x7c, 0x00}, // 56 - '8'
        {0x7c, 0xc6, 0xc6, 0x7e, 0x06, 0x0c, 0x78, 0x00}, // 57 - '9'
        {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00}, // 58 - ':'
        {0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30}, // 59 - ';'
        {0x06, 0x0c, 0x18, 0x30, 0x18, 0x0c, 0x06, 0x00}, // 60 - '<'
        {0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00}, // 61 - '='
        {0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00}, // 62 - '>'
        {0x7c, 0xc6, 0x0c, 0x18, 0x18, 0x00, 0x18, 0x00}, // 63 - '?'
        {0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00}, // 64 - '@'
        {0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00}, // 65 - 'A'
        {0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00}, // 66 - 'B'
        {0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00}, // 67 - 'C'
        {0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00}, // 68 - 'D'
        {0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00}, // 69 - 'E'
        {0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00}, // 70 - 'F'
        {0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3a, 0x00}, // 71 - 'G'
        {0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00}, // 72 - 'H'
        {0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00}, // 73 - 'I'
        {0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00}, // 74 - 'J'
        {0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00}, // 75 - 'K'
        {0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00}, // 76 - 'L'
        {0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00}, // 77 - 'M'
        {0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00}, // 78 - 'N'
        {0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00}, // 79 - 'O'
        {0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00}, // 80 - 'P'
        {0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xce, 0x7c, 0x0e}, // 81 - 'Q'
        {0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00}, // 82 - 'R'
        {0x7c, 0xc6, 0x60, 0x38, 0x0c, 0xc6, 0x7c, 0x00}, // 83 - 'S'
        {0x7e, 0x7e, 0x5a, 0x18, 0x18, 0x18, 0x3c, 0x00}, // 84 - 'T'
        {0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00}, // 85 - 'U'
        {0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00}, // 86 - 'V'
        {0xc6, 0xc6, 0xc6, 0xd6, 0xd6, 0xfe, 0x6c, 0x00}, // 87 - 'W'
        {0xc6, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0xc6, 0x00}, // 88 - 'X'
        {0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x00}, // 89 - 'Y'
        {0xfe, 0xc6, 0x8c, 0x18, 0x32, 0x66, 0xfe, 0x00}, // 90 - 'Z'
        {0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00}, // 91 - '['
        {0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00}, // 92 - '\'
        {0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0x00}, // 93 - ']'
        {0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00}, // 94 - '^'
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff}, // 95 - '_'
        {0x30, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00}, // 96 - '`'
        {0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00}, // 97 - 'a'
        {0xe0, 0x60, 0x7c, 0x66, 0x66, 0x66, 0xdc, 0x00}, // 98 - 'b'
        {0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xc6, 0x7c, 0x00}, // 99 - 'c'
        {0x1c, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76, 0x00}, // 100 - 'd'
        {0x00, 0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0x7c, 0x00}, // 101 - 'e'
        {0x3c, 0x66, 0x60, 0xf8, 0x60, 0x60, 0xf0, 0x00}, // 102 - 'f'
        {0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8}, // 103 - 'g'
        {0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00}, // 104 - 'h'
        {0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x3c, 0x00}, // 105 - 'i'
        {0x06, 0x00, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3c}, // 106 - 'j'
        {0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00}, // 107 - 'k'
        {0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00}, // 108 - 'l'
        {0x00, 0x00, 0xec, 0xfe, 0xd6, 0xd6, 0xd6, 0x00}, // 109 - 'm'
        {0x00, 0x00, 0xdc, 0x66, 0x66, 0x66, 0x66, 0x00}, // 110 - 'n'
        {0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0x00}, // 111 - 'o'
        {0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0}, // 112 - 'p'
        {0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e}, // 113 - 'q'
        {0x00, 0x00, 0xdc, 0x76, 0x60, 0x60, 0xf0, 0x00}, // 114 - 'r'
        {0x00, 0x00, 0x7e, 0xc0, 0x7c, 0x06, 0xfc, 0x00}, // 115 - 's'
        {0x30, 0x30, 0xfc, 0x30, 0x30, 0x36, 0x1c, 0x00}, // 116 - 't'
        {0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00}, // 117 - 'u'
        {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00}, // 118 - 'v'
        {0x00, 0x00, 0xc6, 0xd6, 0xd6, 0xfe, 0x6c, 0x00}, // 119 - 'w'
        {0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00}, // 120 - 'x'
        {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0x7e, 0x06, 0xfc}, // 121 - 'y'
        {0x00, 0x00, 0x7e, 0x4c, 0x18, 0x32, 0x7e, 0x00}, // 122 - 'z'
        {0x0e, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0e, 0x00}, // 123 - '{'
        {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // 124 - '|'
        {0x70, 0x18, 0x18, 0x0e, 0x18, 0x18, 0x70, 0x00}, // 125 - '}'
        {0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 126 - '~'
};