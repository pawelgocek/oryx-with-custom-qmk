# QMK Tap-Hold Settings — Personal Notes

## The core problem

Every dual-function key (tap = one thing, hold = another) requires QMK to decide:
"was that a tap or a hold?" It can only know for sure once time passes or other events happen.

---

## Tapping Term

The fundamental timer. If you hold a key longer than this (~200ms default), it's a **hold**. Shorter = **tap**. Everything else below is about what happens *during* that wait.

---

## The three "don't wait for tapping term" shortcuts

### HOLD_ON_OTHER_KEY_PRESS
> "If another key is pressed *down* while I'm held → immediately treat me as hold, don't wait."

- Good for thumb layer keys where you consciously press layer first, then roll into a key
- Risk: any accidental overlap during fast typing fires the hold instantly
- **Configured per-key** in `get_hold_on_other_key_press()`

### PERMISSIVE_HOLD
> "If another key is pressed *and fully released* while I'm held → treat me as hold."

- Slightly safer than HOLD_ON_OTHER_KEY_PRESS (requires the other key to complete its cycle)
- **Does not apply to `LT()` keys** — only `MT()` (mod-tap). QMK limitation.
- Currently enabled globally in `config.h`

### CHORDAL_HOLD
> "Same hand? Treat as tap. Opposite hand? Use the normal rules."

- Logic: same-hand fast presses = you're typing a sequence, not a chord
- Opposite hands = you're likely intentionally combining (modifier + key)
- Can be overridden per-key in `get_chordal_hold()` by returning `true` (always allow hold)

---

## How they interact in this keymap

| Key | HOLD_ON_OTHER | CHORDAL | PERMISSIVE | Notes |
|-----|--------------|---------|------------|-------|
| `MT(MOD_LSFT, KC_A)` etc | false (default) | default (same-hand=tap) | yes (MT only) | home row mods safe from same-hand rolls |
| `LT(1, KC_ESCAPE)` | **true** | overridden to true | N/A (LT) | rolls ESC→key fire layer 1 instantly |
| `LT(1, KC_SPACE)` | false | overridden to true | N/A (LT) | needs full tapping term hold |
| `LT(3, KC_BSPC)` | false (was true, caused layer lock bug) | overridden to true | N/A (LT) | now time-based only |
| `MT(MOD_LGUI, KC_ENTER)` | **true** | overridden to true | yes | GUI fires on any overlap |
| `MT(MOD_RSFT, KC_SCLN)` | **true** | default | yes | right shift fires on overlap |

---

## Goals mapped to settings

**Home row mods not misfiring while typing fast:**
- CHORDAL_HOLD is the main guard — same-hand typing rolls don't trigger mods
- PERMISSIVE_HOLD applies but only fires on a complete roll-and-release over the mod key

**Layer 1 (symbols/numbers) firing quickly on ESC→key roll:**
- `HOLD_ON_OTHER_KEY_PRESS = true` for `LT(1, KC_ESCAPE)` — layer fires the moment any key is pressed after ESC
- CHORDAL_HOLD overridden to `true` so same-hand rolls also work

**Layer 3 (nav/fn) not accidentally locking:**
- Removed from `HOLD_ON_OTHER_KEY_PRESS` — layer 3 now requires holding BSPC alone for full tapping term
- Root cause of lock bug: holding LT(1) for layer 1 counted as "another key pressed" and instantly triggered layer 3

---

## Key rule of thumb

```
MT() keys  → PERMISSIVE_HOLD + CHORDAL_HOLD protect them
LT() keys  → only HOLD_ON_OTHER_KEY_PRESS and CHORDAL_HOLD matter (PERMISSIVE_HOLD ignored)
```
