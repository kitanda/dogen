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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_VALUE_VISITOR_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_VALUE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/entities/text_fwd.hpp"
#include "dogen.variability/types/entities/number_fwd.hpp"
#include "dogen.variability/types/entities/boolean_fwd.hpp"
#include "dogen.variability/types/entities/key_value_pair_fwd.hpp"
#include "dogen.variability/types/entities/comma_separated_fwd.hpp"
#include "dogen.variability/types/entities/text_collection_fwd.hpp"
#include "dogen.variability/types/entities/comma_separated_collection_fwd.hpp"

namespace dogen::variability::entities {

/**
 * @brief Visitor for value
 */
class value_visitor {
public:
    virtual ~value_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::variability::entities::boolean
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::boolean&) const { }
    virtual void visit(const dogen::variability::entities::boolean&) { }
    virtual void visit(dogen::variability::entities::boolean&) const { }
    virtual void visit(dogen::variability::entities::boolean&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::variability::entities::comma_separated
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::comma_separated&) const { }
    virtual void visit(const dogen::variability::entities::comma_separated&) { }
    virtual void visit(dogen::variability::entities::comma_separated&) const { }
    virtual void visit(dogen::variability::entities::comma_separated&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::variability::entities::comma_separated_collection
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::comma_separated_collection&) const { }
    virtual void visit(const dogen::variability::entities::comma_separated_collection&) { }
    virtual void visit(dogen::variability::entities::comma_separated_collection&) const { }
    virtual void visit(dogen::variability::entities::comma_separated_collection&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::variability::entities::key_value_pair
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::key_value_pair&) const { }
    virtual void visit(const dogen::variability::entities::key_value_pair&) { }
    virtual void visit(dogen::variability::entities::key_value_pair&) const { }
    virtual void visit(dogen::variability::entities::key_value_pair&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::variability::entities::number
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::number&) const { }
    virtual void visit(const dogen::variability::entities::number&) { }
    virtual void visit(dogen::variability::entities::number&) const { }
    virtual void visit(dogen::variability::entities::number&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::variability::entities::text
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::text&) const { }
    virtual void visit(const dogen::variability::entities::text&) { }
    virtual void visit(dogen::variability::entities::text&) const { }
    virtual void visit(dogen::variability::entities::text&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::variability::entities::text_collection
     */
    /**@{*/
    virtual void visit(const dogen::variability::entities::text_collection&) const { }
    virtual void visit(const dogen::variability::entities::text_collection&) { }
    virtual void visit(dogen::variability::entities::text_collection&) const { }
    virtual void visit(dogen::variability::entities::text_collection&) { }
    /**@}*/
};

inline value_visitor::~value_visitor() noexcept { }

}

#endif
