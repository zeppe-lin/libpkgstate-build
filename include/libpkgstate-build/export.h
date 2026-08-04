// SPDX-FileCopyrightText: 2026 Alexandr Savca
// SPDX-License-Identifier: GPL-3.0-or-later

/*! \file export.h
 *  \brief Public symbol-visibility contract for libpkgstate-build.
 */
#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(PKGSTATE_BUILD_BUILDING_LIBRARY)
#define PKGSTATE_BUILD_API __declspec(dllexport)
#else
#define PKGSTATE_BUILD_API __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define PKGSTATE_BUILD_API __attribute__((visibility("default")))
#else
#define PKGSTATE_BUILD_API
#endif
