/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

you should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdint.h>

#define CUSTOM_SAFE_RANGE SAFE_RANGE
#include "lang_shift/include.h"

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_CUR 5
#define L_SYM 6
#define L_ADJUST 8

// English layer
//
// Left-hand home row mods
#define H_O LALT_T(KC_O)
#define H_H LGUI_T(KC_H)
#define H_E LCTL_T(KC_E)
#define H_A LSFT_T(KC_A)

// Right-hand home row mods
#define H_R RSFT_T(KC_R)
#define H_T RCTL_T(KC_T)
#define H_N RGUI_T(KC_N)
#define H_S LALT_T(KC_S)

// Symbol layer
//
// Left-hand home row mods
#define H_SLSH TD(ALT_SL)
#define H_MINS TD(GUI_MN)
#define H_LCBR TD(CTL_LB)
#define H_RCBR TD(SFT_RB)

// Right-hand home row mods
#define H_LPRN TD(SFT_LP)
#define H_RPRN TD(CTL_RP)
#define H_QUOT TD(GUI_QT)
#define H_COLN TD(ALT_CL)

// Cursor layer
//
// Left-hand home row mods
#define H_HOME LALT_T(KC_HOME)
#define H_LEFT LGUI_T(KC_LEFT)
#define H_DOWN LCTL_T(KC_DOWN)
#define H_RIGHT LSFT_T(KC_RIGHT)

// Right-hand home row mods
#define H_4 RSFT_T(KC_4)
#define H_5 RCTL_T(KC_5)
#define H_6 RGUI_T(KC_6)
#define H_NO LALT_T(KC_NO)

// Mod key
#define CUR_SPC LT(L_CUR, KC_SPC)
#define SYM_ENT LT(L_SYM, KC_ENT)

enum custom_keycodes {
    KEYCODES_START = CUSTOM_SAFE_RANGE,

    CTL_PGU,
    CTL_PGD,
    SFT_INS,
    SFT_F10,
};

// Tap Dance keycodes
enum td_keycodes {
    ALT_SL,
    GUI_MN,
    CTL_LB,
    SFT_RB,

    SFT_LP,
    CTL_RP,
    GUI_QT,
    ALT_CL,
};

// Define a type containing as many tap-dance states as you need
typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_SINGLE_TAP } td_state_t;

// Create a global instance of the tap-dance state type
static td_state_t td_state;

// Declare your tap-dance functions:

// Function to determine the current tap-dance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tap-dance keycode
void altsl_finished(qk_tap_dance_state_t *state, void *user_data);
void altsl_reset(qk_tap_dance_state_t *state, void *user_data);
void guimn_finished(qk_tap_dance_state_t *state, void *user_data);
void guimn_reset(qk_tap_dance_state_t *state, void *user_data);
void ctllb_finished(qk_tap_dance_state_t *state, void *user_data);
void ctllb_reset(qk_tap_dance_state_t *state, void *user_data);
void sftrb_finished(qk_tap_dance_state_t *state, void *user_data);
void sftrb_reset(qk_tap_dance_state_t *state, void *user_data);

void sftlp_finished(qk_tap_dance_state_t *state, void *user_data);
void sftlp_reset(qk_tap_dance_state_t *state, void *user_data);
void ctlrp_finished(qk_tap_dance_state_t *state, void *user_data);
void ctlrp_reset(qk_tap_dance_state_t *state, void *user_data);
void guiqt_finished(qk_tap_dance_state_t *state, void *user_data);
void guiqt_reset(qk_tap_dance_state_t *state, void *user_data);
void altcl_finished(qk_tap_dance_state_t *state, void *user_data);
void altcl_reset(qk_tap_dance_state_t *state, void *user_data);

//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_F,    KC_U,    KC_Y,    KC_Z,                         KC_X,    KC_K,    KC_C,    KC_W,    KC_B, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,     H_O,     H_H,     H_E,     H_A,    KC_I,                         KC_D,     H_R,     H_T,     H_N,     H_S, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, AG_COMM,    KC_M,  AG_DOT,    KC_J, AG_SCLN,                         KC_G,    KC_L,    KC_P,    KC_V, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SFT_F10, KC_CAPS, SYM_ENT,  CUR_SPC,   KC_PSCR,  XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   RU_TS,   RU_SF,   RU_JA,    RU_Z,    RU_V,                         RU_K,    RU_D,   RU_CH,   RU_SH,   RU_SC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    RU_U,    RU_I,   RU_JE,    RU_O,    RU_A,                         RU_L,    RU_N,    RU_T,    RU_S,    RU_R,    RU_J,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
<<<<<<< HEAD
      AG_COMM,    RU_F,    RU_E,    RU_H,    RU_Y,   RU_JU,                         RU_B,    RU_M,    RU_P,    RU_G,   RU_ZH,  AG_DOT,
=======
      AG_CMSP,    RU_F,    RU_E,    RU_H,    RU_Y,   RU_JU,                         RU_B,    RU_M,    RU_P,    RU_G,   RU_ZH, AG_SDOT,
