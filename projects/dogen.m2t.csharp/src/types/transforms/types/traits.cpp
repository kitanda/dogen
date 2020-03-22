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
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string traits::facet() {
    static std::string r(csharp::traits::backend() + ".types");
    return r;
}

std::string traits::class_archetype() {
    static std::string r(traits::facet() + ".class");
    return r;
}

std::string traits::enum_archetype() {
    static std::string r(traits::facet() + ".enum");
    return r;
}

std::string traits::primitive_archetype() {
    static std::string r(traits::facet() + ".primitive");
    return r;
}

std::string traits::exception_archetype() {
    static std::string r(traits::facet() + ".exception");
    return r;
}

std::string traits::builtin_archetype() {
    static std::string r(traits::facet() + ".builtin");
    return r;
}

}