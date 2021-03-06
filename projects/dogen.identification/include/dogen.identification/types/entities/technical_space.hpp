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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_TECHNICAL_SPACE_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_TECHNICAL_SPACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::identification::entities {

/**
 * @brief Models need to declare upfront the technical space they will target.
 */
enum class technical_space : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    agnostic = 1, ///< Abstract technical space which is mapped to concrete technical spaces.
    cpp = 2, ///< The C++ programming language.
    csharp = 3, ///< The C# programming language.
    cmake = 4, ///< CMake meta build system.
    xml = 5, ///< Extensible Markup Language.
    odb = 6, ///< ODB options.
    sln = 7, ///< Visual studio solution.
    mustache = 8 ///< Mustache templates.
};

}

#endif
