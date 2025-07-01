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

#include "keyball44.h"

// LED Configuration
led_config_t g_led_config = { {
  // LED Index mapping (行列 → LED)
  {     17,   14,     10,     6,     3,    0 },
  {     18,   15,     11,     7,     4,    1 },
  {     19,   16,     12,     8,     5,    2 },
  { NO_LED,   13,      9,    27,    28,   29 },
  {     40,   43,     47,     50,   53,   56 },
  {     41,   44,     48,     51,   54,   57 },
  {     42,   45,     49,     52,   55,   58 },
  { NO_LED,   46, NO_LED, NO_LED,   31,   30 }
}, {
  // LED Index → 座標 (x:0〜224,y:0～64の範囲)
{85,0},{85,21},{85,42},{68,0},{68,21},{68,42},{51,0},{51,21},{51,42},{34,63},
{34,0},{34,21},{34,42},{17,63},{17,0},{17,21},{17,42},{0,0},{0,21},{0,42},
{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{51,63},{68,63},{85,63},
{136,63},{153,63},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
{221,0},{221,21},{221,42},{204,0},{204,21},{204,42},{204,63},{187,0},{187,21},{187,42},
{170,0},{170,21},{170,42},{153,0},{153,21},{153,42},{136,0},{136,21},{136,42},{0,0}
}, {
  // LED フラグ（キー点灯のフラグ　0は点灯なし）
  4,4,4,4,4,4,4,4,4,1,
  4,4,4,1,4,4,4,1,1,1,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  4,4,1,4,4,4,1,4,4,4,
  4,4,4,4,4,4,4,4,4,0
} };
