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
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/variability/initializer.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

initializer::initializer(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
    const std::list<dogen::assets::meta_model::name>& feature_template_bundles,
    const std::list<dogen::assets::meta_model::name>& feature_bundles)
    : dogen::assets::meta_model::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      archetype_location_properties,
      decoration),
      feature_template_bundles_(feature_template_bundles),
      feature_bundles_(feature_bundles) { }

void initializer::accept(const element_visitor& v) const {
    v.visit(*this);
}

void initializer::accept(element_visitor& v) const {
    v.visit(*this);
    }

void initializer::accept(const element_visitor& v) {
    v.visit(*this);
}

void initializer::accept(element_visitor& v) {
    v.visit(*this);
}

void initializer::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::initializer\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"feature_template_bundles\": " << feature_template_bundles_ << ", "
      << "\"feature_bundles\": " << feature_bundles_
      << " }";
}

void initializer::swap(initializer& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(feature_template_bundles_, other.feature_template_bundles_);
    swap(feature_bundles_, other.feature_bundles_);
}

bool initializer::equals(const dogen::assets::meta_model::element& other) const {
    const initializer* const p(dynamic_cast<const initializer* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool initializer::operator==(const initializer& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        feature_template_bundles_ == rhs.feature_template_bundles_ &&
        feature_bundles_ == rhs.feature_bundles_;
}

initializer& initializer::operator=(initializer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::assets::meta_model::name>& initializer::feature_template_bundles() const {
    return feature_template_bundles_;
}

std::list<dogen::assets::meta_model::name>& initializer::feature_template_bundles() {
    return feature_template_bundles_;
}

void initializer::feature_template_bundles(const std::list<dogen::assets::meta_model::name>& v) {
    feature_template_bundles_ = v;
}

void initializer::feature_template_bundles(const std::list<dogen::assets::meta_model::name>&& v) {
    feature_template_bundles_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& initializer::feature_bundles() const {
    return feature_bundles_;
}

std::list<dogen::assets::meta_model::name>& initializer::feature_bundles() {
    return feature_bundles_;
}

void initializer::feature_bundles(const std::list<dogen::assets::meta_model::name>& v) {
    feature_bundles_ = v;
}

void initializer::feature_bundles(const std::list<dogen::assets::meta_model::name>&& v) {
    feature_bundles_ = std::move(v);
}

}