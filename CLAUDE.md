# Project: ZSA Voyager Custom QMK Firmware

## What this is

Custom QMK firmware for a ZSA Voyager split keyboard. Optionally synchronized with Oryx layout definitions, but primarily maintained by editing `keymap.c` directly. Custom QMK C code handles features Oryx doesn't support (CapsWord, RGB indicators, tap-hold tuning).

## Directory structure

- `3WNoB/` — the keyboard layout (Oryx layout ID)
  - `keymap.c` — keymaps, RGB, tap-hold callbacks, custom key handlers
  - `config.h` — compile-time settings (tap-hold behavior, RGB timeout, etc.)
  - `keymap.json` — ZSA module config (`zsa/oryx` for live view, `zsa/defaults`)
- `scripts/` — build and sync scripts
  - `oryx-fetch.sh` — downloads latest layout from Oryx API → commits to `oryx` branch
  - `draw-layout.sh` — generates SVG layout diagram via keymap-drawer
- `Makefile` — all build commands (`make` for help)
- `TAP_HOLD_NOTES.md` — reference doc explaining tap-hold settings and how they interact

## Build setup

Requires:
- `qmk` CLI (`brew install qmk/qmk/qmk`)
- ZSA QMK firmware at `~/qmk_firmware` (`qmk setup zsa/qmk_firmware -b firmware25`)
- ARM toolchain (`brew install osx-cross/arm/arm-gcc-bin@14`), must be in PATH
- `keymap-drawer` for `make draw` (`pipx install keymap-drawer`)

The keymap is symlinked into `~/qmk_firmware/keyboards/zsa/voyager/keymaps/3WNoB/` (auto-created by `make build`).

## Workflow

### Local changes (primary workflow)
1. Edit `3WNoB/keymap.c` or `config.h`
2. `make build` — compile firmware
3. `make flash` — compile + flash (put keyboard in bootloader mode first via reset button)

### Syncing from Oryx (occasional)
1. Edit layout in Oryx web configurator
2. `make oryx-fetch` — downloads source, commits to `oryx` branch
3. `make oryx-merge` — merges into current branch (resolve conflicts if any)
4. `make build` — compile

Or `make oryx-build` to run all three in sequence.

### Visualizing layout
- `make draw` — generates and opens SVG layout diagram
- ASCII art comments above each layer in `keymap.c` (layers 0, 1, 3)

## Key design decisions

- **Home row mods** (`MT()` on A/S/D/F and J/K/L/;) — protected by CHORDAL_HOLD + PERMISSIVE_HOLD
- **Layer 1** (symbols/numbers) — accessed via `LT(1, KC_ESCAPE)` with HOLD_ON_OTHER_KEY_PRESS for fast roll activation
- **Layer 3** (nav/fn/media) — accessed via `LT(3, KC_BSPC)`, time-based hold only (no HOLD_ON_OTHER_KEY_PRESS to prevent accidental layer lock)
- **CapsWord** — activated by holding `LT(0, KC_NO)` key (above Tab, leftmost QWERTY row); keyboard turns orange while active
- **DUAL_FUNC_0** (`LT(3, KC_F24)`) — tap = quote, hold = switch to layer 1; mapped to the quote key position on home row right

## RGB / LED colors

- Per-key colors are defined in the `ledmap` array as HSV triples `{hue, saturation, value}`
- Only layer 3 has custom per-key colors; other layers use default RGB effect
- CapsWord overrides all LEDs to orange when active
- HSV hue reference: 0=red, 21=orange, 43=yellow, 85=green, 127=cyan, 170=blue, 201=purple
- `{0,0,0}` = LED off for that key

## Important: fragile tap-hold config

The tap-hold settings (PERMISSIVE_HOLD, CHORDAL_HOLD, HOLD_ON_OTHER_KEY_PRESS per key) are carefully tuned. Changes should be atomic and tested individually — one setting change can cascade into misfiring mods or accidental layer switches. See `TAP_HOLD_NOTES.md` for detailed explanation.
