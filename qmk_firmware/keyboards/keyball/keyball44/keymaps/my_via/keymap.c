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

// RGBLayer setting
#include <string.h>  // memchr用

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  uint8_t layer = get_highest_layer(layer_state);

    // LEDグループ定義
    static const uint8_t layer1_leds_col1[] = {4, 6, 7, 11, 48, 51, 54}; // カラー1　矢印・マウス
    static const uint8_t layer1_leds_col2[]   = {5, 8, 14, 15, 16, 44, 45, 57, 58}; // カラー2　ブラウザ操作系
    static const uint8_t layer1_leds_col3[]   = {10, 40, 46, 47, 50, 53, 56}; // カラー3　マウス数値関連とF2・FN
    static const uint8_t layer1_leds_col4[]   = {0, 1, 2, 13, 52, 55}; // カラー4　拡大縮小・プリントスクリーン
  
    static const uint8_t layer2_leds_col1[]   = {1, 4, 7, 11, 15, 44, 48, 51, 54, 55, 57, 58}; // カラー1　数字・記号
    static const uint8_t layer2_leds_col2[]   = {0, 3, 6, 10, 14, 40, 41, 43, 47, 50, 53, 56}; // カラー2　Fキー
    static const uint8_t layer2_leds_col3[]   = {5, 8}; // カラー3　Excelシート移動
  
    static const uint8_t layer3_leds_col1[]   = {47, 48, 49, 50, 51, 52, 53, 54, 55, 58}; // カラー1　テンキー数字
    static const uint8_t layer3_leds_col2[]  = {1, 2, 4, 5, 43, 44, 56, 57}; // カラー2 記号
    static const uint8_t layer3_leds_col3[]  = {0, 3, 6}; // カラー3 Audio vol
    static const uint8_t layer3_leds_col4[]  = {10, 14, 17}; // カラー4　RGB Toggle

    // LED番号27,28,29,30,31は親指キーのため、ケースに入れる際は消灯推奨。keyball44.cのflagも併せて修正すること。

    for (uint8_t i = led_min; i < led_max; i++) {
        bool colored = false;

        if (layer == 1) {
            if (memchr(layer1_leds_col1, i, sizeof(layer1_leds_col1))) {
                rgb_matrix_set_color(i, 255, 220, 0);  // カラー1　矢印・マウス
                colored = true;
            } else if (memchr(layer1_leds_col2, i, sizeof(layer1_leds_col2))) {
                rgb_matrix_set_color(i, 0, 199, 60);  // カラー2　ブラウザ操作系
                colored = true;
            } else if (memchr(layer1_leds_col3, i, sizeof(layer1_leds_col3))) {
                rgb_matrix_set_color(i, 224, 0, 66);  // カラー3　マウス数値関連とF2・FN
                colored = true;
            } else if (memchr(layer1_leds_col4, i, sizeof(layer1_leds_col4))) {
                rgb_matrix_set_color(i, 0, 205, 190);  // カラー4　拡大縮小・プリントスクリーン
                colored = true;
            }
        } else if (layer == 2) {
            if (memchr(layer2_leds_col1, i, sizeof(layer2_leds_col1))) {
                rgb_matrix_set_color(i, 0, 205, 190);  // カラー1　数字・記号
                colored = true;
            } else if (memchr(layer2_leds_col2, i, sizeof(layer2_leds_col2))) {
                rgb_matrix_set_color(i, 224, 0, 66);  // カラー2　Fキー
                colored = true;
            } else if (memchr(layer2_leds_col3, i, sizeof(layer2_leds_col3))) {
                rgb_matrix_set_color(i, 0, 199, 60);  // カラー3　Excelシート移動
                colored = true;
            }
        } else if (layer == 3) {
            if (memchr(layer3_leds_col1, i, sizeof(layer3_leds_col1))) {
                rgb_matrix_set_color(i, 106, 10, 119);  // カラー1　テンキー数字
                colored = true;
            } else if (memchr(layer3_leds_col2, i, sizeof(layer3_leds_col2))) {
                rgb_matrix_set_color(i, 255, 220, 0);  // カラー2 記号
                colored = true;
            } else if (memchr(layer3_leds_col3, i, sizeof(layer3_leds_col3))) {
                rgb_matrix_set_color(i, 0, 199, 60);  // カラー3 Audio vol
                colored = true;
            } else if (memchr(layer3_leds_col4, i, sizeof(layer3_leds_col4))) {
                rgb_matrix_set_color(i, 224, 0, 66);  // カラー4　RGB Toggle
                colored = true;
            }
        }

        if (!colored) {
            // レイヤー1〜3の時はその他を消灯
            if (layer >= 1 && layer <= 3) {
                rgb_matrix_set_color(i, 0, 0, 0);
            } else {
                // デフォルトレイヤー用処理
                if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                    rgb_matrix_set_color(i, 80, 80, 80);   // 外枠キー
                } else if (HAS_FLAGS(g_led_config.flags[i], 0x04)) {
                    rgb_matrix_set_color(i, 0, 199, 60); // メインキー
                }
            }
        }

        // Caps Lock 上書き処理（使いたければ有効に）
        // if (host_keyboard_led_state().caps_lock) {
        //     rgb_matrix_set_color(i, 255, 255, 0);  // Yellow
        // }
    }

    return false;
}

// 250705追加

#include QMK_KEYBOARD_H
#include "transactions.h"  // ← これが必須

#define LED_TOG_KEY  SAFE_RANGE  // LED_TOGのカスタムキーコード

// LED状態保持用変数（初期はON）
bool led_enabled = true;

// トランザクションID
#define TRANS_LED_TOG 0x01

// トランザクション受信時の処理（スレーブ用）
void receive_led_tog(const void *data, size_t size) {
    if (size == sizeof(bool)) {
        led_enabled = *(bool *)data;
        if (led_enabled) {
            rgb_matrix_enable_noeeprom();
        } else {
            rgb_matrix_disable_noeeprom();
        }
    }
}

// 登録（起動時に呼ばれる）
__attribute__((constructor))
void register_transaction(void) {
    transaction_register_rpc(TRANS_LED_TOG, receive_led_tog);
}

// LED_TOGの処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_TOG_KEY:
            if (record->event.pressed && is_keyboard_master()) {
                // 状態切り替え
                led_enabled = !led_enabled;

                if (led_enabled) {
                    rgb_matrix_enable_noeeprom();
                } else {
                    rgb_matrix_disable_noeeprom();
                }

                // スレーブに通知
                transaction_rpc_send(TRANS_LED_TOG, sizeof(led_enabled), &led_enabled);
            }
            return false;
    }
    return true;
}

// 起動時の初期化（親機は状態復元）
void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
        led_enabled = rgb_matrix_is_enabled();
    }
}

// レイヤー切替でLED制御の有効/無効切り替え
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);

    if (layer == 0) {
        // レイヤー0 → LED制御状態を復元
        if (led_enabled) {
            rgb_matrix_enable_noeeprom();
        } else {
            rgb_matrix_disable_noeeprom();
        }
    } else {
        // レイヤー0以外 → 通常通り（EEPROMから）
        rgb_matrix_reload_from_eeprom();
    }

    return state;
}
