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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTERS_ASSISTANT_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTERS_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/optional.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include "masd.dogen.annotations/types/archetype_location.hpp"
#include "masd.dogen.extraction/types/meta_model/artefact.hpp"
#include "masd.dogen.generation/types/formatters/scoped_boilerplate_formatter.hpp"
#include "masd.dogen.generation/types/formatters/scoped_namespace_formatter.hpp"
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.generation.csharp/types/formatters/context.hpp"
#include "masd.dogen.generation.csharp/types/formattables/helper_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/assistant_properties.hpp"
#include "masd.dogen.generation.csharp/types/formatters/helper_formatter_interface.hpp"

namespace masd::dogen::generation::csharp::formatters {

class assistant final {
public:
    assistant(const context& ctx, const annotations::archetype_location& al,
        const std::string& id);

private:
    const formattables::artefact_properties&
    obtain_artefact_properties(const std::string& archetype) const;

public:
    template<typename T>
        static const T& as(const std::string& /*archetype*/,
            const coding::meta_model::element& e) {
        return dynamic_cast<const T&>(e);
    }

    /**
     * @brief Returns the keyword to use for a given class, defining
     * its inheritance properties: sealed or abstract. If non-empty,
     * includes a trailing space.
     */
    static std::string
    make_inheritance_keyword_text(const coding::meta_model::object& o);

public:
    /**
     * @brief Obtains the qualified name.
     */
    /**@{*/
    std::string get_qualified_name(const coding::meta_model::name& n) const;
    std::string
    get_qualified_name(const coding::meta_model::name_tree& nt) const;
    /**@}*/

public:
    /**
     * @brief Returns a scoped boilerplate formatter.
     */
    generation::formatters::scoped_boilerplate_formatter
    make_scoped_boilerplate_formatter(const coding::meta_model::element& e);

    /**
     * @brief Returns a scoped namespace formatter.
     */
    generation::formatters::scoped_namespace_formatter
    make_scoped_namespace_formatter(const std::list<std::string>& ns);

public:
    /**
     * @brief returns the c# namespaces for the name.
     */
    std::list<std::string>
    make_namespaces(const coding::meta_model::name& n) const;

public:
    std::string
    reference_equals(const coding::meta_model::attribute& attr) const;

public:
    /**
     * @brief Adds a top-level comment with mark-up.
     */
    void comment(const std::string& c, const unsigned int identation_level = 0);

    /**
     * @brief Returns @code c as as an inline comment.
     */
    std::string comment_inline(const std::string& c) const;

public:
    std::string
    make_argument_name(const coding::meta_model::attribute& attr) const;

private:
    std::list<std::shared_ptr<formatters::helper_formatter_interface>>
    get_helpers(const formattables::helper_properties& hp) const;

public:
    /**
     * @brief Creates any helper methods that may be required for this
     * formatter.
     */
    void add_helper_methods(const std::string& element_id);

public:
    boost::optional<formattables::assistant_properties>
    get_assistant_properties(const coding::meta_model::attribute& attr) const;

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

    /**
     * @brief Generates a file with the current contents of the
     * stream.
     */
    extraction::meta_model::artefact make_artefact() const;

private:
    std::ostringstream stream_;
    boost::iostreams::filtering_ostream filtering_stream_;
    const std::string element_id_;
    const context& context_;
    formattables::artefact_properties artefact_properties_;
    const annotations::archetype_location archetype_location_;
};

}

#endif
