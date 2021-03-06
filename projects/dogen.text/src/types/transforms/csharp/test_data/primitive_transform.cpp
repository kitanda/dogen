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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/csharp/test_data/primitive_transform.hpp"
#include "dogen.text/types/transforms/csharp/test_data/primitive_factory.hpp"

namespace dogen::text::transforms::csharp::test_data {
namespace {

const std::string transform_id("text.transforms.test_data.primitive_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& primitive_transform::static_archetype() {
    static auto r(primitive_factory::make());
    return r;
}

const physical::entities::archetype& primitive_transform::archetype() const {
    return static_archetype();
}

void primitive_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));
    {
        const auto sn(e.name().simple());
        const auto qn(ast.get_qualified_name(e.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << "using System.Collections;" << std::endl;
ast.stream() << "using System.Collections.Generic;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));

ast.stream() << "    /// <summary>" << std::endl;
ast.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
ast.stream() << "    /// </summary>" << std::endl;
ast.stream() << "    public static class " << sn << "SequenceGenerator" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        static internal void Populate(" << sn << " value, uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
            const auto attr(p.value_attribute());
            const auto oap(ast.get_assistant_properties(attr));
            if (oap && oap->requires_assistance()) {
ast.stream() << "            value." << attr.name().simple() << " = AssistantSequenceGenerator.Create" << oap->method_postfix() << "(position);" << std::endl;
            } else {
                const auto attr_qn(ast.get_qualified_name(attr.parsed_type().current()));
ast.stream() << "            value." << attr.name().simple() << " = " << attr_qn << "SequenceGenerator.Create(position);" << std::endl;
            }
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        static internal " << sn << " Create(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new " << sn << "();" << std::endl;
ast.stream() << "            Populate(result, position);" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        #region Enumerator" << std::endl;
ast.stream() << "        private class " << sn << "Enumerator : IEnumerator, IEnumerator<" << sn << ">, IDisposable" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            #region Properties" << std::endl;
ast.stream() << "            private uint _position;" << std::endl;
ast.stream() << "            private " << sn << " _current;" << std::endl;
ast.stream() << "            #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            private void PopulateCurrent()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                _current = " << sn << "SequenceGenerator.Create(_position);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            #region IDisposable" << std::endl;
ast.stream() << "            public void Dispose()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            #region IEnumerator implementation" << std::endl;
ast.stream() << "            public bool MoveNext()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                ++_position;" << std::endl;
ast.stream() << "                PopulateCurrent();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            public void Reset()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                _position = 0;" << std::endl;
ast.stream() << "                PopulateCurrent();" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            public object Current {" << std::endl;
ast.stream() << "                get" << std::endl;
ast.stream() << "                {" << std::endl;
ast.stream() << "                    return _current;" << std::endl;
ast.stream() << "                }" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            " << sn << " IEnumerator<" << sn << ">.Current" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                get" << std::endl;
ast.stream() << "                {" << std::endl;
ast.stream() << "                    return _current;" << std::endl;
ast.stream() << "                }" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            public " << sn << "Enumerator()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                PopulateCurrent();" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        #region Enumerable" << std::endl;
ast.stream() << "        private class " << sn << "Enumerable : IEnumerable, IEnumerable<" << sn << ">" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            #region IEnumerable implementation" << std::endl;
ast.stream() << "            public IEnumerator GetEnumerator()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                return new " << sn << "Enumerator();" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            IEnumerator<" << sn << "> IEnumerable<" << sn << ">.GetEnumerator()" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                return new " << sn << "Enumerator();" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            #endregion" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        static public IEnumerable<" << sn << "> Sequence()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return new " << sn << "Enumerable();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    }" << std::endl;
        }
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
