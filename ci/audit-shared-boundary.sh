#!/bin/sh
# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
[ "$#" -eq 1 ] || { echo "usage: $0 INSTALLED-LIBRARY" >&2; exit 2; }
library=$1
[ -s "$library" ] || { echo "shared-boundary-audit: missing $library" >&2; exit 1; }
output=$(readelf -d "$library")
printf '%s
' "$output"
printf '%s
' "$output" | grep -F 'Library soname: [libpkgstate-build.so.1]' >/dev/null || { echo 'shared-boundary-audit: wrong SONAME' >&2; exit 1; }
needed=$(printf '%s
' "$output" | grep 'Shared library:' || true)
for library_name in libpkgstate.so.4 libpkgbuild-image.so.1 libpkgstate-source.so.1 libpkgbuild.so.4 libpkgimage.so.1; do
  printf '%s
' "$needed" | grep -F "Shared library: [$library_name]" >/dev/null || { echo "shared-boundary-audit: missing $library_name" >&2; exit 1; }
done
if printf '%s
' "$needed" | grep -E 'libpkgplan|libpkgapply|libpkgsource\.so|libpkgstate-(plan|apply)|libcrypto|libarchive|libyaml' >/dev/null; then echo 'shared-boundary-audit: forbidden direct dependency' >&2; exit 1; fi
