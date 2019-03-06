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
#ifndef MASD_DOGEN_EXTRACTION_TYPES_TRANSFORMS_WRITE_ARTEFACTS_TRANSFORM_HPP
#define MASD_DOGEN_EXTRACTION_TYPES_TRANSFORMS_WRITE_ARTEFACTS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.extraction/types/meta_model/model.hpp"
#include "masd.dogen.extraction/types/transforms/context.hpp"

namespace masd::dogen::extraction::transforms {

class write_artefacts_transform final {
private:
    /**
     * @brief Creates directories to house the file, if they do not
     * yet exist.
     */
    static void
    create_directories(const boost::filesystem::path& file_path);

public:
    static void transform(const context& ctx, const meta_model::model& m);
};

}

#endif
