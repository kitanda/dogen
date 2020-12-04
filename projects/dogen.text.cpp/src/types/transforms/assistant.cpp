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
#include <sstream>
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.identification/types/entities/technical_space_version.hpp"
#include "dogen.physical/types/entities/meta_model_properties.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/formatters/indent_filter.hpp"
#include "dogen.utility/types/formatters/comment_formatter.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/logical_name_flattener.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/hash/entities/logical_meta_physical_id_hash.hpp"
#include "dogen.text/types/formatters/boilerplate_properties.hpp"
#include "dogen.logical/io/entities/streaming_properties_io.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/lexical_cast/traits.hpp"
#include "dogen.text.cpp/types/transforms/odb/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/tests/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text/types/transforms/helper_chain.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.assistant"));

const std::string empty;
const std::string by_ref_text("&");
const std::string void_keyword_text("void");
const std::string final_keyword_text("final ");
const std::string override_keyword_text(" override");
const std::string noexcept_keyword_text(" noexcept");
const std::string namespace_separator("::");
const std::string member_variable_postfix("_");
const std::string underscore("_");
const std::string dot(".");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string facet_properties_missing(
    "Could not find facet configuration for formatter: ");
const std::string facet_directory_missing(
    "Facet directory is missing for facet: ");
const std::string element_not_found("Element not found: ");
const std::string no_helpers_for_family("No helpers found for family: ");
const std::string helpless_family("No registered helpers found for family: ");

}

namespace dogen::text::cpp::transforms {

using identification::entities::logical_name;
using identification::entities::logical_name_tree;
using identification::entities::technical_space_version;

assistant::assistant(const context& ctx, const logical::entities::element& e,
    const identification::entities::physical_meta_name& pmn,
    const bool requires_header_guard,
    physical::entities::artefact& a)
    : element_(e), context_(ctx), artefact_(a),
      physical_meta_name_(pmn), requires_header_guard_(requires_header_guard) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: "
                             << element_.name().qualified().dot()
                             << " for archetype: "
                             << physical_meta_name_.id();

    utility::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);

    validate();
}

void assistant::validate() const {
    const auto& fn(physical_meta_name_.id());
    const auto& pp(artefact_.path_properties());
    const auto fp(pp.file_path());
    if (fp.empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(
            formatting_error(file_path_not_set + fn.value()));
    }

    if (!requires_header_guard_)
        return;

    const auto& hg(pp.header_guard());
    if (hg.empty()) {
        BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
        BOOST_THROW_EXCEPTION(
            formatting_error(header_guard_not_set + fn.value()));
    }
}

std::string assistant::
make_final_keyword_text(const logical::entities::structural::object& o) const {
    if (is_cpp_standard_98())
        return empty;

    return o.is_final() ? final_keyword_text : empty;
}

std::string assistant::make_override_keyword_text() const {
    if (is_cpp_standard_98())
        return empty;

    return override_keyword_text;
}

std::string assistant::make_noexcept_keyword_text() const {
    if (is_cpp_standard_98())
        return empty;

    return noexcept_keyword_text;
}

std::string
assistant::make_by_ref_text(const logical::entities::attribute& attr) {
    return attr.parsed_type().is_current_simple_type() ? empty : by_ref_text;
}

std::string assistant::
make_setter_return_type(const std::string& containing_type_name,
    const logical::entities::attribute& attr) {

    std::ostringstream s;
    if (attr.is_fluent())
        s << containing_type_name << by_ref_text;
    else
        s << void_keyword_text;

    return s.str();
}

std::string
assistant::get_qualified_name(const logical_name& n) const {
    return n.qualified().colon();
}

std::string
assistant::get_qualified_name(const logical_name_tree& nt) const {
    return nt.qualified().colon();
}

std::string
assistant::get_qualified_namespace(const logical_name& n) const {
    const auto& l(n.location());
    auto ns(l.external_modules());
    for (const auto& m : l.model_modules())
        ns.push_back(m);

    for (const auto& m : l.internal_modules())
        ns.push_back(m);

    using boost::algorithm::join;
    const auto r(join(n.location().model_modules(), namespace_separator));
    return r;
}

