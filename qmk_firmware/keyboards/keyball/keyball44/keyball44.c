/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "lib/keyball/keyball.h"

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b00111111,
    0b00111111,
    0b00111111,
    0b00111110,
    0b00111111,
    0b00111111,
    0b00111111,
    0b00111110,
};
// clang-format on

void keyball_on_adjust_layout(keyball_adjust_t v) {
#ifdef RGBLIGHT_ENABLE
    // adjust RGBLIGHT's clipping and effect ranges
    uint8_t lednum_this = keyball.this_have_ball ? 29 : 30;
    uint8_t lednum_that = !keyball.that_enable ? 0 : keyball.that_have_ball ? 29 : 30;
    rgblight_set_clipping_range(is_keyboard_left() ? 0 : lednum_that, lednum_this);
    rgblight_set_effect_range(0, lednum_this + lednum_that);
#endif
}

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  /*
  {    18, 15, 11,  7,  4,  1,    57, 54,     51,     48, 44,      41}, \
  {    19, 16, 12,  8,  5,  2,    58, 55,     52,     49, 45,      42}, \
  {    20, 17, 13,  9,  6,  3,    59, 56,     53,     50, 46,      43}, \
  {NO_LED, 14, 10, 28, 29, 30,    31, 32, NO_LED, NO_LED, 47   NO_LED} \
  // {21,22,23,24,25,26,27,         33,34,35,36,37,38,39,40,} //underglows
  */
  {     18,   15,     11,     7,     4,    1 }, \
  {     19,   16,     12,     8,     5,    2 }, \
  {     20,   17,     13,     9,     6,    3 }, \
  { NO_LED,   14,     10,     28,   29,   30 }, \
  {     41,   44,     48,     51,   54,   57 }, \
  {     42,   45,     49,     52,   55,   58 }, \
  {     43,   46,     50,     53,   56,   59 }, \
  { NO_LED,   47, NO_LED, NO_LED,   32,   33 }\
}, {
  // LED Index to Physical Position
  // {x,y}: x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION , y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
{0,0}	, //0
{85,0}	, //1
{85,21}	, //2
{85,42}	, //3
{68,0}	, //4
{68,21}	, //5
{68,42}	, //6
{51,0}	, //7
{51,21}	, //8
{51,42}	, //9
{51,63}	, //10
{34,0}	, //11
{34,21}	, //12
{34,42}	, //13
{34,63}	, //14
{17,0}	, //15
{17,21}	, //16
{17,42}	, //17
{0,0}	, //18
{0,21}	, //19
{0,42}	, //20
{0,0}	, //21
{0,0}	, //22
{0,0}	, //23
{0,0}	, //24
{0,0}	, //25
{0,0}	, //26
{0,0}	, //27
{68,63}	, //28
{85,63}	, //29
{102,63}, //30
{153,63}, //31
{170,63}, //32
{0,0}	, //33
{0,0}	, //34
{0,0}	, //35
{0,0}	, //36
{0,0}	, //37
{0,0}	, //38
{0,0}	, //39
{0,0}	, //40
{255,0}	, //41
{255,21}, //42
{255,42}, //43
{238,0}	, //44
{238,21}, //45
{238,42}, //46
{238,63}, //47
{221,0}	, //48
{221,21}, //49
{221,42}, //50
{204,0}	, //51
{204,21}, //52
{204,42}, //53
{187,0}	, //54
{187,21}, //55
{187,42}, //56
{170,0}	, //57
{170,21}, //58
{170,42}, //59
{0,0}	, //60
}, {
  // LED Index to Flag
LED_FLAG_NONE	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_NONE
} };
