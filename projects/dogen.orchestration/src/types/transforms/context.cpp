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
#include "dogen.orchestration/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

context::context(
    const dogen::variability::transforms::context& variability_context,
    const dogen::codec::transforms::context& codec_context,
    const dogen::logical::transforms::context& logical_context,
    const dogen::text::transforms::context& text_context,
    const dogen::physical::transforms::context& physical_context)
    : variability_context_(variability_context),
      codec_context_(codec_context),
      logical_context_(logical_context),
      text_context_(text_context),
      physical_context_(physical_context) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(variability_context_, other.variability_context_);
    swap(codec_context_, other.codec_context_);
    swap(logical_context_, other.logical_context_);
    swap(text_context_, other.text_context_);
    swap(physical_context_, other.physical_context_);
}

bool context::operator==(const context& rhs) const {
    return variability_context_ == rhs.variability_context_ &&
        codec_context_ == rhs.codec_context_ &&
        logical_context_ == rhs.logical_context_ &&
        text_context_ == rhs.text_context_ &&
        physical_context_ == rhs.physical_context_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::variability::transforms::context& context::variability_context() const {
    return variability_context_;
}

dogen::variability::transforms::context& context::variability_context() {
    return variability_context_;
}

void context::variability_context(const dogen::variability::transforms::context& v) {
    variability_context_ = v;
}

void context::variability_context(const dogen::variability::transforms::context&& v) {
    variability_context_ = std::move(v);
}

const dogen::codec::transforms::context& context::codec_context() const {
    return codec_context_;
}

dogen::codec::transforms::context& context::codec_context() {
    return codec_context_;
}

void context::codec_context(const dogen::codec::transforms::context& v) {
    codec_context_ = v;
}

void context::codec_context(const dogen::codec::transforms::context&& v) {
    codec_context_ = std::move(v);
}

const dogen::logical::transforms::context& context::logical_context() const {
    return logical_context_;
}

dogen::logical::transforms::context& context::logical_context() {
    return logical_context_;
}

void context::logical_context(const dogen::logical::transforms::context& v) {
    logical_context_ = v;
}

void context::logical_context(const dogen::logical::transforms::context&& v) {
    logical_context_ = std::move(v);
}

const dogen::text::transforms::context& context::text_context() const {
    return text_context_;
}

dogen::text::transforms::context& context::text_context() {
    return text_context_;
}

void context::text_context(const dogen::text::transforms::context& v) {
    text_context_ = v;
}

void context::text_context(const dogen::text::transforms::context&& v) {
    text_context_ = std::move(v);
}

const dogen::physical::transforms::context& context::physical_context() const {
    return physical_context_;
}

dogen::physical::transforms::context& context::physical_context() {
    return physical_context_;
}

void context::physical_context(const dogen::physical::transforms::context& v) {
    physical_context_ = v;
}

void context::physical_context(const dogen::physical::transforms::context&& v) {
    physical_context_ = std::move(v);
}

}
