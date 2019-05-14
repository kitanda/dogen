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
#ifndef DOGEN_LEXICAL_CAST_TRACING_LEVEL_LC_HPP
#define DOGEN_LEXICAL_CAST_TRACING_LEVEL_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/tracing_level.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::tracing_level& v) {
    using dogen::tracing_level;

    switch (v) {
    case tracing_level::invalid:
        return "tracing_level::invalid";
    case tracing_level::detail:
        return "tracing_level::detail";
    case tracing_level::summary:
        return "tracing_level::summary";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::tracing_level lexical_cast(const std::string & s) {
    using dogen::tracing_level;

    if (s == "invalid" || s == "tracing_level::invalid")
        return tracing_level::invalid;
    if (s == "detail" || s == "tracing_level::detail")
        return tracing_level::detail;
    if (s == "summary" || s == "tracing_level::summary")
        return tracing_level::summary;
    throw boost::bad_lexical_cast();
}

}

#endif
