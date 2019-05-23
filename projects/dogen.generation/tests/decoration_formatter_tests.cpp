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
#include <list>
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.assets/types/meta_model/technical_space.hpp"
#include "dogen.assets/types/meta_model/decoration/modeline.hpp"
#include "dogen.assets/types/meta_model/decoration/generation_marker.hpp"
#include "dogen.generation/types/formatters/indent_filter.hpp"
#include "dogen.generation/types/formatters/decoration_formatter.hpp"

namespace {

const std::string test_module("dogen.generation.tests");
const std::string test_suite("decoration_formatter_tests");
const std::string empty;
const auto empty_copyright_notices = std::list<std::string> { };

const std::string expected_cpp_modeline_top(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
)");

const std::string expected_cpp_multiline_licence(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 * another_holder
 *
 * first line of licence text
 * second line of licence text
 *
 */
)");

const std::string expected_cpp_modeline_bottom(
    R"(/*
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
/*
 * Local variables:
 * a_field: a_value
 * End:
 */
)");

const std::string expected_cpp_no_marker(
    R"(/* -*- a_field: a_value -*-
 *
 * a_holder
 *
 * licence text
 *
 */
)");

const std::string expected_cpp_no_licence(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 */
)");

const std::string expected_cpp_licence_no_copyright_notices(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * licence text
 *
 */
)");

const std::string expected_cpp_just_marker(R"(/*
 * this is a marker
 *
 */
)");

const std::string expected_cpp_just_modeline_top(
    R"(// -*- a_field: a_value -*-
)");

const std::string expected_cpp_just_modeline_bottom(
    R"(/*
 * Local variables:
 * a_field: a_value
 * End:
 */
)");

const std::string expected_csharp_modeline_top(
    R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
//
// licence text
//
)");

const std::string expected_csharp_multiline_licence(
    R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
// another_holder
//
// first line of licence text
// second line of licence text
//
)");

const std::string expected_csharp_modeline_bottom(
    R"(//
// this is a marker
//
// a_holder
//
// licence text
//
//
// Local variables:
// a_field: a_value
// End:
)");

const std::string expected_csharp_no_marker(
    R"(// -*- a_field: a_value -*-
//
// a_holder
//
// licence text
//
)");

const std::string expected_csharp_no_licence(
    R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
//
)");

const std::string expected_csharp_licence_no_copyright_notices(
    R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// licence text
//
)");

const std::string expected_csharp_just_marker(
    R"(//
// this is a marker
//
)");

const std::string expected_csharp_just_modeline_top(
    R"(// -*- a_field: a_value -*-
)");

const std::string expected_csharp_just_modeline_bottom(
    R"(//
// Local variables:
// a_field: a_value
// End:
)");

const std::string disable_top_modeline(
    "Logging to disable modeline at the top.");
const std::string disable_bottom_modeline(
    "Logging to disable modeline at the bottom");

const std::string single_line_licence_text("licence text");
const std::string multi_line_licence_text(
    R"(first line of licence text
second line of licence text
)");

const std::string copyright_holder_1("a_holder");
const std::string copyright_holder_2("another_holder");
const std::string first_field_name("a_field");
const std::string first_field_value("a_value");
const std::string single_line_marker_message("this is a marker");

std::string make_licence(const bool is_multi_line = false) {
    if (is_multi_line)
        return multi_line_licence_text;
    return single_line_licence_text;
}

std::list<std::string>
make_copyright_notices(const bool with_multiple_holders = false) {
    std::list<std::string> r;
    r.push_back(copyright_holder_1);
    if (with_multiple_holders)
        r.push_back(copyright_holder_2);
    return r;
}

using namespace dogen::assets::meta_model;
using namespace dogen::assets::meta_model::decoration;
boost::shared_ptr<generation_marker> empty_marker;
boost::shared_ptr<modeline> empty_modeline;

boost::shared_ptr<modeline>
make_modeline(const bool is_top = true) {
    auto r(boost::make_shared<modeline>());
    r->editor(editor::emacs);
    r->technical_space(technical_space::cpp);

    modeline_field f;
    f.name(first_field_name);
    f.value(first_field_value);
    r->fields().push_back(f);
    r->location(is_top ? modeline_location::top : modeline_location::bottom);
    return r;
}

boost::shared_ptr<generation_marker> make_generation_marker() {
    auto r(boost::make_shared<generation_marker>());
    r->message(single_line_marker_message);
    return r;
}

using namespace dogen::generation::formatters;
std::string format_preamble(
    const comment_style& cs,
    const std::string& licence_text,
    const std::list<std::string>& copyright_notices,
    const boost::shared_ptr<modeline> ml, const
    boost::shared_ptr<generation_marker> gm) {

    std::ostringstream s;
    decoration_formatter f;
    f.format_preamble(s, cs, licence_text, copyright_notices, ml, gm);
    f.format_postamble(s, cs,  ml);
    return s.str();
}

}

