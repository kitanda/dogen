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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/io/inserter_implementation_helper.hpp"
#include "dogen.text/types/transforms/cpp/types/class_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/types/class_implementation_factory.hpp"

namespace dogen::text::transforms::cpp::types {
namespace {

const std::string transform_id("text.transforms.types.class_implementation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_implementation_transform::static_archetype() {
    static auto r(class_implementation_factory::make());
    return r;
}

const physical::entities::archetype& class_implementation_transform::archetype() const {
    return static_archetype();
}

void class_implementation_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "class implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(ast.get_qualified_name(o.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        ast.add_helper_methods(o.name().qualified().dot());

        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
            if (ast.requires_manual_default_constructor()) {
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "()" << std::endl;
                // FIXME: this was just too hard to hack with a sequence.
                // FIXME: indentation is all off too.
                std::ostringstream ss;
                bool is_first(true);
                bool found(false);
                for (const auto& attr : o.local_attributes()) {
                    if (!attr.parsed_type().is_current_simple_type())
                        continue;

                    found = true;
                    if (!is_first)
                        ss << "," << std::endl << "      ";

                    ss << attr.member_variable_name()
                       << "(static_cast<" << ast.get_qualified_name(attr.parsed_type())
                       << ">(0))";

                    is_first = false;
                }
                ss << " { }";
                const std::string out(ss.str());
ast.stream() << "    " << (found ? ": " : "") << out << std::endl;
            }

