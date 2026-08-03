# History

## 3.0.0 (2026-08-04)

- Extracted `libpkgstate-build` from the `libpkgstate` 2.5.1 repository.
- Preserved the existing adapter behavior and SONAME generation 1.
- Established an independent dependency closure: libpkgstate >=3.0.0; libpkgbuild >=2.0.0; libpkgimage >=0.3.0; libpkgstate-source >=3.0.0.
- Added public-header, pkg-config, extraction-provenance, architecture, repository, compiler, sanitizer, shared, and static qualification.
