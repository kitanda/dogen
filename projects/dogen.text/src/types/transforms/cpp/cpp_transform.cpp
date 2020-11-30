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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text/types/transforms/cpp/cpp_transform.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"

namespace dogen::text::transforms::cpp {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.transforms.cpp"));

/*
physical::entities::backend make_backend() {
    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");
    b.backend("cpp");

    physical::entities::backend r;
    r.meta_name(b.build());

    const auto lambda([&](const auto& fct) {
        const auto id(fct.meta_name().id());
        const auto pair(std::make_pair(id, fct));
        const auto inserted(r.facets().insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_facet("Duplicate facet: ");
            BOOST_LOG_SEV(lg, error) << duplicate_facet << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + id.value()));
        }
    });

    return r;
}
*/

}
/*
const physical::entities::backend& cpp_backend_chain::static_backend() {
    static const auto r(make_backend());
    return r;
}

const physical::entities::backend& cpp_backend_chain::backend() const {
    return static_backend();
}
*/
}
