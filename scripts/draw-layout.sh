#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"
KEYMAP_DIR="$ROOT_DIR/3WNoB"
OUT_DIR="$ROOT_DIR/.build"

mkdir -p "$OUT_DIR"

# Check dependencies
if ! command -v keymap &>/dev/null; then
    echo "keymap-drawer not found. Install with: pipx install keymap-drawer"
    exit 1
fi

# Convert keymap.c to JSON via QMK
echo "Converting keymap.c → JSON..."
qmk c2json --no-cpp -km 3WNoB -kb zsa/voyager "$KEYMAP_DIR/keymap.c" -o "$OUT_DIR/keymap.json" 2>/dev/null

# Fix layout name (QMK exports LAYOUT_voyager, drawer expects LAYOUT)
sed -i '' 's/LAYOUT_voyager/LAYOUT/g' "$OUT_DIR/keymap.json"

# Parse JSON to YAML, then draw SVG
echo "Generating SVG..."
keymap parse -c 10 -q "$OUT_DIR/keymap.json" | keymap draw - > "$OUT_DIR/keymap.svg"

echo "Opening $OUT_DIR/keymap.svg"
open "$OUT_DIR/keymap.svg"
