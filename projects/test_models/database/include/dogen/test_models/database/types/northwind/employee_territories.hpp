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
#ifndef DOGEN_TEST_MODELS_DATABASE_TYPES_NORTHWIND_EMPLOYEE_TERRITORIES_HPP
#define DOGEN_TEST_MODELS_DATABASE_TYPES_NORTHWIND_EMPLOYEE_TERRITORIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/database/types/northwind/employee_territories_key.hpp"
#include "dogen/test_models/database/serialization/northwind/employee_territories_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace database {
namespace northwind {

class employee_territories final {
public:
    employee_territories() = default;
    employee_territories(const employee_territories&) = default;
    employee_territories(employee_territories&&) = default;
    ~employee_territories() = default;

public:
    explicit employee_territories(const dogen::test_models::database::northwind::employee_territories_key& employee_territories_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::database::northwind::employee_territories& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::database::northwind::employee_territories& v, unsigned int version);

public:
    const dogen::test_models::database::northwind::employee_territories_key& employee_territories_key() const;
    dogen::test_models::database::northwind::employee_territories_key& employee_territories_key();
    void employee_territories_key(const dogen::test_models::database::northwind::employee_territories_key& v);
    void employee_territories_key(const dogen::test_models::database::northwind::employee_territories_key&& v);

public:
    bool operator==(const employee_territories& rhs) const;
    bool operator!=(const employee_territories& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(employee_territories& other) noexcept;
    employee_territories& operator=(employee_territories other);

private:
    dogen::test_models::database::northwind::employee_territories_key employee_territories_key_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::test_models::database::northwind::employee_territories& lhs,
    dogen::test_models::database::northwind::employee_territories& rhs) {
    lhs.swap(rhs);
}

}

#endif
