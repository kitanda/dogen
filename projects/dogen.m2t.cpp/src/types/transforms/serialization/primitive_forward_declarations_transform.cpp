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
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/primitive_forward_declarations_transform.hpp"

namespace dogen::m2t::cpp::transforms::serialization {

std::string primitive_forward_declarations_transform::static_id() {
    return traits::primitive_forward_declarations_archetype_qn();
}

std::string primitive_forward_declarations_transform::id() const {
    return static_id();
}

physical::entities::meta_name
primitive_forward_declarations_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::primitive_forward_declarations_archetype_sn()));
    return r;
}

const logical::entities::name& primitive_forward_declarations_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

physical::entities::archetype primitive_forward_declarations_transform::archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using physical::helpers::meta_name_factory;
        r.meta_name(meta_name_factory::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::primitive_forward_declarations_archetype_sn()));
        return r;
    }());
    return r;
}

inclusion_support_types primitive_forward_declarations_transform::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path primitive_forward_declarations_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path primitive_forward_declarations_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> primitive_forward_declarations_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    auto builder(f.make());

    using tp = transforms::types::traits;
    const auto tp_fn(tp::primitive_forward_declarations_archetype_qn());
    builder.add(e.name(), tp_fn);

    return builder.build();
}

void primitive_forward_declarations_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), true/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(p));
        const auto qn(ast.get_qualified_name(p.name()));
ast.stream() << std::endl;
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << "namespace serialization {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<class Archive>" << std::endl;
ast.stream() << "void save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<class Archive>" << std::endl;
ast.stream() << "void load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "} }" << std::endl;
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
}

}
