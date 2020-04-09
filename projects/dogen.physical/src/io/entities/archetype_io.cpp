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
#include <boost/algorithm/string.hpp>
#include "dogen.physical/io/entities/archetype_io.hpp"
#include "dogen.physical/io/entities/meta_name_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const archetype& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::archetype\"" << ", "
      << "\"description\": " << "\"" << tidy_up_string(v.description()) << "\"" << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"default_postfix\": " << "\"" << tidy_up_string(v.default_postfix()) << "\"" << ", "
      << "\"override_postfix\": " << "\"" << tidy_up_string(v.override_postfix()) << "\"" << ", "
      << "\"archetype_kind_id\": " << "\"" << tidy_up_string(v.archetype_kind_id()) << "\"" << ", "
      << "\"meta_element_id\": " << "\"" << tidy_up_string(v.meta_element_id()) << "\"" << ", "
      << "\"part\": " << "\"" << tidy_up_string(v.part()) << "\""
      << " }";
    return(s);
}

}
