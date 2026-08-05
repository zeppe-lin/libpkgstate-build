#!/bin/sh
# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
build=$1
pc=$build/meson-private/libpkgstate-build.pc
[ -s "$pc" ] || { echo "pkgconfig-metadata: missing $pc" >&2; exit 1; }
grep -F 'Version: 3.0.0' "$pc" >/dev/null
grep -F -- '-lpkgstate-build' "$pc" >/dev/null
public=$(sed -n 's/^Requires:[[:space:]]*//p' "$pc")
private=$(sed -n 's/^Requires.private:[[:space:]]*//p' "$pc")
has_requirement() {
  printf '%s
' "$1" | tr ',' '
' | awk     -v package="$2" -v operator="$3" -v version="$4" '
      $1 == package && $2 == operator && $3 == version { found = 1 }
      END { exit found ? 0 : 1 }
    '
}
for spec in   'libpkgstate >= 3.0.0' 'libpkgstate < 4.0.0'   'libpkgbuild-image >= 1.0.0' 'libpkgbuild-image < 2.0.0'; do
  set -- $spec
  has_requirement "$public" "$1" "$2" "$3" || { echo "pkgconfig-metadata: missing public $spec" >&2; exit 1; }
done
for package in libpkgstate-source libpkgbuild libpkgimage; do
  if printf '%s
' "$public" | grep -F "$package" >/dev/null; then echo "pkgconfig-metadata: private/transitive edge leaked publicly: $package" >&2; exit 1; fi
done
for spec in 'libpkgstate-source >= 3.0.0' 'libpkgstate-source < 4.0.0'; do
  set -- $spec
  has_requirement "$private" "$1" "$2" "$3" || { echo "pkgconfig-metadata: missing private $spec" >&2; exit 1; }
done
