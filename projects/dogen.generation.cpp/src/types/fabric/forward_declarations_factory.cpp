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
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.coding/types/meta_model/structural/object.hpp"
#include "dogen.coding/types/meta_model/structural/enumeration.hpp"
#include "dogen.coding/types/meta_model/structural/exception.hpp"
#include "dogen.coding/types/meta_model/structural/primitive.hpp"
#include "dogen.coding/types/meta_model/structural/visitor.hpp"
#include "dogen.coding/types/meta_model/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/forward_declarations.hpp"
#include "dogen.generation.cpp/types/fabric/forward_declarations_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("generation.cpp.fabric.forward_declarations_factory"));

}

namespace dogen::generation::cpp::fabric {

using coding::meta_model::technical_space;

class generator final : public coding::meta_model::element_visitor {
private:
    template<typename Element>
    boost::shared_ptr<forward_declarations> create(const Element& e) const {
        auto r(boost::make_shared<forward_declarations>());
        r->name(e.name());
        r->meta_name(meta_name_factory::make_forward_declarations_name());
        r->origin_type(e.origin_type());
        r->is_element_extension(true);
        r->intrinsic_technical_space(technical_space::cpp);

        /*
         * FIXME: The copying of the configuration is one big hack. We
         * are copying the configuration from the original element
         * because it already has all of the processing required. This
         * will not be an issue once we implement forward declarations
         * properly and remove element extensions.
         */
        r->configuration(
            boost::make_shared<variability::meta_model::configuration>(
                *e.configuration()));
        r->configuration()->name().simple(e.name().simple());
        r->configuration()->name().qualified(e.name().qualified().dot());
        return r;
    }

public:
    std::list<boost::shared_ptr<coding::meta_model::element>>
    result() { return result_; }

public:
    using coding::meta_model::element_visitor::visit;
    void visit(coding::meta_model::structural::visitor& v) {
        result_.push_back(create(v));
    }

    void visit(coding::meta_model::structural::enumeration& e) {
        const auto fd(create(e));
        fd->is_enum(true);
        fd->underlying_element(e.underlying_element());
        fd->intrinsic_technical_space(technical_space::cpp);
        result_.push_back(fd);
    }

    void visit(coding::meta_model::structural::primitive& p) {
        result_.push_back(create(p));
    }

    void visit(coding::meta_model::structural::object& o) {
        result_.push_back(create(o));
    }

    void visit(coding::meta_model::structural::exception& e) {
        const auto fd(create(e));
        fd->is_exception(true);
        fd->intrinsic_technical_space(technical_space::cpp);
        result_.push_back(fd);
    }

private:
    std::list<boost::shared_ptr<coding::meta_model::element>> result_;
};

std::list<boost::shared_ptr<coding::meta_model::element>>
forward_declarations_factory::
make(const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating forward declarations.";

    generator g;
    for(auto& ptr : m.elements())
        ptr->accept(g);

    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated forward declarations: " << r.size();
    return r;
}

}