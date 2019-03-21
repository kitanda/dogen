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
#include "masd.dogen/test_data/configuration_td.hpp"
#include "masd.dogen.cli/test_data/configuration_td.hpp"
#include "masd.dogen.cli/test_data/cli_configuration_td.hpp"
#include "masd.dogen.utility/test_data/log/logging_configuration_td.hpp"

namespace {

masd::dogen::utility::log::logging_configuration
create_masd_dogen_utility_log_logging_configuration(const unsigned int position) {
    return masd::dogen::utility::log::logging_configuration_generator::create(position);
}

boost::optional<masd::dogen::utility::log::logging_configuration>
create_boost_optional_masd_dogen_utility_log_logging_configuration(unsigned int position) {
    boost::optional<masd::dogen::utility::log::logging_configuration> r(
        create_masd_dogen_utility_log_logging_configuration(position));
    return r;
}

masd::dogen::configuration
create_masd_dogen_configuration(const unsigned int position) {
    return masd::dogen::configuration_generator::create(position);
}

masd::dogen::cli::cli_configuration
create_masd_dogen_cli_cli_configuration(const unsigned int position) {
    return masd::dogen::cli::cli_configuration_generator::create(position);
}

}

namespace masd::dogen::cli {

configuration_generator::configuration_generator() : position_(0) { }

void configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.logging(create_boost_optional_masd_dogen_utility_log_logging_configuration(position + 0));
    v.api(create_masd_dogen_configuration(position + 1));
    v.cli(create_masd_dogen_cli_cli_configuration(position + 2));
}

configuration_generator::result_type
configuration_generator::create(const unsigned int position) {
    configuration r;
    configuration_generator::populate(position, r);
    return r;
}

configuration_generator::result_type*
configuration_generator::create_ptr(const unsigned int position) {
    configuration* p = new configuration();
    configuration_generator::populate(position, *p);
    return p;
}

configuration_generator::result_type
configuration_generator::operator()() {
    return create(position_++);
}

}