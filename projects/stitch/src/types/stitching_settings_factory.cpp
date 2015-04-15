/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/building_error.hpp"
#include "dogen/stitch/types/stitching_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.stitching_settings_factory"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");

}

namespace dogen {
namespace stitch {

stitching_settings_factory::
stitching_settings_factory(const dynamic::schema::repository& rp)
    : formatter_properties_(make_formatter_properties(rp)) {}

stitching_settings_factory::formatter_properties stitching_settings_factory::
make_formatter_properties(const dynamic::schema::repository& rp) const {
    formatter_properties r;
    bool found_stream_variable_name(false), found_template_path(false),
        found_output_path(false), found_inclusion_dependency(false);
    const dynamic::schema::repository_selector s(rp);
    for (const auto fd : s.select_fields_by_model_name(traits::model_name())) {
        if (fd.name().simple() == traits::stream_variable_name()) {
            r.stream_variable_name = fd;
            found_stream_variable_name = true;
        } else if (fd.name().simple() == traits::template_path()) {
            r.template_path = fd;
            found_template_path = true;
        } else if (fd.name().simple() == traits::output_path()) {
            r.output_path = fd;
            found_output_path = true;
        } else if (fd.name().simple() == traits::inclusion_dependency()) {
            r.inclusion_dependency = fd;
            found_inclusion_dependency = true;
        }
    }

    if (!found_stream_variable_name) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::stream_variable_name();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found +
                traits::stream_variable_name()));
    }

    if (!found_template_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::template_path();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::template_path()));
    }

    if (!found_output_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::output_path();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::output_path()));
    }

    if (!found_inclusion_dependency) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::inclusion_dependency();
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found
                + traits::inclusion_dependency()));
    }

    return r;
}

std::string stitching_settings_factory::
extract_stream_variable_name(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    const auto& fp(formatter_properties_);
    return fs.get_text_content_or_default(fp.stream_variable_name);
}

boost::optional<boost::filesystem::path> stitching_settings_factory::
extract_template_path(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    if (!fs.has_field(traits::template_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::template_path()));
    return boost::filesystem::path(text);
}

boost::optional<boost::filesystem::path> stitching_settings_factory::
extract_output_path(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    if (!fs.has_field(traits::output_path()))
        return boost::optional<boost::filesystem::path>();

    const auto text(fs.get_text_content(traits::output_path()));
    return boost::filesystem::path(text);
}

std::list<std::string> stitching_settings_factory::
extract_inclusion_dependencies(const dynamic::schema::object& o) const {
    std::list<std::string> r;
    using namespace dynamic::schema;
    const field_selector fs(o);
    const auto& fd(formatter_properties_.inclusion_dependency);
    if (!fs.has_field(fd))
        return r;

    return fs.get_text_collection_content(fd);
}

stitching_settings stitching_settings_factory::
make(const dynamic::schema::object& o) const {
    stitching_settings r;
    r.stream_variable_name(extract_stream_variable_name(o));
    r.template_path(extract_template_path(o));
    r.output_path(extract_output_path(o));
    r.inclusion_dependencies(extract_inclusion_dependencies(o));
    return r;
}

} }
