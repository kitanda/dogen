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
#ifndef DOGEN_ASSETS_TYPES_TRAITS_FWD_HPP
#define DOGEN_ASSETS_TYPES_TRAITS_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen::assets {

struct traits {
    static std::string enabled();
    static std::string directory();
    static std::string postfix();
    static std::string supported();
    static std::string overwrite();

    struct extraction {
        static std::string force_write();
        static std::string delete_extra_files();
        static std::string ignore_files_matching_regex();
        static std::string cpp_headers_output_directory();
        static std::string enable_backend_directories();
    };
    static std::string enable_backend_directories();

    struct orm {
        static std::string database_system();
        static std::string table_name();
        static std::string schema_name();
        static std::string is_primary_key();
        static std::string column_name();
        static std::string is_nullable();
        static std::string letter_case();
        static std::string type_override();
        static std::string is_composite();
    };

    struct variability {
        static std::string binding_point();
        static std::string labels();
        static std::string archetype_location_kernel();
        static std::string archetype_location_backend();
        static std::string archetype_location_facet();
        static std::string archetype_location_archetype();
        static std::string template_kind();
        static std::string untyped_value();
        static std::string qualified_name();
        static std::string generate_static_configuration();
        static std::string is_optional();
    };
};

}

#endif