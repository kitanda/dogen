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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/inclusion_directives.hpp"

namespace dogen::physical::entities {

class path_properties final {
public:
    path_properties() = default;
    path_properties(const path_properties&) = default;
    ~path_properties() = default;

public:
    path_properties(path_properties&& rhs);

public:
    path_properties(
        const boost::filesystem::path& file_path,
        const std::string& header_guard,
        const boost::filesystem::path& inclusion_path,
        const dogen::physical::entities::inclusion_directives& inclusion_directives,
        const std::list<std::string>& inclusion_dependencies,
        const std::list<std::string>& using_dependencies,
        const boost::filesystem::path& relative_path);

public:
    /**
     * @brief Full path to the file corresponding to this artefact.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief C++ header guard for this artefact, if any,
     */
    /**@{*/
    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);
    /**@}*/

    /**
     * @brief Path for inclusion for this artefact, computed from the path.
     *
     * Note that this is will not necessarily be used for the inclusion directive.
     */
    /**@{*/
    const boost::filesystem::path& inclusion_path() const;
    boost::filesystem::path& inclusion_path();
    void inclusion_path(const boost::filesystem::path& v);
    void inclusion_path(const boost::filesystem::path&& v);
    /**@}*/

    const dogen::physical::entities::inclusion_directives& inclusion_directives() const;
    dogen::physical::entities::inclusion_directives& inclusion_directives();
    void inclusion_directives(const dogen::physical::entities::inclusion_directives& v);
    void inclusion_directives(const dogen::physical::entities::inclusion_directives&& v);

    /**
     * @brief C++ Inlusion dependencies for this artefact.
     */
    /**@{*/
    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);
    /**@}*/

    const std::list<std::string>& using_dependencies() const;
    std::list<std::string>& using_dependencies();
    void using_dependencies(const std::list<std::string>& v);
    void using_dependencies(const std::list<std::string>&& v);

    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);

public:
    bool operator==(const path_properties& rhs) const;
    bool operator!=(const path_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_properties& other) noexcept;
    path_properties& operator=(path_properties other);

private:
    boost::filesystem::path file_path_;
    std::string header_guard_;
    boost::filesystem::path inclusion_path_;
    dogen::physical::entities::inclusion_directives inclusion_directives_;
    std::list<std::string> inclusion_dependencies_;
    std::list<std::string> using_dependencies_;
    boost::filesystem::path relative_path_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::path_properties& lhs,
    dogen::physical::entities::path_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
