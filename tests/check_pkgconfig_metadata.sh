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
private=$(sed -n 's/^Requires\.private:[[:space:]]*//p' "$pc")
has_requirement() {
  printf '%s\n' "$1" | tr ',' '\n' | awk \
    -v package="$2" -v version="$3" '
      $1 == package && $2 == ">=" && $3 == version { found = 1 }
      END { exit found ? 0 : 1 }
    '
}

has_requirement "$public" libpkgstate 3.0.0 || { echo 'pkgconfig-metadata: missing public libpkgstate >= 3.0.0' >&2; exit 1; }
has_requirement "$public" libpkgbuild 2.0.0 || { echo 'pkgconfig-metadata: missing public libpkgbuild >= 2.0.0' >&2; exit 1; }
has_requirement "$public" libpkgimage 0.4.0 || { echo 'pkgconfig-metadata: missing public libpkgimage >= 0.4.0' >&2; exit 1; }
if printf '%s\n' "$public" | grep -F 'libpkgstate-source' >/dev/null; then echo 'pkgconfig-metadata: private edge leaked publicly: libpkgstate-source' >&2; exit 1; fi
has_requirement "$private" libpkgstate-source 3.0.0 || { echo 'pkgconfig-metadata: missing private libpkgstate-source >= 3.0.0' >&2; exit 1; }
