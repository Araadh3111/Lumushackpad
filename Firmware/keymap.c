#include QMK_KEYBOARD_H
#include <stdio.h>

// Custom keycodes for app-launcher macros and the OLED mode switch
enum custom_keycodes {
    OPEN_VSCODE = SAFE_RANGE,
    OPEN_BRAVE_YT,
    LEAVE_CALL,
    ANIM_CYCLE
};

// Physical order matches the direct-pin matrix in keyboard.json:
// SW1..SW5 are the keys, SW6 is the rotary encoder's push button.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LCTL(KC_T),       // SW1: New Tab (Ctrl + T)
        ANIM_CYCLE,       // SW2: Cycle OLED animation mode
        OPEN_VSCODE,      // SW3: Launch VS Code
        OPEN_BRAVE_YT,    // SW4: Open YouTube in Brave
        LEAVE_CALL,       // SW5: Leave call (Zoom / Teams / Discord)
        KC_MUTE           // SW6: Encoder push = mute audio
    )
};

// ---------------------------------------------------------------------------
// Shared state for the OLED status line
// ---------------------------------------------------------------------------
static uint8_t anim_mode = 0;
static char    last_action[12] = "READY";

static void set_action(const char *name) {
    snprintf(last_action, sizeof(last_action), "%s", name);
}

// ---------------------------------------------------------------------------
// Macros: launch apps through the Windows Run dialog (Win+R)
// ---------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case ANIM_CYCLE:
            anim_mode = (anim_mode + 1) % 3;
            return false;

        case OPEN_VSCODE:
            SEND_STRING(SS_LGUI("r") SS_DELAY(150) "code" SS_TAP(X_ENTER));
            set_action("VSCODE");
            return false;

        case OPEN_BRAVE_YT:
            SEND_STRING(SS_LGUI("r") SS_DELAY(150) "brave youtube.com" SS_TAP(X_ENTER));
            set_action("YOUTUBE");
            return false;

        case LEAVE_CALL:
            // Zoom end-call first, then a Ctrl+Shift+H backup for Teams/Discord
            SEND_STRING(SS_LALT("h") SS_DELAY(50) SS_LCTL(SS_LSFT("h")));
            set_action("END CALL");
            return false;

        case LCTL(KC_T):
            set_action("NEW TAB");
            return true;

        case KC_MUTE:
            set_action("MUTE");
            return true;
    }
    return true;
}

// ---------------------------------------------------------------------------
// Rotary encoder: volume control
// ---------------------------------------------------------------------------
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
        set_action("VOL +");
    } else {
        tap_code(KC_VOLD);
        set_action("VOL -");
    }
    return false;
}
#endif

// ---------------------------------------------------------------------------
// OLED: three animated modes on the 128x32 screen (4 rows x 21 columns)
// ---------------------------------------------------------------------------
#ifdef OLED_ENABLE

#define ANIM_FRAME_MS 80

static uint8_t  frame       = 0;
static uint32_t frame_timer = 0;

// Small deterministic noise generator so the equalizer bars dance
static uint8_t noise8(uint8_t x, uint8_t t) {
    uint8_t n = (uint8_t)(x * 37 + t * 13 + 7);
    n ^= n << 3;
    n ^= n >> 2;
    return n;
}

// Mode 0: bouncing scanner beam, cyberpunk style
static void render_cyberpunk(void) {
    char bar[22];

    oled_write_ln("MODE: CYBERPUNK", false);

    uint8_t pos = frame % 36;            // bounce across 19 cells
    if (pos > 18) pos = 36 - pos;
    bar[0] = '[';
    for (uint8_t i = 0; i < 19; i++) {
        if (i == pos)                          bar[i + 1] = '#';
        else if (i + 1 == pos || i == pos + 1) bar[i + 1] = '=';
        else                                   bar[i + 1] = '-';
    }
    bar[20] = ']';
    bar[21] = '\0';
    oled_write_ln(bar, false);

    oled_write_ln((frame & 4) ? "SYS :: ONLINE_" : "SYS :: ONLINE ", false);
    oled_write("> ", false);
    oled_write_ln(last_action, false);
}

// Mode 1: 21-column equalizer made of stacked rows
static void render_equalizer(void) {
    char rows[3][22];

    oled_write_ln("MODE: EQUALIZER", false);

    for (uint8_t col = 0; col < 21; col++) {
        uint8_t h = noise8(col, frame) % 4;  // bar height 0..3
        rows[0][col] = (h > 2) ? '|' : ' ';
        rows[1][col] = (h > 1) ? '|' : ' ';
        rows[2][col] = (h > 0) ? '|' : '.';
    }
    for (uint8_t r = 0; r < 3; r++) {
        rows[r][21] = '\0';
        oled_write_ln(rows[r], false);
    }
}

// Mode 2: minimal breathing logo
static void render_stealth(void) {
    static const char *pulse[4] = {
        "    -  LUMUS PAD  -",
        "   --  LUMUS PAD  --",
        "  ---  LUMUS PAD  --",
        "   --  LUMUS PAD  --"
    };

    oled_write_ln("MODE: STEALTH", false);
    oled_write_ln("", false);
    oled_write_ln(pulse[(frame >> 2) & 3], false);
    oled_write("> ", false);
    oled_write_ln(last_action, false);
}

bool oled_task_user(void) {
    if (timer_elapsed32(frame_timer) > ANIM_FRAME_MS) {
        frame_timer = timer_read32();
        frame++;
    }

    oled_set_cursor(0, 0);
    switch (anim_mode) {
        case 0:  render_cyberpunk(); break;
        case 1:  render_equalizer(); break;
        default: render_stealth();   break;
    }
    return false;
}
#endif
