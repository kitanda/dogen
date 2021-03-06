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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STEREOTYPES_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STEREOTYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"

namespace dogen::logical::entities {

/**
 * @brief Stereotype information associated with this element.
 */
class stereotypes final {
public:
    stereotypes() = default;
    stereotypes(const stereotypes&) = default;
    stereotypes(stereotypes&&) = default;
    ~stereotypes() = default;

public:
    stereotypes(
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes);

public:
    /**
     * @brief Stereotypes that are part of the dogen UML profile, and so are well-known to the
     * model.
     */
    /**@{*/
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes() const;
    std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes();
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>& v);
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are not part of the masd UML profile. These are user defined.
     */
    /**@{*/
    const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes() const;
    std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes();
    void dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>& v);
    void dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>&& v);
    /**@}*/

public:
    bool operator==(const stereotypes& rhs) const;
    bool operator!=(const stereotypes& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(stereotypes& other) noexcept;
    stereotypes& operator=(stereotypes other);

private:
    std::list<dogen::logical::entities::static_stereotypes> static_stereotypes_;
    std::list<dogen::identification::entities::stereotype> dynamic_stereotypes_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::stereotypes& lhs,
    dogen::logical::entities::stereotypes& rhs) {
    lhs.swap(rhs);
}

}

#endif
