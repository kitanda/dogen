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
#include "dogen.physical/io/entities/relation_status_io.hpp"

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const relation_status& v) {
    s << "{ " << "\"__type__\": " << "\"relation_status\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case relation_status::invalid:
        attr = "\"invalid\"";
        break;
    case relation_status::not_relatable:
        attr = "\"not_relatable\"";
        break;
    case relation_status::relatable:
        attr = "\"relatable\"";
        break;
    case relation_status::facet_default:
        attr = "\"facet_default\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for relation_status");
    }
    s << attr << " }";
    return s;
}

}
