// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

#include <libpkgstate-build/adapter.h>

#include <string>
#include <utility>

#include <libpkgstate-source/adapter.h>

namespace pkgstate::build_adapter {
namespace {

template<typename Target, typename Source>
Target translate_build_identity(const Source& source)
{
  try {
    return Target::parse(std::string("v1:sha256:") + source.hex());
  } catch (const identity_error& error) {
    throw projection_error(
        projection_error_code::identity_translation,
        std::string("cannot translate build identity: ") + error.what());
  }
}

template<typename Target, typename Source>
Target translate_external_identity(const Source& source)
{
  try {
    return Target::parse(source.string());
  } catch (const identity_error& error) {
    throw projection_error(
        projection_error_code::identity_translation,
        std::string("cannot translate external identity: ") + error.what());
  }
}

package_source_record project_source(const pkgbuild::build_request& request)
{
  try {
    return source_adapter::project_source(
        request.source(), request.architectures().build(),
        request.architectures().target());
  } catch (const source_adapter::projection_error& error) {
    throw projection_error(
        projection_error_code::source_binding,
        std::string("cannot derive state source authority from build: ") +
            error.what());
  }
}

} // namespace

projection_error::projection_error(projection_error_code code,
                                   std::string message)
    : std::invalid_argument(std::move(message)), code_(code)
{
}

projection_error::~projection_error() = default;

projection_error_code projection_error::code() const noexcept
{
  return code_;
}

struct build_authority::impl final {
  impl(package_source_record source_value, build_provenance provenance_value)
      : source(std::move(source_value)),
        provenance(std::move(provenance_value))
  {
    if (provenance.source_record() != source.identity()) {
      throw projection_error(
          projection_error_code::source_binding,
          "build authority source binding is inconsistent");
    }
  }

  package_source_record source;
  build_provenance provenance;
};

build_authority::build_authority(std::shared_ptr<const impl> value)
    : impl_(std::move(value))
{
}

build_authority::build_authority(const build_authority&) noexcept = default;
build_authority::build_authority(build_authority&&) noexcept = default;
build_authority& build_authority::operator=(
    const build_authority&) noexcept = default;
build_authority& build_authority::operator=(build_authority&&) noexcept = default;
build_authority::~build_authority() = default;

const package_source_record& build_authority::source() const noexcept
{
  return impl_->source;
}

const build_provenance& build_authority::provenance() const noexcept
{
  return impl_->provenance;
}

build_authority project_build(
    const pkgbuild::image_adapter::build_image_authority& authority)
{
  const pkgbuild::build_result& build = authority.build();
  const pkgimage::inspected_package_image& image = authority.image();
  package_source_record source = project_source(build.request());

  try {
    build_provenance provenance(
        source.identity(),
        translate_build_identity<build_request_identity>(
            build.request().identity()),
        translate_build_identity<build_input_set_identity>(
            build.request().inputs().identity()),
        translate_build_identity<environment_policy_identity>(
            build.request().policy().environment().identity()),
        translate_build_identity<build_policy_identity>(
            build.request().policy().identity()),
        translate_build_identity<build_result_identity>(build.identity()),
        translate_build_identity<payload_manifest_identity>(
            build.payload()->identity()),
        translate_build_identity<build_artifact_identity>(
            build.artifact()->identity()),
        translate_external_identity<artifact_content_identity>(
            image.receipt().archive_digest()),
        translate_build_identity<artifact_binding_identity>(
            *build.artifact_binding()),
        translate_build_identity<execution_evidence_identity>(
            build.execution_evidence()),
        translate_build_identity<build_image_identity>(authority.identity()),
        translate_external_identity<artifact_image_identity>(
            image.image().identity()),
        translate_external_identity<artifact_inspection_identity>(
            image.receipt().identity()));

    return build_authority(std::make_shared<const build_authority::impl>(
        std::move(source), std::move(provenance)));
  } catch (const projection_error&) {
    throw;
  } catch (const error& failure) {
    throw projection_error(
        projection_error_code::identity_translation,
        std::string("cannot construct native build provenance: ") +
            failure.what());
  }
}

} // namespace pkgstate::build_adapter
