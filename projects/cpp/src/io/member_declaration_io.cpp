/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/algorithm/string.hpp>
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/cpp/io/decl_specifier_io.hpp"
#include "dogen/cpp/io/declarator_io.hpp"
#include "dogen/cpp/io/function_types_io.hpp"
#include "dogen/cpp/io/member_declaration_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::decl_specifier>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const member_declaration& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::member_declaration\"" << ", "
      << "\"decl_specifier_seq\": " << v.decl_specifier_seq() << ", "
      << "\"declarator\": " << v.declarator() << ", "
      << "\"constant_initialiser\": " << "\"" << tidy_up_string(v.constant_initialiser()) << "\"" << ", "
      << "\"function_type\": " << v.function_type() << ", "
      << "\"is_pure\": " << v.is_pure() << ", "
      << "\"is_override\": " << v.is_override() << ", "
      << "\"is_default\": " << v.is_default()
      << " }";
    return(s);
}

} }