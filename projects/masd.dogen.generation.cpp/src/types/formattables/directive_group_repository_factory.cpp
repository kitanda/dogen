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
#include <typeindex>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.utility/io/list_io.hpp"
#include "masd.dogen.utility/io/unordered_map_io.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.annotations/io/type_io.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "masd.dogen.generation.cpp/types/formattables/expansion_error.hpp"
#include "masd.dogen.generation.cpp/types/formattables/directive_group.hpp"
#include "masd.dogen.generation.cpp/io/formattables/directive_group_io.hpp"
#include "masd.dogen.generation.cpp/types/formattables/directive_group_repository_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(
        "generation.cpp.formattables.directive_group_repository_factory"));

const std::string double_quote("\"");
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");
const std::string override_postfix("_inclusion_directive");

const std::string duplicate_element_name("Duplicate delement name: ");
const std::string missing_archetype("Archetype not found: ");
const std::string empty_primary_directive(
    "Primary include directive is empty.");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");
const std::string empty_archetype("Formatter name is empty.");
const std::string secondary_without_primary(
    "Element contains secondary directives but no primary directives."
    "Archetype: ");

}

namespace masd::dogen::generation::cpp::formattables {

std::ostream& operator<<(std::ostream& s,
    const directive_group_repository_factory::
    formattater_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"masd.dogen::generation::cpp::formattables::"
      << "directive_group_repository_factory::formatters_type_group\""
      << ", "
      << "\"primary_inclusion_directive\": "
      << v.primary_inclusion_directive << ", "
      << "\"secondary_inclusion_directive\": "
      << v.secondary_inclusion_directive
      << " }";

    return s;
}

std::ostream& operator<<(std::ostream& s,
    const directive_group_repository_factory::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"masd.dogen::generation::cpp::formattables::"
      << "directive_group_repository_factory::type_group\"" << ", "
      << "\"inclusion_required\": " << v.inclusion_required << ", "
      << "\"formattaters_type_groups\": "
      << v.formattaters_type_groups
      << " }";

    return s;
}

directive_group_repository_factory::type_group
directive_group_repository_factory::make_type_group(
    const annotations::type_repository& atrp,
    const formatters::repository& frp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto ir(traits::cpp::inclusion_required());
    r.inclusion_required = s.select_type_by_name(ir);

    for (const auto f : frp.stock_artefact_formatters()) {
        const auto& al(f->archetype_location());
        const auto arch(al.archetype());

        using formatters::inclusion_support_types;
        static const auto ns(inclusion_support_types::not_supported);
        if (f->inclusion_support_type() == ns) {
            BOOST_LOG_SEV(lg, debug) << "Skipping archetype: " << arch;
            continue;
        }

        formattater_type_group ftg;
        const auto& pid(traits::primary_inclusion_directive());
        ftg.primary_inclusion_directive = s.select_type_by_name(arch, pid);

        const auto& sid(traits::secondary_inclusion_directive());
        ftg.secondary_inclusion_directive = s.select_type_by_name(arch, sid);

        r.formattaters_type_groups[arch] = ftg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;
    return r;
}

bool directive_group_repository_factory::
make_top_level_inclusion_required(
    const type_group& tg, const annotations::annotation& a) const {
    const annotations::entry_selector s(a);
    return s.get_boolean_content_or_default(tg.inclusion_required);
}

boost::optional<directive_group>
directive_group_repository_factory::make_directive_group(
    const type_group& tg,const std::string& archetype,
    const annotations::annotation& a) const {

    if (archetype.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(expansion_error(empty_archetype));
    }

    const auto i(tg.formattaters_type_groups.find(archetype));
    if (i == tg.formattaters_type_groups.end()) {
        BOOST_LOG_SEV(lg, error) << missing_archetype;
        BOOST_THROW_EXCEPTION(expansion_error(missing_archetype));
    }

    const auto& ft(i->second);
    const annotations::entry_selector s(a);
    directive_group r;

    bool found(false);
    const auto pid(ft.primary_inclusion_directive);
    if (s.has_entry(pid)) {
        found = true;
        r.primary(s.get_text_content(pid));
    }

    const auto sid(ft.secondary_inclusion_directive);
    if (s.has_entry(sid)) {
        if (!found) {
            BOOST_LOG_SEV(lg, error) << secondary_without_primary << archetype;
            BOOST_THROW_EXCEPTION(
                expansion_error(secondary_without_primary + archetype));
        }

        r.secondary(s.get_text_collection_content(sid));
    }

    if (!found)
        return boost::optional<directive_group>();

    return r;
}

bool directive_group_repository_factory::
has_inclusion_directive_overrides(const annotations::annotation& a) const {
    const annotations::entry_selector s(a);
    const auto r(s.has_key_ending_with(override_postfix));
    BOOST_LOG_SEV(lg, debug) << "Found entries with keys ending with "
                             << override_postfix << ": " << r;
    return r;
}

std::string directive_group_repository_factory::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

directive_group_repository_factory::artefact_formatters_type
directive_group_repository_factory::remove_non_includible_formatters(
    const artefact_formatters_type& formatters) const {

    artefact_formatters_type r;
    using formatters::inclusion_support_types;
    static const auto ns(inclusion_support_types::not_supported);
    for (const auto& fmt : formatters) {
        if (fmt->inclusion_support_type() != ns)
            r.push_front(fmt);
    }
    return r;
}

std::unordered_map<std::string,
                   directive_group_repository_factory::artefact_formatters_type>
directive_group_repository_factory::
includible_formatters_by_meta_name(const formatters::repository& frp) const {
    std::unordered_map<std::string, artefact_formatters_type> r;
    for (const auto& pair : frp.stock_artefact_formatters_by_meta_name()) {
        const auto& mt(pair.first);
        const auto& fmts(pair.second);
        r[mt] = remove_non_includible_formatters(fmts);
    }
    return r;
}

void directive_group_repository_factory::
insert_inclusion_directive(const std::string& id, const std::string& archetype,
    const directive_group& dg,
    directive_group_repository& dgrp) const {

    if (dg.primary().empty()) {
        std::ostringstream s;
        s << empty_primary_directive << archetype << " for type: " << id;

        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(expansion_error(msg));
    }

    const auto pair(std::make_pair(archetype, dg));
    const auto inserted(dgrp.by_id()[id].insert(pair).second);
    if (inserted)
        return;

    BOOST_LOG_SEV(lg, error) << duplicate_element_name << id;
    BOOST_THROW_EXCEPTION(expansion_error(duplicate_element_name + id));
}

void directive_group_repository_factory::
compute_directives(const type_group& tg, const modeling::meta_model::element& e,
    const artefact_formatters_type& formatters, const locator& l,
    directive_group_repository& dgrp) const {

    const auto& n(e.name());
    const auto id(n.id());
    BOOST_LOG_SEV(lg, debug) << "Started computing inclusion directives for: "
                             << id;

    /*
     * First we extract the data required to generated include
     * directives for this element. Note that we generate this setting
     * for _all elements_ even if the user did not specify any
     * meta-data (we do so via defaults).
     *
     * The question we are asking is: "does this element require any
     * inclusion directives at all, across all facets?". Not all
     * elements do; for example bool, int and so on don't require any
     * inclusions at all across all facets. If the user did not
     * override this, we default it to true because normally elements
     * require inclusion.
     */
    const auto& a(e.annotation());
    const bool required(make_top_level_inclusion_required(tg, a));
    if (!required) {
        BOOST_LOG_SEV(lg, trace) << "Inclusion not required for element.";
        return;
    } else
        BOOST_LOG_SEV(lg, trace) << "Inclusion directive required for element.";


    /*
     * Find out if this element has any inclusion directive overrides
     * at all. If it has at least one override, we know we don't need
     * to generate inclusion directives manually.
     */
    const bool has_overrides(has_inclusion_directive_overrides(a));

    /*
     * Now we start working at the formatter level.
     */
    const auto cs(formatters::inclusion_support_types::canonical_support);
    for (const auto& fmt : formatters) {
        const auto& al(fmt->archetype_location());
        const auto arch(al.archetype());
        BOOST_LOG_SEV(lg, trace) << "Archetype: " << arch;

        const auto ist(fmt->inclusion_support_type());
        const bool requires_canonical_archetype(ist == cs);

        /*
         * If the user has not provided any overrides at all, we can
         * safely compute the inclusion directive according to a
         * well-defined heuristic, slot it in and get on our way. It's
         * basically a dogen generated model.
         */
        if (!has_overrides) {
            const auto path(fmt->inclusion_path(l, n));
            directive_group dg;
            dg.primary(to_inclusion_directive(path));
            BOOST_LOG_SEV(lg, trace) << "Computed primary directive: "
                                     << dg.primary();

            insert_inclusion_directive(id, arch, dg, dgrp);
            BOOST_LOG_SEV(lg, trace) << "Inserting inclusion directive group: "
                                     << dg;

            /*
             * If this archetype location requires canonical archetype
             * support, map the directive group to the canonical
             * archetype name as well.
             */
            if (requires_canonical_archetype) {
                const auto fct(al.facet());
                const auto carch(formatters::traits::canonical_archetype(fct));
                insert_inclusion_directive(id, carch, dg, dgrp);
            }

            continue;
        }

        /*
         * Now we need to fetch the overrides from meta-data. They may
         * not exist - i.e. the question we're asking is "does the
         * archetype require an inclusion directive for this specific
         * formatter?" Some elements require inclusion directives for
         * some archetypes, but not for others. For example, we may
         * need an include for serialising a std::list, but in test
         * data we make use of helpers and thus not require an
         * include.
         */
        const auto dg(make_directive_group(tg, arch, a));
        if (dg) {
            insert_inclusion_directive(id, arch, *dg, dgrp);
            BOOST_LOG_SEV(lg, trace) << "Read primary directive from "
                                     << "meta-data: " << *dg;

            /*
             * If this archetype location requires canonical archetype
             * support, map the directive group to the canonical
             * archetype name as well.
             */
            if (requires_canonical_archetype) {
                const auto fct(al.facet());
                const auto carch(formatters::traits::canonical_archetype(fct));
                insert_inclusion_directive(id, carch, *dg, dgrp);
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished computing inclusion directives.";
}

directive_group_repository
directive_group_repository_factory::make(const type_group& tg,
    const std::unordered_map<std::string, artefact_formatters_type>& afmt,
    const locator& l,
    const std::unordered_map<std::string, formattable>& formattables) const {

    /*
     * For all formattables and their associated element segments,
     * find the formatters that support the element segment and
     * then compute the inclusion directive group for it.
     */
    directive_group_repository r;
    for (const auto& pair : formattables) {
        const auto& formattable(pair.second);

        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            const auto id(e.name().id());
            const auto mt(e.meta_name().id());

            const auto i(afmt.find(mt));
            if (i == afmt.end() || i->second.empty()) {
                BOOST_LOG_SEV(lg, debug) << formatter_not_found_for_type << id;
                continue;
            }

            compute_directives(tg, e, i->second, l, r);
        }
    }
    return r;
}

directive_group_repository
directive_group_repository_factory::
make(const annotations::type_repository& atrp,
    const formatters::repository& frp, const locator& l,
    const std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating inclusion dependencies "
                             << "group repository.";

    /*
     * First we must make sure we only have formatters which generate
     * files that can be included via an include directive. Filter out
     * all of those that do not, and bucket them all by type index.
     */
    const auto afmt(includible_formatters_by_meta_name(frp));
    const auto tg(make_type_group(atrp, frp));
    const auto r(make(tg, afmt, l, formattables));

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies "
                             << "group repository.";

    return r;
}

}
