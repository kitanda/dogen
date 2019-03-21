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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, masd::dogen::coding::meta_model::name>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace masd::dogen::coding::meta_model {

modeline_group::modeline_group(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const bool is_element_extension,
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<masd::dogen::coding::meta_model::local_decoration>& decoration,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::name>& modelines_for_meta_element)
    : masd::dogen::coding::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      decoration),
      modelines_for_meta_element_(modelines_for_meta_element) { }

void modeline_group::accept(const element_visitor& v) const {
    v.visit(*this);
}

void modeline_group::accept(element_visitor& v) const {
    v.visit(*this);
    }

void modeline_group::accept(const element_visitor& v) {
    v.visit(*this);
}

void modeline_group::accept(element_visitor& v) {
    v.visit(*this);
}

void modeline_group::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::meta_model::modeline_group\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"modelines_for_meta_element\": " << modelines_for_meta_element_
      << " }";
}

void modeline_group::swap(modeline_group& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(modelines_for_meta_element_, other.modelines_for_meta_element_);
}

bool modeline_group::equals(const masd::dogen::coding::meta_model::element& other) const {
    const modeline_group* const p(dynamic_cast<const modeline_group* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool modeline_group::operator==(const modeline_group& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        modelines_for_meta_element_ == rhs.modelines_for_meta_element_;
}

modeline_group& modeline_group::operator=(modeline_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, masd::dogen::coding::meta_model::name>& modeline_group::modelines_for_meta_element() const {
    return modelines_for_meta_element_;
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::name>& modeline_group::modelines_for_meta_element() {
    return modelines_for_meta_element_;
}

void modeline_group::modelines_for_meta_element(const std::unordered_map<std::string, masd::dogen::coding::meta_model::name>& v) {
    modelines_for_meta_element_ = v;
}

void modeline_group::modelines_for_meta_element(const std::unordered_map<std::string, masd::dogen::coding::meta_model::name>&& v) {
    modelines_for_meta_element_ = std::move(v);
}

}