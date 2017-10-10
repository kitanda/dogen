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
#ifndef DOGEN_YARN_TYPES_META_MODEL_BACKEND_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_META_MODEL_BACKEND_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/yarn/serialization/meta_model/backend_properties_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Properties related to the backend.
 */
class backend_properties final {
public:
    backend_properties(const backend_properties&) = default;
    backend_properties(backend_properties&&) = default;
    ~backend_properties() = default;

public:
    backend_properties();

public:
    backend_properties(
        const bool enabled,
        const bool overwrite,
        const std::string& directory,
        const bool force_backend_directory);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::backend_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::backend_properties& v, unsigned int version);

public:
    /**
     * @brief If true, this backend is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    bool overwrite() const;
    void overwrite(const bool v);

    /**
     * @brief Backend specific directory name, if any.
     */
    /**@{*/
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the backend directory will be expressed, even when there is only one
     * backend enabled.
     */
    /**@{*/
    bool force_backend_directory() const;
    void force_backend_directory(const bool v);
    /**@}*/

public:
    bool operator==(const backend_properties& rhs) const;
    bool operator!=(const backend_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(backend_properties& other) noexcept;
    backend_properties& operator=(backend_properties other);

private:
    bool enabled_;
    bool overwrite_;
    std::string directory_;
    bool force_backend_directory_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::backend_properties& lhs,
    dogen::yarn::meta_model::backend_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
