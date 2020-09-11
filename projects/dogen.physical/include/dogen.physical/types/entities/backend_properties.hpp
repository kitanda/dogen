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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_BACKEND_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_BACKEND_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Properties related to the backend.
 */
class backend_properties final {
public:
    backend_properties(const backend_properties&) = default;
    backend_properties(backend_properties&&) = default;
    ~backend_properties() = default;

public:
    backend_properties();

public:
    backend_properties(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const bool enabled,
        const std::string& technical_space_version,
        const std::string& directory);

public:
    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

    /**
     * @brief If true, the backend is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    /**
     * @brief Technical space version to use.
     */
    /**@{*/
    const std::string& technical_space_version() const;
    std::string& technical_space_version();
    void technical_space_version(const std::string& v);
    void technical_space_version(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the directory to use for the backend.
     */
    /**@{*/
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);
    /**@}*/

public:
    bool operator==(const backend_properties& rhs) const;
    bool operator!=(const backend_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(backend_properties& other) noexcept;
    backend_properties& operator=(backend_properties other);

private:
    dogen::identification::entities::physical_meta_name meta_name_;
    bool enabled_;
    std::string technical_space_version_;
    std::string directory_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::backend_properties& lhs,
    dogen::physical::entities::backend_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
