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
#include "dogen.variability/types/entities/feature_repository.hpp"

namespace dogen::variability::entities {

feature_repository::feature_repository(const std::list<dogen::variability::entities::feature>& features)
    : features_(features) { }

void feature_repository::swap(feature_repository& other) noexcept {
    using std::swap;
    swap(features_, other.features_);
}

bool feature_repository::operator==(const feature_repository& rhs) const {
    return features_ == rhs.features_;
}

feature_repository& feature_repository::operator=(feature_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::variability::entities::feature>& feature_repository::features() const {
    return features_;
}

std::list<dogen::variability::entities::feature>& feature_repository::features() {
    return features_;
}

void feature_repository::features(const std::list<dogen::variability::entities::feature>& v) {
    features_ = v;
}

void feature_repository::features(const std::list<dogen::variability::entities::feature>&& v) {
    features_ = std::move(v);
}

}
