// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "build_fixture.h"
#include "test.h"

#include <libpkgstate-build/adapter.h>

#include <utility>

namespace {

void retains_complete_build_authority()
{
  const auto admitted = build_fixture::admitted();
  const pkgstate::build_adapter::build_authority authority =
      pkgstate::build_adapter::project_build(admitted);
  const pkgbuild::build_result& build = admitted.build();
  const pkgimage::inspected_package_image& image = admitted.image();
  const pkgstate::build_provenance& provenance = authority.provenance();

  TEST_EQ(authority.source(), build_fixture::state_source());
  TEST_EQ(provenance.source_record(), authority.source().identity());
  TEST_EQ(provenance.request().string(),
          "v1:sha256:" + build.request().identity().hex());
  TEST_EQ(provenance.build_inputs().string(),
          "v1:sha256:" + build.request().inputs().identity().hex());
  TEST_EQ(provenance.environment_policy().string(),
          "v1:sha256:" +
              build.request().policy().environment().identity().hex());
  TEST_EQ(provenance.build_policy().string(),
          "v1:sha256:" + build.request().policy().identity().hex());
  TEST_EQ(provenance.build_result().string(),
          "v1:sha256:" + build.identity().hex());
  TEST_EQ(provenance.payload_manifest().string(),
          "v1:sha256:" + build.payload()->identity().hex());
  TEST_EQ(provenance.artifact().string(),
          "v1:sha256:" + build.artifact()->identity().hex());
  TEST_EQ(provenance.artifact_content().string(),
          image.receipt().archive_digest().string());
  TEST_EQ(provenance.artifact_binding().string(),
          "v1:sha256:" + build.artifact_binding()->hex());
  TEST_EQ(provenance.execution_evidence().string(),
          "v1:sha256:" + build.execution_evidence().hex());
  TEST_EQ(provenance.build_image().string(),
          "v1:sha256:" + admitted.identity().hex());
  TEST_EQ(provenance.artifact_image().string(),
          image.image().identity().string());
  TEST_EQ(provenance.artifact_inspection().string(),
          image.receipt().identity().string());
}

void preserves_opaque_value_semantics()
{
  const auto admitted = build_fixture::admitted();
  const auto first = pkgstate::build_adapter::project_build(admitted);
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
  retains_complete_build_authority();
  preserves_opaque_value_semantics();
}
