/* Copyright 2019 Ramon Imbao
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include <quantum.h>
#include <quantum/keymap_extras/keymap_jp.h>

static bool ENCODER_A_PRESSED = false;
static bool ENCODER_B_PRESSED = false;

static uint8_t current_layer = 0;

enum ENCODER_A_LAYERS {
    VSCROLL = 0,
    VARROW,
    VOLUME,
    ZOOM,
};

enum ENCODER_B_LAYERS {
    HSCROLL = 0,
    HARROW,
    BRIGHTNESS,
    FLUX_BRIGHTNESS,
};

static enum ENCODER_A_LAYERS ENCODER_A_LAYER = VSCROLL;
static enum ENCODER_B_LAYERS ENCODER_B_LAYER = HSCROLL;

enum custom_keycodes {
    EIGO = SAFE_RANGE,
    NIHONGO,
};


// Layers
#define _ENGLISH 0
#define _JAPANESE 1
#define _SWITCHER 2

// Scroll Lock layer key
#define SWITCH LT(_SWITCHER, KC_SCROLLLOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ENGLISH] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,          SWITCH,              KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PAUSE, KC_PSCR,
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,      KC_INS, KC_HOME, KC_PGUP,    KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQUAL, KC_BSLS, KC_BSPACE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,              KC_DEL, KC_END, KC_PGDN,     KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_ENTER,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                                          KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_BSLS,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                     KC_UP,               KC_NO, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSFT, KC_RSHIFT,
        KC_LCTL, KC_LALT,    KC_NO, KC_SPACE,            KC_LEFT, KC_DOWN, KC_RIGHT,  KC_BSPACE, KC_NO,       KC_RALT, KC_RGUI, KC_RCTL
    ),

    [_JAPANESE] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,          SWITCH,              KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PAUSE, KC_PSCR,
        JP_ZHTG, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,       KC_INS, KC_HOME, KC_PGUP,    KC_7, KC_8, KC_9, KC_0, JP_MINS, JP_CIRC, JP_YEN, KC_BSPACE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,              KC_DEL, KC_END, KC_PGDN,     KC_Y, KC_U, KC_I, KC_O, KC_P, JP_AT, JP_LBRC, KC_ENTER,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                                          KC_H, KC_J, KC_K, KC_L, KC_SCOLON, JP_COLN, JP_RBRC,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                     KC_UP,               JP_KANA, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, JP_BSLS, KC_RSHIFT,
        KC_LCTL, KC_LALT,    JP_MHEN, KC_SPACE,            KC_LEFT, KC_DOWN, KC_RIGHT,  KC_BSPACE, JP_HENK,       KC_RALT, KC_RGUI, KC_RCTL
    ),

    [_SWITCHER] = LAYOUT(
        KC_NO, EIGO, NIHONGO, KC_NO, KC_NO, KC_NO, KC_NO,            SWITCH,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                    KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

void matrix_user_init(void) {
    // Set encoder button pins to pull-up.
    setPinInputHigh(ENCODER_BUTTON_A);
    setPinInputHigh(ENCODER_BUTTON_B);

    // Check the default layer (for encoder correctness)
    current_layer = eeconfig_read_default_layer();
}

void matrix_scan_user(void) {
    if (readPin(ENCODER_BUTTON_A) == 0) { // Encoder A pressed
        if (ENCODER_A_PRESSED == false) {
            switch (ENCODER_A_LAYER) {
                case VSCROLL:
                    ENCODER_A_LAYER = VARROW;
                    break;
                case VARROW:
                    ENCODER_A_LAYER = VOLUME;
                    break;
                case VOLUME:
                    ENCODER_A_LAYER = ZOOM;
                    break;
                case ZOOM:
                    ENCODER_A_LAYER = VSCROLL;
                    break;
            }
            ENCODER_A_PRESSED = true;
        }
    } else {
        ENCODER_A_PRESSED = false;
    }

    if (readPin(ENCODER_BUTTON_B) == 0) { // Encoder B pressed
        if (ENCODER_B_PRESSED == false) {
            switch (ENCODER_B_LAYER) {
                case HSCROLL:
                    ENCODER_B_LAYER = HARROW;
                    break;
                case HARROW:
                    ENCODER_B_LAYER = BRIGHTNESS;
                    break;
                case BRIGHTNESS:
                    ENCODER_B_LAYER = FLUX_BRIGHTNESS;
                    break;
                case FLUX_BRIGHTNESS:
                    ENCODER_B_LAYER = HSCROLL;
                    break;
            }
            ENCODER_B_PRESSED = true;
        }
    } else {
        ENCODER_B_PRESSED = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EIGO:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_RSHIFT));
                tap_code(KC_1);
                current_layer = _ENGLISH;
                set_single_persistent_default_layer(_ENGLISH);
            } else {
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_RSHIFT));
            }
            break;
        case NIHONGO:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_RSHIFT));
                tap_code(KC_2);
                current_layer = _JAPANESE;
                set_single_persistent_default_layer(_JAPANESE);
            } else {
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_RSHIFT));
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // First encoder
        if (clockwise) {
            switch(ENCODER_A_LAYER) {
                case VSCROLL:
                    tap_code(KC_WH_D);
                    break;
                case VARROW:
                    tap_code(KC_DOWN);
                    break;
                case VOLUME:
                    tap_code(KC_VOLD);
                    break;
                case ZOOM:
                    if (current_layer == _ENGLISH) {
                        tap_code16(LCTL(KC_EQUAL));
                    } else {
                        tap_code16(LCTL(JP_SCLN));
                    }
                    break;
            }
        } else {
            switch (ENCODER_A_LAYER) {
                case VSCROLL:
                    tap_code(KC_WH_U);
                    break;
                case VARROW:
                    tap_code(KC_UP);
                    break;
                case VOLUME:
                    tap_code(KC_VOLU);
                    break;
                case ZOOM:
                    tap_code16(LCTL(KC_MINUS));
                    break;
            }
        }
    } else if (index == 1) { // Second encoder
        if (clockwise) {
            switch (ENCODER_B_LAYER) {
                case HSCROLL:
                    tap_code(KC_WH_R);
                    break;
                case HARROW:
                    tap_code16(LCTL(KC_RIGHT));
                    break;
                case BRIGHTNESS:
                    tap_code(KC_BRIGHTNESS_UP);
                    break;
                case FLUX_BRIGHTNESS:
                    tap_code16(LALT(KC_PGUP));
                    break;
            }
        } else {
            switch (ENCODER_B_LAYER) {
                case HSCROLL:
                    tap_code(KC_WH_L);
                    break;
                case HARROW:
                    tap_code16(LCTL(KC_LEFT));
                    break;
                case BRIGHTNESS:
                    tap_code(KC_BRIGHTNESS_DOWN);
                    break;
                case FLUX_BRIGHTNESS:
                    tap_code16(LALT(KC_PGDN));
                    break;
            }
        }
    }
}
