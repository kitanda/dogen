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
#include "dogen.org/types/helpers/node.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::org::helpers::node>& lhs,
const boost::shared_ptr<dogen::org::helpers::node>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::org::helpers {

node::node(
    const dogen::org::entities::headline& data,
    const std::list<boost::shared_ptr<dogen::org::helpers::node> >& children)
    : data_(data),
      children_(children) { }

void node::swap(node& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(children_, other.children_);
}

bool node::operator==(const node& rhs) const {
    return data_ == rhs.data_ &&
        children_ == rhs.children_;
}

node& node::operator=(node other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::org::entities::headline& node::data() const {
    return data_;
}

dogen::org::entities::headline& node::data() {
    return data_;
}

void node::data(const dogen::org::entities::headline& v) {
    data_ = v;
}

void node::data(const dogen::org::entities::headline&& v) {
    data_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::org::helpers::node> >& node::children() const {
    return children_;
}

std::list<boost::shared_ptr<dogen::org::helpers::node> >& node::children() {
    return children_;
}

void node::children(const std::list<boost::shared_ptr<dogen::org::helpers::node> >& v) {
    children_ = v;
}

void node::children(const std::list<boost::shared_ptr<dogen::org::helpers::node> >&& v) {
    children_ = std::move(v);
}

}
