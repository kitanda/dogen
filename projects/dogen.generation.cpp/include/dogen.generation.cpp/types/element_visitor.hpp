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
#ifndef DOGEN_GENERATION_CPP_TYPES_ELEMENT_VISITOR_HPP
#define DOGEN_GENERATION_CPP_TYPES_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/cmakelists_fwd.hpp"

namespace dogen::generation::cpp {

/**
 * @brief Visitor for element
 */
class element_visitor : public dogen::assets::meta_model::element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    using dogen::assets::meta_model::element_visitor::visit;

    /**
     * @brief Accept visits for type dogen::generation::cpp::fabric::cmakelists
     */
    /**@{*/
    virtual void visit(const dogen::generation::cpp::fabric::cmakelists&) const { }
    virtual void visit(const dogen::generation::cpp::fabric::cmakelists&) { }
    virtual void visit(dogen::generation::cpp::fabric::cmakelists&) const { }
    virtual void visit(dogen::generation::cpp::fabric::cmakelists&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif
