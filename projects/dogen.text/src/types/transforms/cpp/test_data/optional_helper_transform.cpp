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
#include "dogen.text/types/transforms/cpp/test_data/optional_helper_transform.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::transforms::cpp::test_data {
std::string optional_helper_transform::id() const {
    static auto r(std::string("<masd.cpp.test_data>") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string optional_helper_transform::family() const {
    static std::string r("Optional");
    return r;
}

std::list<std::string>
optional_helper_transform::owning_formatters() const {
    static auto r(std::list<std::string> {
        "masd.cpp.test_data.class_implementation",
        "masd.cpp.test_data.primitive_implementation"
    });
    return r;
}

std::list<std::string>
optional_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        "masd.cpp.test_data"
    });
    return r;
}

std::string optional_helper_transform::helper_name() const {
    static std::string r("optional_helper_transform");
    return r;
}

bool optional_helper_transform::is_enabled(
    const physical::entities::model& /*m*/,
    const logical::entities::element& /*e*/,
    const physical::entities::artefact& /*a*/,
    const logical::entities::helper_properties& /*hp*/) const {
    return true;
}

void optional_helper_transform::apply(std::ostream& os, const logical::entities::model& /*m*/,
    const logical::entities::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const auto containee(hp.direct_descendants().front());
os << std::endl;
os << qn << std::endl;
os << "create_" << ident << "(unsigned int position) {" << std::endl;
os << "    " << qn << " r(" << std::endl;
os << "        create_" << containee.name_tree_identifiable() << "(position));" << std::endl;
os << "    return r;" << std::endl;
os << "}" << std::endl;
}
}
