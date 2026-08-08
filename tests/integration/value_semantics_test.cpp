// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgstate-build/adapter.h>

#include <utility>

namespace {

void preserves_opaque_value_semantics()
{
  const auto first = pkgstate::build_adapter::project_build(
      build_fixture::admitted());
  const auto copied = first;
  auto moved = copied;
  auto assigned = first;
  assigned = std::move(moved);

  TEST_EQ(assigned.source(), first.source());
  TEST_EQ(assigned.provenance(), first.provenance());
}

} // namespace

int main()
{
  preserves_opaque_value_semantics();
}
