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
#include "masd.dogen/test_data/tracing_level_td.hpp"
#include "masd.dogen/test_data/tracing_format_td.hpp"
#include "masd.dogen/test_data/tracing_configuration_td.hpp"

namespace {

masd::dogen::tracing_level
create_masd_dogen_tracing_level(const unsigned int position) {
    return masd::dogen::tracing_level_generator::create(position);
}

masd::dogen::tracing_format
create_masd_dogen_tracing_format(const unsigned int position) {
    return masd::dogen::tracing_format_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace masd::dogen {

tracing_configuration_generator::tracing_configuration_generator() : position_(0) { }

void tracing_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.level(create_masd_dogen_tracing_level(position + 0));
    v.format(create_masd_dogen_tracing_format(position + 1));
    v.guids_enabled(create_bool(position + 2));
    v.logging_impact(create_std_string(position + 3));
    v.use_short_names(create_bool(position + 4));
    v.output_directory(create_boost_filesystem_path(position + 5));
}

tracing_configuration_generator::result_type
tracing_configuration_generator::create(const unsigned int position) {
    tracing_configuration r;
    tracing_configuration_generator::populate(position, r);
    return r;
}

tracing_configuration_generator::result_type*
tracing_configuration_generator::create_ptr(const unsigned int position) {
    tracing_configuration* p = new tracing_configuration();
    tracing_configuration_generator::populate(position, *p);
    return p;
}

tracing_configuration_generator::result_type
tracing_configuration_generator::operator()() {
    return create(position_++);
}

}