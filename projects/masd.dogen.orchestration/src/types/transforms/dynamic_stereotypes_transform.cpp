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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/io/meta_model/model_set_io.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.orchestration/types/transforms/dynamic_stereotypes_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.dynamic_stereotypes_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::orchestration::transforms {

namespace {

class updater {
private:
    template<typename Configurable>
    std::list<std::string> extract(Configurable& c) {
        const auto& n(c.configuration()->name());
        const auto& qn(n.qualified());
        BOOST_LOG_SEV(lg, trace) << "Extracting: "
                                 << n.simple()
                                 << " (" << qn << ") ";

        std::list<std::string> r;
        const auto& pbs(c.configuration()->profile_bindings());
        for (const auto& pb : pbs) {
            if (!pb.realized())
                r.push_back(pb.name());
        }
        return r;
    }

    void update(coding::meta_model::element& e) {
        e.dynamic_stereotypes(extract(e));
    }

public:
    void operator()(coding::meta_model::element&) { }
    void operator()(coding::meta_model::module& m) { update(m); }
    void operator()(coding::meta_model::object_template &ot) { update(ot); }
    void operator()(coding::meta_model::builtin& b) {  update(b); }
    void operator()(coding::meta_model::enumeration& e) { update(e); }
    void operator()(coding::meta_model::primitive& p) { update(p); }
    void operator()(coding::meta_model::object& o) { update(o); }
    void operator()(coding::meta_model::exception& e) { update(e); }
    void operator()(coding::meta_model::visitor& v) { update(v); }
    void operator()(coding::meta_model::licence& l) { update(l); }
    void operator()(coding::meta_model::modeline& ml) { update(ml); }
    void operator()(coding::meta_model::modeline_group& mg) { update(mg); }
    void operator()(coding::meta_model::generation_marker& gm) { update(gm); }
};

}

void
dynamic_stereotypes_transform::apply(const coding::transforms::context& ctx,
    coding::meta_model::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "dynamic stereotypes transform",
        transform_id, *ctx.tracer(), ms);

    updater u;
    using coding::meta_model::elements_traversal;
    elements_traversal(ms.target(), u);
    for (auto& m : ms.references())
        elements_traversal(m, u);

    stp.end_transform(ms);
}

}
