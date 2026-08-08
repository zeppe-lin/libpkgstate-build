# Testing

Qualification is layered so a green projection case cannot hide a damaged neighbor boundary or package contract.

The `unit` suite exercises adapter-owned value/error semantics that do not require constructing a package-management authority graph. The `integration` suite constructs real `libpkgsource`, `libpkgcatalog`, `libpkgresolve`, `libpkgbuild`, `libpkgimage`, and `libpkgbuild-image` values before crossing the `libpkgstate-build` seam. It separately proves source binding, build-owned provenance, image/artifact provenance, admission/restoration equivalence, identity sensitivity, upstream mismatch refusal, and opaque projected-value semantics.

Payload/image disagreement is intentionally tested at the `libpkgbuild-image` admission seam. `libpkgstate-build` consumes an already admitted authority and must not become a second payload comparator. Conversely, the projection tests verify every durable identity against the exact admitted build/image values rather than against copied fixture constants.

The `header` suite compiles the umbrella and each installed header independently. The `contract` suite owns static architecture, documentation, release, repository, extraction, CI, style, test-layout, ABI, and generated pkg-config checks. Shared builds compare dynamic exports to `abi/libpkgstate-build.exports`, verify SONAME `1`, and audit direct `DT_NEEDED` edges. Static builds prove the complete private pkg-config closure.

Fixtures contain deterministic authority construction only. Shared assertion/query helpers live under `tests/support`; behavioral assertions stay in the individual unit or integration program. No fixture is production authority and no integration test is allowed to bypass the public admission APIs merely to manufacture a convenient state.

Source contracts verify architecture placement, release metadata, repository hygiene, CI coverage, style, test topology, and root-commit extraction provenance. The provenance contract checks the root extraction against the recorded `libpkgstate` 2.5.1 hashes; it intentionally does not freeze current implementation files.

CI runs GCC and Clang in separate shared and static configurations, one optimized release configuration, and ASan/UBSan configurations. Installation qualification compiles a consumer against staged headers and metadata, checks every installed header, audits the shared boundary or static archive, and verifies installed manual and project documentation.

The documentation contract receives the include roots of the production dependencies resolved by Meson before Clang parses public headers. Ambient system-installed zoo headers are not accepted as dependency closure.

A release candidate is incomplete until the exact dependency tags used by CI exist and the whole matrix is green from clean build directories.
