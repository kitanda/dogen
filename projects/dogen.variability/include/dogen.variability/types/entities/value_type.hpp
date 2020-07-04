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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_VALUE_TYPE_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_VALUE_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::variability::entities {

/**
 * @brief What values can a feature have.
 */
enum class value_type : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    text = 1, ///< Represents a text value.
    text_collection = 2, ///< Represents a collection of text values.
    number = 3, ///< Represents a numeric integral value.
    boolean = 4, ///< Represents a boolean value.
    key_value_pair = 5, ///< Represents a pair of key and value.
    comma_separated = 6, ///< Represents a CSV input that is split into a collection of text values.
    comma_separated_collection = 7 ///< Represents a collection of CSV input that is split into a collection of text values.
};

}

#endif
