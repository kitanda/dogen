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
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.generation.cpp/types/formattables/adapter.hpp"
#include "dogen.generation.cpp/types/fabric/common_odb_options.hpp"
#include "dogen.generation.cpp/types/fabric/object_odb_options.hpp"
#include "dogen.generation.cpp/types/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen.generation.cpp/io/formattables/odb_properties_io.hpp"
#include "dogen.generation.cpp/types/formattables/header_guard_factory.hpp"
#include "dogen.generation.cpp/types/formatters/odb/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formattables/odb_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.odb_expander"));

const std::string empty_column_attribute("column(\"\")");
const std::string id_pragma("id");
const std::string no_id_pragma("no_id");

const std::string null_pragma("null");
const std::string not_null_pragma("not_null");
const std::string value_pragma("value");

}

namespace dogen::generation::cpp::formattables {

class updator : public element_visitor {
public:
    updator(model& fm, const locator& l,
        const odb_expander::feature_group& fg);

private:
    std::string make_type_overrides(const std::unordered_map<
        assets::meta_model::orm::database_system, std::string>& type_overrides)
    const;

    std::list<std::string> make_odb_pragmas(
        const variability::meta_model::configuration& cfg) const;

public:
    using element_visitor::visit;
    void visit(fabric::common_odb_options& coo);
    void visit(fabric::object_odb_options& ooo);
    void visit(assets::meta_model::structural::object& o);
    void visit(assets::meta_model::structural::primitive& p);

public:
    const boost::optional<odb_properties>& result() const;

private:
    const model& model_;
    const locator locator_;
    const odb_expander::feature_group& feature_group_;
    boost::optional<odb_properties> result_;
};

updator::
updator(model& fm, const locator& l, const odb_expander::feature_group& fg)
    : model_(fm), locator_(l), feature_group_(fg) {}

std::string
updator::make_type_overrides(const std::unordered_map<
    assets::meta_model::orm::database_system, std::string>& type_overrides)
    const {
    if (!type_overrides.empty())
        return std::string();

    std::ostringstream s;
    bool is_first(true);
    for (const auto pair : type_overrides) {
        if (!is_first)
            s << " ";

        const auto ds(pair.first);
        const auto type(pair.second);
        s << adapter::to_odb_database(ds)
          << ":type(\"" << type << "\")";
        is_first = false;
    }

    return s.str();
}

std::list<std::string> updator::make_odb_pragmas(
    const variability::meta_model::configuration& cfg) const {

    const variability::helpers::configuration_selector s(cfg);
    if (!s.has_configuration_point(feature_group_.odb_pragma))
        return std::list<std::string>();

    return s.get_text_collection_content(feature_group_.odb_pragma);
}

void updator::visit(fabric::common_odb_options& coo) {
    coo.databases(model_.odb_databases());
    coo.sql_name_case(model_.odb_sql_name_case());
}

void updator::visit(fabric::object_odb_options& ooo) {
    const auto odb_arch(formatters::odb::traits::class_header_archetype());
    const auto odb_rp(locator_.make_inclusion_path_for_cpp_header(ooo.name(),
            odb_arch));

    std::ostringstream os;
    os << "'#include \"" << odb_rp.generic_string() << "\"'";
    ooo.epilogue(os.str());
    os.str("");

    const auto types_arch(formatters::types::traits::class_header_archetype());
    const auto types_rp(locator_.make_inclusion_path_for_cpp_header(ooo.name(),
            types_arch).parent_path());

    os << "'%(.*).hpp%" << types_rp.generic_string() << "/$1.hpp%'";
    ooo.include_regexes().push_back(os.str());

    os.str("");
    os << "'%(^[a-zA-Z0-9_]+)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    ooo.include_regexes().push_back(os.str());

    os.str("");
    os << "'%" << types_rp.generic_string() << "/(.*)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    ooo.include_regexes().push_back(os.str());
    ooo.header_guard_prefix(header_guard_factory::make(odb_rp.parent_path()));
}

void updator::visit(assets::meta_model::structural::object& o) {
    odb_properties op;

    auto top_level_pragmas(make_odb_pragmas(*o.configuration()));
    if (o.orm_properties()) {
        /*
         * If the user has supplied an ORM properties and this
         * object does not have a primary key, we need to inject ODB's
         * pragma for it.
         */
        const auto& cfg(*o.orm_properties());
        op.is_value(cfg.is_value());

        if (cfg.generate_mapping() && !op.is_value() && !cfg.has_primary_key())
            top_level_pragmas.push_back(no_id_pragma);

        using assets::meta_model::orm::letter_case;
        const auto& sn(cfg.schema_name());
        if (!sn.empty() && (op.is_value() || cfg.generate_mapping())) {
            std::ostringstream s;
            s << "schema(\"" << cfg.capitalised_schema_name() << "\")";
            top_level_pragmas.push_back(s.str());
        }
    }

    op.top_level_odb_pragmas(top_level_pragmas);

    for (const auto& attr : o.local_attributes()) {
        const auto id(attr.name().qualified().dot());
        auto attr_pragmas(make_odb_pragmas(*attr.configuration()));

        if (attr.orm_properties()) {
            const auto& cfg(*attr.orm_properties());
            if (cfg.is_primary_key())
                attr_pragmas.push_back(id_pragma);

            /*
             * For composite keys, we do not want to use the column
             * name as a prefix.
             */
            if (cfg.is_composite())
                attr_pragmas.push_back(empty_column_attribute);

            if (cfg.is_nullable()) {
                if (*cfg.is_nullable())
                    attr_pragmas.push_back(null_pragma);
                else
                    attr_pragmas.push_back(not_null_pragma);
            }

            if (!cfg.type_overrides().empty()) {
                const auto to(make_type_overrides(cfg.type_overrides()));
                attr_pragmas.push_back(to);
            }
        }

        if (attr_pragmas.empty())
            continue;

        op.attribute_level_odb_pragmas()[id] = attr_pragmas;
    }

    const bool has_top_level_pragmas(!op.top_level_odb_pragmas().empty());
    const bool has_attribute_pragmas(!op.attribute_level_odb_pragmas().empty());
    const bool has_pragmas(has_top_level_pragmas || has_attribute_pragmas);

    if (has_pragmas)
        result_ = op;
}

void updator::visit(assets::meta_model::structural::primitive& p) {
    odb_properties op;
    op.is_value(true);
    op.top_level_odb_pragmas(make_odb_pragmas(*p.configuration()));

    if (p.orm_properties()) {
        const auto& cfg(*p.orm_properties());

        const auto& sn(cfg.schema_name());
        if (!sn.empty() && cfg.generate_mapping()) {
            std::ostringstream s;
            s << "schema(\"" << cfg.capitalised_schema_name() << "\")";
            op.top_level_odb_pragmas().push_back(s.str());
        }

        for (const auto& tm: cfg.type_mappings()) {
            std::ostringstream s;
            s << "map ";
            if (tm.database())
                s << adapter::to_odb_database(*tm.database()) << ":";

            s << "type(\"" << tm.source_type() << "\") as (\""
              << tm.destination_type() << "\")";

            if (!tm.to_source_type().empty())
                s << "to(\"" << tm.to_source_type() << "\")";

            if (!tm.to_destination_type().empty())
                s << "to(\"" << tm.to_destination_type() << "\")";

            op.top_level_odb_pragmas().push_back(s.str());
        }
    }

    const bool has_top_level_pragmas(!op.top_level_odb_pragmas().empty());
    if (!has_top_level_pragmas)
        return;

    /*
     * For primitives, we need to inject manually the attribute level
     * pragmas, if there was a top-level pragma. This is because users
     * cannot see the internal attribute.
     *
     * We add this pragma so as to name the primitive's internal value
     * attribute correctly. Primitives do not have column names; they
     * are set by the type that owns them. This avoids names such as
     * "primitive_id_primitive_id", which become "primitive_id"
     * instead.
     *
     * In addition, we also need to obtain all of the type overrides.
     */
    std::ostringstream s;
    s << empty_column_attribute;
    if (p.orm_properties() && !p.orm_properties()->type_overrides().empty())
        s << make_type_overrides(p.orm_properties()->type_overrides());
    const auto pragmas = std::list<std::string> { s.str() };

    const auto& attr(p.value_attribute());
    const auto id(attr.name().qualified().dot());
    op.attribute_level_odb_pragmas()[id] = pragmas;
    result_ = op;
}

const boost::optional<odb_properties>&
updator::result() const {
    return result_;
}

odb_expander::feature_group odb_expander::
make_feature_group(const variability::meta_model::feature_model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Creating feature groups.";

    feature_group r;
    const variability::helpers::feature_selector s(fm);
    const auto& op(formatters::odb::traits::odb_pragma());
    r.odb_pragma = s.get_by_name(op);

    BOOST_LOG_SEV(lg, debug) << "Created feature groups.";
    return r;
}

void odb_expander::expand(
    const variability::meta_model::feature_model& feature_model,
    const locator& l, model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding odb properties.";

    const auto fg(make_feature_group(feature_model));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        /*
         * We only need to generate the aspect properties for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspect propertiess must
         * be build prior to reduction or else we will not get aspects
         * for referenced models.
         */
        auto segment(formattable.master_segment());
        if (segment->origin_type() != assets::meta_model::origin_types::target)
            continue;

        for (const auto& ptr : formattable.all_segments()) {
            auto& e(*ptr);
            updator g(fm, l, fg);
            e.accept(g);

            if (!g.result())
                continue;

            auto& eprops(formattable.element_properties());
            eprops.odb_properties(*g.result());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb properties. ";
}

}
