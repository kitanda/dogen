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
#include "dogen.identification/types/entities/logical_provenance.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/physical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_id_factory.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/artefact_set.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/text_model_to_physical_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.text_model_to_physical_model_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty_path("Artefact has an empty path. ID: ");
const std::string duplicate_archetype(
    "Found more than one artefact for archetype:");
const std::string duplicate_logical_element(
    "Found more than one artefact set for logical model ID: ");

}

namespace dogen::orchestration::transforms {

physical::entities::model_set text_model_to_physical_model_transform::
apply(const text::transforms::context& ctx,
    const text::entities::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "logical to text model transform",
        transform_id, ms.name().qualified().dot(), *ctx.tracer(), ms);

    physical::entities::model_set r;
    for (const auto& m : ms.models()) {
        /*
         * Update the main model properties.
         */
        physical::entities::model pm;
        pm.configuration(m.root_module()->configuration());
        pm.name().simple(m.name().simple());
        pm.managed_directories(m.managed_directories());

        identification::helpers::physical_id_factory f;
        using namespace identification::entities;
        logical_id id(m.name().qualified().dot());
        pm.name().id(f.make(id, m.output_technical_space()));

        /*
         * Create the provenance for the physical model.
         */
        logical_provenance prov;
        prov.logical_name().simple(m.name().simple());

        prov.logical_name().id(id);
        prov.injection(m.provenance());

        logical_meta_id mid(m.meta_name().id());
        prov.logical_meta_name().id(mid);
        pm.provenance(prov);

        /*
         * Obtain artefact sets from the text model.
         */
        for (const auto& ea : m.elements()) {
            const auto& e(*ea.element());
            physical::entities::artefact_set as;
            as.provenance(ea.artefacts().provenance());

            for (const auto& pair : ea.artefacts().artefacts_by_archetype()) {
                const auto archetype_id(pair.first);
                const auto aptr(pair.second);

                /*
                 * FIXME: we are still generating artefacts for global
                 * module.
                 */
                if (aptr->artefact_properties().file_path().empty()) {
                    BOOST_LOG_SEV(lg, error) << empty_path
                                             << aptr->name().id();
                    // BOOST_THROW_EXCEPTION(transform_exception(empty_path +
                    //         aptr->name().id().value()));
                    continue;
                }

                auto& aba(as.artefacts_by_archetype());
                const auto aa_pair(std::make_pair(archetype_id, aptr));
                const bool inserted(aba.insert(aa_pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_archetype
                                             << archetype_id;
                    BOOST_THROW_EXCEPTION(transform_exception(
                            duplicate_archetype + archetype_id.value()));
                }
            }

            if (!as.artefacts_by_archetype().empty()) {
                auto& asbli(pm.artefact_sets_by_logical_id());
                const auto& leid(e.name().qualified().dot());
                auto pair(std::make_pair(leid, as));
                const bool inserted(asbli.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_logical_element
                                             << leid;
                    BOOST_THROW_EXCEPTION(transform_exception(
                            duplicate_logical_element + leid));
                }
            }
        }
        r.models().push_back(pm);
    }
    return r;
}

}
