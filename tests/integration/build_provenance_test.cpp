// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgstate-build/adapter.h>

#include <string>

namespace {

template<typename Identity>
std::string state_build_identity(const Identity& value)
{
  return "v1:sha256:" + value.hex();
}

void retains_every_build_owned_identity()
{
  const auto admitted = build_fixture::admitted();
  const auto projected = pkgstate::build_adapter::project_build(admitted);
  const auto& build = admitted.build();
  const auto& provenance = projected.provenance();

  TEST_EQ(provenance.request().string(),
          state_build_identity(build.request().identity()));
  TEST_EQ(provenance.build_inputs().string(),
          state_build_identity(build.request().inputs().identity()));
  TEST_EQ(provenance.environment_policy().string(),
          state_build_identity(build.request().policy().environment().identity()));
  TEST_EQ(provenance.build_policy().string(),
          state_build_identity(build.request().policy().identity()));
  TEST_EQ(provenance.build_result().string(),
          state_build_identity(build.identity()));
  TEST_EQ(provenance.payload_manifest().string(),
          state_build_identity(build.payload()->identity()));
  TEST_EQ(provenance.artifact().string(),
          state_build_identity(build.artifact()->identity()));
  TEST_EQ(provenance.artifact_binding().string(),
          state_build_identity(*build.artifact_binding()));
  TEST_EQ(provenance.execution_evidence().string(),
          state_build_identity(build.execution_evidence()));
}

} // namespace

int main()
{
  retains_every_build_owned_identity();
}
