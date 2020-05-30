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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_builder.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text.cpp/types/transforms/test_data/test_data.hpp"
#include "dogen.text.cpp/types/transforms/test_data/enum_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/class_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/builtin_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/primitive_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/enum_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/class_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/primitive_implementation_transform.hpp"

namespace dogen::text::cpp::transforms::test_data {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.cpp.transforms.test_data"));

physical::entities::facet make_facet() {
    physical::helpers::meta_name_builder b;
    b.kernel("masd");
    b.backend("cpp");
    b.facet("test_data");

    physical::entities::facet r;
    r.meta_name(b.build());

    const auto lambda([&](const auto& arch) {
        const auto id(arch.meta_name().qualified());
        const auto pair(std::make_pair(id, arch));
        const auto inserted(r.archetypes().insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_archetype("Duplicate archetype: ");
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype + id));
        }
    });

    lambda(enum_implementation_transform::static_archetype());
    lambda(enum_header_transform::static_archetype());
    lambda(builtin_header_transform::static_archetype());
    lambda(class_implementation_transform::static_archetype());
    lambda(primitive_implementation_transform::static_archetype());
    lambda(primitive_header_transform::static_archetype());
    lambda(class_header_transform::static_archetype());
    return r;
}

}

physical::entities::facet test_data_facet::static_facet() {
    static const auto r(make_facet());
    return r;
}

physical::entities::facet test_data_facet::facet() const {
    return static_facet();
}

}

