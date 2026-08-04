# Integration

Call `project_build()` only after the build result has completed successfully
and the exact retained artifact bytes have been independently inspected by
`libpkgimage`.

```text
libpkgbuild result ------------+--> libpkgstate-build --> build_authority
  `- sealed source request -----|          |
libpkgimage inspection --------+          `- derived package_source_record
```

Do not supply a second source record and do not replace the inspection with
archive filenames, package coordinates, or planner candidate identity. `build_authority` is intended for the later
application-admission boundary; it performs no target mutation or state I/O.

Release after `libpkgstate` 3.0.0, `libpkgsource` 3.0.0, `libpkgimage` 0.4.0,
`libpkgbuild` 2.0.0, and `libpkgstate-source` 3.0.0. Release before
`libpkgstate-apply`.
