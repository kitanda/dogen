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
#include "masd.dogen.coding/test_data/meta_model/orm/database_system_td.hpp"

namespace masd::dogen::coding::meta_model::orm {

database_system_generator::database_system_generator() : position_(0) { }
void database_system_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<database_system>(position % 6);
}

database_system_generator::result_type
database_system_generator::create(const unsigned int  position) {
    result_type r;
    database_system_generator::populate(position, r);
    return r;
}

database_system_generator::result_type
database_system_generator::operator()() {
    return create(position_++);
}

}