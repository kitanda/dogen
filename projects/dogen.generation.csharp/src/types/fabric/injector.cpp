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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation.csharp/types/fabric/assembly_info_factory.hpp"
#include "dogen.generation.csharp/types/fabric/assistant_factory.hpp"
#include "dogen.generation.csharp/types/fabric/injector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.csharp.fabric.injector"));

const std::string duplicate_qualified_name("Duplicate qualified name: ");

}

namespace dogen::generation::csharp::fabric {

injector::~injector() noexcept {}

void injector::
add_element(const boost::shared_ptr<assets::meta_model::element>& e,
    generation::meta_model::model& m) const {
    m.elements().push_back(e);
}

void injector::add_elements(
    const std::list<boost::shared_ptr<assets::meta_model::element>>& elements,
    generation::meta_model::model& m) const {
    for (auto& e : elements)
        add_element(e, m);
}

void injector::
inject_assembly_info(generation::meta_model::model& m) const {
    assembly_info_factory f;
    const auto e(f.make(m));
    add_element(e, m);
}

void injector::inject_assistant(generation::meta_model::model& m) const {
    assistant_factory f;
    const auto e(f.make(m));
    add_element(e, m);
}

void injector::inject(generation::meta_model::model& m) const {
    inject_assembly_info(m);
    inject_assistant(m);
}

}
