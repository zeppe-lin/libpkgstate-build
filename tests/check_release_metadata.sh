# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
root=$1
fail(){ echo "release-metadata: $*" >&2; exit 1; }
grep -F "version: '3.0.0'" "$root/meson.build" >/dev/null || fail 'version is not 3.0.0'
grep -F "soversion: '1'" "$root/src/meson.build" >/dev/null || fail 'SONAME generation is wrong'
grep -F 'PROJECT_NUMBER         = 3.0.0' "$root/Doxyfile" >/dev/null || fail 'Doxygen version is wrong'
grep -F '## 3.0.0' "$root/HISTORY.md" >/dev/null || fail 'history omits release'
grep -F "'libpkgstate'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgstate'
grep -F "version: '>=3.0.0'" "$root/meson.build" >/dev/null || fail 'missing floor libpkgstate >=3.0.0'
grep -F "'libpkgbuild'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgbuild'
grep -F "version: '>=2.0.0'" "$root/meson.build" >/dev/null || fail 'missing floor libpkgbuild >=2.0.0'
grep -F "'libpkgimage'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgimage'
grep -F "version: '>=0.4.0'" "$root/meson.build" >/dev/null || fail 'missing floor libpkgimage >=0.4.0'
grep -F "'libpkgstate-source'" "$root/meson.build" >/dev/null || fail 'missing dependency libpkgstate-source'
grep -F "version: '>=3.0.0'" "$root/meson.build" >/dev/null || fail 'missing floor libpkgstate-source >=3.0.0'
grep -F "soversion: '1'" "$root/src/meson.build" >/dev/null || fail 'SONAME generation changed'
test -s "$root/abi/libpkgstate-build.exports" || fail 'ABI manifest is absent'