std::string assistant::
get_identifiable_model_name(const logical_name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), underscore);
}

std::string assistant::
get_dot_separated_model_name(const logical_name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), dot);
}

std::string
assistant::get_product_name(const logical_name& n) const {
    if (n.location().external_modules().empty())
        return empty;

    return n.location().external_modules().front();
}

physical::entities::facet_properties assistant::obtain_facet_properties(
    const identification::entities::physical_meta_id& facet_name) const {
    const auto& mmp(context_.model().physical().meta_model_properties());
    const auto& fct_props(mmp.facet_properties());
    const auto i(fct_props.find(facet_name));
    if (i == fct_props.end()) {
        BOOST_LOG_SEV(lg, error) << facet_properties_missing
                                 << facet_name;
        BOOST_THROW_EXCEPTION(formatting_error(facet_properties_missing +
                facet_name.value()));
    }
    return i->second;
}

std::list<std::string>
assistant::make_namespaces(const logical_name& n,
    const bool detect_model_name) const {
    identification::helpers::logical_name_flattener nf(detect_model_name);
    return nf.flatten(n);
}

bool assistant::is_archetype_enabled(
    const identification::entities::physical_meta_id& archetype) const {
    identification::entities::logical_id lid(element_.name().qualified().dot());
    identification::entities::logical_meta_physical_id ea(lid, archetype);
    const auto& mmp(context_.model().physical().meta_model_properties());
    const auto& eafe(mmp.enabled_archetype_for_element());
    const auto i(eafe.find(ea));
    const bool is_disabled(i == eafe.end());
    return !is_disabled;
}

bool assistant::is_facet_enabled(
    const identification::entities::physical_meta_id& facet) const {
    const auto& fct_props(obtain_facet_properties(facet));
    return fct_props.enabled();
}

std::string assistant::get_facet_directory_for_facet(
    const identification::entities::physical_meta_id& facet_name) const {
    const auto& fct_props(obtain_facet_properties(facet_name));
    if (fct_props.directory_name().empty()) {
        BOOST_LOG_SEV(lg, error) << facet_directory_missing << facet_name;
        BOOST_THROW_EXCEPTION(
            formatting_error(facet_directory_missing + facet_name.value()));
    }
    return fct_props.directory_name();
}

bool assistant::is_cpp_standard_98() const {
    const auto tsv(context_.technical_space_version());
    return tsv == technical_space_version::cpp_98;
}

bool assistant::is_cpp_standard_17() const {
    const auto tsv(context_.technical_space_version());
    return tsv == technical_space_version::cpp_17;
}

bool assistant::supports_defaulted_functions() const {
    return !is_cpp_standard_98();
}

bool assistant::requires_nested_namespaces() const {
    return is_cpp_standard_17();
}

bool assistant::requires_manual_default_constructor() const {
    /*
     * We are only interested in objects or primitives; all other
     * element types do not need aspect properties.
     */
    using logical::entities::structural::object;
    const auto optr(dynamic_cast<const object*>(&element_));
    using logical::entities::structural::primitive;
    const auto pptr(dynamic_cast<const primitive*>(&element_));

    if (optr != nullptr) {
        return optr->technical_space_properties().
            requires_manual_default_constructor();
    } else if (pptr != nullptr) {
        return pptr->technical_space_properties().
            requires_manual_default_constructor();
    }
    return false;
}

bool assistant::supports_move_operator() const {
    return !is_cpp_standard_98();
}

bool assistant::requires_manual_move_constructor() const {
    /*
     * We are only interested in objects or primitives; all other
     * element types do not need aspect properties.
     */
    using logical::entities::structural::object;
    const auto optr(dynamic_cast<const object*>(&element_));
    using logical::entities::structural::primitive;
    const auto pptr(dynamic_cast<const primitive*>(&element_));

    if (optr != nullptr) {
        return optr->technical_space_properties().
            requires_manual_move_constructor();
    } else if (pptr != nullptr) {
        return pptr->technical_space_properties().
            requires_manual_move_constructor();
    }
    return false;
}

