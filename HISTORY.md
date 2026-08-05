# History

## 3.0.0 (2026-08-05)

- Extracted `libpkgstate-build` from the `libpkgstate` 2.5.1 repository while preserving extraction provenance and SONAME generation 1.
- Replaced separate build-result and inspected-image inputs with one admitted `libpkgbuild-image` authority.
- Removed the duplicated payload/image comparator; exact build/image agreement now has one owner.
- Removed counterfeit source-material and package-tree provenance and retained the logical resolver-backed build-input set plus build/image admission identity.
- Made `build_authority` opaque and completed reviewed export, public-header, pkg-config, shared/static, compiler, sanitizer, documentation, and installed-consumer qualification.
- Established the bounded dependency closure: `libpkgstate >=3.0.0,<4.0.0`, `libpkgbuild-image >=1.0.0,<2.0.0`, and private `libpkgstate-source >=3.0.0,<4.0.0`.
