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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/cpp/hash/class_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/hash/class_header_factory.hpp"

namespace dogen::text::transforms::cpp::hash {
namespace {

const std::string transform_id("text.transforms.hash.class_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_header_transform::static_archetype() {
    static auto r(class_header_factory::make());
    return r;
}

const physical::entities::archetype& class_header_transform::archetype() const {
    return static_archetype();
}

void class_header_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "FIXME",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, true/*requires_header_guard*/);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    const auto sn(o.name().simple());
    const auto qn(ast.get_qualified_name(o.name()));
    {

        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "struct " << sn << "_hasher {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    static std::size_t hash(const " << sn << "& v);" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
ast.stream() << "namespace std {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "struct hash<" << qn << "> {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    size_t operator()(const " << qn << "& v) const {" << std::endl;
ast.stream() << "        return " << qn << "_hasher::hash(v);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
