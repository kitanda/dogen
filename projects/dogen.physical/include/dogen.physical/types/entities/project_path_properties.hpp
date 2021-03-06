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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PROJECT_PATH_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PROJECT_PATH_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::physical::entities {

/**
 * @brief Legacy type containing all proprties related to paths.
 */
class project_path_properties final {
public:
    project_path_properties(const project_path_properties&) = default;
    ~project_path_properties() = default;

public:
    project_path_properties();

public:
    project_path_properties(project_path_properties&& rhs);

public:
    project_path_properties(
        const std::string& include_directory_name,
        const std::string& source_directory_name,
        const bool disable_facet_directories,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension,
        const std::string& tests_directory_name,
        const std::string& templates_directory_name,
        const std::string& templates_file_extension,
        const bool enable_unique_file_names,
        const std::string& headers_output_directory,
        const bool enable_backend_directories,
        const boost::filesystem::path& implementation_directory_full_path,
        const boost::filesystem::path& include_directory_full_path,
        const boost::filesystem::path& templates_directory_full_path);

public:
    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    bool disable_facet_directories() const;
    void disable_facet_directories(const bool v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

    const std::string& tests_directory_name() const;
    std::string& tests_directory_name();
    void tests_directory_name(const std::string& v);
    void tests_directory_name(const std::string&& v);

    const std::string& templates_directory_name() const;
    std::string& templates_directory_name();
    void templates_directory_name(const std::string& v);
    void templates_directory_name(const std::string&& v);

    const std::string& templates_file_extension() const;
    std::string& templates_file_extension();
    void templates_file_extension(const std::string& v);
    void templates_file_extension(const std::string&& v);

    bool enable_unique_file_names() const;
    void enable_unique_file_names(const bool v);

    /**
     * @brief Directory in which to place C++ header files. Must be a relative path.
     */
    /**@{*/
    const std::string& headers_output_directory() const;
    std::string& headers_output_directory();
    void headers_output_directory(const std::string& v);
    void headers_output_directory(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, backends should have backend-specific directories to store their artefacts.
     */
    /**@{*/
    bool enable_backend_directories() const;
    void enable_backend_directories(const bool v);
    /**@}*/

    const boost::filesystem::path& implementation_directory_full_path() const;
    boost::filesystem::path& implementation_directory_full_path();
    void implementation_directory_full_path(const boost::filesystem::path& v);
    void implementation_directory_full_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& include_directory_full_path() const;
    boost::filesystem::path& include_directory_full_path();
    void include_directory_full_path(const boost::filesystem::path& v);
    void include_directory_full_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& templates_directory_full_path() const;
    boost::filesystem::path& templates_directory_full_path();
    void templates_directory_full_path(const boost::filesystem::path& v);
    void templates_directory_full_path(const boost::filesystem::path&& v);

public:
    bool operator==(const project_path_properties& rhs) const;
    bool operator!=(const project_path_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(project_path_properties& other) noexcept;
    project_path_properties& operator=(project_path_properties other);

private:
    std::string include_directory_name_;
    std::string source_directory_name_;
    bool disable_facet_directories_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
    std::string tests_directory_name_;
    std::string templates_directory_name_;
    std::string templates_file_extension_;
    bool enable_unique_file_names_;
    std::string headers_output_directory_;
    bool enable_backend_directories_;
    boost::filesystem::path implementation_directory_full_path_;
    boost::filesystem::path include_directory_full_path_;
    boost::filesystem::path templates_directory_full_path_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::project_path_properties& lhs,
    dogen::physical::entities::project_path_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
