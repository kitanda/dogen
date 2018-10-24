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
#include "masd.dogen.generation.cpp/types/formatters/visual_studio_solution_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/visual_studio_project_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/msbuild_targets_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/initializer.hpp"

namespace masd::dogen::generation::cpp::formatters {

void initializer::initialize(registrar& rg) {
    register_formatter<visual_studio_solution_formatter>(rg);
    register_formatter<visual_studio_project_formatter>(rg);
    register_formatter<include_cmakelists_formatter>(rg);
    register_formatter<source_cmakelists_formatter>(rg);
    register_formatter<msbuild_targets_formatter>(rg);

    types::initializer::initialize(rg);
    hash::initializer::initialize(rg);
    odb::initializer::initialize(rg);
    io::initializer::initialize(rg);
    test_data::initializer::initialize(rg);
    serialization::initializer::initialize(rg);
}

}
