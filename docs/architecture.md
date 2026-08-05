# Architecture

## Authority flow

Contract shorthand: `admitted build/image authority -> build_authority`.

```text
pkgbuild::image_adapter::build_image_authority
                    |
                    v
              build_authority
```

`libpkgbuild-image` already proves that one complete successful build result and one independently inspected package image describe the same exact artifact. `libpkgstate-build` does not repeat that proof. It translates the admitted pair into durable state vocabulary.

## Projection invariants

`project_build()` derives the source projection from the exact sealed source snapshot and architecture selections retained by the admitted build request. It accepts no parallel caller-supplied source record.

The resulting provenance retains:

- the derived package-source-record identity;
- logical build-request and resolver-backed build-input-set identities;
- environment and build-policy identities;
- successful result, payload, artifact, exact artifact-content, artifact-binding, and execution identities;
- the build/image admission identity;
- normalized image and inspection-receipt identities.

The provenance source identity must equal the derived source record identity. Foreign identity encodings must translate exactly into their state-owned typed identities.

## Non-authorities

The adapter does not execute a build, inspect archive bytes, compare payload entries, mutate a target, construct planner candidates, publish state, or recover missing evidence. It exports disagreement rather than choosing between authorities.

## Failure translation

The boundary translates only typed source-projection and identity-translation failures. Allocation, logic, and unrelated runtime failures retain their native type. In particular, the adapter must not classify every `std::exception` as a projection disagreement.

## Dependency placement

`libpkgstate` and `libpkgbuild-image` are public because their types occur in installed declarations. `libpkgstate-source` is implementation-only: it derives the request-bound source record and remains private for shared consumers while being retained in the static link closure.

The root commit records the extracted implementation. The 3.0 authority reset removes its duplicated build/image proof without rewriting extraction history.
