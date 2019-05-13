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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTERS_IO_INSERTER_IMPLEMENTATION_HELPER_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTERS_IO_INSERTER_IMPLEMENTATION_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.coding/types/meta_model/structural/object.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"

namespace dogen::generation::cpp::formatters::io {

void inserter_implementation_helper(
    assistant& a, const coding::meta_model::structural::object& o, const bool inside_class);

}

#endif