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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/types/features/origin.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/structural/module.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/builtin.hpp"
#include "dogen.assets/types/meta_model/structural/visitor.hpp"
#include "dogen.assets/types/meta_model/structural/exception.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/meta_model/structural/object_template.hpp"
#include "dogen.assets/types/meta_model/elements_traversal.hpp"
#include "dogen.assets/types/meta_model/decoration/licence.hpp"
#include "dogen.assets/types/meta_model/decoration/modeline.hpp"
#include "dogen.assets/types/meta_model/decoration/modeline_group.hpp"
#include "dogen.assets/types/meta_model/decoration/generation_marker.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_initializer.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.assets/types/meta_model/templating/logic_less_template.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/origin_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.origin_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string target_cannot_be_proxy(
    "Model has origin set to target but is also a proxy: ");

}

namespace dogen::assets::transforms {

namespace {

using namespace meta_model::structural;
using namespace meta_model::decoration;
using namespace meta_model::variability;
using namespace meta_model::templating;

class updater {
public:
    explicit updater(const meta_model::origin_types ot) : origin_types_(ot) {}

public:
    template<typename DeterminableOrigin>
    void update(DeterminableOrigin& d) { d.origin_type(origin_types_); }

public:
    void operator()(meta_model::element&) { }
    void operator()(module& m) { update(m); }
    void operator()(object_template& ot) { update(ot); }
    void operator()(builtin& b) { update(b); }
    void operator()(enumeration& e) { update(e); }
    void operator()(primitive& p) { update(p); }
    void operator()(object& o) { update(o); }
    void operator()(exception& e) { update(e); }
    void operator()(visitor& v) { update(v); }
    void operator()(modeline_group& mg) { update(mg); }
    void operator()(modeline& m) { update(m); }
    void operator()(generation_marker& gm) { update(gm); }
    void operator()(licence& l) { update(l); }
    void operator()(feature_template_initializer& fti) { update(fti); }
    void operator()(feature_bundle& ftg) { update(ftg); }
    void operator()(profile_template& pt) { update(pt); }
    void operator()(logic_less_template& llt) { update(llt); }

private:
    const meta_model::origin_types origin_types_;
};

}

meta_model::origin_types origin_transform::
compute_origin_types(const meta_model::model& m, const bool is_proxy_model) {
    using meta_model::origin_types;
    if (is_proxy_model && m.origin_type() == origin_types::target) {
        const auto& id(m.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << target_cannot_be_proxy << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(target_cannot_be_proxy + id));
    }

    if (m.origin_type() == origin_types::target)
        return origin_types::target;
    else if (is_proxy_model)
        return origin_types::proxy_reference;

    return origin_types::non_proxy_reference;
}

void origin_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "origin transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);


    /*
     * First we obtain the is proxy model flag from the model's static
     * configuration.
     */
    const auto& fm(*ctx.feature_model());
    const auto fg(features::origin::make_feature_group(fm));
    const auto& cfg(*m.root_module()->configuration());
    const auto scfg(features::origin::make_static_configuration(fg, cfg));

    BOOST_LOG_SEV(lg, debug) << "Read is proxy model: " << scfg.is_proxy_model
                             << " for model: " << m.name().qualified().dot();

    /*
     * We then use the proxy model flag to compute the appropriate
     * origin type for this model.
     */
    const auto ot(compute_origin_types(m, scfg.is_proxy_model));
    m.origin_type(ot);

    /*
     * Finally, we update all model elements with the computed origin
     * type. Note that if you do not add the correct origin type to a
     * model element, it will not be code generated as we ignore all
     * non-target elements.
     */
    updater g(ot);
    meta_model::elements_traversal(m, g);

    stp.end_transform(m);
}

}