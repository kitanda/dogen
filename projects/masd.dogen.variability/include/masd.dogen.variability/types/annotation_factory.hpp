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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_ANNOTATIONS_FACTORY_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_ANNOTATIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/scope_types.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.archetypes/types/archetype_location_repository.hpp"

namespace masd::dogen::variability {

/**
 * @brief Produces an annotation object from raw data.
 */
class annotation_factory final {
public:
    /**
     * @brief Initialise the annotations object factory.
     *
     * @param alrp the archetype location repository.
     * @param trp the type repository.
     */
    annotation_factory(
        const archetypes::archetype_location_repository& alrp,
        const type_repository& trp, const bool compatibility_mode);

private:
    /**
     * @brief Returns the field definition for the qualified name, if
     * any exists.
     */
    boost::optional<type> try_obtain_type(const std::string& n) const;

    /**
     * @brief Ensures the field definition is valid for the current
     * scope.
     */
    void validate_scope(const type& fd,
        const scope_types current_scope) const;

    /**
     * @brief Given a scope, returns the well-known name of its the
     * default profile.
     */
    std::string
    get_default_profile_name_for_scope(const scope_types scope) const;

private:
    /**
     * @brief Converts the raw data into an annotation.
     */
    annotation create_annotation(const scope_types scope,
        const std::unordered_map<std::string, std::list<std::string>>&
        aggregated_entries) const;

    /**
     * @brief Aggregate entry data by key.
     */
    std::unordered_map<std::string, std::list<std::string>>
    aggregate_entries(const std::list<std::pair<std::string, std::string>>&
        entries) const;

public:
    /**
     * @brief Create an annotation with profile support.
     */
    annotation
    make(const std::list<std::pair<std::string, std::string>>& entries,
        const scope_types scope) const;

private:
    const archetypes::archetype_location_repository&
    archetype_location_repository_;
    const type_repository& type_repository_;
    const bool compatibility_mode_;
};

}

#endif
