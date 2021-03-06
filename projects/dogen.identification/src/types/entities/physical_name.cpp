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
#include "dogen.identification/types/entities/physical_name.hpp"

namespace dogen::identification::entities {

physical_name::physical_name(
    const std::string& simple,
    const dogen::identification::entities::physical_id& id)
    : simple_(simple),
      id_(id) { }

void physical_name::swap(physical_name& other) noexcept {
    using std::swap;
    swap(simple_, other.simple_);
    swap(id_, other.id_);
}

bool physical_name::operator==(const physical_name& rhs) const {
    return simple_ == rhs.simple_ &&
        id_ == rhs.id_;
}

physical_name& physical_name::operator=(physical_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& physical_name::simple() const {
    return simple_;
}

std::string& physical_name::simple() {
    return simple_;
}

void physical_name::simple(const std::string& v) {
    simple_ = v;
}

void physical_name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const dogen::identification::entities::physical_id& physical_name::id() const {
    return id_;
}

dogen::identification::entities::physical_id& physical_name::id() {
    return id_;
}

void physical_name::id(const dogen::identification::entities::physical_id& v) {
    id_ = v;
}

void physical_name::id(const dogen::identification::entities::physical_id&& v) {
    id_ = std::move(v);
}

}
