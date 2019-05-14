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
#ifndef DOGEN_LEXICAL_CAST_TRACING_FORMAT_LC_HPP
#define DOGEN_LEXICAL_CAST_TRACING_FORMAT_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/tracing_format.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::tracing_format& v) {
    using dogen::tracing_format;

    switch (v) {
    case tracing_format::invalid:
        return "tracing_format::invalid";
    case tracing_format::plain:
        return "tracing_format::plain";
    case tracing_format::org_mode:
        return "tracing_format::org_mode";
    case tracing_format::graphviz:
        return "tracing_format::graphviz";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::tracing_format lexical_cast(const std::string & s) {
    using dogen::tracing_format;

    if (s == "invalid" || s == "tracing_format::invalid")
        return tracing_format::invalid;
    if (s == "plain" || s == "tracing_format::plain")
        return tracing_format::plain;
    if (s == "org_mode" || s == "tracing_format::org_mode")
        return tracing_format::org_mode;
    if (s == "graphviz" || s == "tracing_format::graphviz")
        return tracing_format::graphviz;
    throw boost::bad_lexical_cast();
}

}

#endif
