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
#include "dogen.assets/types/features/enumerator.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::assets::features {

namespace {

dogen::variability::meta_model::feature_template
make_masd_enumeration_add_invalid_enumerator() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("add_invalid_enumerator");
    r.name().qualified("masd.enumeration.add_invalid_enumerator");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_enumerator_value() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("value");
    r.name().qualified("masd.enumerator.value");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}

enumerator::feature_group
enumerator::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.add_invalid_enumerator = s.get_by_name("masd.enumeration.add_invalid_enumerator");
    r.value = s.get_by_name("masd.enumerator.value");

    return r;
}

enumerator::static_configuration enumerator::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.add_invalid_enumerator = s.get_boolean_content_or_default(fg.add_invalid_enumerator);
    if (s.has_configuration_point(fg.value))
        r.value = s.get_text_content(fg.value);
    return r;
}

std::list<dogen::variability::meta_model::feature_template>
enumerator::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature_template> r;
    r.push_back(make_masd_enumeration_add_invalid_enumerator());
    r.push_back(make_masd_enumerator_value());
    return r;
}

}
