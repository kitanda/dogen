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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/features/primitive.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/primitives_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.primitives_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string csharp_value("Value");
const std::string cpp_value("value");
const std::string documentation("Obtain the underlying value.");

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");
const std::string missing_underlier(
    "Primitive does not have an underlying element name: ");

}

namespace dogen::assets::transforms {

std::string primitives_transform::
obtain_value_attribute_simple_name(const meta_model::technical_space ts) {
    using meta_model::technical_space;
    switch(ts) {
    case technical_space::csharp: return csharp_value;
    case technical_space::cpp: return cpp_value;
    default: {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_technical_space + s));
    } }
}

meta_model::attribute
primitives_transform::create_attribute_for_underlying_element(
    const meta_model::name& owner, const meta_model::technical_space ts,
    std::string underlying_element) {

    /*
     * Obtain the underlying element name from the meta-data. If there
     * isn't one, bomb out as primitives require it.
     */
    const auto ue(boost::algorithm::trim_copy(underlying_element));
    if (ue.empty()) {
        const auto id(owner.qualified().dot());
        BOOST_LOG_SEV(lg, error) << missing_underlier << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_underlier + id));
    }

    /*
     * Create the name for the value attribute.
     */
    helpers::name_factory nf;
    const auto& n(owner);
    const auto sn(obtain_value_attribute_simple_name(ts));

    /*
     * Create the name value attribute.
     */
    meta_model::attribute r;
    r.name(nf.build_attribute_name(n, sn));
    r.unparsed_type(ue);
    r.documentation(documentation);

    return r;
}

void primitives_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "primitives transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * Obtain the feature groups.
     */
    const auto& fm(*ctx.feature_model());
    const auto fg(features::primitive::make_feature_group(fm));

    /*
     * Update each primitive, using data read from its dynamic
     * configuration.
     */
    const auto its(m.input_technical_space());
    for (auto& pair : m.structural_elements().primitives()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Transforming: " << id;

        /*
         * Convert the dynamic configuration into the static
         * configuration.
         */
        auto& p(*pair.second);
        const auto scfg(features::primitive::make_static_configuration(fg, p));

        /*
         * Update all properties.
         */
        p.is_nullable(scfg.is_nullable);
        p.use_type_aliasing(scfg.use_type_aliasing);
        p.value_attribute(create_attribute_for_underlying_element(p.name(), its,
                scfg.underlying_element));
    }

    stp.end_transform(m);
}

}