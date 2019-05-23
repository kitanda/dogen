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
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.generation.cpp/test_data/fabric/cmakelists_td.hpp"
#include "dogen.generation.cpp/test_data/fabric/odb_targets_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::generation::cpp::fabric::odb_targets
create_dogen_generation_cpp_fabric_odb_targets(const unsigned int position) {
    return dogen::generation::cpp::fabric::odb_targets_generator::create(position);
}

}

namespace dogen::generation::cpp::fabric {

cmakelists_generator::cmakelists_generator() : position_(0) { }

void cmakelists_generator::
populate(const unsigned int position, result_type& v) {
    dogen::assets::meta_model::element_generator::populate(position, v);
    v.include_directory_path(create_std_string(position + 0));
    v.source_directory_name(create_std_string(position + 1));
    v.header_file_extension(create_std_string(position + 2));
    v.implementation_file_extension(create_std_string(position + 3));
    v.odb_targets(create_dogen_generation_cpp_fabric_odb_targets(position + 4));
    v.tests_directory_name(create_std_string(position + 5));
}

cmakelists_generator::result_type
cmakelists_generator::create(const unsigned int position) {
    cmakelists r;
    cmakelists_generator::populate(position, r);
    return r;
}

cmakelists_generator::result_type*
cmakelists_generator::create_ptr(const unsigned int position) {
    cmakelists* p = new cmakelists();
    cmakelists_generator::populate(position, *p);
    return p;
}

cmakelists_generator::result_type
cmakelists_generator::operator()() {
    return create(position_++);
}

}
