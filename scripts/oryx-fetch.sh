#!/usr/bin/env bash
set -euo pipefail

LAYOUT_ID="3WNoB"
LAYOUT_GEOMETRY="voyager"
ORYX_API="https://oryx.zsa.io/graphql"

echo "Fetching latest layout from Oryx..."

response=$(curl -s "$ORYX_API" \
    -H 'Content-Type: application/json' \
    -d '{"query":"query getLayout($hashId: String!, $revisionId: String!, $geometry: String) {layout(hashId: $hashId, geometry: $geometry, revisionId: $revisionId) { revision { hashId, qmkVersion, title }}}","variables":{"hashId":"'"$LAYOUT_ID"'","geometry":"'"$LAYOUT_GEOMETRY"'","revisionId":"latest"}}' \
    | jq '.data.layout.revision | [.hashId, .qmkVersion, .title]')

hash_id=$(echo "$response" | jq -r '.[0]')
description=$(echo "$response" | jq -r '.[2] // "latest layout modification"')
echo "Revision: $hash_id — $description"

curl -sL "https://oryx.zsa.io/source/$hash_id" -o /tmp/oryx-source.zip

# Stash any uncommitted work
git stash --include-untracked -q 2>/dev/null || true

current_branch=$(git branch --show-current)

# Switch to oryx branch (create if needed)
git checkout oryx 2>/dev/null || git checkout -b oryx

# Replace layout files with Oryx source
rm -f "$LAYOUT_ID"/*.c "$LAYOUT_ID"/*.h "$LAYOUT_ID"/*.json "$LAYOUT_ID"/*.mk
unzip -oj /tmp/oryx-source.zip '*_source/*' -d "$LAYOUT_ID"
rm /tmp/oryx-source.zip

# Commit if changed
git add "$LAYOUT_ID"
git commit -m "oryx: $description" || echo "No layout change"

# Return to original branch
git checkout "$current_branch"
git stash pop -q 2>/dev/null || true

echo "Done. Oryx branch updated. Run 'make oryx-merge' to merge."
