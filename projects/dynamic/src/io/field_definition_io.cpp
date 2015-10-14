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
#include <ostream>
#include "dogen/dynamic/io/name_io.hpp"
#include "dogen/dynamic/io/value_io.hpp"
#include "dogen/dynamic/io/scope_types_io.hpp"
#include "dogen/dynamic/io/value_types_io.hpp"
#include "dogen/dynamic/io/field_definition_io.hpp"
#include "dogen/dynamic/io/ownership_hierarchy_io.hpp"
#include "dogen/dynamic/io/field_definition_types_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::dynamic::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace dynamic {

std::ostream& operator<<(std::ostream& s, const field_definition& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::field_definition\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"value_type\": " << v.value_type() << ", "
      << "\"scope\": " << v.scope() << ", "
      << "\"ownership_hierarchy\": " << v.ownership_hierarchy() << ", "
      << "\"default_value\": " << v.default_value() << ", "
      << "\"definition_type\": " << v.definition_type()
      << " }";
    return(s);
}

} }
