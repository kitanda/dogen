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
#ifndef DOGEN_SML_TYPES_META_DATA_WORKFLOW_FWD_HPP
#define DOGEN_SML_TYPES_META_DATA_WORKFLOW_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif


#include <memory>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/meta_data/registrar.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

class workflow {
public:
    workflow() = default;
    workflow(const workflow&) = default;
    ~workflow() = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    /**
     * @brief Add enricher to the workflow.
     */
    static void register_enricher(std::shared_ptr<enricher_interface> e);

    /**
     * @brief Execute the meta-data workflow on the supplied model.
     */
    void execute(model& m) const;

private:
    static std::unique_ptr<registrar> registrar_;
};

} } }

#endif
