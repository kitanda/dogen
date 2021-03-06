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
#include "dogen.cli/types/conversion_configuration.hpp"

namespace dogen::cli {

conversion_configuration::conversion_configuration(conversion_configuration&& rhs)
    : source_(std::move(rhs.source_)),
      destination_(std::move(rhs.destination_)) { }

conversion_configuration::conversion_configuration(
    const boost::filesystem::path& source,
    const std::string& destination)
    : source_(source),
      destination_(destination) { }

void conversion_configuration::swap(conversion_configuration& other) noexcept {
    using std::swap;
    swap(source_, other.source_);
    swap(destination_, other.destination_);
}

bool conversion_configuration::operator==(const conversion_configuration& rhs) const {
    return source_ == rhs.source_ &&
        destination_ == rhs.destination_;
}

conversion_configuration& conversion_configuration::operator=(conversion_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& conversion_configuration::source() const {
    return source_;
}

boost::filesystem::path& conversion_configuration::source() {
    return source_;
}

conversion_configuration& conversion_configuration::source(const boost::filesystem::path& v) {
    source_ = v;
    return *this;
}

conversion_configuration& conversion_configuration::source(const boost::filesystem::path&& v) {
    source_ = std::move(v);
    return *this;
}

const std::string& conversion_configuration::destination() const {
    return destination_;
}

std::string& conversion_configuration::destination() {
    return destination_;
}

conversion_configuration& conversion_configuration::destination(const std::string& v) {
    destination_ = v;
    return *this;
}

conversion_configuration& conversion_configuration::destination(const std::string&& v) {
    destination_ = std::move(v);
    return *this;
}

}
