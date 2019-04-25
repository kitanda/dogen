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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_model_set_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_set_io.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.orchestration/types/transforms/context.hpp"
#include "masd.dogen.orchestration/types/transforms/transform_exception.hpp"
#include "masd.dogen.orchestration/types/transforms/coding_model_set_to_configuration_model_set_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.coding_model_set_to_configuration_model_set_transform");
using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_qualified_name(
    "Duplicate qualified name for configuration: ");

}

namespace masd::dogen::orchestration::transforms {

namespace {

class extractor {
private:
    template<typename NameableAndConfigurable>
    void extract(NameableAndConfigurable& nac) {
        const auto qn(nac.name().qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Extracting: "
                                 << nac.name().simple()
                                 << " (" << qn << ") ";

        auto pair(std::make_pair(qn, nac.configuration()));
        const auto inserted(model_.local().insert(pair).second);

        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << qn;
            BOOST_THROW_EXCEPTION(
                transform_exception(duplicate_qualified_name + qn));
        }
    }

public:
    void operator()(coding::meta_model::element&) { }
    void operator()(coding::meta_model::module& m) {
        if (m.is_root())
            model_.global(m.configuration());
        else
            extract(m);
    }
    void operator()(coding::meta_model::object_template& ot) {
        extract(ot);
        for (auto& attr : ot.local_attributes())
            extract(attr);
    }
    void operator()(coding::meta_model::builtin& b) { extract(b); }
    void operator()(coding::meta_model::enumeration& e) {
        extract(e);
        for (auto& enm : e.enumerators())
            extract(enm);
    }
    void operator()(coding::meta_model::primitive& p) { extract(p); }
    void operator()(coding::meta_model::object& o) {
        extract(o);
        for (auto& attr : o.local_attributes())
            extract(attr);
    }
    void operator()(coding::meta_model::exception& e) { extract(e); }
    void operator()(coding::meta_model::visitor& v) { extract(v); }
    void operator()(coding::meta_model::licence& l) { extract(l); }
    void operator()(coding::meta_model::modeline& ml) { extract(ml); }
    void operator()(coding::meta_model::modeline_group& mg) { extract(mg); }
    void operator()(coding::meta_model::generation_marker& gm) { extract(gm); }

public:
    variability::meta_model::configuration_model& result() {
        return model_;
    }

private:
    variability::meta_model::configuration_model model_;
};

}

variability::meta_model::configuration_model
coding_model_set_to_configuration_model_set_transform::
to_configuration_model(const coding::meta_model::model& m) {
    extractor e;
    coding::meta_model::elements_traversal(m, e);
    return e.result();
}

variability::meta_model::configuration_model_set
coding_model_set_to_configuration_model_set_transform::
apply(const context& ctx, const coding::meta_model::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg,
        "coding model to generation model transform",
        transform_id, *ctx.variability_context().tracer(), ms);

    variability::meta_model::configuration_model_set r;
    r.models().push_back(to_configuration_model(ms.target()));

    for (const auto& m : ms.references())
        r.models().push_back(to_configuration_model(m));

    stp.end_transform(r);
    return r;
}

}
