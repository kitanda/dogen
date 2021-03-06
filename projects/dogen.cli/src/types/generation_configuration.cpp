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
#include "dogen.cli/types/generation_configuration.hpp"

namespace dogen::cli {

generation_configuration::generation_configuration(generation_configuration&& rhs)
    : reference_model_directories_(std::move(rhs.reference_model_directories_)),
      target_(std::move(rhs.target_)),
      output_directory_(std::move(rhs.output_directory_)) { }

generation_configuration::generation_configuration(
    const std::vector<boost::filesystem::path>& reference_model_directories,
    const boost::filesystem::path& target,
    const boost::filesystem::path& output_directory)
    : reference_model_directories_(reference_model_directories),
      target_(target),
      output_directory_(output_directory) { }

void generation_configuration::swap(generation_configuration& other) noexcept {
    using std::swap;
    swap(reference_model_directories_, other.reference_model_directories_);
    swap(target_, other.target_);
    swap(output_directory_, other.output_directory_);
}

bool generation_configuration::operator==(const generation_configuration& rhs) const {
    return reference_model_directories_ == rhs.reference_model_directories_ &&
        target_ == rhs.target_ &&
        output_directory_ == rhs.output_directory_;
}

generation_configuration& generation_configuration::operator=(generation_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<boost::filesystem::path>& generation_configuration::reference_model_directories() const {
    return reference_model_directories_;
}

std::vector<boost::filesystem::path>& generation_configuration::reference_model_directories() {
    return reference_model_directories_;
}

generation_configuration& generation_configuration::reference_model_directories(const std::vector<boost::filesystem::path>& v) {
    reference_model_directories_ = v;
    return *this;
}

generation_configuration& generation_configuration::reference_model_directories(const std::vector<boost::filesystem::path>&& v) {
    reference_model_directories_ = std::move(v);
    return *this;
}

const boost::filesystem::path& generation_configuration::target() const {
    return target_;
}

boost::filesystem::path& generation_configuration::target() {
    return target_;
}

generation_configuration& generation_configuration::target(const boost::filesystem::path& v) {
    target_ = v;
    return *this;
}

generation_configuration& generation_configuration::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
    return *this;
}

const boost::filesystem::path& generation_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& generation_configuration::output_directory() {
    return output_directory_;
}

generation_configuration& generation_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

generation_configuration& generation_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

}
