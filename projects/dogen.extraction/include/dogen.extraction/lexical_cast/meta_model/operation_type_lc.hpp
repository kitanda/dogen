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
#ifndef DOGEN_EXTRACTION_LEXICAL_CAST_META_MODEL_OPERATION_TYPE_LC_HPP
#define DOGEN_EXTRACTION_LEXICAL_CAST_META_MODEL_OPERATION_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.extraction/types/meta_model/operation_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::extraction::meta_model::operation_type& v) {
    using dogen::extraction::meta_model::operation_type;

    switch (v) {
    case operation_type::invalid:
        return "operation_type::invalid";
    case operation_type::create_only:
        return "operation_type::create_only";
    case operation_type::write:
        return "operation_type::write";
    case operation_type::ignore:
        return "operation_type::ignore";
    case operation_type::remove:
        return "operation_type::remove";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::extraction::meta_model::operation_type lexical_cast(const std::string & s) {
    using dogen::extraction::meta_model::operation_type;

    if (s == "invalid" || s == "operation_type::invalid")
        return operation_type::invalid;
    if (s == "create_only" || s == "operation_type::create_only")
        return operation_type::create_only;
    if (s == "write" || s == "operation_type::write")
        return operation_type::write;
    if (s == "ignore" || s == "operation_type::ignore")
        return operation_type::ignore;
    if (s == "remove" || s == "operation_type::remove")
        return operation_type::remove;
    throw boost::bad_lexical_cast();
}

}

#endif
