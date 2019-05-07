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
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/generation_marker_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace masd::dogen::coding::meta_model::decoration {

generation_marker_generator::generation_marker_generator() : position_(0) { }

void generation_marker_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.add_date_time(create_bool(position + 0));
    v.add_dogen_version(create_bool(position + 1));
    v.add_model_to_text_transform_details(create_bool(position + 2));
    v.add_warning(create_bool(position + 3));
    v.message(create_std_string(position + 4));
}

generation_marker_generator::result_type
generation_marker_generator::create(const unsigned int position) {
    generation_marker r;
    generation_marker_generator::populate(position, r);
    return r;
}

generation_marker_generator::result_type*
generation_marker_generator::create_ptr(const unsigned int position) {
    generation_marker* p = new generation_marker();
    generation_marker_generator::populate(position, *p);
    return p;
}

generation_marker_generator::result_type
generation_marker_generator::operator()() {
    return create(position_++);
}

}
