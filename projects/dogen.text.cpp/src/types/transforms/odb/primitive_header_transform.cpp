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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/odb/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/odb/primitive_header_transform.hpp"

namespace dogen::text::cpp::transforms::odb {

physical::entities::archetype primitive_header_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::primitive_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_primitive_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype primitive_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types primitive_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path primitive_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> primitive_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());
    builder.add(p.name(), types::traits::primitive_header_archetype_qn());

    return builder.build();
}

void primitive_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    {
        const auto sn(p.name().simple());
        const auto qn(ast.get_qualified_name(p.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        const auto attr(p.value_attribute());

        if (!p.orm_properties() || p.orm_properties()->odb_pragmas().empty()) {
ast.stream() << "// class has no ODB pragmas defined." << std::endl;
ast.stream() << std::endl;
        } else {
            {
                const auto ns(ast.make_namespaces(p.name()));
                auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "#ifdef ODB_COMPILER" << std::endl;
ast.stream() << std::endl;
                for (const auto& pg : p.orm_properties()->odb_pragmas())
ast.stream() << pg << std::endl;

                bool is_first(true);
                if (p.value_attribute().orm_properties() &&
                    !p.value_attribute().orm_properties()->odb_pragmas().empty()) {
                    for (const auto& pg : p.value_attribute().orm_properties()->odb_pragmas()) {
                        if (is_first)
ast.stream() << std::endl;
                            is_first = false;
ast.stream() << pg << std::endl;
                    }
ast.stream() << std::endl;
ast.stream() << "#endif" << std::endl;
ast.stream() << std::endl;
                }
            }
ast.stream() << std::endl;
        }
    } // sbf
    ast.update_artefact();
}

}