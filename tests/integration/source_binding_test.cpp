// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgstate-build/adapter.h>
#include <libpkgstate-source/adapter.h>

namespace {

void derives_source_from_the_admitted_build_request()
{
  const auto admitted = build_fixture::admitted();
  const auto projected = pkgstate::build_adapter::project_build(admitted);
  const auto& request = admitted.build().request();

  const auto expected = pkgstate::source_adapter::project_source(
      request.source(), request.architectures().build(),
      request.architectures().target());

  TEST_EQ(projected.source(), expected);
  TEST_EQ(projected.provenance().source_record(), expected.identity());
}

} // namespace

int main()
{
  derives_source_from_the_admitted_build_request();
}
