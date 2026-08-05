% LIBPKGSTATE-BUILD(3) libpkgstate-build | Version 3.0.0

<!-- Generated from libpkgstate-build.3.scdoc; do not edit. -->


# NAME

libpkgstate-build - project admitted native build/image authority into installed state

# SYNOPSIS

**#include <libpkgstate-build/adapter.h>**

# DESCRIPTION

**project_build()** accepts one
**pkgbuild::image_adapter::build_image_authority**. That value already binds one
complete successful **libpkgbuild** result to one independently inspected
**libpkgimage**.

The adapter derives the exact **package_source_record** from the admitted build
request's sealed source snapshot and selected build and target architectures,
then returns an immutable **build_authority** value for later application and
state-publication composition. It performs no archive inspection, payload
comparison, filesystem application, or state publication.

# RETAINED AUTHORITY

The resulting provenance retains typed identities for the source record,
logical build request and resolver-backed build-input set, environment policy,
build policy, successful result, payload manifest, sealed artifact, exact
artifact content, artifact binding, execution evidence, build/image admission,
normalized artifact image, and inspection receipt.

The adapter does not derive build authority from planner candidates, package
filenames, archive labels, mutable build directories, or separate caller-supplied
build and image values.

# ERRORS

**projection_error** classifies request-bound source-projection failure and exact
foreign-identity translation failure. Build/image disagreement is refused by
**libpkgbuild-image** before this boundary is entered.

# SEE ALSO

**libpkgbuild-image**(3), **libpkgstate-source**(3),
**libpkgstate-apply**(3), **pkgstate_model**(3)