bool assistant::requires_stream_manipulators() const {
    /*
     * We are only interested in objects or primitives; all other
     * element types do not need aspect properties.
     */
    using logical::entities::structural::object;
    const auto optr(dynamic_cast<const object*>(&element_));
    using logical::entities::structural::primitive;
    const auto pptr(dynamic_cast<const primitive*>(&element_));

    if (optr != nullptr) {
        return optr->technical_space_properties().
            requires_stream_manipulators();
    } else if (pptr != nullptr) {
        return pptr->technical_space_properties().
            requires_stream_manipulators();
    }
    return false;
}

bool assistant::is_serialization_enabled() const {
    using transforms::serialization::traits;
    identification::entities::physical_meta_id
        ca(traits::canonical_archetype());
    return is_archetype_enabled(ca);
}

bool assistant::is_io_enabled() const {
    using transforms::io::traits;
    identification::entities::physical_meta_id
        ca(traits::canonical_archetype());
    return is_archetype_enabled(ca);
}

bool assistant::is_lexical_cast_enabled() const {
    using transforms::lexical_cast::traits;
    identification::entities::physical_meta_id
        ca(traits::canonical_archetype());
    return is_archetype_enabled(ca);
}

bool assistant::is_odb_facet_enabled() const {
    using transforms::odb::traits;
    identification::entities::physical_meta_id
        fqn(traits::facet_qn());
    return is_facet_enabled(fqn);
}

bool assistant::is_tests_enabled() const {
    using transforms::tests::traits;
    identification::entities::physical_meta_id
        fqn(traits::facet_qn());
    return is_facet_enabled(fqn);
}

bool assistant::is_hash_enabled() const {
    using transforms::hash::traits;
    identification::entities::physical_meta_id
        ca(traits::canonical_archetype());
    return is_archetype_enabled(ca);
}

bool assistant::is_test_data_enabled() const {
    using transforms::test_data::traits;
    identification::entities::physical_meta_id
        fqn(traits::facet_qn());
    return is_facet_enabled(fqn);
}

text::formatters::scoped_boilerplate_formatter assistant::
make_scoped_boilerplate_formatter(const logical::entities::element& e,
    const identification::entities::technical_space ts) {
    text::formatters::boilerplate_properties bp;

    const auto pp(artefact_.path_properties());
    bp.dependencies(pp.inclusion_dependencies());
    bp.header_guard(pp.header_guard());
    bp.technical_space(ts);
    const auto i(e.decoration().find(ts));
    if (i != e.decoration().end() && i->second) {
        const auto dec(*i->second);
        bp.preamble(dec.preamble());
        bp.postamble(dec.postamble());
    }
    bp.generate_preamble(true);
    bp.generate_header_guards(true);

    using text::formatters::scoped_boilerplate_formatter;
    return scoped_boilerplate_formatter(stream(), bp);
}

text::formatters::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return text::formatters::scoped_namespace_formatter(
        stream(), identification::entities::technical_space::cpp,
        ns, true/*add_new_line*/, requires_nested_namespaces());
}

void assistant::make_decoration_preamble(const logical::entities::element& e,
    const identification::entities::technical_space ts) {

    const auto i(e.decoration().find(ts));
    if (i != e.decoration().end() && i->second) {
        const auto dec(*i->second);
        stream() << dec.preamble();
    }
}

void assistant::comment(const std::string& c) {
    if (c.empty())
        return;

    utility::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        utility::formatters::comment_style::c_style,
        !last_line_is_blank);
    f.format(stream(), c);
}

void assistant::
comment_start_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        utility::formatters::positive_indenter_scope pis(stream());
        utility::formatters::comment_formatter f(
            !start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            utility::formatters::comment_style::c_style,
            !last_line_is_blank);

        f.format(stream(), documentation);
        if (add_comment_blocks) {
            f.format_doxygen_start_block(stream(), documentation);
            stream() << std::endl;
        }
    }
}

