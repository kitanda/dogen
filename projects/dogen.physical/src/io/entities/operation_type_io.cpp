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
#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen.physical/io/entities/operation_type_io.hpp"

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const operation_type& v) {
    s << "{ " << "\"__type__\": " << "\"operation_type\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case operation_type::invalid:
        attr = "\"invalid\"";
        break;
    case operation_type::create_only:
        attr = "\"create_only\"";
        break;
    case operation_type::write:
        attr = "\"write\"";
        break;
    case operation_type::ignore:
        attr = "\"ignore\"";
        break;
    case operation_type::remove:
        attr = "\"remove\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for operation_type");
    }
    s << attr << " }";
    return s;
}

}
