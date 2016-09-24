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
#include "dogen/quilt.cpp/types/formattables/enablement_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"
#include "dogen/quilt.cpp/types/formattables/pre_reduction_workflow.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void pre_reduction_workflow::expand_enablement(const dynamic::repository& drp,
    const dynamic::object& root_object, const formatters::container& fc,
    std::unordered_map<std::string, formattable>& formattables) const {
    enablement_expander ex;
    ex.expand(drp, root_object, fc, formattables);
}


std::unordered_map<std::string, formattable> pre_reduction_workflow::
transform(const formatters::container& fc, const yarn::model& m) const {
    transformer t;
    return t.transform(fc, m);
}

std::unordered_map<std::string, formattable> pre_reduction_workflow::
execute(const dynamic::repository& /*drp*/, const dynamic::object& /*root_object*/,
    const formatters::container& fc, const yarn::model& m) const {
    auto r(transform(fc, m));
    // expand_enablement(drp, root_object, fc, r);
    return r;
}

} } } }
