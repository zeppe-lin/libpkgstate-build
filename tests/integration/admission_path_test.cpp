// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgstate-build/adapter.h>

namespace {

void admission_and_restoration_project_the_same_authority()
{
  const auto admitted = build_fixture::admitted();
  const auto restored = build_fixture::restored();

  TEST_EQ(restored.identity(), admitted.identity());
  TEST_EQ(restored.build(), admitted.build());
  TEST_EQ(restored.image().image().identity(),
          admitted.image().image().identity());
  TEST_EQ(restored.image().receipt().identity(),
          admitted.image().receipt().identity());

  const auto admitted_state = pkgstate::build_adapter::project_build(admitted);
  const auto restored_state = pkgstate::build_adapter::project_build(restored);
  TEST_EQ(restored_state.source(), admitted_state.source());
  TEST_EQ(restored_state.provenance(), admitted_state.provenance());
}

} // namespace

int main()
{
  admission_and_restoration_project_the_same_authority();
}
