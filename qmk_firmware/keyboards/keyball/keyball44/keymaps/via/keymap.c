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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  /*
  {    18, 15, 11,  7,  4,  1,    57, 54,     51,     48, 44,     41}, \
  {    19, 16, 12,  8,  5,  2,    58, 55,     52,     49, 45,     42}, \
  {    20, 17, 13,  9,  6,  3,    59, 56,     53,     50, 46,     43}, \
  {NO_LED, 14, 10, 28, 29, 30,    31, 32, NO_LED, NO_LED, 47, NO_LED} \
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
