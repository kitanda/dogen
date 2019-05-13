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
#ifndef DOGEN_ENGINE_TYPES_TRANSFORMS_DYNAMIC_STEREOTYPES_TRANSFORM_HPP
#define DOGEN_ENGINE_TYPES_TRANSFORMS_DYNAMIC_STEREOTYPES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.coding/types/meta_model/model_set.hpp"
#include "dogen.coding/types/transforms/context_fwd.hpp"

namespace dogen::engine::transforms {

/**
 * @brief Populates the dynamic stereotypes of the coding model.
 */
class dynamic_stereotypes_transform final {
public:
    static void apply(const coding::transforms::context& ctx,
        coding::meta_model::model_set& ms);
};

}

#endif