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
#include "masd.dogen.generation.csharp/types/initializer.hpp"
#include "masd.dogen.generation.cpp/types/initializer.hpp"
#include "masd.dogen.external.json/types/initializer.hpp"
#include "masd.dogen.external.dia/types/initializer.hpp"
#include "masd.dogen.knitter/initializer.hpp"

namespace masd::dogen::knitter {

void initializer::initialize() {
    masd::dogen::external::json::initializer::initialize();
    masd::dogen::external::dia::initializer::initialize();
    masd::dogen::generation::csharp::initializer::initialize();
    masd::dogen::generation::cpp::initializer::initialize();
}

}
