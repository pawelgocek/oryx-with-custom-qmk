# Project: ZSA Voyager Custom QMK Firmware

## What this is

Custom QMK firmware config for a ZSA Voyager split keyboard, synchronized with Oryx layout definitions. The Oryx web configurator generates the base layout, and custom QMK C code is layered on top for features Oryx doesn't support.

## Directory structure

- `3WNoB/` — the keyboard layout (Oryx layout ID)
  - `keymap.c` — keymaps, RGB, tap-hold callbacks, custom key handlers
  - `config.h` — compile-time settings (tap-hold behavior, RGB timeout, etc.)
  - `keymap.json` — Oryx/ZSA module config
- `TAP_HOLD_NOTES.md` — reference doc explaining tap-hold settings and how they interact

## Workflow

1. Edit layout in Oryx → download → files land in `3WNoB/`
2. Add custom QMK code on top (caps word, RGB indicators, tap-hold tuning, etc.)
3. Compile and flash via ZSA toolchain

Oryx exports may overwrite parts of `keymap.c` and `config.h`. Custom code added outside Oryx-generated sections must be preserved across syncs.

## Key design decisions

- **Home row mods** (`MT()` on A/S/D/F and J/K/L/;) — protected by CHORDAL_HOLD + PERMISSIVE_HOLD
- **Layer 1** (symbols/numbers) — accessed via `LT(1, KC_ESCAPE)` with HOLD_ON_OTHER_KEY_PRESS for fast roll activation
- **Layer 3** (nav/fn/media) — accessed via `LT(3, KC_BSPC)`, time-based hold only (no HOLD_ON_OTHER_KEY_PRESS to prevent accidental layer lock)
- **CapsWord** — activated by holding `LT(0, KC_NO)` key (above Tab, leftmost QWERTY row); keyboard turns orange while active
- **DUAL_FUNC_0** (`LT(3, KC_F24)`) — tap = quote, hold = switch to layer 1; mapped to the quote key position on home row right

## Important: fragile tap-hold config

The tap-hold settings (PERMISSIVE_HOLD, CHORDAL_HOLD, HOLD_ON_OTHER_KEY_PRESS per key) are carefully tuned. Changes should be atomic and tested individually — one setting change can cascade into misfiring mods or accidental layer switches. See `TAP_HOLD_NOTES.md` for detailed explanation.
