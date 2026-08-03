# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
public_inc = include_directories('../include')

elf_export_generator = find_program(
  meson.project_source_root() / 'tools/generate-elf-export-script.sh',
)
export_script_name = 'libpkgstate-build.exports.map'
export_script_path = meson.current_build_dir() / export_script_name
export_script = configure_file(
  input: '../abi/libpkgstate-build.exports',
  output: export_script_name,
  command: [elf_export_generator, '@INPUT@'],
  capture: true,
)

pkgstate_build = library(
  'pkgstate-build',
  [
    'adapter.cpp',
  ],
  cpp_args: visibility_cpp_args + ['-DPKGSTATE_BUILD_BUILDING_LIBRARY'],
  gnu_symbol_visibility: 'hidden',
  link_args: ['-Wl,--version-script=' + export_script_path],
  link_depends: [export_script],
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
libpkgstate_build_consumer_deps = [
  libpkgstate_dep,
  libpkgbuild_dep,
  libpkgimage_dep,
]
if want_static
  libpkgstate_build_consumer_deps += [libpkgstate_source_dep]
endif

libpkgstate_build_dep = declare_dependency(
  link_with: pkgstate_build,
  include_directories: public_inc,
  dependencies: libpkgstate_build_consumer_deps,
  version: meson.project_version(),
)
meson.override_dependency('libpkgstate-build', libpkgstate_build_dep)
install_headers(
  '../include/libpkgstate-build/export.h',
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
