# ABI policy

`libpkgstate-build` is an independently released C++17 shared and static library. Release 3.0.0 retains SONAME generation `1` while replacing the unpublished extracted surface with the admitted build/image authority contract.

The public `build_authority` value uses opaque immutable storage. Foreign `libpkgbuild-image` and `libpkgstate` object layouts do not become its public object layout.

The reviewed ELF export set is stored in `abi/libpkgstate-build.exports`. Shared builds use hidden visibility and a generated version script; unreviewed implementation symbols must not escape. Any export addition, removal, signature change, exception hierarchy change, or public value-layout change requires an explicit ABI decision before release.

The pkg-config file is part of the installed contract. Public requirements are exactly `libpkgstate >=3.0.0,<4.0.0` and `libpkgbuild-image >=1.0.0,<2.0.0`. The private requirement is `libpkgstate-source >=3.0.0,<4.0.0`. Private requirements must not leak into ordinary shared-consumer flags, but they must appear in the static closure.

Repository version and SONAME generation are separate decisions. Semantic identity protocols in the unpublished state model remain at their first actual generation.
