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
#include "dogen.codec/types/entities/reference_graph_data.hpp"

namespace dogen::codec::entities {

reference_graph_data::reference_graph_data(
    const std::string& root,
    const std::unordered_map<std::string, std::list<std::string> >& edges_per_model)
    : root_(root),
      edges_per_model_(edges_per_model) { }

void reference_graph_data::swap(reference_graph_data& other) noexcept {
    using std::swap;
    swap(root_, other.root_);
    swap(edges_per_model_, other.edges_per_model_);
}

bool reference_graph_data::operator==(const reference_graph_data& rhs) const {
    return root_ == rhs.root_ &&
        edges_per_model_ == rhs.edges_per_model_;
}

reference_graph_data& reference_graph_data::operator=(reference_graph_data other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& reference_graph_data::root() const {
    return root_;
}

std::string& reference_graph_data::root() {
    return root_;
}

void reference_graph_data::root(const std::string& v) {
    root_ = v;
}

void reference_graph_data::root(const std::string&& v) {
    root_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& reference_graph_data::edges_per_model() const {
    return edges_per_model_;
}

std::unordered_map<std::string, std::list<std::string> >& reference_graph_data::edges_per_model() {
    return edges_per_model_;
}

void reference_graph_data::edges_per_model(const std::unordered_map<std::string, std::list<std::string> >& v) {
    edges_per_model_ = v;
}

void reference_graph_data::edges_per_model(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    edges_per_model_ = std::move(v);
}

}
