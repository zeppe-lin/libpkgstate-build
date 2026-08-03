# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
build=$1
pc=$build/meson-private/libpkgstate-build.pc
[ -s "$pc" ] || { echo "missing $pc" >&2; exit 1; }
grep -F 'Version: 3.0.0' "$pc" >/dev/null
grep -F -- '-lpkgstate-build' "$pc" >/dev/null
grep -F 'libpkgstate >=3.0.0' "$pc" >/dev/null || { echo 'missing libpkgstate >=3.0.0 metadata' >&2; exit 1; }
grep -F 'libpkgbuild >=2.0.0' "$pc" >/dev/null || { echo 'missing libpkgbuild >=2.0.0 metadata' >&2; exit 1; }
grep -F 'libpkgimage >=0.3.0' "$pc" >/dev/null || { echo 'missing libpkgimage >=0.3.0 metadata' >&2; exit 1; }
grep -F 'libpkgstate-source >=3.0.0' "$pc" >/dev/null || { echo 'missing libpkgstate-source >=3.0.0 metadata' >&2; exit 1; }
