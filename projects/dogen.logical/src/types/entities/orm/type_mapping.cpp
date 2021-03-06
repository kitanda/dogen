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
#include "dogen.logical/types/entities/orm/type_mapping.hpp"

namespace dogen::logical::entities::orm {

type_mapping::type_mapping(type_mapping&& rhs)
    : source_type_(std::move(rhs.source_type_)),
      destination_type_(std::move(rhs.destination_type_)),
      to_source_type_(std::move(rhs.to_source_type_)),
      to_destination_type_(std::move(rhs.to_destination_type_)),
      database_(std::move(rhs.database_)) { }

type_mapping::type_mapping(
    const std::string& source_type,
    const std::string& destination_type,
    const std::string& to_source_type,
    const std::string& to_destination_type,
    const boost::optional<dogen::logical::entities::orm::database_system>& database)
    : source_type_(source_type),
      destination_type_(destination_type),
      to_source_type_(to_source_type),
      to_destination_type_(to_destination_type),
      database_(database) { }

void type_mapping::swap(type_mapping& other) noexcept {
    using std::swap;
    swap(source_type_, other.source_type_);
    swap(destination_type_, other.destination_type_);
    swap(to_source_type_, other.to_source_type_);
    swap(to_destination_type_, other.to_destination_type_);
    swap(database_, other.database_);
}

bool type_mapping::operator==(const type_mapping& rhs) const {
    return source_type_ == rhs.source_type_ &&
        destination_type_ == rhs.destination_type_ &&
        to_source_type_ == rhs.to_source_type_ &&
        to_destination_type_ == rhs.to_destination_type_ &&
        database_ == rhs.database_;
}

type_mapping& type_mapping::operator=(type_mapping other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& type_mapping::source_type() const {
    return source_type_;
}

std::string& type_mapping::source_type() {
    return source_type_;
}

void type_mapping::source_type(const std::string& v) {
    source_type_ = v;
}

void type_mapping::source_type(const std::string&& v) {
    source_type_ = std::move(v);
}

const std::string& type_mapping::destination_type() const {
    return destination_type_;
}

std::string& type_mapping::destination_type() {
    return destination_type_;
}

void type_mapping::destination_type(const std::string& v) {
    destination_type_ = v;
}

void type_mapping::destination_type(const std::string&& v) {
    destination_type_ = std::move(v);
}

const std::string& type_mapping::to_source_type() const {
    return to_source_type_;
}

std::string& type_mapping::to_source_type() {
    return to_source_type_;
}

void type_mapping::to_source_type(const std::string& v) {
    to_source_type_ = v;
}

void type_mapping::to_source_type(const std::string&& v) {
    to_source_type_ = std::move(v);
}

const std::string& type_mapping::to_destination_type() const {
    return to_destination_type_;
}

std::string& type_mapping::to_destination_type() {
    return to_destination_type_;
}

void type_mapping::to_destination_type(const std::string& v) {
    to_destination_type_ = v;
}

void type_mapping::to_destination_type(const std::string&& v) {
    to_destination_type_ = std::move(v);
}

const boost::optional<dogen::logical::entities::orm::database_system>& type_mapping::database() const {
    return database_;
}

boost::optional<dogen::logical::entities::orm::database_system>& type_mapping::database() {
    return database_;
}

void type_mapping::database(const boost::optional<dogen::logical::entities::orm::database_system>& v) {
    database_ = v;
}

void type_mapping::database(const boost::optional<dogen::logical::entities::orm::database_system>&& v) {
    database_ = std::move(v);
}

}
