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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_template_io.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_template_io.hpp"
#include "masd.dogen.variability/types/transforms/configuration_template_instantiation_transform.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.configuration_template_instantiation_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::variability::transforms {

std::list<meta_model::configuration>
configuration_template_instantiation_transform::apply(const context& ctx,
    const std::list<meta_model::configuration_template>& cts) {
    tracing::scoped_transform_tracer stp(lg,
        "configuration template instantiation transform",
        transform_id, transform_id, *ctx.tracer(), cts);

    std::list<meta_model::configuration> r;
    return r;
}

}
