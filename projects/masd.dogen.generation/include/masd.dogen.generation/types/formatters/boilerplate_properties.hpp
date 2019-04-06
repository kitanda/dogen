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
#ifndef MASD_DOGEN_GENERATION_TYPES_FORMATTERS_BOILERPLATE_PROPERTIES_HPP
#define MASD_DOGEN_GENERATION_TYPES_FORMATTERS_BOILERPLATE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"

namespace masd::dogen::generation::formatters {

class boilerplate_properties final {
public:
    boilerplate_properties(const boilerplate_properties&) = default;
    boilerplate_properties(boilerplate_properties&&) = default;
    ~boilerplate_properties() = default;

public:
    boilerplate_properties();

public:
    boilerplate_properties(
        const std::string& preamble,
        const std::string& postamble,
        const std::list<std::string>& dependencies,
        const std::string& header_guard,
        const masd::dogen::coding::meta_model::technical_space technical_space);

public:
    const std::string& preamble() const;
    std::string& preamble();
    void preamble(const std::string& v);
    void preamble(const std::string&& v);

    const std::string& postamble() const;
    std::string& postamble();
    void postamble(const std::string& v);
    void postamble(const std::string&& v);

    const std::list<std::string>& dependencies() const;
    std::list<std::string>& dependencies();
    void dependencies(const std::list<std::string>& v);
    void dependencies(const std::list<std::string>&& v);

    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);

    masd::dogen::coding::meta_model::technical_space technical_space() const;
    void technical_space(const masd::dogen::coding::meta_model::technical_space v);

public:
    bool operator==(const boilerplate_properties& rhs) const;
    bool operator!=(const boilerplate_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(boilerplate_properties& other) noexcept;
    boilerplate_properties& operator=(boilerplate_properties other);

private:
    std::string preamble_;
    std::string postamble_;
    std::list<std::string> dependencies_;
    std::string header_guard_;
    masd::dogen::coding::meta_model::technical_space technical_space_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::formatters::boilerplate_properties& lhs,
    masd::dogen::generation::formatters::boilerplate_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif