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
#include "dogen/yarn/test_data/meta_model/path_contribution_types_td.hpp"
#include "dogen/yarn/test_data/meta_model/model_segment_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::meta_model::path_contribution_types
create_dogen_yarn_meta_model_path_contribution_types(const unsigned int position) {
    return dogen::yarn::meta_model::path_contribution_types_generator::create(position);
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

model_segment_properties_generator::model_segment_properties_generator() : position_(0) { }

void model_segment_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.directory(create_std_string(position + 0));
    v.external_modules(create_dogen_yarn_meta_model_path_contribution_types(position + 1));
    v.model_modules(create_dogen_yarn_meta_model_path_contribution_types(position + 2));
}

model_segment_properties_generator::result_type
model_segment_properties_generator::create(const unsigned int position) {
    model_segment_properties r;
    model_segment_properties_generator::populate(position, r);
    return r;
}

model_segment_properties_generator::result_type*
model_segment_properties_generator::create_ptr(const unsigned int position) {
    model_segment_properties* p = new model_segment_properties();
    model_segment_properties_generator::populate(position, *p);
    return p;
}

model_segment_properties_generator::result_type
model_segment_properties_generator::operator()() {
    return create(position_++);
}

} } }
