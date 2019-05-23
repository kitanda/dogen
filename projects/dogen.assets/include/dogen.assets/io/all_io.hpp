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
#ifndef DOGEN_ASSETS_IO_ALL_IO_HPP
#define DOGEN_ASSETS_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.assets/io/helpers/node_io.hpp"
#include "dogen.assets/io/helpers/indices_io.hpp"
#include "dogen.assets/io/helpers/mapping_io.hpp"
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/io/helpers/separators_io.hpp"
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/io/transforms/context_io.hpp"
#include "dogen.assets/io/helpers/mapping_set_io.hpp"
#include "dogen.assets/io/meta_model/location_io.hpp"
#include "dogen.assets/io/meta_model/attribute_io.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/io/meta_model/name_tree_io.hpp"
#include "dogen.assets/io/helpers/mapping_value_io.hpp"
#include "dogen.assets/io/helpers/mapping_actions_io.hpp"
#include "dogen.assets/io/helpers/mapping_context_io.hpp"
#include "dogen.assets/io/meta_model/origin_types_io.hpp"
#include "dogen.assets/io/meta_model/orm/letter_case_io.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.assets/io/meta_model/type_parameters_io.hpp"
#include "dogen.assets/io/helpers/decomposition_result_io.hpp"
#include "dogen.assets/io/meta_model/decoration/editor_io.hpp"
#include "dogen.assets/io/meta_model/formatting_styles_io.hpp"
#include "dogen.assets/io/meta_model/structural/module_io.hpp"
#include "dogen.assets/io/meta_model/structural/object_io.hpp"
#include "dogen.assets/io/meta_model/decoration/licence_io.hpp"
#include "dogen.assets/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.assets/io/meta_model/structural/builtin_io.hpp"
#include "dogen.assets/io/meta_model/structural/visitor_io.hpp"
#include "dogen.assets/io/helpers/mapping_set_repository_io.hpp"
#include "dogen.assets/io/meta_model/artefact_properties_io.hpp"
#include "dogen.assets/io/meta_model/decoration/modeline_io.hpp"
#include "dogen.assets/io/meta_model/mapping/destination_io.hpp"
#include "dogen.assets/io/meta_model/orm/database_system_io.hpp"
#include "dogen.assets/io/meta_model/orm/model_properties_io.hpp"
#include "dogen.assets/io/meta_model/structural/exception_io.hpp"
#include "dogen.assets/io/meta_model/structural/primitive_io.hpp"
#include "dogen.assets/io/meta_model/extraction_properties_io.hpp"
#include "dogen.assets/io/meta_model/orm/module_properties_io.hpp"
#include "dogen.assets/io/meta_model/orm/object_properties_io.hpp"
#include "dogen.assets/io/meta_model/structural/enumerator_io.hpp"
#include "dogen.assets/io/meta_model/mapping/fixed_mappable_io.hpp"
#include "dogen.assets/io/meta_model/structural/enumeration_io.hpp"
#include "dogen.assets/io/meta_model/orm/attribute_properties_io.hpp"
#include "dogen.assets/io/meta_model/orm/primitive_properties_io.hpp"
#include "dogen.assets/io/meta_model/decoration/modeline_field_io.hpp"
#include "dogen.assets/io/meta_model/decoration/modeline_group_io.hpp"
#include "dogen.assets/io/meta_model/mapping/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/structural/object_template_io.hpp"
#include "dogen.assets/io/meta_model/variability/feature_bundle_io.hpp"
#include "dogen.assets/io/meta_model/mapping/extensible_mappable_io.hpp"
#include "dogen.assets/io/meta_model/decoration/generation_marker_io.hpp"
#include "dogen.assets/io/meta_model/decoration/modeline_location_io.hpp"
#include "dogen.assets/io/meta_model/variability/feature_template_io.hpp"
#include "dogen.assets/io/meta_model/variability/profile_template_io.hpp"
#include "dogen.assets/io/meta_model/decoration/element_properties_io.hpp"
#include "dogen.assets/io/meta_model/decoration/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/structural/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/templating/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/fully_qualified_representation_io.hpp"
#include "dogen.assets/io/meta_model/templating/logic_less_template_io.hpp"
#include "dogen.assets/io/meta_model/variability/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/variability/profile_template_entry_io.hpp"
#include "dogen.assets/io/meta_model/local_archetype_location_properties_io.hpp"
#include "dogen.assets/io/meta_model/variability/feature_template_initializer_io.hpp"

#endif
