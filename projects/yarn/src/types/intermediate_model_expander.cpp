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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/origin_expander.hpp"
#include "dogen/yarn/types/parsing_expander.hpp"
#include "dogen/yarn/types/modules_expander.hpp"
#include "dogen/yarn/types/language_expander.hpp"
#include "dogen/yarn/types/enumeration_expander.hpp"
#include "dogen/yarn/types/annotations_expander.hpp"
#include "dogen/yarn/types/type_parameters_expander.hpp"
#include "dogen/yarn/types/intermediate_model_validator.hpp"
#include "dogen/yarn/types/intermediate_model_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.intermediate_model_expander"));

}

namespace dogen {
namespace yarn {

void intermediate_model_expander::
expand_enumerations(intermediate_model& im) const {
    enumeration_expander ex;
    ex.expand(im);
}

void intermediate_model_expander::expand_language(
    const annotations::type_repository& atrp, intermediate_model& im) const {
    language_expander ex;
    ex.expand(atrp, im);
}

void intermediate_model_expander::expand_modules(intermediate_model& im) const {
    modules_expander ex;
    ex.expand(im);
}

void intermediate_model_expander::
expand_annotations(const annotations::annotation_groups_factory& agf,
    intermediate_model& im) const {
    annotations_expander ex;
    ex.expand(agf, im);
}

void intermediate_model_expander::
expand_origin(const annotations::type_repository& atrp,
    intermediate_model& im) const {
    origin_expander ex;
    ex.expand(atrp, im);
}

void intermediate_model_expander::expand_type_parameters(
    const annotations::type_repository& atrp, intermediate_model& im) const {
    type_parameters_expander ex;
    ex.expand(atrp, im);
}

void intermediate_model_expander::expand_parsing(
    const annotations::type_repository& atrp, intermediate_model& im) const {
    parsing_expander ex;
    ex.expand(atrp, im);
}

void intermediate_model_expander::validate(const intermediate_model& im) const {
    intermediate_model_validator v;
    v.validate(im);
}

void intermediate_model_expander::
expand(const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp, intermediate_model& im) const {
    /*
     * We must expand annotations before we expand modules to
     * ensure the root module is populated with entries
     * before being copied over.
     */
    expand_annotations(agf, im);
    expand_modules(im);
    expand_origin(atrp, im);
    expand_language(atrp, im);

    /*
     * Enumeration expansion must be done after language expansion as
     * we do some language-specific processing.
     */
    expand_enumerations(im);

    expand_type_parameters(atrp, im);
    expand_parsing(atrp, im);

    /*
     * Ensure the model is valid.
     */
    validate(im);
}

} }