void assistant::comment_end_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        utility::formatters::positive_indenter_scope pis(stream());
        utility::formatters::comment_formatter f(
            start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            utility::formatters::comment_style::c_style,
            !last_line_is_blank);

        if (add_comment_blocks) {
            f.format_doxygen_end_block(stream(), documentation);
            stream() << std::endl;
        }
    }
}

std::string assistant::comment_inline(const std::string& c) const {
    if (c.empty())
        return empty;

    std::ostringstream s;
    s << " ";
    utility::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        utility::formatters::comment_style::cpp_style,
        !last_line_is_blank);

    f.format(s, c);
    return s.str();
}

bool assistant::is_io() const {
    const auto fn(physical_meta_name_.location().facet());
    return transforms::io::traits::facet_sn()  == fn;
}

void assistant::add_helper_methods(const std::string& /*element_id*/) {
    dogen::text::transforms::helper_chain::model_ =
        &context_.model().physical();
    dogen::text::transforms::helper_chain::apply(stream(),
        context_.model().logical(), element_, artefact_);
}

std::string assistant::
streaming_for_type(const logical::entities::streaming_properties& sp,
    const std::string& s) const {

    std::ostringstream stream;
    utility::formatters::utility_formatter uf(stream);
    BOOST_LOG_SEV(lg, debug) << "Streaming properties for type: " << sp;
    if (sp.remove_unprintable_characters())
        uf.insert_streamed("tidy_up_string(" + s + ")");
    else if (!sp.string_conversion_method().empty()) {
        // FIXME: hack to determine if we are being dereferenced.
        std::string s1(s);
        const auto i(s1.find('*'));
        if (i != std::string::npos)
            s1 = "(" + s + ")";
        uf.insert_streamed(s1 + "." + sp.string_conversion_method());
    } else if (sp.requires_quoting())
        uf.insert_streamed(s);
    else
        uf.insert(s);

    return stream.str();
}

std::string assistant::streaming_for_type(const logical_name& n,
    const std::string& s) const {

    const auto str_propss(context_.model().logical().streaming_properties());
    const auto i(str_propss.find(n.id()));
    if (i == str_propss.end())
        return s;

    return streaming_for_type(i->second, s);
}

bool assistant::requires_hashing_helper_method(
    const logical::entities::attribute& attr) const {
    const auto& hps(element_.helper_properties());
    for (const auto& hlp_props : hps) {
        const auto ident(attr.parsed_type().qualified().identifiable());
        const auto& desc(hlp_props.current());
        if (ident != desc.name_tree_identifiable())
            continue;

        if (desc.requires_hashing_helper())
            return true;
    }
    return false;
}

std::list<logical_name> assistant::names_with_enabled_archetype(
    const identification::entities::physical_meta_id& archetype,
    const std::list<logical_name> names) const {
    std::list<logical_name> r;
    const auto& mmp(context_.model().physical().meta_model_properties());
    const auto& eafe(mmp.enabled_archetype_for_element());
    for (const auto& n : names) {
        const identification::entities::logical_id lid(n.qualified().dot());
        BOOST_LOG_SEV(lg, debug) << "Checking enablement for name: " << lid;
        identification::entities::logical_meta_physical_id ea(lid, archetype);
        const auto i(eafe.find(ea));
        const bool is_disabled(i == eafe.end());
        if (is_disabled)
            continue;

        r.push_back(n);
    }
    return r;
}

std::ostream& assistant::stream() {
    return filtering_stream_;
}

void assistant::update_artefact() const {
    artefact_.content(stream_.str());

    const auto fp(artefact_.path_properties().file_path());
    artefact_.file_path(fp);

    physical::entities::operation op;
    using ot = physical::entities::operation_type;
    const bool overwrite(artefact_.enablement_properties().overwrite());
    op.type(overwrite? ot::write : ot::create_only);
    artefact_.operation(op);
}

}
