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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.variability/io/meta_model/profile_io.hpp"
#include "dogen.variability/io/meta_model/feature_io.hpp"
#include "dogen.variability/io/meta_model/feature_template_io.hpp"
#include "dogen.variability/io/meta_model/profile_template_io.hpp"
#include "dogen.variability/io/meta_model/configuration_point_io.hpp"
#include "dogen.variability/io/meta_model/configuration_point_template_io.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/instantiation_exception.hpp"
#include "dogen.variability/types/helpers/template_instantiator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("variability.helpers.template_instantiator"));

const std::string empty;
const std::string empty_msg("<empty>");

const std::string empty_qualified_name(
    "Qualified name cannot be empty for instance templates.");
const std::string empty_owner("Owner cannot be empty.");
const std::string empty_simple_name("Simple name cannot be empty.");
const std::string empty_domains("No instantiation domain names found.");
const std::string empty_domain_name(
    "Template has an empty domain name: ");
const std::string invalid_domain_name(
    "Instantiation domain name could not be located: ");
const std::string missing_feature("Feature not found: ");
const std::string duplicate_configuration_point(
    "Found more than one configuration point for the same feature: ");

}

namespace dogen::variability::helpers {

template_instantiator::template_instantiator(const bool compatibility_mode)
    : compatibility_mode_(compatibility_mode) {

    BOOST_LOG_SEV(lg, trace) << "Compatibility mode: " << compatibility_mode_;
}

bool template_instantiator::
is_partially_mathcable(const meta_model::value_type vt) const {
    return vt == meta_model::value_type::key_value_pair;
}

meta_model::configuration_point template_instantiator::to_configuration_point(
    const meta_model::feature_model& fm, const std::string& owner,
    const meta_model::configuration_point_template& cpt) const {
    /*
     * Non-instance templates must have a owner.
     */
    if (owner.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_owner;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_owner));
    }
    const std::string fqn(owner + "." + cpt.name().simple());

    /*
     * Locate the feature for this configuration point template.
     */
    const auto& bn(fm.by_name());
    BOOST_LOG_SEV(lg, trace) << "Feature qualified name: " << fqn;
    const auto i(bn.find(fqn));
    if (i == bn.end()) {
        BOOST_LOG_SEV(lg, error) << missing_feature << fqn;
        BOOST_THROW_EXCEPTION(instantiation_exception(missing_feature + fqn));
    }

    /*
     * Now we can populate the name of the point from the point
     * template's associated feature, and, if supplied, the owner.
     */
    const auto& feature(i->second);
    meta_model::configuration_point r;
    r.name().simple(feature.name().simple());
    r.name().qualified(feature.name().qualified());

    /*
     * Finally we can create the value.
     */
    helpers::value_factory vf;
    r.value(vf.make(feature, cpt.untyped_value()));
    return r;
}

meta_model::feature template_instantiator::
to_feature(const meta_model::feature_template& ft) const {
    meta_model::feature r;

    r.name(ft.name());
    r.value_type(ft.value_type());
    r.binding_point(ft.binding_point());
    r.default_value(ft.default_value());
    r.is_partially_matchable(is_partially_mathcable(r.value_type()));

    return r;
}

std::list<meta_model::feature> template_instantiator::
instantiate(const std::unordered_map<std::string, std::vector<std::string>>&
    template_instantiation_domains,
    const meta_model::feature_template& ft) const {
    /*
     * Domain names should never be empty.
     */
    const auto& tid(template_instantiation_domains);
    if (tid.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_domains ;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_domains));
    }

    /*
     * All templates must supply a simple name. This cannot be
     * inferred.
     */
    const auto& n(ft.name());
    const auto sn(n.simple());
    if (sn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_simple_name));
    }

    /*
     * All templates must supply a instantiation domain name.
     */
    const auto idn(ft.instantiation_domain_name());
    if (idn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_domain_name << sn;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_domain_name + sn));
    }

    /*
     * The instantiation domain name provided must exist in our
     * collection of all domain names.
     */
    const auto i(tid.find(idn));
    if (i == tid.end()) {
        BOOST_LOG_SEV(lg, error) << invalid_domain_name << idn
                                 << " Requested for template: " << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_exception(invalid_domain_name + idn));
    }

    /*
     * Perform the template expansion across the domain.
     */
    const auto& domain(i->second);
    std::list<meta_model::feature> r;
    for (const auto& e : domain) {
        auto f(to_feature(ft));
        f.name().qualified(e + "." + sn);
        r.push_back(f);
    }
    return r;
}

