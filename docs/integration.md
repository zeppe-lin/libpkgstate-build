# Integration

Call `project_build()` only with one authority already admitted by `libpkgbuild-image`.

```text
libpkgbuild result -----+
                        +--> libpkgbuild-image --> libpkgstate-build
libpkgimage inspection -+                             |
                                                      `- build_authority
```

`libpkgstate-build` derives the package-source record from the admitted build request and translates the admitted identities into `libpkgstate::build_provenance`. It does not reopen the archive or compare payload and image again.

Do not replace the admitted authority with archive filenames, package coordinates, planner candidate identity, separate build/image values, or mutable build directories. `build_authority` is intended for the later application/state-publication composition boundary; it performs no target mutation or state I/O.

Release after `libpkgstate` 3.0.0, `libpkgsource` 3.0.0, `libpkgbuild` 3.0.0, `libpkgimage` 0.4.0, `libpkgbuild-image` 1.0.0, and `libpkgstate-source` 3.0.0. Release before `libpkgstate-apply`.
