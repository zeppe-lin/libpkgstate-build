# Architecture

## Authority flow

Contract shorthand: `package_source_record + successful build + inspected image -> build_authority`.

```text
package_source_record
+ complete successful libpkgbuild result
+ independently inspected libpkgimage
                    |
                    v
              build_authority
```

`libpkgstate-build` admits build evidence into the durable provenance
vocabulary. It does not make a build successful and does not treat an archive
name as evidence.

## Admission invariants

`project_build()` derives the source projection from the exact sealed source
snapshot and architecture selections retained by the build request. It accepts
no parallel caller-supplied source record. `libpkgstate-source` remains the
single translation implementation, while the build bridge owns the composition
of that source record with verified build and image evidence.

The build result must be complete and successful. Its sealed artifact digest
must identify the exact archive bytes inspected by `libpkgimage`. The
inspection receipt must bind the supplied normalized image and its entry count.
Finally, every ordered build-payload entry must equal the corresponding image
entry across path, type, mode, ownership, size, timestamp, content digest, link
target, and device data. Count or field drift is a typed refusal.

A successful result retains source-record, request, material, policy, execution,
payload, artifact, image, and inspection identities as one immutable
`build_authority`.

## Non-authorities

The adapter does not execute a build, inspect archive bytes, mutate a target,
construct planner candidates, publish state, or recover missing evidence. It
exports disagreement rather than choosing between authorities.

## Dependency placement

`libpkgstate`, `libpkgbuild`, and `libpkgimage` are public because their types
occur in installed declarations. `libpkgstate-source` is implementation-only:
it derives the request-bound source record and remains private for shared
consumers while being retained in the static link closure.

The implementation body and behavior test are byte-for-byte extractions from
`libpkgstate` 2.5.1. Header normalization is limited to the independent export
annotation.
