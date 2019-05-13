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
#ifndef DOGEN_EXTRACTION_TYPES_META_MODEL_MODEL_HPP
#define DOGEN_EXTRACTION_TYPES_META_MODEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.extraction/types/meta_model/artefact.hpp"
#include "dogen.variability/types/meta_model/configuration_fwd.hpp"
#include "dogen.extraction/types/meta_model/outputting_properties.hpp"

namespace dogen::extraction::meta_model {

class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const std::string& name,
        const std::string& technical_space,
        const std::list<dogen::extraction::meta_model::artefact>& artefacts,
        const std::list<boost::filesystem::path>& managed_directories,
        const dogen::extraction::meta_model::outputting_properties& outputting_properties);

public:
    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v);
    /**@}*/

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    /**
     * @brief Primary technical space that this model belongs to.
     */
    /**@{*/
    const std::string& technical_space() const;
    std::string& technical_space();
    void technical_space(const std::string& v);
    void technical_space(const std::string&& v);
    /**@}*/

    const std::list<dogen::extraction::meta_model::artefact>& artefacts() const;
    std::list<dogen::extraction::meta_model::artefact>& artefacts();
    void artefacts(const std::list<dogen::extraction::meta_model::artefact>& v);
    void artefacts(const std::list<dogen::extraction::meta_model::artefact>&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

    const dogen::extraction::meta_model::outputting_properties& outputting_properties() const;
    dogen::extraction::meta_model::outputting_properties& outputting_properties();
    void outputting_properties(const dogen::extraction::meta_model::outputting_properties& v);
    void outputting_properties(const dogen::extraction::meta_model::outputting_properties&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    boost::shared_ptr<dogen::variability::meta_model::configuration> configuration_;
    std::string name_;
    std::string technical_space_;
    std::list<dogen::extraction::meta_model::artefact> artefacts_;
    std::list<boost::filesystem::path> managed_directories_;
    dogen::extraction::meta_model::outputting_properties outputting_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::extraction::meta_model::model& lhs,
    dogen::extraction::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif