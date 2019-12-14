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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen.relational/io/tracing/run_id_io.hpp"
#include "dogen.relational/io/tracing/log_event_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::relational::tracing {

std::ostream& operator<<(std::ostream& s, const log_event& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::relational::tracing::log_event\"" << ", "
      << "\"timestamp\": " << "\"" << v.timestamp() << "\"" << ", "
      << "\"run_id\": " << v.run_id() << ", "
      << "\"component\": " << "\"" << tidy_up_string(v.component()) << "\"" << ", "
      << "\"severity\": " << "\"" << tidy_up_string(v.severity()) << "\"" << ", "
      << "\"message\": " << "\"" << tidy_up_string(v.message()) << "\""
      << " }";
    return(s);
}

}
