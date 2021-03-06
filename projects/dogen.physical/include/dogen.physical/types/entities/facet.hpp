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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_FACET_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_FACET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/helper.hpp"
#include "dogen.physical/types/entities/archetype.hpp"
#include "dogen.identification/types/entities/label.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents a meta-region in physical space with archetypes for a given theme.
 */
class facet final {
public:
    facet() = default;
    facet(const facet&) = default;
    facet(facet&&) = default;
    ~facet() = default;

public:
    facet(
        const std::string& directory_name,
        const std::string& description,
        const dogen::identification::entities::physical_meta_name& meta_name,
        const std::list<dogen::identification::entities::label>& labels,
        const std::string& postfix,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::helper>& helpers,
        const std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id);

public:
    /**
     * @brief Default name to use for the directory in the file-system representing this element.
     */
    /**@{*/
    const std::string& directory_name() const;
    std::string& directory_name();
    void directory_name(const std::string& v);
    void directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

    /**
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::label>& labels() const;
    std::list<dogen::identification::entities::label>& labels();
    void labels(const std::list<dogen::identification::entities::label>& v);
    void labels(const std::list<dogen::identification::entities::label>&& v);
    /**@}*/

    /**
     * @brief Postfix to apply to artefacts within this element, if any.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes();
    void archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& v);
    void archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>&& v);

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::helper>& helpers() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::helper>& helpers();
    void helpers(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::helper>& v);
    void helpers(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::helper>&& v);

    /**
     * @brief Maps the logical model element ID to the default archetype for this facet.
     *
     * Used to obtain the default archetype for referencing.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id();
    void default_archetype_for_logical_meta_model_id(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v);
    void default_archetype_for_logical_meta_model_id(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v);
    /**@}*/

public:
    bool operator==(const facet& rhs) const;
    bool operator!=(const facet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet& other) noexcept;
    facet& operator=(facet other);

private:
    std::string directory_name_;
    std::string description_;
    dogen::identification::entities::physical_meta_name meta_name_;
    std::list<dogen::identification::entities::label> labels_;
    std::string postfix_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype> archetypes_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::helper> helpers_;
    std::unordered_map<std::string, dogen::physical::entities::archetype> default_archetype_for_logical_meta_model_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::facet& lhs,
    dogen::physical::entities::facet& rhs) {
    lhs.swap(rhs);
}

}

#endif
