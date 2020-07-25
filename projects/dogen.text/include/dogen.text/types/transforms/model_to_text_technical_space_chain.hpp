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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_MODEL_TO_TEXT_TECHNICAL_SPACE_CHAIN_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_MODEL_TO_TEXT_TECHNICAL_SPACE_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::transforms {

/**
 * @brief Performs a model to text transformation of a meta-model,
 * into its supported technical space.
 */
class model_to_text_technical_space_chain {
public:
    model_to_text_technical_space_chain() = default;
    model_to_text_technical_space_chain(
        const model_to_text_technical_space_chain&) = delete;
    model_to_text_technical_space_chain(
        model_to_text_technical_space_chain&&) = default;
    virtual ~model_to_text_technical_space_chain() noexcept = default;

public:
    /**
     * @brief Returns the identity of this transform.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Returns a human readable description of this transform.
     */
    virtual std::string description() const = 0;

public:
    /**
     * @brief Technical space targeted by this transform.
     */
    virtual identification::entities::technical_space
    technical_space() const = 0;

    /**
     * @brief Updates all artefacts with a text representation for
     * this technical space.
     */
    virtual void apply(const text::transforms::context& ctx,
        const bool requires_backend_directory,
        text::entities::model& m) const = 0;
};

}

#endif
