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
#ifndef DOGEN_QUILT_CPP_TYPES_ALL_HPP
#define DOGEN_QUILT_CPP_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/types/cpp.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/workflow.hpp"
#include "dogen/quilt.cpp/types/initializer.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/types/fabric/workflow.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/properties/entity.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/properties/factory.hpp"
#include "dogen/quilt.cpp/types/settings/registrar.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/properties/workflow.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar.hpp"
#include "dogen/quilt.cpp/types/properties/container.hpp"
#include "dogen/quilt.cpp/types/properties/registrar.hpp"
#include "dogen/quilt.cpp/types/settings/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/file_types.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/properties/class_info.hpp"
#include "dogen/quilt.cpp/types/settings/odb_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/initializer.hpp"
#include "dogen/quilt.cpp/types/properties/formattable.hpp"
#include "dogen/quilt.cpp/types/properties/parent_info.hpp"
#include "dogen/quilt.cpp/types/properties/transformer.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/properties/origin_types.hpp"
#include "dogen/quilt.cpp/types/settings/building_error.hpp"
#include "dogen/quilt.cpp/types/properties/property_info.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings.hpp"
#include "dogen/quilt.cpp/types/settings/registrar_error.hpp"
#include "dogen/quilt.cpp/types/formatters/building_error.hpp"
#include "dogen/quilt.cpp/types/formatters/io/initializer.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/types/properties/includers_info.hpp"
#include "dogen/quilt.cpp/types/properties/registrar_info.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/context_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar_error.hpp"
#include "dogen/quilt.cpp/types/properties/cmakelists_info.hpp"
#include "dogen/quilt.cpp/types/properties/provision_error.hpp"
#include "dogen/quilt.cpp/types/properties/registrar_error.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/initializer.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/properties/nested_type_info.hpp"
#include "dogen/quilt.cpp/types/properties/odb_options_info.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives.hpp"
#include "dogen/quilt.cpp/types/settings/streaming_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/element_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/initializer.hpp"
#include "dogen/quilt.cpp/types/properties/aspect_properties.hpp"
#include "dogen/quilt.cpp/types/properties/helper_descriptor.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties.hpp"
#include "dogen/quilt.cpp/types/properties/element_properties.hpp"
#include "dogen/quilt.cpp/types/properties/enablement_factory.hpp"
#include "dogen/quilt.cpp/types/settings/odb_settings_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/properties/formattable_visitor.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties.hpp"
#include "dogen/quilt.cpp/types/properties/transformation_error.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/initializer.hpp"
#include "dogen/quilt.cpp/types/properties/enablement_repository.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings_factory.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_factory.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings_builder.hpp"
#include "dogen/quilt.cpp/types/settings/directory_names_settings.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/enum_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/io/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_factory.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings_repository.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository.hpp"
#include "dogen/quilt.cpp/types/settings/streaming_settings_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/initializer.hpp"
#include "dogen/quilt.cpp/types/properties/aspect_properties_factory.hpp"
#include "dogen/quilt.cpp/types/properties/forward_declarations_info.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_factory.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_repository.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/helper_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/settings/inclusion_directive_settings.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/visitor_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_repository.hpp"
#include "dogen/quilt.cpp/types/settings/inclusion_directives_settings.hpp"
#include "dogen/quilt.cpp/types/settings/streaming_settings_repository.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/aspect_properties_repository.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties_factory.hpp"
#include "dogen/quilt.cpp/types/properties/global_enablement_properties.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_repository.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/exception_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/namespace_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/new_class_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/properties/element_properties_repository.hpp"
#include "dogen/quilt.cpp/types/properties/enablement_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/cmakelists_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/types/visitor_header_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_builder.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_factory.hpp"
#include "dogen/quilt.cpp/types/settings/directory_names_settings_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/odb_options_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties_repository.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_repository.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings_factory_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/io/enum_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/nested_type_formatting_assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/exception_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/namespace_header_formatter.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings_repository_factory.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_repository.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_repository_factory.hpp"
#include "dogen/quilt.cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/quilt.cpp/types/settings/streaming_settings_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/forward_declarations_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/aspect_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/element_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_builder_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/enum_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/forward_declarations_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_provider_interface.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_repository_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/forward_declarations_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_implementation_formatter.hpp"

#endif
