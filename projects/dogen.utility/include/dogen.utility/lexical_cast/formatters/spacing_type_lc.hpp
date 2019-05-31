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
#ifndef DOGEN_UTILITY_LEXICAL_CAST_FORMATTERS_SPACING_TYPE_LC_HPP
#define DOGEN_UTILITY_LEXICAL_CAST_FORMATTERS_SPACING_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/formatters/spacing_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::utility::formatters::spacing_type& v) {
    using dogen::utility::formatters::spacing_type;

    switch (v) {
    case spacing_type::invalid:
        return "spacing_type::invalid";
    case spacing_type::no_space:
        return "spacing_type::no_space";
    case spacing_type::left_space:
        return "spacing_type::left_space";
    case spacing_type::right_space:
        return "spacing_type::right_space";
    case spacing_type::left_and_right_space:
        return "spacing_type::left_and_right_space";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::utility::formatters::spacing_type lexical_cast(const std::string & s) {
    using dogen::utility::formatters::spacing_type;

    if (s == "invalid" || s == "spacing_type::invalid")
        return spacing_type::invalid;
    if (s == "no_space" || s == "spacing_type::no_space")
        return spacing_type::no_space;
    if (s == "left_space" || s == "spacing_type::left_space")
        return spacing_type::left_space;
    if (s == "right_space" || s == "spacing_type::right_space")
        return spacing_type::right_space;
    if (s == "left_and_right_space" || s == "spacing_type::left_and_right_space")
        return spacing_type::left_and_right_space;
    throw boost::bad_lexical_cast();
}

}

#endif