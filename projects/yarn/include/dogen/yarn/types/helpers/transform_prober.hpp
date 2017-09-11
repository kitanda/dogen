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
#ifndef DOGEN_YARN_TYPES_HELPERS_TRANSFORM_PROBER_HPP
#define DOGEN_YARN_TYPES_HELPERS_TRANSFORM_PROBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <stack>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"
#include "dogen/yarn/types/helpers/transform_metrics.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_builder.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class transform_prober final {
private:
    template<typename Ioable>
    inline void write(const boost::filesystem::path& path,
        const Ioable& target) const {
        boost::filesystem::ofstream stream(path);
        stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        stream << target;
    }

public:
    transform_prober(const bool probe_data, const bool probe_stats,
        const boost::filesystem::path& probe_directory,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp);

private:
    void validate() const;
    bool probing_enabled() const;
    void handle_probe_directory() const;
    void handle_current_directory() const;
    void ensure_transform_position_not_empty() const;

    void write_initial_inputs(
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp) const;

    boost::filesystem::path
    full_path_for_writing(const std::string& id, const std::string& type) const;


public:
    void start_chain(const std::string& id) const;

    template<typename Ioable>
    void start_chain(const std::string& id, const Ioable& input) const {
        start_chain(id);
        if (!probe_data_)
            return;

        ensure_transform_position_not_empty();
        ++transform_position_.top();
        const auto path(full_path_for_writing(id, "input"));
        write(path, input);
    }

    void start_transform(const std::string& id) const;

    template<typename Ioable>
    void start_transform(const std::string& id, const Ioable& input) const {
        if (probe_data_) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto path(full_path_for_writing(id, "input"));
            write(path, input);
        }
        start_transform(id);
    }

    void end_chain() const;

    template<typename Ioable>
    void end_chain(const Ioable& output) const {
        if (probe_data_) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto id(builder_.current().id());
            const auto path(full_path_for_writing(id, "output"));
            write(path, output);
        }
        end_chain();
    }

    void end_transform() const;

    template<typename Ioable>
    void end_transform(const Ioable& output) const {
        if (probe_data_) {
            ensure_transform_position_not_empty();
            ++transform_position_.top();
            const auto id(builder_.current().id());
            const auto path(full_path_for_writing(id, "output"));
            write(path, output);
        }
        end_transform();
    }

private:
    mutable transform_metrics_builder builder_;
    mutable std::stack<unsigned int> transform_position_;
    mutable boost::filesystem::path current_directory_;
    const bool probe_data_;
    const bool probe_stats_;
    const boost::filesystem::path probe_directory_;
};

} } }

#endif
