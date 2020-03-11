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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_VARIABILITY_FEATURES_TRANSFORM_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_VARIABILITY_FEATURES_TRANSFORM_HPP

#include "dogen.variability/types/meta_model/feature_template.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/features/variability_templates.hpp"
#include "dogen.assets/types/features/variability_bundle.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_bundle.hpp"

namespace dogen::assets::transforms {

/**
 * @brief Processes the variability entities related to the
 * code-generation of variability code.
 *
 * The variability features transform is only worried about
 * "feature-like" meta-model elements. It is considered the
 * third-phase of variability processing. It is important to note that
 * these elements have no part to play in the _current_ processing of
 * variability data - instead, they will be used to generate code
 * which will, in the future (e.g. after recompiling the code
 * generator), inject features into dogen during the first phase of
 * variability processing. As such, these are best understood as just
 * like any other code-generation elements rather than variability
 * entities per se.
 */
class variability_features_transform final {
private:
    /**
     * @brief Reads configuration related to variability templates.
     */
    static void update(const features::variability_templates::feature_group& fg,
        meta_model::variability::abstract_feature& af);

    /**
     * @brief Reads configuration related to feature bundles.
     */
    static void update(const features::variability_bundle::feature_group& fg,
        meta_model::variability::abstract_bundle& ab);

private:
    /**
     * @brief Populates the properties common to both features and
     * feature templates.
     */
    static void process_abstract_feature(
        const features::variability_templates::feature_group& fg1,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        const boost::optional<variability::meta_model::binding_point>&
        default_binding_point, meta_model::variability::abstract_feature& af);

private:
    /**
     * @brief Processes the meta-model element representing feature
     * bundles.
     */
    static void process_feature_bundles(
        const variability::meta_model::feature_model& fm,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);

    /**
     * @brief Processes the meta-model element representing feature
     * template bundles.
     */
    static void process_feature_template_bundles(
        const variability::meta_model::feature_model& fm,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);

    /**
     * @brief Processes the variability initialiser meta-model element.
     */
    static void process_initialiser(meta_model::model& m);

public:
    /**
     * @brief Transforms all variability meta-model elements involved
     * in code generation.
     */
    static void apply(const context& ctx,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);
};

}

#endif
