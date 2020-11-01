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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/hash/entities/logical_meta_id_hash.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.text.cpp/types/transforms/repository.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"

namespace dogen::text::cpp::formattables {

class model_expander {
private:
    void expand_helpers(
        const variability::entities::feature_model& feature_model,
        const std::unordered_map<identification::entities::logical_id,
        logical::entities::streaming_properties>& streaming_properties,
        const transforms::repository& frp, model& fm) const;

    void reduce(model& fm) const;

public:
    void expand(const variability::entities::feature_model& feature_model,
        const std::unordered_map<identification::entities::logical_id,
        logical::entities::streaming_properties>& streaming_properties,
        const transforms::repository& frp, model& fm) const;
};

}

#endif
