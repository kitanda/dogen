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
#include "dogen.logical/types/entities/orm/odb_targets.hpp"

namespace dogen::logical::entities::orm {

odb_targets::odb_targets(
    const std::string& main_target_name,
    const std::string& common_odb_options,
    const std::list<dogen::logical::entities::orm::odb_target>& targets)
    : main_target_name_(main_target_name),
      common_odb_options_(common_odb_options),
      targets_(targets) { }

void odb_targets::swap(odb_targets& other) noexcept {
    using std::swap;
    swap(main_target_name_, other.main_target_name_);
    swap(common_odb_options_, other.common_odb_options_);
    swap(targets_, other.targets_);
}

bool odb_targets::operator==(const odb_targets& rhs) const {
    return main_target_name_ == rhs.main_target_name_ &&
        common_odb_options_ == rhs.common_odb_options_ &&
        targets_ == rhs.targets_;
}

odb_targets& odb_targets::operator=(odb_targets other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& odb_targets::main_target_name() const {
    return main_target_name_;
}

std::string& odb_targets::main_target_name() {
    return main_target_name_;
}

void odb_targets::main_target_name(const std::string& v) {
    main_target_name_ = v;
}

void odb_targets::main_target_name(const std::string&& v) {
    main_target_name_ = std::move(v);
}

const std::string& odb_targets::common_odb_options() const {
    return common_odb_options_;
}

std::string& odb_targets::common_odb_options() {
    return common_odb_options_;
}

void odb_targets::common_odb_options(const std::string& v) {
    common_odb_options_ = v;
}

void odb_targets::common_odb_options(const std::string&& v) {
    common_odb_options_ = std::move(v);
}

const std::list<dogen::logical::entities::orm::odb_target>& odb_targets::targets() const {
    return targets_;
}

std::list<dogen::logical::entities::orm::odb_target>& odb_targets::targets() {
    return targets_;
}

void odb_targets::targets(const std::list<dogen::logical::entities::orm::odb_target>& v) {
    targets_ = v;
}

void odb_targets::targets(const std::list<dogen::logical::entities::orm::odb_target>&& v) {
    targets_ = std::move(v);
}

}
