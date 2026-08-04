// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

/*!
 * \file adapter.h
 * \brief Admission of native build and image authority into installed state.
 */
#pragma once

#include <libpkgstate-build/export.h>

#include <cstdint>
#include <stdexcept>
#include <string>

#include <libpkgbuild/result.h>
#include <libpkgimage/inspection_receipt.h>
#include <libpkgstate/installed_control.h>
#include <libpkgstate/package_source_record.h>

/*! \brief Build-authority admission into the durable state vocabulary. */
namespace pkgstate::build_adapter {

/*! \brief Stable reason that build-to-state projection was refused. */
enum class projection_error_code : std::uint8_t {
  build_result = 1,        //!< The build result was not complete and successful.
  source_binding = 2,      //!< Request-bound source authority was inconsistent.
  artifact_binding = 3,    //!< Artifact bytes and inspection evidence disagreed.
  payload_mismatch = 4,    //!< Normalized image and ordered payload disagreed.
  identity_translation = 5,//!< A foreign identity representation was invalid.
};

/*! \brief Typed build-to-state projection failure. */
class PKGSTATE_BUILD_API projection_error final : public std::invalid_argument {
public:
  /*!
   * \brief Construct a typed projection failure.
   * \param code Stable refusal category.
   * \param message Human-readable diagnostic text.
   */
  projection_error(projection_error_code code, std::string message);

  /*! \brief Destroy the polymorphic projection failure. */
  ~projection_error() override;

  /*! \brief Return the stable refusal category. */
  [[nodiscard]] projection_error_code code() const noexcept;

private:
  projection_error_code code_;
};

/*!
 * \brief Source-bound build authority admitted by this adapter.
 *
 * The value keeps the exact durable source projection beside the build
 * provenance derived from the same request. Callers cannot combine provenance
 * with another source record after admission.
 */
class PKGSTATE_BUILD_API build_authority final {
public:
  /*! \brief Return the request-bound durable source record. */
  [[nodiscard]] const package_source_record& source() const noexcept;
  /*! \brief Return the exact admitted build provenance. */
  [[nodiscard]] const build_provenance& provenance() const noexcept;

private:
  build_authority(package_source_record source,
                  build_provenance provenance);

  package_source_record source_;
  build_provenance provenance_;

  friend PKGSTATE_BUILD_API build_authority project_build(
      const pkgbuild::build_result& build,
      const pkgimage::inspected_package_image& image);
};

/*!
 * \brief Retain one verified successful build as native state provenance.
 *
 * Source authority is derived only from the sealed source snapshot and exact
 * architecture selections retained by the build request. The independently
 * inspected image must name the exact artifact bytes and equal the complete
 * ordered build payload, including kind-specific metadata and content.
 *
 * No parallel caller-supplied source record is accepted. The function performs
 * no build execution, planner projection, filesystem application, target
 * observation, or state publication.
 *
 * \param build Complete native build result.
 * \param image Independent inspection of the exact produced artifact.
 * \return Source-bound durable build authority.
 * \throws projection_error when the build is incomplete, request-bound source
 * projection fails, artifact evidence disagrees, payload/image facts differ,
 * or a foreign identity cannot be translated.
 */
[[nodiscard]] PKGSTATE_BUILD_API build_authority project_build(
    const pkgbuild::build_result& build,
    const pkgimage::inspected_package_image& image);

} // namespace pkgstate::build_adapter
