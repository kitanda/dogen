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
#include "dogen.variability/types/entities/feature_template_repository.hpp"

namespace dogen::variability::entities {

feature_template_repository::feature_template_repository(const std::list<dogen::variability::entities::feature_template>& templates)
    : templates_(templates) { }

void feature_template_repository::swap(feature_template_repository& other) noexcept {
    using std::swap;
    swap(templates_, other.templates_);
}

bool feature_template_repository::operator==(const feature_template_repository& rhs) const {
    return templates_ == rhs.templates_;
}

feature_template_repository& feature_template_repository::operator=(feature_template_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::variability::entities::feature_template>& feature_template_repository::templates() const {
    return templates_;
}

std::list<dogen::variability::entities::feature_template>& feature_template_repository::templates() {
    return templates_;
}

void feature_template_repository::templates(const std::list<dogen::variability::entities::feature_template>& v) {
    templates_ = v;
}

void feature_template_repository::templates(const std::list<dogen::variability::entities::feature_template>&& v) {
    templates_ = std::move(v);
}

}
