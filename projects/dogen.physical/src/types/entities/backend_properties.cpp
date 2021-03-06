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
    : meta_id_(std::move(rhs.meta_id_)),
      enabled_(std::move(rhs.enabled_)),
      file_path_(std::move(rhs.file_path_)),
      technical_space_version_(std::move(rhs.technical_space_version_)),
      enable_backend_directories_(std::move(rhs.enable_backend_directories_)),
      directory_name_(std::move(rhs.directory_name_)),
      computed_directory_name_(std::move(rhs.computed_directory_name_)) { }

backend_properties::backend_properties(
    const dogen::identification::entities::physical_meta_id& meta_id,
    const bool enabled,
    const boost::filesystem::path& file_path,
    const std::string& technical_space_version,
    const bool enable_backend_directories,
    const std::string& directory_name,
    const std::string& computed_directory_name)
    : meta_id_(meta_id),
      enabled_(enabled),
      file_path_(file_path),
      technical_space_version_(technical_space_version),
      enable_backend_directories_(enable_backend_directories),
      directory_name_(directory_name),
      computed_directory_name_(computed_directory_name) { }

void backend_properties::swap(backend_properties& other) noexcept {
    using std::swap;
    swap(meta_id_, other.meta_id_);
    swap(enabled_, other.enabled_);
    swap(file_path_, other.file_path_);
    swap(technical_space_version_, other.technical_space_version_);
    swap(enable_backend_directories_, other.enable_backend_directories_);
    swap(directory_name_, other.directory_name_);
    swap(computed_directory_name_, other.computed_directory_name_);
}

bool backend_properties::operator==(const backend_properties& rhs) const {
    return meta_id_ == rhs.meta_id_ &&
        enabled_ == rhs.enabled_ &&
        file_path_ == rhs.file_path_ &&
        technical_space_version_ == rhs.technical_space_version_ &&
        enable_backend_directories_ == rhs.enable_backend_directories_ &&
        directory_name_ == rhs.directory_name_ &&
        computed_directory_name_ == rhs.computed_directory_name_;
}

backend_properties& backend_properties::operator=(backend_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_id& backend_properties::meta_id() const {
    return meta_id_;
}

dogen::identification::entities::physical_meta_id& backend_properties::meta_id() {
    return meta_id_;
}

void backend_properties::meta_id(const dogen::identification::entities::physical_meta_id& v) {
    meta_id_ = v;
}

void backend_properties::meta_id(const dogen::identification::entities::physical_meta_id&& v) {
    meta_id_ = std::move(v);
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

bool backend_properties::enable_backend_directories() const {
    return enable_backend_directories_;
}

void backend_properties::enable_backend_directories(const bool v) {
    enable_backend_directories_ = v;
}

const std::string& backend_properties::directory_name() const {
    return directory_name_;
}

std::string& backend_properties::directory_name() {
    return directory_name_;
}

void backend_properties::directory_name(const std::string& v) {
    directory_name_ = v;
}

void backend_properties::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const std::string& backend_properties::computed_directory_name() const {
    return computed_directory_name_;
}

std::string& backend_properties::computed_directory_name() {
    return computed_directory_name_;
}

void backend_properties::computed_directory_name(const std::string& v) {
    computed_directory_name_ = v;
}

void backend_properties::computed_directory_name(const std::string&& v) {
    computed_directory_name_ = std::move(v);
}

}
