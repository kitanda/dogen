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
#include "dogen.assets/types/meta_model/orm/primitive_properties.hpp"

namespace dogen::assets::meta_model::orm {

primitive_properties::primitive_properties()
    : generate_mapping_(static_cast<bool>(0)) { }

primitive_properties::primitive_properties(primitive_properties&& rhs)
    : odb_options_(std::move(rhs.odb_options_)),
      schema_name_(std::move(rhs.schema_name_)),
      capitalised_schema_name_(std::move(rhs.capitalised_schema_name_)),
      letter_case_(std::move(rhs.letter_case_)),
      generate_mapping_(std::move(rhs.generate_mapping_)),
      type_mappings_(std::move(rhs.type_mappings_)),
      odb_pragmas_(std::move(rhs.odb_pragmas_)),
      type_overrides_(std::move(rhs.type_overrides_)) { }

primitive_properties::primitive_properties(
    const dogen::assets::meta_model::orm::odb_options& odb_options,
    const std::string& schema_name,
    const std::string& capitalised_schema_name,
    const boost::optional<dogen::assets::meta_model::orm::letter_case>& letter_case,
    const bool generate_mapping,
    const std::list<dogen::assets::meta_model::orm::type_mapping>& type_mappings,
    const std::list<std::string>& odb_pragmas,
    const std::unordered_map<dogen::assets::meta_model::orm::database_system, std::string>& type_overrides)
    : odb_options_(odb_options),
      schema_name_(schema_name),
      capitalised_schema_name_(capitalised_schema_name),
      letter_case_(letter_case),
      generate_mapping_(generate_mapping),
      type_mappings_(type_mappings),
      odb_pragmas_(odb_pragmas),
      type_overrides_(type_overrides) { }

void primitive_properties::swap(primitive_properties& other) noexcept {
    using std::swap;
    swap(odb_options_, other.odb_options_);
    swap(schema_name_, other.schema_name_);
    swap(capitalised_schema_name_, other.capitalised_schema_name_);
    swap(letter_case_, other.letter_case_);
    swap(generate_mapping_, other.generate_mapping_);
    swap(type_mappings_, other.type_mappings_);
    swap(odb_pragmas_, other.odb_pragmas_);
    swap(type_overrides_, other.type_overrides_);
}

bool primitive_properties::operator==(const primitive_properties& rhs) const {
    return odb_options_ == rhs.odb_options_ &&
        schema_name_ == rhs.schema_name_ &&
        capitalised_schema_name_ == rhs.capitalised_schema_name_ &&
        letter_case_ == rhs.letter_case_ &&
        generate_mapping_ == rhs.generate_mapping_ &&
        type_mappings_ == rhs.type_mappings_ &&
        odb_pragmas_ == rhs.odb_pragmas_ &&
        type_overrides_ == rhs.type_overrides_;
}

primitive_properties& primitive_properties::operator=(primitive_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::assets::meta_model::orm::odb_options& primitive_properties::odb_options() const {
    return odb_options_;
}

dogen::assets::meta_model::orm::odb_options& primitive_properties::odb_options() {
    return odb_options_;
}

void primitive_properties::odb_options(const dogen::assets::meta_model::orm::odb_options& v) {
    odb_options_ = v;
}

void primitive_properties::odb_options(const dogen::assets::meta_model::orm::odb_options&& v) {
    odb_options_ = std::move(v);
}

const std::string& primitive_properties::schema_name() const {
    return schema_name_;
}

std::string& primitive_properties::schema_name() {
    return schema_name_;
}

void primitive_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void primitive_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::string& primitive_properties::capitalised_schema_name() const {
    return capitalised_schema_name_;
}

std::string& primitive_properties::capitalised_schema_name() {
    return capitalised_schema_name_;
}

void primitive_properties::capitalised_schema_name(const std::string& v) {
    capitalised_schema_name_ = v;
}

void primitive_properties::capitalised_schema_name(const std::string&& v) {
    capitalised_schema_name_ = std::move(v);
}

const boost::optional<dogen::assets::meta_model::orm::letter_case>& primitive_properties::letter_case() const {
    return letter_case_;
}

boost::optional<dogen::assets::meta_model::orm::letter_case>& primitive_properties::letter_case() {
    return letter_case_;
}

void primitive_properties::letter_case(const boost::optional<dogen::assets::meta_model::orm::letter_case>& v) {
    letter_case_ = v;
}

void primitive_properties::letter_case(const boost::optional<dogen::assets::meta_model::orm::letter_case>&& v) {
    letter_case_ = std::move(v);
}

bool primitive_properties::generate_mapping() const {
    return generate_mapping_;
}

void primitive_properties::generate_mapping(const bool v) {
    generate_mapping_ = v;
}

const std::list<dogen::assets::meta_model::orm::type_mapping>& primitive_properties::type_mappings() const {
    return type_mappings_;
}

std::list<dogen::assets::meta_model::orm::type_mapping>& primitive_properties::type_mappings() {
    return type_mappings_;
}

void primitive_properties::type_mappings(const std::list<dogen::assets::meta_model::orm::type_mapping>& v) {
    type_mappings_ = v;
}

void primitive_properties::type_mappings(const std::list<dogen::assets::meta_model::orm::type_mapping>&& v) {
    type_mappings_ = std::move(v);
}

const std::list<std::string>& primitive_properties::odb_pragmas() const {
    return odb_pragmas_;
}

std::list<std::string>& primitive_properties::odb_pragmas() {
    return odb_pragmas_;
}

void primitive_properties::odb_pragmas(const std::list<std::string>& v) {
    odb_pragmas_ = v;
}

void primitive_properties::odb_pragmas(const std::list<std::string>&& v) {
    odb_pragmas_ = std::move(v);
}

const std::unordered_map<dogen::assets::meta_model::orm::database_system, std::string>& primitive_properties::type_overrides() const {
    return type_overrides_;
}

std::unordered_map<dogen::assets::meta_model::orm::database_system, std::string>& primitive_properties::type_overrides() {
    return type_overrides_;
}

void primitive_properties::type_overrides(const std::unordered_map<dogen::assets::meta_model::orm::database_system, std::string>& v) {
    type_overrides_ = v;
}

void primitive_properties::type_overrides(const std::unordered_map<dogen::assets::meta_model::orm::database_system, std::string>&& v) {
    type_overrides_ = std::move(v);
}

}
