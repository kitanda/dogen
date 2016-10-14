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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/io/annotation_io.hpp"
#include "dogen/annotations/io/scope_types_io.hpp"
#include "dogen/annotations/types/merger.hpp"
#include "dogen/annotations/types/profiler.hpp"
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.annotation_groups_factory"));

const std::string empty;
const std::string expected_scope(" Expected scope: ");
const std::string actual_scope(" Actual scope: ");
const std::string duplicate_type(
    "Field definition already inserted: ");
const std::string type_not_found(
    "Field definition not found: ");
const std::string field_used_in_invalid_scope(
    "Field used in invalid scope: ");
const std::string missing_profile(
    "Annotation uses a profile that could not be found: ");

const std::string model_name("annotations");
const std::string type_name("profile");

const std::string default_root("default.root_module");

}

namespace dogen {
namespace annotations {

annotation_groups_factory::
annotation_groups_factory(
    const std::vector<boost::filesystem::path>& data_dirs,
    const ownership_hierarchy_repository& ohrp,
    const type_repository& trp, const bool throw_on_missing_type)
    : data_dirs_(data_dirs), ownership_hierarchy_repository_(ohrp),
      type_repository_(trp), throw_on_missing_type_(throw_on_missing_type) { }

inline std::ostream&
operator<<(std::ostream& s, const annotation_groups_factory::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "profile_group_expander::type_group\"" << ", "
      << "\"profile\": " << v.profile
      << " }";

    return s;
}

annotation_groups_factory::type_group
annotation_groups_factory::make_type_group(const type_repository& trp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating annotation types.";

    type_group r;
    const type_repository_selector s(trp);
    r.profile = s.select_type_by_name(model_name, type_name);

    BOOST_LOG_SEV(lg, debug) << "Created annotation types. Result: " << r;
    return r;
}

std::string annotation_groups_factory::
obtain_profile_name(const type_group& tg, const annotation& a) const {
    BOOST_LOG_SEV(lg, debug) << "Reading profile name.";
    const entry_selector s(a);
    std::string r;
    if (s.has_entry(tg.profile))
        r = s.get_text_content(tg.profile);

    BOOST_LOG_SEV(lg, debug) << "Profile name: '" << r << "'";
    return r;
}

boost::optional<type> annotation_groups_factory::
obtain_type(const std::string& n) const {
    const auto i(type_repository_.types_by_name().find(n));
    if (i == type_repository_.types_by_name().end()) {
        if (throw_on_missing_type_) {
            BOOST_LOG_SEV(lg, error) << type_not_found << n;

            BOOST_THROW_EXCEPTION(
                building_error(type_not_found + n));
        }

        BOOST_LOG_SEV(lg, warn) << type_not_found << n;
        return boost::optional<type>();
    }
    return i->second;
}

void annotation_groups_factory::validate_scope(const type& t,
    const scope_types current_scope) const {
    if (t.scope() != scope_types::any &&
        t.scope() != scope_types::not_applicable &&
        t.scope() != current_scope) {

        std::stringstream s;
        s << field_used_in_invalid_scope << t.name().qualified()
          << expected_scope << t.scope()
          << actual_scope << current_scope;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(building_error(s.str()));
    }
}

std::string annotation_groups_factory::
get_default_profile_name_for_scope(const scope_types scope) const {
    if (scope == scope_types::root_module)
        return default_root;

    return empty;
}

annotation annotation_groups_factory::create_annotation(const scope_types scope,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_scribble_entries) const {

    annotation r;
    r.scope(scope);

    value_factory f;
    std::unordered_map<std::string, boost::shared_ptr<value>> entries;
    for (auto kvp : aggregated_scribble_entries) {
        const auto& k(kvp.first);
        const auto t(obtain_type(k));
        if (!t)
            continue;

        validate_scope(*t, r.scope());
        const auto& v(kvp.second);
        r.entries()[k] = f.make(*t, v);
    }
    return r;
}

std::unordered_map<std::string, std::list<std::string >>
annotation_groups_factory::
aggregate_scribble_entries(const scribble& scribble) const {
    std::unordered_map<std::string, std::list<std::string> > r;

    for (const auto& entry : scribble.entries())
        r[entry.first].push_front(entry.second);

    return r;
}

std::unordered_map<std::string, annotation> annotation_groups_factory::
create_annotation_profiles() const {
    profiler prf;
    const auto& ohrp(ownership_hierarchy_repository_);
    const auto& trp(type_repository_);
    return prf.generate(data_dirs_, ohrp, trp);
}

annotation annotation_groups_factory::
handle_profiles(const type_group& tg, const std::unordered_map<std::string,
    annotation>& profiles, const annotation& original) const {

    BOOST_LOG_SEV(lg, error) << "Started handling profiles. Original: "
                             << original;

    /*
     * If a profile name was specified via the meta-data, it must
     * exist on our profile collection. Locate it, merge it with the
     * original annotation and return that.
     */
    const auto profn(obtain_profile_name(tg, original));
    if (!profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Configured profile: " << profn;
        const auto i(profiles.find(profn));
        if (i == profiles.end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << profn;
            BOOST_THROW_EXCEPTION(building_error(missing_profile + profn));
        }

        merger mg;
        const auto annotation_profile(i->second);
        const annotation r(mg.merge(original, annotation_profile));
        BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
        return r;
    } else
        BOOST_LOG_SEV(lg, debug) << "Profile not set in meta-data.";

    /*
     * If no profile name was set, try looking for the well-known
     * default profiles, based on the scope of the annotation. Not all
     * scope types have a mapping, and the default profiles do not
     * necessarily exist.
     */
    const auto def_profn(get_default_profile_name_for_scope(original.scope()));
    if (!def_profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Looking for default profile; " << def_profn;

        const auto i(profiles.find(def_profn));
        if (i != profiles.end()) {
            merger mg;
            const auto annotation_profile(i->second);
            const annotation r(mg.merge(original, annotation_profile));
            BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
            return r;
        }
    } else
        BOOST_LOG_SEV(lg, debug) << "Scope does not have a default profile.";

    /*
     * If we could find nothing suitable, just return the original.
     */
    BOOST_LOG_SEV(lg, debug) << "No profiles found, using original.";
    return original;
}

annotation annotation_groups_factory::
make(const scribble& scribble) const {
    auto aggregated_entries(aggregate_scribble_entries(scribble));
    auto r(create_annotation(scribble.scope(), aggregated_entries));
    return r;
}

std::unordered_map<std::string, annotation_group> annotation_groups_factory::
make(const type_repository& trp, const std::unordered_map<std::string,
    scribble_group>& scribble_groups) const {

    const auto profiles(create_annotation_profiles());
    const auto tg(make_type_group(trp));

    std::unordered_map<std::string, annotation_group> r;
    for (const auto& pair : scribble_groups) {
        /*
         * First we generate the main annotation off of the scribble's
         * parent.
         */
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing scribble group: " << id;

        const auto& scribble(pair.second);
        const auto parent(make(scribble.parent()));

        /*
         * Then we augment the annotation with a profile, if it is so
         * configured.
         */
        annotation_group ag;
        ag.parent(handle_profiles(tg, profiles, parent));

        /*
         * Finally we obtain annotations for all the scribble's
         * children.
         */
        for (const auto& pair : scribble.children()) {
            const auto child_id(pair.first);
            const auto& child(pair.second);
            ag.children()[child_id] = make(child);
        }
        r[id] = ag;
    }
    return r;
}

} }
