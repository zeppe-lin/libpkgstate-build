# libpkgstate-build

libpkgstate-build provides durable admission of successful native build and exact image evidence.

```text
request-bound successful build + inspected image -> build_authority
```

## Authority

This repository owns the composition of request-bound source admission, successful build evidence, and independent image inspection into state build provenance. It is a translation boundary, not another semantic owner. Its input and output models remain authoritative in their respective repositories.

The public operation accepts one complete successful `libpkgbuild` result and the independently inspected exact artifact image. A successful projection retains the derived state source record and identities for request, materials, inputs, policies, result, payload, artifact bytes, binding, execution, image, and inspection.

The adapter performs no discovery, parsing, dependency resolution, build execution, archive inspection, target mutation, state publication, migration, retry policy, or compatibility import unless the operation is explicitly part of the contract above. It exports refusal rather than guessing. It refuses failed or incomplete builds, source projection failure, artifact-byte disagreement, receipt disagreement, and any ordered payload field mismatch.

See `docs/architecture.md` for invariants and `docs/integration.md` for placement in the package-management graph.

## Dependency boundary

Public installed closure: `libpkgstate >=3.0.0`, `libpkgbuild >=2.0.0`, and `libpkgimage >=0.4.0`.

Private implementation closure: `libpkgstate-source >=3.0.0`.

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

The 3.0 repository was extracted from `libpkgstate` 2.5.1. The repository root preserves extraction provenance; later commits may evolve the independent product without rewriting that history. The library preserves SONAME generation 1.

Release after `libpkgstate-source` and before `libpkgstate-apply`.

## Documentation

- `docs/architecture.md` — authority and refusal invariants;
- `docs/integration.md` — composition and release order;
- `docs/testing.md` — qualification matrix;
- `docs/abi.md` — ABI and pkg-config policy;
- `MAINTAINING.md` — release gate.

## License

GPL-3.0-or-later. See `COPYING` and `COPYRIGHT`.
