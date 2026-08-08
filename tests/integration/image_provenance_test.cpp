// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgstate-build/adapter.h>

#include <string>

namespace {

void retains_every_image_and_artifact_identity()
{
  const auto admitted = build_fixture::admitted();
  const auto projected = pkgstate::build_adapter::project_build(admitted);
  const auto& image = admitted.image();
  const auto& provenance = projected.provenance();

  TEST_EQ(provenance.artifact_content().string(),
          image.receipt().archive_digest().string());
  TEST_EQ(provenance.build_image().string(),
          "v1:sha256:" + admitted.identity().hex());
  TEST_EQ(provenance.artifact_image().string(),
          image.image().identity().string());
  TEST_EQ(provenance.artifact_inspection().string(),
          image.receipt().identity().string());
}

} // namespace

int main()
{
  retains_every_image_and_artifact_identity();
}
