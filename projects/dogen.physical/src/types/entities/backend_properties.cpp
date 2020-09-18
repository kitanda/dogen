/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen.physical/types/entities/backend_properties.hpp"

namespace dogen::physical::entities {

backend_properties::backend_properties()
    : enabled_(static_cast<bool>(0)),
      enable_backend_directories_(static_cast<bool>(0)) { }

backend_properties::backend_properties(backend_properties&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      file_path_(std::move(rhs.file_path_)),
      technical_space_version_(std::move(rhs.technical_space_version_)),
      directory_(std::move(rhs.directory_)),
      enable_backend_directories_(std::move(rhs.enable_backend_directories_)) { }

backend_properties::backend_properties(
    const bool enabled,
    const boost::filesystem::path& file_path,
    const std::string& technical_space_version,
    const std::string& directory,
    const bool enable_backend_directories)
    : enabled_(enabled),
      file_path_(file_path),
      technical_space_version_(technical_space_version),
      directory_(directory),
      enable_backend_directories_(enable_backend_directories) { }

void backend_properties::swap(backend_properties& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(file_path_, other.file_path_);
    swap(technical_space_version_, other.technical_space_version_);
    swap(directory_, other.directory_);
    swap(enable_backend_directories_, other.enable_backend_directories_);
}

bool backend_properties::operator==(const backend_properties& rhs) const {
    return enabled_ == rhs.enabled_ &&
        file_path_ == rhs.file_path_ &&
        technical_space_version_ == rhs.technical_space_version_ &&
        directory_ == rhs.directory_ &&
        enable_backend_directories_ == rhs.enable_backend_directories_;
}

backend_properties& backend_properties::operator=(backend_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool backend_properties::enabled() const {
    return enabled_;
}

void backend_properties::enabled(const bool v) {
    enabled_ = v;
}

const boost::filesystem::path& backend_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& backend_properties::file_path() {
    return file_path_;
}

void backend_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void backend_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& backend_properties::technical_space_version() const {
    return technical_space_version_;
}

std::string& backend_properties::technical_space_version() {
    return technical_space_version_;
}

void backend_properties::technical_space_version(const std::string& v) {
    technical_space_version_ = v;
}

void backend_properties::technical_space_version(const std::string&& v) {
    technical_space_version_ = std::move(v);
}

const std::string& backend_properties::directory() const {
    return directory_;
}

std::string& backend_properties::directory() {
    return directory_;
}

void backend_properties::directory(const std::string& v) {
    directory_ = v;
}

void backend_properties::directory(const std::string&& v) {
    directory_ = std::move(v);
}

bool backend_properties::enable_backend_directories() const {
    return enable_backend_directories_;
}

void backend_properties::enable_backend_directories(const bool v) {
    enable_backend_directories_ = v;
}

}
