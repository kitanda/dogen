/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_CHILD_OF_A_CHILD1_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_CHILD_OF_A_CHILD1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/domain/third_child_with_members.hpp"
#include "dogen/trivial_inheritance/serialization/child_of_a_child1_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {

class child_of_a_child1 final : public dogen::trivial_inheritance::third_child_with_members {
public:
    child_of_a_child1() = default;
    child_of_a_child1(const child_of_a_child1&) = default;
    child_of_a_child1(child_of_a_child1&&) = default;

public:
    child_of_a_child1(
        const int prop_0,
        const dogen::trivial_inheritance::versioned_key& versioned_key,
        const unsigned int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const child_of_a_child1& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, child_of_a_child1& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const child_of_a_child1& rhs) const;
    bool operator!=(const child_of_a_child1& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::trivial_inheritance::parent_with_members& other) const override;

public:
    void swap(child_of_a_child1& other) noexcept;
    child_of_a_child1& operator=(child_of_a_child1 other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::trivial_inheritance::child_of_a_child1& lhs,
    dogen::trivial_inheritance::child_of_a_child1& rhs) {
    lhs.swap(rhs);
}

}

#endif