std::list<meta_model::configuration_point> template_instantiator::instantiate(
    const std::unordered_map<std::string, std::vector<std::string>>&
    template_instantiation_domains, const meta_model::feature_model& fm,
    const meta_model::configuration_point_template& cpt) const {
    const auto cptqn(cpt.name().qualified());
    BOOST_LOG_SEV(lg, debug) << "Configuration point template: "
                             << cpt.name().simple() << " ('"
                             << (cptqn.empty() ? empty_msg : cptqn)
                             << "')" ;

    /*
     * All templates must supply a simple name. This cannot be
     * inferred.
     */
    const auto& n(cpt.name());
    const auto sn(n.simple());
    if (sn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_simple_name));
    }

    /*
     * All templates must supply a instantiation domain name.
     */
    const auto idn(cpt.instantiation_domain_name());
    if (idn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_domain_name << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_exception(empty_domain_name + sn));
    }

    /*
     * The instantiation domain name provided must exist in our
     * collection of all domain names.
     */
    const auto& tid(template_instantiation_domains);
    const auto i(tid.find(idn));
    if (i == tid.end()) {
        BOOST_LOG_SEV(lg, error) << invalid_domain_name << idn
                                 << " Requested for template: " << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_exception(invalid_domain_name + idn));
    }

    /*
     * Perform the template expansion across the domain.
     */
    const auto& domain(i->second);
    std::list<meta_model::configuration_point> r;
    for (const auto& e : domain)
        r.push_back(to_configuration_point(fm, e, cpt));

    return r;
}

meta_model::profile template_instantiator::instantiate(
    const std::unordered_map<std::string, std::vector<std::string>>&
    template_instantiation_domains, const meta_model::feature_model& fm,
    const meta_model::profile_template& pt) const {

    const auto ptqn(pt.name().qualified());
    BOOST_LOG_SEV(lg, debug) << "Instantiating profile template: " << ptqn;

    /*
     * Domain names should never be empty.
     */
    const auto& tid(template_instantiation_domains);
    if (tid.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_domains ;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_domains));

    }

    meta_model::profile r;
    r.name(pt.name());
    r.stereotype(pt.stereotype());
    r.parents(pt.parents());

    for (auto& cpt : pt.templates()) {
        const auto cptqn(cpt.name().qualified());
        BOOST_LOG_SEV(lg, debug) << "Configuration point template: "
                                 << cpt.name().simple() << " ('"
                                 << (cptqn.empty() ? empty_msg : cptqn)
                                 << "')" ;
        std::list<meta_model::configuration_point> cps;

        /*
         * Try to instantiate the template.
         */
        try {
            cps = instantiate(tid, fm, cpt);
        } catch(const instantiation_exception& e) {
            /*
             * This is not a particularly glamorous approach to handling
             * backwards compatibility. The idea is that we may be trying
             * to instantiate features that are no longer supported. If
             * the user has requested backwards compatibility mode, we try
             * to continue by ignoring the fact that those features no
             * longer exist. This is also not ideal because we may capture
             * errors when the user requested a template kind that is not
             * supported.
             */
            if (!compatibility_mode_) {
                BOOST_LOG_SEV(lg, error) << "Error instantiating template: "
                                         << ptqn << ". Message: "
                                         << e.what() << ".";
                throw e;
            }

            BOOST_LOG_SEV(lg, warn) << "Error instantiating template: "
                                    << ptqn << ". Message: " << e.what()
                                    << ". Skipping template.";
            continue;
        }

        /*
         * Now process all configuration points that were generated as
         * part of the instantiation.
         */
        for (const auto& cp : cps) {
            const auto cpqn(cp.name().qualified());
            const auto pair(std::make_pair(cpqn, cp));
            const auto inserted(r.configuration_points().insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_configuration_point
                                         << cpqn;
                BOOST_THROW_EXCEPTION(instantiation_exception(
                        duplicate_configuration_point + cpqn));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiated profile template: "
                             << ptqn << " Result: " << r;
    return r;
}

}
