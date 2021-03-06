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
#include "dogen/types/diffing_configuration.hpp"

namespace dogen {

diffing_configuration::diffing_configuration()
    : destination_(static_cast<dogen::diffing_destination>(0)) { }

diffing_configuration::diffing_configuration(diffing_configuration&& rhs)
    : destination_(std::move(rhs.destination_)),
      output_directory_(std::move(rhs.output_directory_)) { }

diffing_configuration::diffing_configuration(
    const dogen::diffing_destination destination,
    const boost::filesystem::path& output_directory)
    : destination_(destination),
      output_directory_(output_directory) { }

void diffing_configuration::swap(diffing_configuration& other) noexcept {
    using std::swap;
    swap(destination_, other.destination_);
    swap(output_directory_, other.output_directory_);
}

bool diffing_configuration::operator==(const diffing_configuration& rhs) const {
    return destination_ == rhs.destination_ &&
        output_directory_ == rhs.output_directory_;
}

diffing_configuration& diffing_configuration::operator=(diffing_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::diffing_destination diffing_configuration::destination() const {
    return destination_;
}

diffing_configuration& diffing_configuration::destination(const dogen::diffing_destination v) {
    destination_ = v;
    return *this;
}

const boost::filesystem::path& diffing_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& diffing_configuration::output_directory() {
    return output_directory_;
}

diffing_configuration& diffing_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

diffing_configuration& diffing_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

}