>>>>>>> c9a005c2e707404a750eb74d49796a84225204ad
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, KC_CAPS, SYM_ENT,  CUR_SPC,   KC_LSFT,  XXXXXXX
                                      //`--------------------------'  `-------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,  RU_S_TS, RU_S_SF,  RU_S_JA,  RU_S_Z, RU_S_V,                       RU_S_K,  RU_S_D, RU_S_CH, RU_S_SH,  RU_S_SC,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  RU_S_U,  RU_S_I, RU_S_JE,  RU_S_O,  RU_S_A,                       RU_S_L,  RU_S_N,  RU_S_T,  RU_S_S,  RU_S_R,  RU_S_J,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  RU_S_F,  RU_S_E,  RU_S_H,  RU_S_Y, RU_S_JU,                       RU_S_B,  RU_S_M,  RU_S_P,  RU_S_G, RU_S_ZH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, SYM_ENT,  CUR_SPC,   XXXXXXX,  XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [L_CUR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL, KC_PGDN,                      LA_CHNG,    AG_1,    AG_2,    AG_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  H_HOME,  H_LEFT,  H_DOWN, H_RIGHT,  KC_END,                         AG_0,     H_4,     H_5,     H_6,    H_NO, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CTL_PGU, CTL_PGD, XXXXXXX,                      LA_SYNC,    AG_7,    AG_8,    AG_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, KC_ESC, SYM_ENT,  XXXXXXX,   XXXXXXX,    XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [L_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, AG_DQUO, AG_UNDS, EN_LBRC, EN_RBRC, EN_CIRC,                      AG_EXCL,   EN_LT,   EN_GT,  AG_EQL, EN_AMPR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, H_SLSH,  H_MINS,  H_LCBR,  H_RCBR,  AG_ASTR,                      AG_QUES,   H_LPRN, H_RPRN,  H_QUOT,  H_COLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, EN_HASH,  EN_DLR, EN_PIPE, EN_TILD,  EN_GRV,                      AG_PLUS, AG_PERC, AG_BSLS,   EN_AT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,  CUR_SPC,   SFT_INS, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};
// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    }

    if (state->count == 2)
        return TD_DOUBLE_SINGLE_TAP;
    else
        return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void sftlp_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_LPRN);
            register_code16(KC_LPRN);
            break;
        default:
            break;
    }
}

void sftlp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        default:
            break;
    }
}

void ctlrp_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_RPRN);
            register_code16(KC_RPRN);
            break;
        default:
            break;
    }
}

void ctlrp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        default:
            break;
    }
}

void guiqt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RGUI)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_QUOT);
            register_code16(KC_QUOT);
            break;
        default:
            break;
    }
}

void guiqt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RGUI)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_QUOT);
            break;
        default:
            break;
    }
}

void altcl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
//            register_code16(KC_COLN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
//            tap_code16(KC_COLN);
//            register_code16(KC_COLN);
            break;
        default:
            break;
    }
}

void altcl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_COLN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_COLN);
            break;
        default:
            break;
    }
}

void sftrb_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_RCBR);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_RCBR);
            register_code16(KC_RCBR);
            break;
        default:
            break;
    }
}

void sftrb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_RCBR);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_RCBR);
            break;
        default:
            break;
    }
}

void ctllb_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LCBR);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_LCBR);
            register_code16(KC_LCBR);
            break;
        default:
            break;
    }
}

void ctllb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        default:
            break;
    }
}

void guimn_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_MINS);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_MINS);
            register_code16(KC_MINS);
            break;
        default:
            break;
    }
}

void guimn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_MINS);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_MINS);
            break;
        default:
            break;
    }
}

void altsl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_SLSH);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_SLSH);
            register_code16(KC_SLSH);
            break;
        default:
            break;
    }
}

void altsl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SLSH);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SLSH);
            break;
        default:
            break;
    }
}
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {[ALT_SL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altsl_finished, altsl_reset), [GUI_MN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guimn_finished, guimn_reset), [CTL_LB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctllb_finished, ctllb_reset), [SFT_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftrb_finished, sftrb_reset), [SFT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftlp_finished, sftlp_reset), [CTL_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlrp_finished, ctlrp_reset), [GUI_QT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guiqt_finished, guiqt_reset), [ALT_CL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altcl_finished, altcl_reset)};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("English"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Shift EN"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Russian"), false);
            break;
        case L_SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case L_CUR:
            oled_write_ln_P(PSTR("Cursor"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!lang_shift_process_record(keycode, record)) return false;
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }

    switch (keycode) {
        case CTL_PGU:
            if (record->event.pressed) {
                register_code(KC_LCTRL);
                register_code(KC_PGUP);
                unregister_code(KC_LCTRL);
                unregister_code(KC_PGUP);
            }
            return false;
        case CTL_PGD:
            if (record->event.pressed) {
                register_code(KC_LCTRL);
                register_code(KC_PGDN);
                unregister_code(KC_LCTRL);
                unregister_code(KC_PGDN);
            }
            return false;
        case SFT_INS:
            if (record->event.pressed) {
                register_code(KC_LSHIFT);
                register_code(KC_INS);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_INS);
            }
            return false;
        case SFT_F10:
            if (record->event.pressed) {
                register_code(KC_LSHIFT);
                register_code(KC_F10);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_F10);
            }
            return false;
    }
    return true;
}

void user_timer(void) {
    lang_shift_user_timer();
}

void matrix_scan_user(void) {
    user_timer();
}
