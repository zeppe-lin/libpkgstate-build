# libpkgstate-build

libpkgstate-build projects one already admitted native build/image authority into durable state provenance.

```text
admitted build/image authority -> build_authority
```

## Authority

This repository owns the translation from `libpkgbuild-image` authority into the `libpkgstate` vocabulary. It does not decide whether build payload and inspected image agree; that statement is already owned and sealed by `libpkgbuild-image`.

`project_build()` accepts one complete `pkgbuild::image_adapter::build_image_authority`. It derives the request-bound state source record and retains identities for the logical build request and inputs, policies, successful result, payload, artifact bytes and binding, execution evidence, build/image admission, normalized image, and inspection receipt.

The adapter performs no discovery, parsing, dependency resolution, source acquisition, build execution, archive inspection, payload comparison, target mutation, state publication, migration, retry policy, or compatibility import. It exports refusal rather than guessing. It refuses source-projection and identity-translation failures.

See `docs/architecture.md` for invariants and `docs/integration.md` for placement in the package-management graph.

## Dependency boundary

Public installed closure: `libpkgstate >=3.0.0,<4.0.0` and `libpkgbuild-image >=1.0.0,<2.0.0`.

Private implementation closure: `libpkgstate-source >=3.0.0,<4.0.0`.

Fallback subprojects are intentionally unsupported. Shared consumers receive only public requirements; static consumers receive the complete private closure through pkg-config.

## Build

```sh
meson setup build-shared \
  -Ddefault_library=shared \
  -Dlink_mode=shared
meson compile -C build-shared
meson test -C build-shared --print-errorlogs

meson setup build-static \
  -Ddefault_library=static \
  -Dlink_mode=static
meson compile -C build-static
meson test -C build-static --print-errorlogs
```

Shared and static artifacts must come from separate build directories. `default_library=both` is rejected because one dependency closure cannot truthfully represent both linkage modes.

## Release lineage

The repository was extracted from `libpkgstate` 2.5.1. The repository root preserves extraction provenance; the 3.0 authority reset removes duplicated build/image validation and retains SONAME generation 1.

Release after `libpkgbuild-image` and `libpkgstate-source`, and before `libpkgstate-apply`.

## Documentation

- `docs/architecture.md` — authority and refusal invariants;
- `docs/integration.md` — composition and release order;
- `docs/testing.md` — qualification matrix;
- `docs/abi.md` — ABI and pkg-config policy;
- `man/libpkgstate-build.3.scdoc` — installed `libpkgstate-build.3` interface manual;
- `MAINTAINING.md` — release gate.

## License

GPL-3.0-or-later. See `COPYING` and `COPYRIGHT`.
