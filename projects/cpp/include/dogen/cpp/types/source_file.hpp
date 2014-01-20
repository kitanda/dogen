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
#ifndef DOGEN_CPP_TYPES_SOURCE_FILE_HPP
#define DOGEN_CPP_TYPES_SOURCE_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "dogen/cpp/serialization/source_file_fwd_ser.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/cpp/types/entity_fwd.hpp"
#include "dogen/cpp/types/includes.hpp"
#include "dogen/formatters/types/annotation.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a file containing C++ source code.
 */
class source_file final {
public:
    source_file() = default;
    source_file(const source_file&) = default;
    ~source_file() = default;

public:
    source_file(source_file&& rhs);

public:
    source_file(
        const std::string& documentation,
        const dogen::cpp::includes& includes,
        const dogen::cpp::content_descriptor& descriptor,
        const std::string& header_guard,
        const boost::filesystem::path& file_path,
        const boost::filesystem::path& relative_path,
        const boost::shared_ptr<dogen::cpp::entity>& entity,
        const dogen::formatters::annotation& annotation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const source_file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, source_file& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Headers included by this source file.
     */
    /**@{*/
    const dogen::cpp::includes& includes() const;
    dogen::cpp::includes& includes();
    void includes(const dogen::cpp::includes& v);
    void includes(const dogen::cpp::includes&& v);
    /**@}*/

    /**
     * @brief Description of the file's content.
     */
    /**@{*/
    const dogen::cpp::content_descriptor& descriptor() const;
    dogen::cpp::content_descriptor& descriptor();
    void descriptor(const dogen::cpp::content_descriptor& v);
    void descriptor(const dogen::cpp::content_descriptor&& v);
    /**@}*/

    /**
     * @brief If file type is header, name to use for header guards.
     */
    /**@{*/
    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);
    /**@}*/

    /**
     * @brief Path to the file.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Relative path to file.
     */
    /**@{*/
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Entity contained in this file, if any.
     */
    /**@{*/
    const boost::shared_ptr<dogen::cpp::entity>& entity() const;
    boost::shared_ptr<dogen::cpp::entity>& entity();
    void entity(const boost::shared_ptr<dogen::cpp::entity>& v);
    void entity(const boost::shared_ptr<dogen::cpp::entity>&& v);
    /**@}*/

    const dogen::formatters::annotation& annotation() const;
    dogen::formatters::annotation& annotation();
    void annotation(const dogen::formatters::annotation& v);
    void annotation(const dogen::formatters::annotation&& v);

public:
    bool operator==(const source_file& rhs) const;
    bool operator!=(const source_file& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(source_file& other) noexcept;
    source_file& operator=(source_file other);

private:
    std::string documentation_;
    dogen::cpp::includes includes_;
    dogen::cpp::content_descriptor descriptor_;
    std::string header_guard_;
    boost::filesystem::path file_path_;
    boost::filesystem::path relative_path_;
    boost::shared_ptr<dogen::cpp::entity> entity_;
    dogen::formatters::annotation annotation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::source_file& lhs,
    dogen::cpp::source_file& rhs) {
    lhs.swap(rhs);
}

}

#endif
