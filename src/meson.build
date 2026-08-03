# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
public_inc = include_directories('../include')
pkgstate_build = library(
  'pkgstate-build',
  [
    'adapter.cpp',
  ],
  cpp_args: [],
  include_directories: public_inc,
  dependencies: [
    libpkgstate_dep,
    libpkgbuild_dep,
    libpkgimage_dep,
    libpkgstate_source_dep,
  ],
  install: true,
  version: meson.project_version(),
  soversion: '1',
)
libpkgstate_build_dep = declare_dependency(
  link_with: pkgstate_build,
  include_directories: public_inc,
  dependencies: [
    libpkgstate_dep,
    libpkgbuild_dep,
    libpkgimage_dep,
    libpkgstate_source_dep,
  ],
  compile_args: [],
  version: meson.project_version(),
)
meson.override_dependency('libpkgstate-build', libpkgstate_build_dep)
install_headers(
  '../include/libpkgstate-build/adapter.h',
  '../include/libpkgstate-build/libpkgstate-build.h',
  subdir: 'libpkgstate-build',
)
pkgconf.generate(
  pkgstate_build,
  name: 'libpkgstate-build',
  filebase: 'libpkgstate-build',
  description: 'Admission of verified libpkgbuild authority into libpkgstate',
  subdirs: '.',
  requires: [libpkgstate_dep, libpkgbuild_dep, libpkgimage_dep],
  requires_private: [libpkgstate_source_dep],
)
