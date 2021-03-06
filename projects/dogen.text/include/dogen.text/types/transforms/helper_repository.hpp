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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_HELPER_REPOSITORY_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_HELPER_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.text/types/transforms/helper_transform_fwd.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::text::transforms {

class helper_repository final {
public:
    helper_repository() = default;
    helper_repository(const helper_repository&) = default;
    helper_repository(helper_repository&&) = default;
    ~helper_repository() = default;

public:
    explicit helper_repository(const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helpers_by_family);

public:
    const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helpers_by_family() const;
    std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helpers_by_family();
    void helpers_by_family(const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& v);
    void helpers_by_family(const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >&& v);

public:
    bool operator==(const helper_repository& rhs) const;
    bool operator!=(const helper_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_repository& other) noexcept;
    helper_repository& operator=(helper_repository other);

private:
    std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > > helpers_by_family_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::transforms::helper_repository& lhs,
    dogen::text::transforms::helper_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
