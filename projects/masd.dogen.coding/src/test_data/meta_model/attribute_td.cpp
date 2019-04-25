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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.variability/test_data/annotation_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/attribute_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/name_tree_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm_attribute_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::variability::annotation
create_masd_dogen_variability_annotation(const unsigned int position) {
    return masd::dogen::variability::annotation_generator::create(position);
}

masd::dogen::variability::meta_model::configuration*
create_masd_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>
create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> r(
        create_masd_dogen_variability_meta_model_configuration_ptr(position));
    return r;
}

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

masd::dogen::coding::meta_model::name_tree
create_masd_dogen_coding_meta_model_name_tree(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_tree_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

masd::dogen::coding::meta_model::orm_attribute_properties
create_masd_dogen_coding_meta_model_orm_attribute_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::orm_attribute_properties_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::orm_attribute_properties>
create_boost_optional_masd_dogen_coding_meta_model_orm_attribute_properties(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::orm_attribute_properties> r(
        create_masd_dogen_coding_meta_model_orm_attribute_properties(position));
    return r;
}

}

namespace masd::dogen::coding::meta_model {

attribute_generator::attribute_generator() : position_(0) { }

void attribute_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.annotation(create_masd_dogen_variability_annotation(position + 1));
    v.configuration(create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + 2));
    v.name(create_masd_dogen_coding_meta_model_name(position + 3));
    v.unparsed_type(create_std_string(position + 4));
    v.parsed_type(create_masd_dogen_coding_meta_model_name_tree(position + 5));
    v.is_immutable(create_bool(position + 6));
    v.is_fluent(create_bool(position + 7));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_attribute_properties(position + 8));
}

attribute_generator::result_type
attribute_generator::create(const unsigned int position) {
    attribute r;
    attribute_generator::populate(position, r);
    return r;
}

attribute_generator::result_type*
attribute_generator::create_ptr(const unsigned int position) {
    attribute* p = new attribute();
    attribute_generator::populate(position, *p);
    return p;
}

attribute_generator::result_type
attribute_generator::operator()() {
    return create(position_++);
}

}
