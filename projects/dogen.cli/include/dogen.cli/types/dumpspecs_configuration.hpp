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
#ifndef DOGEN_CLI_TYPES_DUMPSPECS_CONFIGURATION_HPP
#define DOGEN_CLI_TYPES_DUMPSPECS_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/types/reporting_style.hpp"

namespace dogen::cli {

/**
 * @brief Dumps all the specs about this version of dogen.
 */
class dumpspecs_configuration final {
public:
    dumpspecs_configuration(const dumpspecs_configuration&) = default;
    dumpspecs_configuration(dumpspecs_configuration&&) = default;
    ~dumpspecs_configuration() = default;

public:
    dumpspecs_configuration();

public:
    explicit dumpspecs_configuration(const dogen::reporting_style style);

public:
    /**
     * @brief Which style to use when dumping the specs.
     */
    /**@{*/
    dogen::reporting_style style() const;
    dumpspecs_configuration& style(const dogen::reporting_style v);
    /**@}*/

public:
    bool operator==(const dumpspecs_configuration& rhs) const;
    bool operator!=(const dumpspecs_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(dumpspecs_configuration& other) noexcept;
    dumpspecs_configuration& operator=(dumpspecs_configuration other);

private:
    dogen::reporting_style style_;
};

}

namespace std {

template<>
inline void swap(
    dogen::cli::dumpspecs_configuration& lhs,
    dogen::cli::dumpspecs_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