using namespace dogen::generation::formatters;
using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(decoration_formatter_tests)

BOOST_AUTO_TEST_CASE(cpp_top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_top_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            make_licence(),
            make_copyright_notices(),
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_cpp_modeline_top);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_top_modeline_and_multiline_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_top_modeline_and_multiline_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            make_licence(true/*is_multi_line*/),
            make_copyright_notices(true/*with_multiple_holders*/),
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_cpp_multiline_licence);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_bottom_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_bottom_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            make_licence(),
            make_copyright_notices(),
            make_modeline(false/*is_top*/),
            make_generation_marker()));

    const auto& e(expected_cpp_modeline_bottom);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_no_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_no_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            make_licence(),
            make_copyright_notices(),
            make_modeline(),
            empty_marker));

    const auto& e(expected_cpp_no_marker);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_no_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_no_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            empty,
            make_copyright_notices(),
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_cpp_no_licence);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_licence_with_text_but_no_copyright_notices_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_licence_with_text_but_no_copyright_notices_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            make_licence(),
            empty_copyright_notices,
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_cpp_licence_no_copyright_notices);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_preamble_with_just_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_preamble_with_just_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            empty,
            empty_copyright_notices,
            empty_modeline,
            make_generation_marker()));

    const auto& e(expected_cpp_just_marker);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_preamble_with_just_modeline_at_the_top_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_preamble_with_just_modeline_at_the_top_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::cpp_style,
            empty,
            empty_copyright_notices,
            make_modeline(),
            empty_marker));

    const auto& e(expected_cpp_just_modeline_top);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(cpp_postamble_with_just_modeline_at_the_bottom_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_postamble_with_just_modeline_at_the_bottom_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            empty,
            empty_copyright_notices,
            make_modeline(false/*is_top*/),
            empty_marker));

    const auto& e(expected_cpp_just_modeline_bottom);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(not_supplying_content_results_in_no_boilerplate) {
    SETUP_TEST_LOG_SOURCE("not_supplying_content_results_in_no_boilerplate");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::c_style,
            empty,
            empty_copyright_notices,
            empty_modeline,
            empty_marker));

    const auto& e(empty);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_top_modeline_is_formatted_correctly");

    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            make_licence(),
            make_copyright_notices(),
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_csharp_modeline_top);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_top_modeline_and_multiline_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_top_modeline_and_multiline_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            make_licence(true/*is_multi_line*/),
            make_copyright_notices(true/*with_multiple_holders*/),
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_csharp_multiline_licence);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_bottom_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_bottom_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            make_licence(),
            make_copyright_notices(),
            make_modeline(false/*is_top*/),
            make_generation_marker()));

    const auto& e(expected_csharp_modeline_bottom);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_no_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_no_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            make_licence(),
            make_copyright_notices(),
            make_modeline(),
            empty_marker));

    const auto& e(expected_csharp_no_marker);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_no_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_no_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            empty,
            make_copyright_notices(),
            make_modeline(),
            make_generation_marker()));

    const auto& e(expected_csharp_no_licence);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_preamble_with_just_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_preamble_with_just_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            empty,
            empty_copyright_notices,
            empty_modeline,
            make_generation_marker()));

    const auto& e(expected_csharp_just_marker);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_preamble_with_just_modeline_at_the_top_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_preamble_with_just_modeline_at_the_top_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            empty,
            empty_copyright_notices,
            make_modeline(),
            empty_marker));

    const auto& e(expected_csharp_just_modeline_top);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_CASE(csharp_postamble_with_just_modeline_at_the_bottom_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_postamble_with_just_modeline_at_the_bottom_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << disable_top_modeline;

    const auto a(format_preamble(
            comment_style::csharp_style,
            empty,
            empty_copyright_notices,
            make_modeline(false/*is_top*/),
            empty_marker));

    const auto& e(expected_csharp_just_modeline_bottom);
    BOOST_CHECK(asserter::assert_equals_string(e, a));

    BOOST_LOG_SEV(lg, debug) << disable_bottom_modeline;
}

BOOST_AUTO_TEST_SUITE_END()
