/*
This is the c configuration file for the keymap

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

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 110

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLED_NUM 27
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#define LANG_CHANGE_DEFAULT LANG_CHANGE_ALT_SHIFT

#ifndef NO_DEBUG
	#define NO_DEBUG
	#endif // !NO_DEBUG
	#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
	#define NO_PRINT
#endif // !NO_PRINT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
