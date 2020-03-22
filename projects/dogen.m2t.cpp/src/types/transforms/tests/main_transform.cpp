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
#include "dogen.logical/types/entities/structural/entry_point.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/main_transform.hpp"

namespace dogen::m2t::cpp::transforms::tests {

std::string main_transform::static_id() {
    return traits::main_archetype();
}

std::string main_transform::id() const {
    return static_id();
}

physical::entities::location
main_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          main_transform::static_id());
    return r;
}

const logical::entities::name& main_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_entry_point_name());
    return r;
}

inclusion_support_types main_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path main_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(main_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path main_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_tests_cpp_implementation(n, static_id());
}

std::list<std::string> main_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& /*e*/) const {

    using logical::entities::structural::object;
    auto builder(f.make());

    using ic = inclusion_constants;
    builder.add(ic::boost::test::unit_test());
    builder.add(ic::boost::test::unit_test_monitor());
    builder.add(ic::boost::exception::info());
    builder.add(ic::std::iostream());
    builder.add(ic::boost::exception::diagnostic_information());

    return builder.build();
}

physical::entities::artefact main_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    using logical::entities::structural::entry_point;
    const auto& ep(a.as<entry_point>(e));
    const auto qn(a.get_qualified_name(ep.name()));
a.stream() << "#define BOOST_TEST_MODULE " << qn << std::endl;
a.stream() << std::endl;
    {
        auto sbf(a.make_scoped_boilerplate_formatter(ep));
a.stream() << std::endl;
a.stream() << "namespace  {" << std::endl;
a.stream() << std::endl;
a.stream() << "const std::string error_msg(\"Error during test.\");" << std::endl;
a.stream() << std::endl;
a.stream() << "inline void translate(const boost::exception& e) {" << std::endl;
a.stream() << "    std::cerr << std::endl << boost::diagnostic_information(e);" << std::endl;
a.stream() << "    throw std::runtime_error(error_msg);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "struct exception_fixture {" << std::endl;
a.stream() << "    exception_fixture() {" << std::endl;
a.stream() << "        using boost::exception;" << std::endl;
a.stream() << "        using boost::unit_test::unit_test_monitor;" << std::endl;
a.stream() << "        unit_test_monitor.register_exception_translator<exception>(&translate);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_GLOBAL_FIXTURE(exception_fixture);" << std::endl;
    } // sbf
    return a.make_artefact();
}
}