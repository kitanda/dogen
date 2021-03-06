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
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::artefact>& lhs,
const boost::shared_ptr<dogen::physical::entities::artefact>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::physical::entities {

region::region()
    : is_generatable_(static_cast<bool>(0)) { }

region::region(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const dogen::identification::entities::logical_provenance& provenance,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts_by_archetype,
    const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& archetype_for_role,
    const bool is_generatable)
    : configuration_(configuration),
      provenance_(provenance),
      artefacts_by_archetype_(artefacts_by_archetype),
      archetype_for_role_(archetype_for_role),
      is_generatable_(is_generatable) { }

void region::swap(region& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(provenance_, other.provenance_);
    swap(artefacts_by_archetype_, other.artefacts_by_archetype_);
    swap(archetype_for_role_, other.archetype_for_role_);
    swap(is_generatable_, other.is_generatable_);
}

bool region::operator==(const region& rhs) const {
    return configuration_ == rhs.configuration_ &&
        provenance_ == rhs.provenance_ &&
        artefacts_by_archetype_ == rhs.artefacts_by_archetype_ &&
        archetype_for_role_ == rhs.archetype_for_role_ &&
        is_generatable_ == rhs.is_generatable_;
}

region& region::operator=(region other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::variability::entities::configuration>& region::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& region::configuration() {
    return configuration_;
}

void region::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void region::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::identification::entities::logical_provenance& region::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& region::provenance() {
    return provenance_;
}

void region::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void region::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& region::artefacts_by_archetype() const {
    return artefacts_by_archetype_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& region::artefacts_by_archetype() {
    return artefacts_by_archetype_;
}

void region::artefacts_by_archetype(const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& v) {
    artefacts_by_archetype_ = v;
}

void region::artefacts_by_archetype(const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >&& v) {
    artefacts_by_archetype_ = std::move(v);
}

const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& region::archetype_for_role() const {
    return archetype_for_role_;
}

std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& region::archetype_for_role() {
    return archetype_for_role_;
}

void region::archetype_for_role(const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& v) {
    archetype_for_role_ = v;
}

void region::archetype_for_role(const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>&& v) {
    archetype_for_role_ = std::move(v);
}

bool region::is_generatable() const {
    return is_generatable_;
}

void region::is_generatable(const bool v) {
    is_generatable_ = v;
}

}
