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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_FACET_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_FACET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"

namespace dogen::logical::entities::physical {

/**
 * @brief Represents a facet within a backend, such as type definitions.
 */
class facet final : public dogen::logical::entities::element {
public:
    facet(const facet&) = default;
    facet(facet&&) = default;

public:
    facet();

    virtual ~facet() noexcept { }

public:
    facet(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::logical::entities::helper_properties>& helper_properties,
        const std::string& id,
        const dogen::identification::entities::technical_space major_technical_space,
        const std::string& meta_model_name,
        const std::string& backend_name,
        const std::list<dogen::identification::entities::logical_id>& contains,
        const std::list<dogen::identification::entities::logical_name>& archetypes,
        const std::list<dogen::identification::entities::logical_name>& helpers,
        const std::string& directory_name,
        const std::string& postfix);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Unique identifier in physical space for this element.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Technical space to which this physical element belongs to.
     */
    /**@{*/
    dogen::identification::entities::technical_space major_technical_space() const;
    void major_technical_space(const dogen::identification::entities::technical_space v);
    /**@}*/

    /**
     * @brief Name of the physical meta-model containing this element.
     */
    /**@{*/
    const std::string& meta_model_name() const;
    std::string& meta_model_name();
    void meta_model_name(const std::string& v);
    void meta_model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the backend containing this element.
     */
    /**@{*/
    const std::string& backend_name() const;
    std::string& backend_name();
    void backend_name(const std::string& v);
    void backend_name(const std::string&& v);
    /**@}*/

    /**
     * @brief All elements contained by this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::logical_id>& contains() const;
    std::list<dogen::identification::entities::logical_id>& contains();
    void contains(const std::list<dogen::identification::entities::logical_id>& v);
    void contains(const std::list<dogen::identification::entities::logical_id>&& v);
    /**@}*/

    /**
     * @brief All archetypes in this facet.
     */
    /**@{*/
    const std::list<dogen::identification::entities::logical_name>& archetypes() const;
    std::list<dogen::identification::entities::logical_name>& archetypes();
    void archetypes(const std::list<dogen::identification::entities::logical_name>& v);
    void archetypes(const std::list<dogen::identification::entities::logical_name>&& v);
    /**@}*/

    const std::list<dogen::identification::entities::logical_name>& helpers() const;
    std::list<dogen::identification::entities::logical_name>& helpers();
    void helpers(const std::list<dogen::identification::entities::logical_name>& v);
    void helpers(const std::list<dogen::identification::entities::logical_name>&& v);

    /**
     * @brief Default directory name to use for this facet.
     */
    /**@{*/
    const std::string& directory_name() const;
    std::string& directory_name();
    void directory_name(const std::string& v);
    void directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Default postfix to use for this facet.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const facet& rhs) const;
    bool operator!=(const facet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(facet& other) noexcept;
    facet& operator=(facet other);

private:
    std::string id_;
    dogen::identification::entities::technical_space major_technical_space_;
    std::string meta_model_name_;
    std::string backend_name_;
    std::list<dogen::identification::entities::logical_id> contains_;
    std::list<dogen::identification::entities::logical_name> archetypes_;
    std::list<dogen::identification::entities::logical_name> helpers_;
    std::string directory_name_;
    std::string postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::facet& lhs,
    dogen::logical::entities::physical::facet& rhs) {
    lhs.swap(rhs);
}

}

#endif
