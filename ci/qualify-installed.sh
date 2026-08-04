#!/bin/sh
# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
set -eu
[ "$#" -eq 2 ] || exit 2
build_dir=$1
link_mode=$2
install_prefix=$(cat "$build_dir/ci-install-prefix")
rm -rf "$install_prefix"
meson install -C "$build_dir"
export PKG_CONFIG_PATH=$install_prefix/lib/pkgconfig${PKG_CONFIG_PATH:+:$PKG_CONFIG_PATH}
unset PKG_CONFIG_SYSROOT_DIR
test "$(pkg-config --modversion libpkgstate-build)" = 3.0.0
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT HUP INT TERM
flags=$(pkg-config --cflags --libs libpkgstate-build)
[ "$link_mode" = shared ] || flags=$(pkg-config --static --cflags --libs libpkgstate-build)
documentation_dir="$install_prefix/share/doc/libpkgstate-build"
for document in README.md HISTORY.md CONTRIBUTING.md MAINTAINING.md architecture.md integration.md testing.md abi.md code-style.md; do
  test -s "$documentation_dir/$document" || {
    echo "installed documentation is absent: $document" >&2
    exit 1
  }
done
case $link_mode in
  shared) if printf '%s\n' "$flags" | grep -F -- '-lpkgstate-source' >/dev/null; then echo 'private link edge leaked into shared consumer flags: -lpkgstate-source' >&2; exit 1; fi ;;
  static) printf '%s\n' "$flags" | grep -F -- '-lpkgstate-source' >/dev/null || { echo 'static link closure omits -lpkgstate-source' >&2; exit 1; } ;;
esac
# shellcheck disable=SC2086
${CXX:-c++} -std=c++17 -Wall -Wextra -Wpedantic -Werror "$(dirname "$0")/installed-build-consumer.cpp" $flags -o "$tmp/consumer"
"$tmp/consumer"
for header in "$install_prefix"/include/libpkgstate-build/*.h; do
  printf '#include <libpkgstate-build/%s>
int main() { return 0; }
' "$(basename "$header")" >"$tmp/header.cpp"
  # shellcheck disable=SC2046
  ${CXX:-c++} -std=c++17 -Wall -Wextra -Wpedantic -Werror -fsyntax-only $(pkg-config --cflags libpkgstate-build) "$tmp/header.cpp"
done
case $link_mode in
  shared) "$(dirname "$0")/audit-shared-boundary.sh" "$install_prefix/lib/libpkgstate-build.so.3.0.0" ;;
  static) test -f "$install_prefix/lib/libpkgstate-build.a" ;;
esac
if [ -s "$build_dir/man/libpkgstate-build.3" ]; then
  test -s "$install_prefix/share/man/man3/libpkgstate-build.3"
fi