            /*
             * Move constructor.
             */
            if (ast.requires_manual_move_constructor()) {
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "(" << sn << "&& rhs)" << std::endl;
                const auto size(o.parents().size() + o.local_attributes().size());

                utility::formatters::sequence_formatter sf(size);
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    " << sf.prefix() << pqn << "(" << std::endl;
ast.stream() << "        std::forward<" << pqn << ">(rhs))" << sf.postfix() << std::endl;
                    sf.next();
                }

                for (const auto& attr : o.local_attributes()) {
ast.stream() << "    " << sf.prefix() << attr.member_variable_name() << "(std::move(rhs." << attr.member_variable_name() << "))" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Complete constructor.
             */
            if (!o.all_attributes().empty()) {
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                     const auto attr(*o.all_attributes().begin());
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << ")" << std::endl;
                } else {
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "(" << std::endl;

                    utility::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(")");
                    for (const auto& attr : o.all_attributes()) {
ast.stream() << "    const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }

                auto sequence_size(o.local_attributes().size() + o.parents().size());
                for (const auto& pair : o.inherited_attributes()) {
                    const auto& pattrs(pair.second);
                    sequence_size += (pattrs.size() > 1 ? pattrs.size() : 0);
                }

                utility::formatters::sequence_formatter sf(sequence_size);
                sf.postfix_configuration().last(" { }");
                sf.prefix_configuration().first(": ").not_first("  ");
                for (const auto& pair : o.inherited_attributes()) {
                    const auto pqn(ast.get_qualified_name(pair.first));
                    const auto& pattrs(pair.second);
                    if (pattrs.size() <= 1) {
ast.stream() << "    " << sf.prefix() << pqn << "(" << (pattrs.empty() ? "" : pattrs.front().name().simple()) << ")" << sf.postfix() << std::endl;
                        sf.next();
                    } else {
ast.stream() << "    " << sf.prefix() << pqn << "(" << sf.postfix(true/*skip*/) << std::endl;
                        sf.next();
                        utility::formatters::sequence_formatter sf2(pattrs.size());
                        sf2.element_separator("");

                        sf2.prefix_configuration().first("  ").not_first("  ");
                        sf2.postfix_configuration().last(")");
                        for (const auto& attr : pattrs) {
ast.stream() << "    " << sf2.prefix() << attr.name().simple() << sf2.postfix() << sf.postfix() << std::endl;
                            sf2.next();
                            sf.next();
                        }
                    }
                }

                for (const auto& attr : o.local_attributes()) {
ast.stream() << "    " << sf.prefix() << attr.member_variable_name() << "(" << attr.name().simple() << ")" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Visitation.
             */
            if (o.is_visitation_leaf()) {
                std::string bvn;
                std::string dvn;
                std::string rpn;
                if (o.derived_visitor()) {
                    bvn = ast.get_qualified_name(*o.base_visitor());
                    dvn = o.derived_visitor()->simple();
                    rpn = ast.get_qualified_name(o.root_parents().front());
                } else {
                    bvn = o.base_visitor()->simple();
                    rpn = o.root_parents().front().simple();
                }
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::accept(const " << bvn << "& v) const {" << std::endl;
                if (o.derived_visitor()) {
ast.stream() << "    typedef const " << dvn << "* derived_ptr;" << std::endl;
ast.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
ast.stream() << "    if (dv)" << std::endl;
ast.stream() << "        dv->visit(*this);" << std::endl;
                } else {
ast.stream() << "    v.visit(*this);" << std::endl;
                }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::accept(" << bvn << "& v) const {" << std::endl;
                if (o.derived_visitor()) {
ast.stream() << "    typedef " << dvn << "* derived_ptr;" << std::endl;
ast.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
ast.stream() << "    if (dv)" << std::endl;
ast.stream() << "        dv->visit(*this);" << std::endl;
                } else {
ast.stream() << "    v.visit(*this);" << std::endl;
                }
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::accept(const " << bvn << "& v) {" << std::endl;
                if (o.derived_visitor()) {
ast.stream() << "    typedef const " << dvn << "* derived_ptr;" << std::endl;
ast.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
ast.stream() << "    if (dv)" << std::endl;
ast.stream() << "        dv->visit(*this);" << std::endl;
                } else {
ast.stream() << "    v.visit(*this);" << std::endl;
                }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::accept(" << bvn << "& v) {" << std::endl;
                if (o.derived_visitor()) {
ast.stream() << "    typedef " << dvn << "* derived_ptr;" << std::endl;
ast.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
ast.stream() << "    if (dv)" << std::endl;
ast.stream() << "        dv->visit(*this);" << std::endl;
                } else {
ast.stream() << "    v.visit(*this);" << std::endl;
                }
ast.stream() << "}" << std::endl;
            }

            /*
             * Streaming
             */
            if (ast.is_io_enabled()) {
                if (o.in_inheritance_relationship()) {
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::to_stream(std::ostream& s) const {" << std::endl;
                io::inserter_implementation_helper(ast, o, true/*inside_class*/);
ast.stream() << "}" << std::endl;
                }
            }

            /*
             * Swap
             */
            if (!o.is_immutable() && (!o.all_attributes().empty() || o.is_parent())) {
                const bool empty(o.all_attributes().empty() && o.parents().empty());
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::swap(" << sn << "&" << (empty ? "" : " other") << ")" << ast.make_noexcept_keyword_text() << " {" << std::endl;
               if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    " << pqn << "::swap(other);" << std::endl;
ast.stream() << std::endl;

               }

               if (!o.local_attributes().empty()) {
ast.stream() << "    using std::swap;" << std::endl;
                   for (const auto& attr : o.local_attributes())
ast.stream() << "    swap(" << attr.member_variable_name() << ", other." << attr.member_variable_name() << ");" << std::endl;
               }
ast.stream() << "}" << std::endl;
            }

            /*
             * Equals method
             */
            // FIXME: looking at root_parent as a hack due to service leafs not
            // FIXME: being processed atm.
            if (!o.is_parent() && !o.parents().empty() && !o.root_parents().empty()) {
                const auto rpn(o.root_parents().front());
ast.stream() << std::endl;
ast.stream() << "bool " << sn << "::equals(const " << ast.get_qualified_name(rpn) << "& other) const {" << std::endl;
ast.stream() << "    const " << sn << "* const p(dynamic_cast<const " << sn << "* const>(&other));" << std::endl;
ast.stream() << "    if (!p) return false;" << std::endl;
ast.stream() << "    return *this == *p;" << std::endl;
ast.stream() << "}" << std::endl;
            }

            /*
             * Equals operator
             */
            std::string method_name;
            if (o.is_parent())
                method_name = "compare";
            else
                method_name = "operator==";
ast.stream() << std::endl;
ast.stream() << "bool " << sn << "::" << method_name << "(const " << sn << "& " << (o.all_attributes().empty() ? "/*rhs*/" : "rhs") << ") const {" << std::endl;

            if (o.all_attributes().empty())
ast.stream() << "    return true;" << std::endl;
            else {
                utility::formatters::sequence_formatter sf(o.parents().size());
                sf.element_separator("");
                sf.prefix_configuration().first("return ").not_first("    ");
                sf.postfix_configuration().not_last(" &&");
                if (o.local_attributes().empty())
                    sf.postfix_configuration().last(";");
                else
                    sf.postfix_configuration().last(" &&");

                if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    " << sf.prefix() << pqn << "::compare(rhs)" << sf.postfix() << std::endl;
                    sf.next();
                }
                sf.reset(o.local_attributes().size());
                sf.element_separator("");
                if (o.parents().empty())
                   sf.prefix_configuration().first("return ");
                else
                   sf.prefix_configuration().first("    ");
                sf.prefix_configuration().not_first("    ");
                sf.postfix_configuration().last(";").not_last(" &&");
                for (const auto& attr : o.local_attributes()) {
ast.stream() << "    " << sf.prefix() << attr.member_variable_name() << " == rhs." << attr.member_variable_name() << sf.postfix() << std::endl;
                    sf.next();
                }
            }
ast.stream() << "}" << std::endl;

            /*
             * Assignment
             */
            if (!o.all_attributes().empty() && !o.is_parent() && !o.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << sn << "& " << sn << "::operator=(" << sn << " other) {" << std::endl;
ast.stream() << "    using std::swap;" << std::endl;
ast.stream() << "    swap(*this, other);" << std::endl;
ast.stream() << "    return *this;" << std::endl;
ast.stream() << "}" << std::endl;
            }

            /*
             * Getters and setters
             */
             for (const auto& attr : o.local_attributes()) {
                 if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << std::endl;
ast.stream() << ast.get_qualified_name(attr.parsed_type()) << " " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
                    if (!o.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << (attr.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << " v) {" << std::endl;
ast.stream() << "    " << attr.member_variable_name() << " = v;" << std::endl;
                        if (attr.is_fluent()) {
ast.stream() << "    return *this;" << std::endl;
                        }
ast.stream() << "}" << std::endl;
                    }
                } else {
ast.stream() << std::endl;
ast.stream() << "const " << ast.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
                    if (!o.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << ast.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << (o.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "& v) {" << std::endl;
ast.stream() << "    " << attr.member_variable_name() << " = v;" << std::endl;
                        if (o.is_fluent()) {
ast.stream() << "    return *this;" << std::endl;
                        }
ast.stream() << "}" << std::endl;
                        if (ast.supports_move_operator()) {
ast.stream() << std::endl;
ast.stream() << (o.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "&& v) {" << std::endl;
ast.stream() << "    " << attr.member_variable_name() << " = std::move(v);" << std::endl;
                            if (o.is_fluent()) {
ast.stream() << "    return *this;" << std::endl;
                            }
ast.stream() << "}" << std::endl;
                        }
                    }
                }
            }
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
