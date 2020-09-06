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
#include <typeindex>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/hash/entities/logical_meta_id_hash.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_support_types.hpp"
#include "dogen.text.cpp/types/transforms/model_to_text_transform.hpp"
#include "dogen.text.cpp/types/formattables/canonical_archetype_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("text.cpp.formattables.canonical_archetype_expander"));

}

namespace dogen::text::cpp::formattables {

void canonical_archetype_expander::expand(const transforms::repository& frp,
    formattables::element_properties& eprops,
    const logical::entities::element& e) const {
    BOOST_LOG_SEV(lg, debug) << "Procesing element: "
                             << e.name().qualified().dot();
    const auto cs(transforms::inclusion_support_types::canonical_support);
    const auto& safmt(frp.stock_artefact_formatters_by_meta_name());

    /*
     * For each element segment, find the corresponding formatters.
     */
    const auto mid(e.meta_name().id());
    BOOST_LOG_SEV(lg, debug) << "Meta-type: " << mid;

    /*
     * Not all elements have formatters; for example, object templates
     * don't have any at present. If so, skip the element.
     */
    const auto i(safmt.find(mid));
    if (i == safmt.end()) {
        BOOST_LOG_SEV(lg, debug) << "Element has no formatters.";
        return;
    }

    /*
     * Find the canonical formatter for the element and slot it in,
     * pairing the canonical name against the formatter name.
     */
    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        if (fmt.inclusion_support_type() != cs)
            continue;

        const auto pmn(fmt.archetype().meta_name());
        const auto arch(pmn.id());
        identification::helpers::physical_meta_id_builder b;
        const auto fct(b.build_facet(pmn));

        const auto carch(transforms::traits::canonical_archetype(fct.value()));
        eprops.canonical_archetype_to_archetype()[carch] = arch.value();
        BOOST_LOG_SEV(lg, debug) << "Mapped " << carch << " to " << arch;
    }
    BOOST_LOG_SEV(lg, debug) << "Processed element.";
}

void canonical_archetype_expander::
expand(const transforms::repository& frp, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expansion.";
    for (auto& pair : fm.formattables()) {
        auto& formattable(pair.second);
        auto& eprops(pair.second.element_properties());
        const auto& e(*formattable.element());
        expand(frp, eprops, e);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished expansion.";
}

}
