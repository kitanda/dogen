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
#include "dogen.physical/types/entities/facet_properties.hpp"

namespace dogen::physical::entities {

facet_properties::facet_properties()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)) { }

facet_properties::facet_properties(
    const dogen::identification::entities::physical_meta_id& meta_id,
    const bool enabled,
    const bool overwrite,
    const std::string& directory_name,
    const std::string& computed_directory_name,
    const std::string& postfix,
    const std::string& computed_postfix)
    : meta_id_(meta_id),
      enabled_(enabled),
      overwrite_(overwrite),
      directory_name_(directory_name),
      computed_directory_name_(computed_directory_name),
      postfix_(postfix),
      computed_postfix_(computed_postfix) { }

void facet_properties::swap(facet_properties& other) noexcept {
    using std::swap;
    swap(meta_id_, other.meta_id_);
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(directory_name_, other.directory_name_);
    swap(computed_directory_name_, other.computed_directory_name_);
    swap(postfix_, other.postfix_);
    swap(computed_postfix_, other.computed_postfix_);
}

bool facet_properties::operator==(const facet_properties& rhs) const {
    return meta_id_ == rhs.meta_id_ &&
        enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        directory_name_ == rhs.directory_name_ &&
        computed_directory_name_ == rhs.computed_directory_name_ &&
        postfix_ == rhs.postfix_ &&
        computed_postfix_ == rhs.computed_postfix_;
}

facet_properties& facet_properties::operator=(facet_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_id& facet_properties::meta_id() const {
    return meta_id_;
}

dogen::identification::entities::physical_meta_id& facet_properties::meta_id() {
    return meta_id_;
}

void facet_properties::meta_id(const dogen::identification::entities::physical_meta_id& v) {
    meta_id_ = v;
}

void facet_properties::meta_id(const dogen::identification::entities::physical_meta_id&& v) {
    meta_id_ = std::move(v);
}

bool facet_properties::enabled() const {
    return enabled_;
}

void facet_properties::enabled(const bool v) {
    enabled_ = v;
}

bool facet_properties::overwrite() const {
    return overwrite_;
}

void facet_properties::overwrite(const bool v) {
    overwrite_ = v;
}

const std::string& facet_properties::directory_name() const {
    return directory_name_;
}

std::string& facet_properties::directory_name() {
    return directory_name_;
}

void facet_properties::directory_name(const std::string& v) {
    directory_name_ = v;
}

void facet_properties::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const std::string& facet_properties::computed_directory_name() const {
    return computed_directory_name_;
}

std::string& facet_properties::computed_directory_name() {
    return computed_directory_name_;
}

void facet_properties::computed_directory_name(const std::string& v) {
    computed_directory_name_ = v;
}

void facet_properties::computed_directory_name(const std::string&& v) {
    computed_directory_name_ = std::move(v);
}

const std::string& facet_properties::postfix() const {
    return postfix_;
}

std::string& facet_properties::postfix() {
    return postfix_;
}

void facet_properties::postfix(const std::string& v) {
    postfix_ = v;
}

void facet_properties::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

const std::string& facet_properties::computed_postfix() const {
    return computed_postfix_;
}

std::string& facet_properties::computed_postfix() {
    return computed_postfix_;
}

void facet_properties::computed_postfix(const std::string& v) {
    computed_postfix_ = v;
}

void facet_properties::computed_postfix(const std::string&& v) {
    computed_postfix_ = std::move(v);
}

}
