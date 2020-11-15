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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.text.csharp/types/transforms/types/floating_point_number_helper_factory.hpp"

namespace dogen::text::csharp::transforms::types {

physical::entities::helper floating_point_number_helper_factory::make() {
    physical::entities::helper r;
    using pmnf = identification::helpers::physical_meta_name_factory;
    r.meta_name(pmnf::make("csharp", "types", "floating_point_number_helper"));
    // r.relations().status(physical::entities::relation_status::);
    r.family("FloatingPointNumber");
    using identification::entities::physical_meta_id;
    r.owning_formatters().push_back(
        physical_meta_id("masd.csharp.types.class"));
    r.owning_formatters().push_back(
        physical_meta_id("masd.csharp.types.primitive"));
    r.owning_facets().push_back(
        physical_meta_id("masd.csharp.types"));

    return r;
}

}