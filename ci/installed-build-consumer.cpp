// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include <libpkgstate-build/libpkgstate-build.h>

int
main()
{
  auto* volatile function = &pkgstate::build_adapter::project_build;
  return function == nullptr ? 1 : 0;
}
