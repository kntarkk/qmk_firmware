/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEE2
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0100
#define MANUFACTURER    marksard
#define PRODUCT         angelina
#define DESCRIPTION     Irregular Row-Staggerd 48 Keys Keyboard

#define PREVENT_STUCK_MODIFIERS
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 150

/* Use I2C or Serial */
#define USE_I2C
#define USE_SERIAL
//#define USE_MATRIX_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// OLED support
//      see ./rules.mk: OLED_ENABLE=yes or no
#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 16
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }

// wiring of each half
#define MATRIX_COLS 6
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_TIMER
//#define RGBLED_NUM 12    // Number of LEDs. see ./keymaps/default/config.h
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD

// angelina keyboard RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLED_BACK
  #define RGBLED_NUM 12
#else
  #define RGBLED_NUM 12
#endif

#ifndef IOS_DEVICE_ENABLE
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #define RGBLIGHT_LIMIT_VAL 200
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #define RGBLIGHT_LIMIT_VAL 45
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for angelina keyboard
//  120  RGBoff, OLEDoff
//  120  OLED
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION


#endif
