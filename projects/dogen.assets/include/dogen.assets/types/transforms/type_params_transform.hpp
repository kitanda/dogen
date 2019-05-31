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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_TYPE_PARAMS_TRANSFORM_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_TYPE_PARAMS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.assets/types/features/type_parameters.hpp"
#include "dogen.assets/types/meta_model/type_parameters.hpp"
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"

namespace dogen::assets::transforms {

class type_params_transform final {
private:
    static void populate_type_parameters(
        const features::type_parameters::feature_group& fg,
        meta_model::structural::object& o);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif