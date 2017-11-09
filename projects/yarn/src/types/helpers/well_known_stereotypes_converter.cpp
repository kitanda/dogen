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
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/yarn/io/meta_model/well_known_stereotypes_io.hpp"
#include "dogen/yarn/types/helpers/well_known_stereotypes_converter.hpp"

namespace {

const std::string transform_id("yarn.transforms.stereotypes_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stereotype_object("yarn::object");
const std::string stereotype_object_template("yarn::object_template");
const std::string stereotype_enumeration("yarn::enumeration");
const std::string stereotype_primitive("yarn::primitive");
const std::string stereotype_exception("yarn::exception");
const std::string stereotype_builtin("yarn::builtin");
const std::string stereotype_visitor("yarn::visitable");
const std::string stereotype_fluent("yarn::fluent");
const std::string stereotype_immutable("yarn::immutable");
const std::string stereotype_orm_object("yarn::orm::object");
const std::string stereotype_orm_value("yarn::orm::value");

const std::string unsupported_stereotype("Invalid or unsupported stereotype: ");

}

namespace dogen {
namespace yarn {
namespace helpers {

std::pair<
    std::list<meta_model::well_known_stereotypes>,
    std::list<std::string>
    >
well_known_stereotypes_converter::from_csv_string(const std::string& s) {
    using meta_model::well_known_stereotypes;
    std::list<well_known_stereotypes> wks;
    std::list<std::string> uks;

    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));
    for (const auto& stereotype : stereotypes) {
        if (stereotype == stereotype_object)
            wks.push_back(well_known_stereotypes::object);
        else if (stereotype == stereotype_object_template)
            wks.push_back(well_known_stereotypes::object_template);
        else if (stereotype == stereotype_enumeration)
            wks.push_back(well_known_stereotypes::enumeration);
        else if (stereotype == stereotype_primitive)
            wks.push_back(well_known_stereotypes::primitive);
        else if (stereotype == stereotype_builtin)
            wks.push_back(well_known_stereotypes::builtin);
        else if (stereotype == stereotype_exception)
            wks.push_back(well_known_stereotypes::exception);
        else if (stereotype == stereotype_fluent)
            wks.push_back(well_known_stereotypes::fluent);
        else if (stereotype == stereotype_immutable)
            wks.push_back(well_known_stereotypes::immutable);
        else if (stereotype == stereotype_orm_object)
            wks.push_back(well_known_stereotypes::orm_object);
        else if (stereotype == stereotype_orm_value)
            wks.push_back(well_known_stereotypes::orm_value);
        else
            uks.push_back(stereotype);
    }
    return std::make_pair(wks, uks);
}

std::string to_string(const meta_model::well_known_stereotypes st) {
    using meta_model::well_known_stereotypes;
    switch(st) {
    case well_known_stereotypes::object: return stereotype_object;
    case well_known_stereotypes::object_template: return stereotype_object;
    case well_known_stereotypes::enumeration: return stereotype_enumeration;
    case well_known_stereotypes::primitive: return stereotype_primitive;
    case well_known_stereotypes::builtin: return stereotype_builtin;
    case well_known_stereotypes::exception: return stereotype_exception;
    case well_known_stereotypes::fluent: return stereotype_fluent;
    case well_known_stereotypes::immutable: return stereotype_immutable;
    case well_known_stereotypes::orm_object: return stereotype_orm_object;
    case well_known_stereotypes::orm_value: return stereotype_orm_value;
    default: {
        const std::string s(boost::lexical_cast<std::string>(st));
        BOOST_LOG_SEV(lg, error) << unsupported_stereotype << s;
        using dogen::utility::exception::invalid_enum_value;
        BOOST_THROW_EXCEPTION(invalid_enum_value(unsupported_stereotype + s));
    } }
}

} } }
