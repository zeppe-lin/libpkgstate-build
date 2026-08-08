// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../fixtures/build_image.h"
#include "../support/test.h"

#include <libpkgbuild-image/authority.h>

namespace {

void payload_disagreement_is_refused_before_state_projection()
{
  const auto build = build_fixture::result();
  const auto mismatched = build_fixture::inspected('1', 0644);

  bool refused = false;
  try {
    (void)pkgbuild::image_adapter::build_image_authority::admit(
        build, mismatched);
  } catch (const pkgbuild::image_adapter::admission_error& error) {
    refused = true;
    TEST_EQ(error.code(),
            pkgbuild::image_adapter::admission_error_code::payload_mismatch);
  }
  TEST(refused);
}

void artifact_disagreement_is_refused_before_state_projection()
{
  const auto build = build_fixture::result();
  const auto mismatched = build_fixture::inspected('2');

  bool refused = false;
  try {
    (void)pkgbuild::image_adapter::build_image_authority::admit(
        build, mismatched);
  } catch (const pkgbuild::image_adapter::admission_error& error) {
    refused = true;
    TEST_EQ(error.code(),
            pkgbuild::image_adapter::admission_error_code::artifact_binding);
  }
  TEST(refused);
}

} // namespace

int main()
{
  payload_disagreement_is_refused_before_state_projection();
  artifact_disagreement_is_refused_before_state_projection();
}
