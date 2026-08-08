#!/bin/sh
# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
root=$1
fail(){ echo "ci-contract: $*" >&2; exit 1; }
workflow=$root/.github/workflows/ci.yml
[ -s "$workflow" ] || fail 'workflow is absent'
for script in ci/configure-and-test.sh ci/build-dependencies.sh ci/qualify-installed.sh ci/audit-shared-boundary.sh; do
  [ -x "$root/$script" ] || fail "missing executable $script"
  sh -n "$root/$script" || fail "invalid shell: $script"
done
for token in 'GCC shared' 'GCC static' 'Clang shared' 'Clang static' 'GCC release' 'address,undefined' 'meson==1.10.2' '--wrap-mode=nofallback'; do
  grep -F -- "$token" "$workflow" "$root/ci/configure-and-test.sh" "$root/ci/build-dependencies.sh" >/dev/null || fail "missing $token"
done
for pin in   'zeppe-lin/libpkgcatalog|v3.0.0'   'zeppe-lin/libpkgsource|v3.0.0'   'zeppe-lin/libpkgimage|v0.4.0'   'zeppe-lin/libpkgstate|v3.0.0'   'zeppe-lin/libpkgresolve|v2.0.0'   'zeppe-lin/libpkgbuild|v3.0.0'   'zeppe-lin/libpkgbuild-image|v1.0.0'   'zeppe-lin/libpkgstate-source|v3.0.0'; do
  repository=${pin%|*}
  ref=${pin#*|}
  grep -F "repository: $repository" "$workflow" >/dev/null || fail "missing dependency pin: $repository"
  awk -v repo="$repository" -v ref="$ref" '
    $0 ~ "repository: " repo { seen = 1; next }
    seen && $0 ~ "ref: " ref { found = 1; exit }
    seen && /repository:/ { exit }
    END { exit found ? 0 : 1 }
  ' "$workflow" || fail "wrong dependency ref: $repository $ref"
done

grep -F 'html: enabled' "$workflow" >/dev/null || fail 'GCC shared HTML build is absent'
grep -F 'pandoc' "$workflow" >/dev/null || fail 'Pandoc qualification dependency is absent'
grep -F -- '-Dhtml_docs=' "$workflow" >/dev/null || fail 'HTML Meson feature is not configured'
grep -F 'qualify-html-docs.sh' "$workflow" >/dev/null || fail 'installed HTML qualification is absent'
