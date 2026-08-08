# SPDX-FileCopyrightText: 2026 Alexandr Savca
# SPDX-License-Identifier: GPL-3.0-or-later
if get_option('tests').allowed()
  unit_tests = [
    ['projection-error', 'unit/projection_error_test.cpp'],
  ]
  foreach item : unit_tests
    unit_test = executable(
      item[0] + '-test',
      item[1],
      dependencies: libpkgstate_build_dep,
      cpp_args: ['-UNDEBUG'],
    )
    test(item[0], unit_test, suite: 'unit')
  endforeach

  integration_tests = [
    ['source-binding', 'integration/source_binding_test.cpp'],
    ['build-provenance', 'integration/build_provenance_test.cpp'],
    ['image-provenance', 'integration/image_provenance_test.cpp'],
    ['admission-path', 'integration/admission_path_test.cpp'],
    ['identity-sensitivity', 'integration/identity_sensitivity_test.cpp'],
    ['upstream-refusal', 'integration/upstream_refusal_test.cpp'],
    ['value-semantics', 'integration/value_semantics_test.cpp'],
  ]
  foreach item : integration_tests
    integration_test = executable(
      item[0] + '-integration-test',
      item[1],
      dependencies: [libpkgstate_build_dep, libpkgstate_source_dep],
      cpp_args: ['-UNDEBUG'],
    )
    test(item[0], integration_test, suite: 'integration')
  endforeach

  public_headers = [
    ['export', 'libpkgstate-build/export.h'],
    ['adapter', 'libpkgstate-build/adapter.h'],
    ['libpkgstate_build', 'libpkgstate-build/libpkgstate-build.h'],
  ]
  foreach header : public_headers
    public_header = executable(
      header[0] + '-public-header-test',
      'header/public_header_test.cpp',
      dependencies: libpkgstate_build_dep,
      cpp_args: ['-DLIBPKGSTATE_ADAPTER_TEST_HEADER="' + header[1] + '"'],
    )
    test(
      'compile public header ' + header[1],
      public_header,
      suite: 'header',
    )
  endforeach

  sh = find_program('sh')
  if library_kind == 'shared'
    nm = find_program('nm')
    test(
      'verify reviewed adapter ABI surface',
      sh,
      args: [
        join_paths(meson.current_source_dir(), 'contracts/check_abi_surface.sh'),
        pkgstate_build.full_path(),
        meson.project_source_root() / 'abi/libpkgstate-build.exports',
        nm.full_path(),
      ],
      suite: 'contract',
    )
  endif

  libpkgstate_public_include = libpkgstate_dep.get_variable(
    pkgconfig: 'includedir',
  )
  libpkgbuild_image_public_include = libpkgbuild_image_dep.get_variable(
    pkgconfig: 'includedir',
  )
  libpkgstate_source_public_include = libpkgstate_source_dep.get_variable(
    pkgconfig: 'includedir',
  )
  foreach contract : [
    'architecture',
    'documentation',
    'release_metadata',
    'repository',
    'extraction',
    'ci',
    'test_layout',
  ]
    contract_args = [
      join_paths(meson.current_source_dir(), 'contracts/check_' + contract + '.sh'),
      meson.project_source_root(),
    ]
    if contract == 'documentation'
      contract_args += [
        libpkgstate_public_include,
        libpkgbuild_image_public_include,
        libpkgstate_source_public_include,
      ]
    endif
    test(
      contract.replace('_', '-'),
      sh,
      args: contract_args,
      suite: 'contract',
    )
  endforeach
  test(
    'style-contract',
    sh,
    args: [
      join_paths(meson.current_source_dir(), 'contracts/check_style.sh'),
      meson.project_source_root(),
      meson.project_build_root(),
    ],
    suite: 'contract',
  )
  test(
    'pkgconfig-metadata',
    sh,
    args: [
      join_paths(meson.current_source_dir(), 'contracts/check_pkgconfig_metadata.sh'),
      meson.project_build_root(),
    ],
    suite: 'contract',
  )
endif
