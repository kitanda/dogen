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
#include "dogen.tracing/types/metrics.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::metrics>& lhs,
const boost::shared_ptr<dogen::tracing::metrics>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::tracing {

metrics::metrics()
    : start_(static_cast<unsigned long>(0)),
      end_(static_cast<unsigned long>(0)) { }

metrics::metrics(
    const std::string& transform_id,
    const std::string& model_id,
    const std::string& guid,
    const unsigned long start,
    const unsigned long end,
    const std::list<boost::shared_ptr<dogen::tracing::metrics> >& children)
    : transform_id_(transform_id),
      model_id_(model_id),
      guid_(guid),
      start_(start),
      end_(end),
      children_(children) { }

void metrics::swap(metrics& other) noexcept {
    using std::swap;
    swap(transform_id_, other.transform_id_);
    swap(model_id_, other.model_id_);
    swap(guid_, other.guid_);
    swap(start_, other.start_);
    swap(end_, other.end_);
    swap(children_, other.children_);
}

bool metrics::operator==(const metrics& rhs) const {
    return transform_id_ == rhs.transform_id_ &&
        model_id_ == rhs.model_id_ &&
        guid_ == rhs.guid_ &&
        start_ == rhs.start_ &&
        end_ == rhs.end_ &&
        children_ == rhs.children_;
}

metrics& metrics::operator=(metrics other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& metrics::transform_id() const {
    return transform_id_;
}

std::string& metrics::transform_id() {
    return transform_id_;
}

void metrics::transform_id(const std::string& v) {
    transform_id_ = v;
}

void metrics::transform_id(const std::string&& v) {
    transform_id_ = std::move(v);
}

const std::string& metrics::model_id() const {
    return model_id_;
}

std::string& metrics::model_id() {
    return model_id_;
}

void metrics::model_id(const std::string& v) {
    model_id_ = v;
}

void metrics::model_id(const std::string&& v) {
    model_id_ = std::move(v);
}

const std::string& metrics::guid() const {
    return guid_;
}

std::string& metrics::guid() {
    return guid_;
}

void metrics::guid(const std::string& v) {
    guid_ = v;
}

void metrics::guid(const std::string&& v) {
    guid_ = std::move(v);
}

unsigned long metrics::start() const {
    return start_;
}

void metrics::start(const unsigned long v) {
    start_ = v;
}

unsigned long metrics::end() const {
    return end_;
}

void metrics::end(const unsigned long v) {
    end_ = v;
}

const std::list<boost::shared_ptr<dogen::tracing::metrics> >& metrics::children() const {
    return children_;
}

std::list<boost::shared_ptr<dogen::tracing::metrics> >& metrics::children() {
    return children_;
}

void metrics::children(const std::list<boost::shared_ptr<dogen::tracing::metrics> >& v) {
    children_ = v;
}

void metrics::children(const std::list<boost::shared_ptr<dogen::tracing::metrics> >&& v) {
    children_ = std::move(v);
}

}
