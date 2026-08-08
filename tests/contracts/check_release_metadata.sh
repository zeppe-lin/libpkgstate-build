#!/bin/sh
# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
root=$1
fail(){ echo "release-metadata: $*" >&2; exit 1; }
grep -F "version: '3.0.0'" "$root/meson.build" >/dev/null || fail 'version is not 3.0.0'
grep -F "soversion: '1'" "$root/src/meson.build" >/dev/null || fail 'SONAME generation is wrong'
grep -F 'PROJECT_NUMBER         = 3.0.0' "$root/Doxyfile" >/dev/null || fail 'Doxygen version is wrong'
grep -F '## 3.0.0' "$root/HISTORY.md" >/dev/null || fail 'history omits release'
grep -F "version: ['>=3.0.0', '<4.0.0']" "$root/meson.build" >/dev/null || fail 'libpkgstate ABI interval is wrong'
grep -F "version: ['>=1.0.0', '<2.0.0']" "$root/meson.build" >/dev/null || fail 'libpkgbuild-image ABI interval is wrong'
test "$(grep -F -c "version: ['>=3.0.0', '<4.0.0']" "$root/meson.build")" -eq 2 || fail 'state/state-source ABI intervals are incomplete'
grep -F "'libpkgstate'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgstate'
grep -F "'libpkgbuild-image'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgbuild-image'
grep -F "'libpkgstate-source'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgstate-source'
test -s "$root/abi/libpkgstate-build.exports" || fail 'ABI manifest is absent'
