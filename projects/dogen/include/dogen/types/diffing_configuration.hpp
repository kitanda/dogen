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
#ifndef DOGEN_TYPES_DIFFING_CONFIGURATION_HPP
#define DOGEN_TYPES_DIFFING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/types/diffing_destination.hpp"

namespace dogen {

/**
 * @brief Configuration for diff generation.
 */
class diffing_configuration final {
public:
    diffing_configuration(const diffing_configuration&) = default;
    ~diffing_configuration() = default;

public:
    diffing_configuration();

public:
    diffing_configuration(diffing_configuration&& rhs);

public:
    diffing_configuration(
        const dogen::diffing_destination destination,
        const boost::filesystem::path& output_directory);

public:
    dogen::diffing_destination destination() const;
    diffing_configuration& destination(const dogen::diffing_destination v);

    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    diffing_configuration& output_directory(const boost::filesystem::path& v);
    diffing_configuration& output_directory(const boost::filesystem::path&& v);

public:
    bool operator==(const diffing_configuration& rhs) const;
    bool operator!=(const diffing_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(diffing_configuration& other) noexcept;
    diffing_configuration& operator=(diffing_configuration other);

private:
    dogen::diffing_destination destination_;
    boost::filesystem::path output_directory_;
};

}

namespace std {

template<>
inline void swap(
    dogen::diffing_configuration& lhs,
    dogen::diffing_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
