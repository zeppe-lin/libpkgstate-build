// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../support/test.h"

#include <libpkgstate-build/adapter.h>

#include <string>

namespace {

void retains_typed_projection_error()
{
  const pkgstate::build_adapter::projection_error failure(
      pkgstate::build_adapter::projection_error_code::source_binding,
      "source binding failed");

  TEST_EQ(failure.code(),
          pkgstate::build_adapter::projection_error_code::source_binding);
  TEST_EQ(std::string(failure.what()), "source binding failed");
}

} // namespace

int main()
{
  retains_typed_projection_error();
}
