// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgstate-build/adapter.h>

namespace {

void policy_change_reaches_durable_build_provenance()
{
  const auto first = pkgstate::build_adapter::project_build(
      build_fixture::admitted(build_fixture::policy(4)));
  const auto second = pkgstate::build_adapter::project_build(
      build_fixture::admitted(build_fixture::policy(8)));

  TEST_EQ(first.source(), second.source());
  TEST_NE(first.provenance().environment_policy(),
          second.provenance().environment_policy());
  TEST_NE(first.provenance().build_policy(),
          second.provenance().build_policy());
  TEST_NE(first.provenance().request(), second.provenance().request());
  TEST_NE(first.provenance().build_result(),
          second.provenance().build_result());
}

void artifact_change_reaches_durable_content_provenance()
{
  const auto first = pkgstate::build_adapter::project_build(
      build_fixture::admitted(build_fixture::policy(), '1'));
  const auto second = pkgstate::build_adapter::project_build(
      build_fixture::admitted(build_fixture::policy(), '2'));

  TEST_EQ(first.source(), second.source());
  TEST_EQ(first.provenance().request(), second.provenance().request());
  TEST_EQ(first.provenance().build_inputs(), second.provenance().build_inputs());
  TEST_NE(first.provenance().artifact(), second.provenance().artifact());
  TEST_NE(first.provenance().artifact_content(),
          second.provenance().artifact_content());
  TEST_NE(first.provenance().artifact_binding(),
          second.provenance().artifact_binding());
  TEST_NE(first.provenance().build_result(),
          second.provenance().build_result());
  TEST_NE(first.provenance().build_image(), second.provenance().build_image());
}

} // namespace

int main()
{
  policy_change_reaches_durable_build_provenance();
  artifact_change_reaches_durable_content_provenance();
}
