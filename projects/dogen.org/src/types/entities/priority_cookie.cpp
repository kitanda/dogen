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
#include "dogen.org/types/entities/priority_cookie.hpp"

namespace dogen::org::entities {

priority_cookie::priority_cookie(const std::string& value)
    : value_(value) { }

const std::string& priority_cookie::value() const {
    return value_;
}

std::string& priority_cookie::value() {
    return value_;
}

void priority_cookie::value(const std::string& v) {
    value_ = v;
}

void priority_cookie::value(const std::string&& v) {
    value_ = std::move(v);
}

bool priority_cookie::operator==(const priority_cookie& rhs) const {
    return value_ == rhs.value_;
}

void priority_cookie::swap(priority_cookie& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

priority_cookie& priority_cookie::operator=(priority_cookie other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
