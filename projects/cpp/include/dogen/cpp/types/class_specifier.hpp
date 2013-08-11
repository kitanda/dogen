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
#ifndef DOGEN_CPP_TYPES_CLASS_SPECIFIER_HPP
#define DOGEN_CPP_TYPES_CLASS_SPECIFIER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/cpp/serialization/class_specifier_fwd_ser.hpp"
#include "dogen/cpp/types/class_head.hpp"
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/member_specification.hpp"

namespace dogen {
namespace cpp {

class class_specifier final : public dogen::cpp::entity {
public:
    class_specifier() = default;
    class_specifier(const class_specifier&) = default;
    class_specifier(class_specifier&&) = default;

    virtual ~class_specifier() noexcept { }

public:
    class_specifier(
        const std::string& documentation,
        const dogen::cpp::class_head& head,
        const std::list<dogen::cpp::member_specification>& members);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_specifier& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_specifier& v, unsigned int version);

public:
    virtual void accept(const entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const entity_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    const dogen::cpp::class_head& head() const;
    dogen::cpp::class_head& head();
    void head(const dogen::cpp::class_head& v);
    void head(const dogen::cpp::class_head&& v);

    const std::list<dogen::cpp::member_specification>& members() const;
    std::list<dogen::cpp::member_specification>& members();
    void members(const std::list<dogen::cpp::member_specification>& v);
    void members(const std::list<dogen::cpp::member_specification>&& v);

public:
    bool operator==(const class_specifier& rhs) const;
    bool operator!=(const class_specifier& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::entity& other) const override;

public:
    void swap(class_specifier& other) noexcept;
    class_specifier& operator=(class_specifier other);

private:
    dogen::cpp::class_head head_;
    std::list<dogen::cpp::member_specification> members_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::class_specifier& lhs,
    dogen::cpp::class_specifier& rhs) {
    lhs.swap(rhs);
}

}

#endif
