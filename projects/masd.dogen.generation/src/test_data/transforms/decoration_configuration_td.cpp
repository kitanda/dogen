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
#include <sstream>
#include "masd.dogen.generation/test_data/transforms/decoration_configuration_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

boost::optional<bool>
create_boost_optional_bool(unsigned int position) {
    boost::optional<bool> r(
        create_bool(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace masd::dogen::generation::transforms {

decoration_configuration_generator::decoration_configuration_generator() : position_(0) { }

void decoration_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_boost_optional_bool(position + 0));
    v.copyright_notices(create_std_list_std_string(position + 1));
    v.licence_name(create_std_string(position + 2));
    v.modeline_group_name(create_std_string(position + 3));
    v.marker_name(create_std_string(position + 4));
}

decoration_configuration_generator::result_type
decoration_configuration_generator::create(const unsigned int position) {
    decoration_configuration r;
    decoration_configuration_generator::populate(position, r);
    return r;
}

decoration_configuration_generator::result_type*
decoration_configuration_generator::create_ptr(const unsigned int position) {
    decoration_configuration* p = new decoration_configuration();
    decoration_configuration_generator::populate(position, *p);
    return p;
}

decoration_configuration_generator::result_type
decoration_configuration_generator::operator()() {
    return create(position_++);
}

}
