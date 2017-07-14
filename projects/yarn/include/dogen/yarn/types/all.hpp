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
#ifndef DOGEN_YARN_TYPES_ALL_HPP
#define DOGEN_YARN_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/yarn.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/helpers/node.hpp"
#include "dogen/yarn/types/code_generator.hpp"
#include "dogen/yarn/types/helpers/mapper.hpp"
#include "dogen/yarn/types/helpers/indexer.hpp"
#include "dogen/yarn/types/helpers/indices.hpp"
#include "dogen/yarn/types/helpers/mapping.hpp"
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/helpers/resolver.hpp"
#include "dogen/yarn/types/meta_model/model.hpp"
#include "dogen/yarn/types/helpers/persister.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/helpers/decomposer.hpp"
#include "dogen/yarn/types/helpers/separators.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/helpers/mapping_set.hpp"
#include "dogen/yarn/types/meta_model/location.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/meta_model/name_tree.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/helpers/mapping_error.hpp"
#include "dogen/yarn/types/helpers/mapping_value.hpp"
#include "dogen/yarn/types/helpers/parsing_error.hpp"
#include "dogen/yarn/types/meta_model/enumerator.hpp"
#include "dogen/yarn/types/helpers/building_error.hpp"
#include "dogen/yarn/types/helpers/indexing_error.hpp"
#include "dogen/yarn/types/helpers/name_flattener.hpp"
#include "dogen/yarn/types/helpers/pretty_printer.hpp"
#include "dogen/yarn/types/helpers/printing_error.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/helpers/hydration_error.hpp"
#include "dogen/yarn/types/helpers/mapping_actions.hpp"
#include "dogen/yarn/types/helpers/mapping_context.hpp"
#include "dogen/yarn/types/helpers/persister_error.hpp"
#include "dogen/yarn/types/meta_model/letter_cases.hpp"
#include "dogen/yarn/types/meta_model/object_types.hpp"
#include "dogen/yarn/types/meta_model/origin_types.hpp"
#include "dogen/yarn/types/helpers/resolution_error.hpp"
#include "dogen/yarn/types/helpers/string_processor.hpp"
#include "dogen/yarn/types/helpers/validation_error.hpp"
#include "dogen/yarn/types/transforms/configuration.hpp"
#include "dogen/yarn/types/transforms/orm_transform.hpp"
#include "dogen/yarn/types/helpers/mappings_hydrator.hpp"
#include "dogen/yarn/types/helpers/name_tree_builder.hpp"
#include "dogen/yarn/types/helpers/mappings_validator.hpp"
#include "dogen/yarn/types/meta_model/element_visitor.hpp"
#include "dogen/yarn/types/meta_model/type_parameters.hpp"
#include "dogen/yarn/types/transforms/context_factory.hpp"
#include "dogen/yarn/types/transforms/merge_transform.hpp"
#include "dogen/yarn/types/transforms/registrar_error.hpp"
#include "dogen/yarn/types/transforms/kernel_interface.hpp"
#include "dogen/yarn/types/transforms/kernel_registrar.hpp"
#include "dogen/yarn/types/transforms/origin_transform.hpp"
#include "dogen/yarn/types/transforms/references_chain.hpp"
#include "dogen/yarn/types/helpers/decomposition_result.hpp"
#include "dogen/yarn/types/helpers/new_name_tree_parser.hpp"
#include "dogen/yarn/types/meta_model/formatting_styles.hpp"
#include "dogen/yarn/types/transforms/mapping_transform.hpp"
#include "dogen/yarn/types/transforms/modules_transform.hpp"
#include "dogen/yarn/types/transforms/parsing_transform.hpp"
#include "dogen/yarn/types/meta_model/element_properties.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn/types/transforms/concepts_transform.hpp"
#include "dogen/yarn/types/transforms/language_transform.hpp"
#include "dogen/yarn/types/transforms/resolver_transform.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository.hpp"
#include "dogen/yarn/types/meta_model/artefact_properties.hpp"
#include "dogen/yarn/types/helpers/legacy_name_tree_parser.hpp"
#include "dogen/yarn/types/meta_model/orm_database_systems.hpp"
#include "dogen/yarn/types/meta_model/orm_model_properties.hpp"
#include "dogen/yarn/types/transforms/attributes_transform.hpp"
#include "dogen/yarn/types/transforms/enablement_transform.hpp"
#include "dogen/yarn/types/transforms/initial_target_chain.hpp"
#include "dogen/yarn/types/transforms/model_assembly_chain.hpp"
#include "dogen/yarn/types/transforms/pre_processing_chain.hpp"
#include "dogen/yarn/types/transforms/primitives_transform.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/helpers/pre_processing_validator.hpp"
#include "dogen/yarn/types/meta_model/orm_module_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_object_properties.hpp"
#include "dogen/yarn/types/transforms/annotations_transform.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"
#include "dogen/yarn/types/transforms/containment_transform.hpp"
#include "dogen/yarn/types/transforms/exogenous_model_chain.hpp"
#include "dogen/yarn/types/transforms/final_model_transform.hpp"
#include "dogen/yarn/types/transforms/post_processing_chain.hpp"
#include "dogen/yarn/types/transforms/stereotypes_transform.hpp"
#include "dogen/yarn/types/transforms/type_params_transform.hpp"
#include "dogen/yarn/types/helpers/post_processing_validator.hpp"
#include "dogen/yarn/types/helpers/reference_paths_extractor.hpp"
#include "dogen/yarn/types/transforms/associations_transform.hpp"
#include "dogen/yarn/types/transforms/code_generation_output.hpp"
#include "dogen/yarn/types/transforms/enumerations_transform.hpp"
#include "dogen/yarn/types/transforms/generability_transform.hpp"
#include "dogen/yarn/types/transforms/model_generation_chain.hpp"
#include "dogen/yarn/types/meta_model/orm_attribute_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_primitive_properties.hpp"
#include "dogen/yarn/types/transforms/generalization_transform.hpp"
#include "dogen/yarn/types/transforms/exogenous_transform_types.hpp"
#include "dogen/yarn/types/transforms/external_transforms_chain.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository_factory.hpp"
#include "dogen/yarn/types/transforms/external_transform_interface.hpp"
#include "dogen/yarn/types/transforms/external_transform_registrar.hpp"
#include "dogen/yarn/types/transforms/exogenous_transform_interface.hpp"
#include "dogen/yarn/types/transforms/exogenous_transform_registrar.hpp"
#include "dogen/yarn/types/transforms/local_enablement_configuration.hpp"
#include "dogen/yarn/types/helpers/identifiable_and_qualified_builder.hpp"
#include "dogen/yarn/types/transforms/global_enablement_configuration.hpp"

#endif
