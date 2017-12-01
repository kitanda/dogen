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
#include "dogen/yarn/types/helpers/mapper.hpp"
#include "dogen/yarn/types/helpers/adapter.hpp"
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
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/options.hpp"
#include "dogen/yarn/types/helpers/file_linter.hpp"
#include "dogen/yarn/types/helpers/mapping_set.hpp"
#include "dogen/yarn/types/meta_model/artefact.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn/types/meta_model/location.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/meta_model/endomodel.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/meta_model/name_tree.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/helpers/mapping_error.hpp"
#include "dogen/yarn/types/helpers/mapping_value.hpp"
#include "dogen/yarn/types/helpers/parsing_error.hpp"
#include "dogen/yarn/types/helpers/probing_error.hpp"
#include "dogen/yarn/types/helpers/stream_writer.hpp"
#include "dogen/yarn/types/helpers/writing_error.hpp"
#include "dogen/yarn/types/meta_model/enumerator.hpp"
#include "dogen/yarn/types/meta_model/exoelement.hpp"
#include "dogen/yarn/types/meta_model/text_model.hpp"
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
#include "dogen/yarn/types/meta_model/exoattribute.hpp"
#include "dogen/yarn/types/meta_model/letter_cases.hpp"
#include "dogen/yarn/types/meta_model/origin_types.hpp"
#include "dogen/yarn/types/helpers/adaptation_error.hpp"
#include "dogen/yarn/types/helpers/location_builder.hpp"
#include "dogen/yarn/types/helpers/resolution_error.hpp"
#include "dogen/yarn/types/helpers/string_processor.hpp"
#include "dogen/yarn/types/helpers/transform_prober.hpp"
#include "dogen/yarn/types/helpers/validation_error.hpp"
#include "dogen/yarn/types/transforms/configuration.hpp"
#include "dogen/yarn/types/transforms/orm_transform.hpp"
#include "dogen/yarn/types/helpers/filesystem_writer.hpp"
#include "dogen/yarn/types/helpers/mappings_hydrator.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/helpers/name_tree_builder.hpp"
#include "dogen/yarn/types/helpers/transform_metrics.hpp"
#include "dogen/yarn/types/transforms/building_error.hpp"
#include "dogen/yarn/types/helpers/mappings_validator.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"
#include "dogen/yarn/types/meta_model/element_visitor.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/meta_model/type_parameters.hpp"
#include "dogen/yarn/types/transforms/context_factory.hpp"
#include "dogen/yarn/types/transforms/merge_transform.hpp"
#include "dogen/yarn/types/transforms/registrar_error.hpp"
#include "dogen/yarn/types/meta_model/facet_properties.hpp"
#include "dogen/yarn/types/transforms/origin_transform.hpp"
#include "dogen/yarn/types/transforms/references_chain.hpp"
#include "dogen/yarn/types/transforms/validation_error.hpp"
#include "dogen/yarn/types/helpers/decomposition_result.hpp"
#include "dogen/yarn/types/helpers/naming_configuration.hpp"
#include "dogen/yarn/types/helpers/new_name_tree_parser.hpp"
#include "dogen/yarn/types/meta_model/element_archetype.hpp"
#include "dogen/yarn/types/meta_model/formatting_styles.hpp"
#include "dogen/yarn/types/transforms/mapping_transform.hpp"
#include "dogen/yarn/types/transforms/modules_transform.hpp"
#include "dogen/yarn/types/transforms/options_validator.hpp"
#include "dogen/yarn/types/transforms/parsing_transform.hpp"
#include "dogen/yarn/types/transforms/sorting_transform.hpp"
#include "dogen/yarn/types/meta_model/backend_properties.hpp"
#include "dogen/yarn/types/meta_model/elements_traversal.hpp"
#include "dogen/yarn/types/meta_model/locator_properties.hpp"
#include "dogen/yarn/types/meta_model/static_stereotypes.hpp"
#include "dogen/yarn/types/transforms/language_transform.hpp"
#include "dogen/yarn/types/transforms/resolver_transform.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository.hpp"
#include "dogen/yarn/types/meta_model/artefact_properties.hpp"
#include "dogen/yarn/types/helpers/legacy_name_tree_parser.hpp"
#include "dogen/yarn/types/meta_model/archetype_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_database_systems.hpp"
#include "dogen/yarn/types/meta_model/orm_model_properties.hpp"
#include "dogen/yarn/types/transforms/attributes_transform.hpp"
#include "dogen/yarn/types/transforms/enablement_transform.hpp"
#include "dogen/yarn/types/transforms/formatting_transform.hpp"
#include "dogen/yarn/types/transforms/initial_target_chain.hpp"
#include "dogen/yarn/types/transforms/naming_configuration.hpp"
#include "dogen/yarn/types/transforms/primitives_transform.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/meta_model/orm_module_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_object_properties.hpp"
#include "dogen/yarn/types/transforms/annotations_transform.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"
#include "dogen/yarn/types/transforms/containment_transform.hpp"
#include "dogen/yarn/types/transforms/meta_naming_transform.hpp"
#include "dogen/yarn/types/transforms/stereotypes_transform.hpp"
#include "dogen/yarn/types/transforms/type_params_transform.hpp"
#include "dogen/yarn/types/helpers/artefact_writer_interface.hpp"
#include "dogen/yarn/types/helpers/reference_paths_extractor.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_builder.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_printer.hpp"
#include "dogen/yarn/types/transforms/associations_transform.hpp"
#include "dogen/yarn/types/transforms/enumerations_transform.hpp"
#include "dogen/yarn/types/transforms/generability_transform.hpp"
#include "dogen/yarn/types/transforms/model_generation_chain.hpp"
#include "dogen/yarn/types/meta_model/path_contribution_types.hpp"
#include "dogen/yarn/types/meta_model/model_segment_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_attribute_properties.hpp"
#include "dogen/yarn/types/meta_model/orm_primitive_properties.hpp"
#include "dogen/yarn/types/transforms/dynamic_transforms_chain.hpp"
#include "dogen/yarn/types/transforms/endomodel_assembly_chain.hpp"
#include "dogen/yarn/types/transforms/exomodel_transform_types.hpp"
#include "dogen/yarn/types/transforms/formatting_configuration.hpp"
#include "dogen/yarn/types/transforms/generalization_transform.hpp"
#include "dogen/yarn/types/transforms/exomodel_generation_chain.hpp"
#include "dogen/yarn/types/transforms/model_to_text_model_chain.hpp"
#include "dogen/yarn/types/helpers/stereotypes_conversion_result.hpp"
#include "dogen/yarn/types/meta_model/directory_structure_styles.hpp"
#include "dogen/yarn/types/transforms/endomodel_generation_chain.hpp"
#include "dogen/yarn/types/transforms/exomodel_to_exomodel_chain.hpp"
#include "dogen/yarn/types/transforms/object_templates_transform.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository_factory.hpp"
#include "dogen/yarn/types/meta_model/archetype_family_properties.hpp"
#include "dogen/yarn/types/transforms/dynamic_transform_interface.hpp"
#include "dogen/yarn/types/transforms/dynamic_transform_registrar.hpp"
#include "dogen/yarn/types/transforms/model_post_processing_chain.hpp"
#include "dogen/yarn/types/transforms/text_model_generation_chain.hpp"
#include "dogen/yarn/types/transforms/endomodel_to_model_transform.hpp"
#include "dogen/yarn/types/transforms/exomodel_transform_interface.hpp"
#include "dogen/yarn/types/transforms/exomodel_transform_registrar.hpp"
#include "dogen/yarn/types/transforms/locator_properties_transform.hpp"
#include "dogen/yarn/types/transforms/artefact_properties_transform.hpp"
#include "dogen/yarn/types/transforms/endomodel_pre_processing_chain.hpp"
#include "dogen/yarn/types/helpers/endomodel_pre_processing_validator.hpp"
#include "dogen/yarn/types/helpers/identifiable_and_qualified_builder.hpp"
#include "dogen/yarn/types/transforms/endomodel_post_processing_chain.hpp"
#include "dogen/yarn/types/transforms/exomodel_to_endomodel_transform.hpp"
#include "dogen/yarn/types/helpers/endomodel_post_processing_validator.hpp"
#include "dogen/yarn/types/meta_model/intra_backend_segment_properties.hpp"
#include "dogen/yarn/types/meta_model/denormalised_archetype_properties.hpp"
#include "dogen/yarn/types/meta_model/local_archetype_location_properties.hpp"
#include "dogen/yarn/types/meta_model/global_archetype_location_properties.hpp"
#include "dogen/yarn/types/transforms/archetype_location_properties_transform.hpp"
#include "dogen/yarn/types/transforms/model_to_text_model_transform_interface.hpp"
#include "dogen/yarn/types/transforms/model_to_text_model_transform_registrar.hpp"

#endif
