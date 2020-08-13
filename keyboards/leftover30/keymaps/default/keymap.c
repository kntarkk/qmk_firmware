/* Copyright 2020 marksard
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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  LOWER,
  RAISE,
  KANJI,
  RE_PUSH,
};

// #define KC_ESAD  LT(_ADJUST, KC_ESC)
// #define KC_BSLO  LT(_LOWER, KC_BSPC)
#define KC_LOWR  MO(_LOWER)
#define KC_SPRA  LT(_RAISE, KC_SPC)
#define KC_AJST  MO(_ADJUST)

#define KC_Q_AL  LALT_T(KC_Q)
#define KC_A_CT  LCTL_T(KC_A)
#define KC_Z_SF  LSFT_T(KC_Z)
#define KC_X_AL  LALT_T(KC_X)
#define KC_ENCT  RCTL_T(KC_ENT)
#define KC_SLSF  RSFT_T(KC_SLSH)

#define KC_F1AL  LALT_T(KC_F1)
#define KC_F6CT  LCTL_T(KC_F6)
#define KC_11SF  LSFT_T(KC_F11)
#define KC_12AL  LALT_T(KC_F12)
#define KC_QUSF  RCTL_T(KC_QUOT)
#define KC_ROSF  RSFT_T(KC_RO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
               KC_Q_AL,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_A_CT,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_ENCT,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_Z_SF, KC_X_AL,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,     KC_SLSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      RE_PUSH, KC_LGUI,                                KC_SPRA,                                 KC_LOWR, KC_RCTL
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
               KC_F1AL,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_MINS,  KC_EQL, KC_JYEN, KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_F6CT,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN,     KC_QUSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_11SF, KC_12AL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_GRV,     KC_ROSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,                                KC_AJST,                                 _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,     _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               KC_LSFT, XXXXXXX,  KC_ESC,  KC_TAB,   KANJI,  KC_DEL, KC_COMM,  KC_DOT, KC_BSLS,     KC_ROSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,                                _______,                                 KC_AJST, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
                 RESET,  RGBRST, AG_NORM, AG_SWAP, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,     KC_NLCK,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
               RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX,     KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,                                _______,                                 _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  )
};

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case KC_SPRA:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      break;
#ifdef RGBLIGHT_ENABLE
    //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
        if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
        rgblight_step();
        RGB_current_mode = rgblight_config.mode;
        }
    break;
    case RGBRST:
        if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        RGB_current_mode = rgblight_config.mode;
        }
    break;
#endif
    default:
      result = true;
      break;
  }

  return result;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_ADJUST)) {
          if (clockwise) {
              rgblight_increase_hue_noeeprom();
          }
          else
          {
              rgblight_decrease_hue_noeeprom();
          }
        }
        else if (IS_LAYER_ON(_LOWER)) {
          if (clockwise) {
            SEND_STRING(SS_LCTL("y"));
          } else {
            SEND_STRING(SS_LCTL("z"));
          }
        }
        else if (IS_LAYER_ON(_RAISE)) {
          if (clockwise) {
            SEND_STRING(SS_DOWN(X_LSFT)SS_TAP(X_DOWN)SS_UP(X_LSFT));
          } else {
            SEND_STRING(SS_DOWN(X_LSFT)SS_TAP(X_UP)SS_UP(X_LSFT));
          }
        }
        else {
          tap_code((clockwise == true) ? KC_WH_D : KC_WH_U);
        }

    }
}

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}

// for exsample customize of LED inducator
// bool led_set_keymap(uint8_t usb_led) {

//     if (IS_LAYER_ON(_LOWER)) {
//         writePinHigh(D2);
//     }
//     else {
//        writePinLow(D2);
//     }

//     if (IS_LAYER_ON(_RAISE)) {
//         writePinHigh(D1);
//     }
//     else {
//         writePinLow(D1);
//     }

//     return true;
// }
