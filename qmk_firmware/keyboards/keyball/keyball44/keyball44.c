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
  {      0,    3,      6,     10,   14,   17 },
  // 左手第2段
  {      1,    4,      7,     11,   15,   18 },
  // 左手第3段
  {      2,    5,      8,     12,   16,   19 },
  // 左手小指列（4段目）
  { NO_LED,    9,     13,     27,   28,   29 },
  {     40,   43,     47,     50,   53,   56 },
  {     41,   44,     48,     51,   54,   57 },
  {     42,   45,     49,     52,   55,   58 },
  { NO_LED,   46, NO_LED, NO_LED,   31,   30 }
}, {
  // LED Index → 座標 (0〜255の範囲)
  {102,0},{102,21},{102,42},{85,0},{85,21},{85,42},{68,0},{68,21},{68,42},{51,63},{51,0},{51,21},{51,42},{34,63},{34,0},{34,21},{34,42},{17,0},{17,21},{17,42},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{68,63},{85,63},{102,63},{153,63},{170,63},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{238,0},{238,21},{238,42},{221,0},{221,21},{221,42},{221,63},{204,0},{204,21},{204,42},
{187,0},{187,21},{187,42},{170,0},{170,21},{170,42},{153,0},{153,21}, {153,42}, {0,0}
}, {
  // LED フラグ（キー点灯 or 無効）
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE,
  LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE,
  LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE, LED_FLAG_NONE,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_NONE
} };
