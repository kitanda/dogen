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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_HELPER_DESCRIPTOR_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_HELPER_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/quilt.cpp/types/settings/helper_settings.hpp"
#include "dogen/quilt.cpp/serialization/properties/helper_descriptor_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

class helper_descriptor final {
public:
    helper_descriptor(const helper_descriptor&) = default;
    ~helper_descriptor() = default;

public:
    helper_descriptor();

public:
    helper_descriptor(helper_descriptor&& rhs);

public:
    helper_descriptor(
        const std::list<std::string>& namespaces,
        const std::string& name_identifiable,
        const std::string& name_qualified,
        const std::string& name_tree_qualified,
        const std::string& name_tree_identifiable,
        const boost::optional<dogen::quilt::cpp::settings::helper_settings>& settings,
        const bool is_primitive);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::properties::helper_descriptor& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::properties::helper_descriptor& v, unsigned int version);

public:
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);

    const std::string& name_identifiable() const;
    std::string& name_identifiable();
    void name_identifiable(const std::string& v);
    void name_identifiable(const std::string&& v);

    const std::string& name_qualified() const;
    std::string& name_qualified();
    void name_qualified(const std::string& v);
    void name_qualified(const std::string&& v);

    const std::string& name_tree_qualified() const;
    std::string& name_tree_qualified();
    void name_tree_qualified(const std::string& v);
    void name_tree_qualified(const std::string&& v);

    const std::string& name_tree_identifiable() const;
    std::string& name_tree_identifiable();
    void name_tree_identifiable(const std::string& v);
    void name_tree_identifiable(const std::string&& v);

    const boost::optional<dogen::quilt::cpp::settings::helper_settings>& settings() const;
    boost::optional<dogen::quilt::cpp::settings::helper_settings>& settings();
    void settings(const boost::optional<dogen::quilt::cpp::settings::helper_settings>& v);
    void settings(const boost::optional<dogen::quilt::cpp::settings::helper_settings>&& v);

    bool is_primitive() const;
    void is_primitive(const bool v);

public:
    bool operator==(const helper_descriptor& rhs) const;
    bool operator!=(const helper_descriptor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_descriptor& other) noexcept;
    helper_descriptor& operator=(helper_descriptor other);

private:
    std::list<std::string> namespaces_;
    std::string name_identifiable_;
    std::string name_qualified_;
    std::string name_tree_qualified_;
    std::string name_tree_identifiable_;
    boost::optional<dogen::quilt::cpp::settings::helper_settings> settings_;
    bool is_primitive_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::properties::helper_descriptor& lhs,
    dogen::quilt::cpp::properties::helper_descriptor& rhs) {
    lhs.swap(rhs);
}

}

#endif
