// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

/*! \file adapter.h
 *  \brief Projection of admitted build/image authority into durable state.
 */
#pragma once

#include <libpkgstate-build/export.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

#include <libpkgbuild-image/authority.h>
#include <libpkgstate/installed_control.h>
#include <libpkgstate/package_source_record.h>

/*! \brief Build-authority projection into the durable state vocabulary. */
namespace pkgstate::build_adapter {

/*! \brief Stable reason that build-to-state projection was refused. */
enum class projection_error_code : std::uint8_t {
  source_binding = 1,      //!< Request-bound source projection failed.
  identity_translation = 2,//!< A foreign identity representation was invalid.
};

/*! \brief Typed build-to-state projection failure. */
class PKGSTATE_BUILD_API projection_error final : public std::invalid_argument {
public:
  projection_error(projection_error_code code, std::string message);
  ~projection_error() override;
  [[nodiscard]] projection_error_code code() const noexcept;

private:
  projection_error_code code_;
};

/*! \brief Durable source and provenance projected from one admitted build image. */
class PKGSTATE_BUILD_API build_authority final {
public:
  build_authority(const build_authority&) noexcept;
  build_authority(build_authority&&) noexcept;
  build_authority& operator=(const build_authority&) noexcept;
  build_authority& operator=(build_authority&&) noexcept;
  ~build_authority();

  [[nodiscard]] const package_source_record& source() const noexcept;
  [[nodiscard]] const build_provenance& provenance() const noexcept;

private:
  struct impl;
  explicit build_authority(std::shared_ptr<const impl> value);
  std::shared_ptr<const impl> impl_;

  friend PKGSTATE_BUILD_API build_authority project_build(
      const pkgbuild::image_adapter::build_image_authority& authority);
};

/*! \brief Project one already admitted successful build/image pair into state.
 *  \param authority Complete build/image admission owned by libpkgbuild-image.
 *  \return Immutable durable source and build provenance projection.
 */
[[nodiscard]] PKGSTATE_BUILD_API build_authority project_build(
    const pkgbuild::image_adapter::build_image_authority& authority);

} // namespace pkgstate::build_adapter
