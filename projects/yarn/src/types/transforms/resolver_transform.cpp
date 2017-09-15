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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/helpers/resolver.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/transforms/resolver_transform.hpp"

namespace {

const std::string id("yarn.transforms.resolver_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace yarn {
namespace transforms {

void resolver_transform::transform(const context& ctx,
    const helpers::indices& idx, meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started resolver transform. Model: "
                             << em.name().id();
    ctx.prober().start_transform(id, em.name().id(), em);
    helpers::resolver::resolve(idx, em);
    ctx.prober().end_transform(em);
    BOOST_LOG_SEV(lg, debug) << "Finished resolver transform.";
}

} } }
