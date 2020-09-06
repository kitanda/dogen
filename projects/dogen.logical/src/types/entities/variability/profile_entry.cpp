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
#include <ostream>
#include "dogen.logical/types/entities/variability/profile_entry.hpp"
#include "dogen.logical/io/entities/variability/abstract_profile_entry_io.hpp"

namespace dogen::logical::entities::variability {

profile_entry::profile_entry(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const dogen::identification::entities::logical_name& name,
    const std::string& original_key,
    const std::string& key,
    const std::list<std::string>& value)
    : dogen::logical::entities::variability::abstract_profile_entry(
      documentation,
      configuration,
      name,
      original_key,
      key,
      value) { }

void profile_entry::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::variability::profile_entry\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::variability::abstract_profile_entry::to_stream(s);
    s << " }";
}

void profile_entry::swap(profile_entry& other) noexcept {
    dogen::logical::entities::variability::abstract_profile_entry::swap(other);

}

bool profile_entry::equals(const dogen::logical::entities::variability::abstract_profile_entry& other) const {
    const profile_entry* const p(dynamic_cast<const profile_entry* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool profile_entry::operator==(const profile_entry& rhs) const {
    return dogen::logical::entities::variability::abstract_profile_entry::compare(rhs);
}

profile_entry& profile_entry::operator=(profile_entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
