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
#include "dogen.physical/types/entities/archetype_kind.hpp"

namespace dogen::physical::entities {

archetype_kind::archetype_kind(
    const std::string& description,
    const std::string& id,
    const std::string& file_extension)
    : description_(description),
      id_(id),
      file_extension_(file_extension) { }

void archetype_kind::swap(archetype_kind& other) noexcept {
    using std::swap;
    swap(description_, other.description_);
    swap(id_, other.id_);
    swap(file_extension_, other.file_extension_);
}

bool archetype_kind::operator==(const archetype_kind& rhs) const {
    return description_ == rhs.description_ &&
        id_ == rhs.id_ &&
        file_extension_ == rhs.file_extension_;
}

archetype_kind& archetype_kind::operator=(archetype_kind other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archetype_kind::description() const {
    return description_;
}

std::string& archetype_kind::description() {
    return description_;
}

void archetype_kind::description(const std::string& v) {
    description_ = v;
}

void archetype_kind::description(const std::string&& v) {
    description_ = std::move(v);
}

const std::string& archetype_kind::id() const {
    return id_;
}

std::string& archetype_kind::id() {
    return id_;
}

void archetype_kind::id(const std::string& v) {
    id_ = v;
}

void archetype_kind::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::string& archetype_kind::file_extension() const {
    return file_extension_;
}

std::string& archetype_kind::file_extension() {
    return file_extension_;
}

void archetype_kind::file_extension(const std::string& v) {
    file_extension_ = v;
}

void archetype_kind::file_extension(const std::string&& v) {
    file_extension_ = std::move(v);
}

}
