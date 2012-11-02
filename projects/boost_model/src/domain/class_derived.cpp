/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <ostream>
#include "dogen/boost_model/domain/class_derived.hpp"
#include "dogen/boost_model/io/class_base_io.hpp"

namespace dogen {
namespace boost_model {

class_derived::class_derived()
    : prop_1_(static_cast<int>(0)) { }

class_derived::class_derived(
    const int prop_0,
    const dogen::boost_model::versioned_key& versioned_key,
    const int prop_1)
    : dogen::boost_model::class_base(prop_0,
      versioned_key),
      prop_1_(prop_1) { }

void class_derived::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"class_derived\"" << ", "
      << "\"__parent_0__\": ";
    class_base::to_stream(s);
    s << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void class_derived::swap(class_derived& other) noexcept {
    class_base::swap(other);

    using std::swap;
    swap(prop_1_, other.prop_1_);
}

bool class_derived::equals(const dogen::boost_model::class_base& other) const {
    const class_derived* const p(dynamic_cast<const class_derived* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool class_derived::operator==(const class_derived& rhs) const {
    return class_base::operator==(rhs) &&
        prop_1_ == rhs.prop_1_;
}

class_derived& class_derived::operator=(class_derived other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }