/*
    cocoKeyMaps.h v1.0
    by: Paul Fiscarelli
    
    Copyright (c) 2020, Paul Fiscarelli

    MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#include <Keyboard.h>

#define KEY_AT  0x5B
#define KEY_A   0x61
#define KEY_B   0x62
#define KEY_C   0x63
#define KEY_D   0x64
#define KEY_E   0x65
#define KEY_F   0x66
#define KEY_G   0x67
#define KEY_H   0x68
#define KEY_I   0x69
#define KEY_J   0x6A
#define KEY_K   0x6B
#define KEY_L   0x6C
#define KEY_M   0x6D
#define KEY_N   0x6E
#define KEY_O   0x6F
#define KEY_P   0x70
#define KEY_Q   0x71
#define KEY_R   0x72
#define KEY_S   0x73
#define KEY_T   0x74
#define KEY_U   0x75
#define KEY_V   0x76
#define KEY_W   0x77
#define KEY_X   0x78
#define KEY_Y   0x79
#define KEY_Z   0x7A
#define KEY_0   0x30
#define KEY_1   0x31
#define KEY_2   0x32
#define KEY_3   0x33
#define KEY_4   0x34
#define KEY_5   0x35
#define KEY_6   0x36
#define KEY_7   0x37
#define KEY_8   0x38
#define KEY_9   0x39

#define KEY_TAB         0x09
#define KEY_F1          0xC2
#define KEY_F2          0xC3
#define KEY_SHIFT       0x81
#define KEY_SPACE       0x20
#define KEY_COLON       0x2D
#define KEY_SEMICOLON   0x3B
#define KEYPAD_ASTERIX  0xDD
#define KEY_COMMA       0x2C
#define KEY_PERIOD      0x2E
#define KEY_SLASH       0x2F
#define KEY_MINUS       0x3D

const uint8_t keyMapVCC[56] = {KEY_RIGHT_ALT, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
                               KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
                               KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W,
                               KEY_X, KEY_Y, KEY_Z, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_BACKSPACE, KEY_RIGHT_ARROW, KEY_SPACE,
                               KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
                               KEY_8, KEY_9, KEY_COLON, KEY_SEMICOLON, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH,
                               KEY_RETURN, KEY_HOME, KEY_END, KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_F1, KEY_F2, KEY_LEFT_SHIFT};

const uint8_t keyMapXRoar[56] = {KEY_AT, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
                                 KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
                                 KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W,
                                 KEY_X, KEY_Y, KEY_Z, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_SPACE,
                                 KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
                                 KEY_8, KEY_9, KEY_COLON, KEY_SEMICOLON, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, 
                                 KEY_RETURN, KEY_HOME, KEY_ESC, KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_F1, KEY_F2, KEY_LEFT_SHIFT};

const uint8_t keyMapMAME[56] = {KEY_AT, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
                                KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
                                KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W,
                                KEY_X, KEY_Y, KEY_Z, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_SPACE,
                                KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
                                KEY_8, KEY_9, KEY_COLON, KEY_SEMICOLON, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH,
                                KEY_RETURN, KEY_HOME, KEY_ESC, KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_F1, KEY_F2, KEY_LEFT_SHIFT};                                 

// Old MAME keyMap below - KEYPAD_ASTERIX used for '@' at some point - not sure why I had set it this way
//
//const uint8_t keyMapMAME[56] = {KEYPAD_ASTERIX, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
//                                KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
//                                KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W,
//                                KEY_X, KEY_Y, KEY_Z, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_SPACE,
//                                KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
//                                KEY_8, KEY_9, KEY_COLON, KEY_SEMICOLON, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH,
//                                KEY_RETURN, KEY_HOME, KEY_ESC, KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_F1, KEY_F2, KEY_LEFT_SHIFT};
