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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.assets/types/meta_model/structural/entry_point.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/types/main_formatter.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"

namespace dogen::generation::cpp::formatters::types {

std::string main_formatter::static_id() {
    return traits::main_archetype();
}

std::string main_formatter::id() const {
    return static_id();
}

archetypes::location
main_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          main_formatter::static_id());
    return r;
}

const assets::meta_model::name& main_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_entry_point_name());
    return r;
}

std::string main_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types main_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path main_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(main_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path main_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> main_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const assets::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact main_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<assets::meta_model::structural::entry_point>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(o));
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "int main(int /*argc*/, char* /*argv*/[]) {" << std::endl;
a.stream() << "    return 0;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}