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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_ENDOMODEL_PRODUCTION_CHAIN_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_ENDOMODEL_PRODUCTION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/model_set.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Top-level transformation responsible for converting a raw
 * model set into a group of models with all coding transforms
 * applied.
 */
class model_production_chain final {
public:
    static std::list<meta_model::model>
    apply(const context& ctx, coding::meta_model::model_set ms);
};

}

#endif
