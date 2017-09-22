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
#ifndef DOGEN_YARN_TYPES_META_MODEL_ARCHETYPE_GROUP_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_META_MODEL_ARCHETYPE_GROUP_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/yarn/serialization/meta_model/archetype_group_properties_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Properties pertaining to groupings of archetypes, related to the path computation.
 */
class archetype_group_properties final {
public:
    archetype_group_properties() = default;
    archetype_group_properties(const archetype_group_properties&) = default;
    archetype_group_properties(archetype_group_properties&&) = default;
    ~archetype_group_properties() = default;

public:
    explicit archetype_group_properties(const std::string& extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::archetype_group_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::archetype_group_properties& v, unsigned int version);

public:
    /**
     * @brief Extension to use for files of this group. Includes the leading dot.
     */
    /**@{*/
    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);
    /**@}*/

public:
    bool operator==(const archetype_group_properties& rhs) const;
    bool operator!=(const archetype_group_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_group_properties& other) noexcept;
    archetype_group_properties& operator=(archetype_group_properties other);

private:
    std::string extension_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::archetype_group_properties& lhs,
    dogen::yarn::meta_model::archetype_group_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
