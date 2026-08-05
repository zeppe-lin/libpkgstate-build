#!/bin/sh
# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
root=$1
fail(){ echo "architecture-contract: $*" >&2; exit 1; }
for forbidden in libpkgplan libpkgapply; do
  if grep -R -F "$forbidden" "$root/include" "$root/src" "$root/meson.build" "$root/src/meson.build" >/dev/null 2>&1; then fail "forbidden authority dependency: $forbidden"; fi
done
grep -F 'admitted build/image authority -> build_authority' "$root/docs/architecture.md" >/dev/null || fail 'authority flow is undocumented'
grep -F 'does not repeat that proof' "$root/docs/architecture.md" >/dev/null || fail 'non-revalidation invariant is undocumented'
grep -F 'const pkgbuild::image_adapter::build_image_authority& authority' "$root/include/libpkgstate-build/adapter.h" >/dev/null || fail 'public admission does not consume build-image authority'
if grep -R -E 'archive_backend|file_size\(|payload_mismatch|artifact_mismatch|inspection_mismatch' "$root/include" "$root/src" >/dev/null; then fail 'archive/payload verification returned to the projection boundary'; fi
grep -F "gnu_symbol_visibility: 'hidden'" "$root/src/meson.build" >/dev/null || fail 'hidden visibility is not enforced'
test -s "$root/abi/libpkgstate-build.exports" || fail 'reviewed export manifest is absent'
grep -F "version: ['>=1.0.0', '<2.0.0']" "$root/meson.build" >/dev/null || fail 'libpkgbuild-image ABI interval is not bounded'
if grep -R -F 'catch (const std::exception' "$root/src" >/dev/null; then fail 'adapter launders unrelated failures through std::exception'; fi
