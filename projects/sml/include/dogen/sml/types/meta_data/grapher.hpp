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
#ifndef DOGEN_SML_TYPES_META_DATA_GRAPHER_HPP
#define DOGEN_SML_TYPES_META_DATA_GRAPHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/sml/types/meta_data/enricher_interface.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

/**
 * @brief Graph of dependencies between enrichers.
 */
typedef boost::adjacency_list<
    boost::setS, boost::vecS, boost::directedS,
    std::shared_ptr<enricher_interface>
    > graph_type;

/**
 * @brief Builds a DAG of enrichers.
 */
class grapher {
private:
    typedef boost::graph_traits<graph_type>::vertex_descriptor
    vertex_descriptor_type;

    typedef std::unordered_map<std::string, vertex_descriptor_type>
    id_to_vertex_type;

public:
    grapher();

private:
    /**
     * @brief Given a enricher ID, return its associated vertex.
     *
     * If the vertex does not yet exist, creates it.
     *
     * @param id enricher ID.
     */
    vertex_descriptor_type vertex_for_id(const std::string& id);

    /**
     * @brief Ensures the graph has not yet been built.
     */
    void require_not_built() const;

    /**
     * @brief Ensures the graph has been built.
     */
    void require_built() const;

public:
    /**
     * @brief Adds an object to the graph.
     *
     * @pre The graph must not yet have been built.
     * @pre The object must be relevant to the graph.
     */
    void add(std::shared_ptr<enricher_interface> e);

    /**
     * @brief Returns true if the graph has been built, false
     * otherwise.
     */
    bool is_built() const { return built_; }

    /**
     * @brief Generate a DAG of all objects that have been added.
     *
     * @pre Graph must not yet have been built.
     */
    void build();

    /**
     * @brief Returns the generated graph.
     *
     * @pre The graph must have already been built.
     */
    const graph_type& graph() const;

private:
    bool built_;
    graph_type graph_;
    id_to_vertex_type id_to_vertex_;
    id_to_vertex_type orphanage_;
    vertex_descriptor_type root_vertex_;
    std::shared_ptr<enricher_interface> root_;
};

} } }

#endif
