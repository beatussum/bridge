/*
 * Copyright (C) 2024 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef BRIDGE_ANALYZER_TYPES_RAW_HPP
#define BRIDGE_ANALYZER_TYPES_RAW_HPP

#include "raw/counted.hpp"
#include "raw/uncounted.hpp"

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::types::raw
 */

/**
 * @brief This namespace describes different types related to raw types
 *
 * The types defined is this namespace are related to their associated types in
 * \ref bridge::analyzer::types. These types describe outputs of the neural
 * network or intermediate states.
 */

namespace bridge::analyzer::types::raw
{
    namespace boxed
    {
        class trick;
    }

    /**
     * @brief Cast a \ref uncounted::trick_unit to a \ref counted::trick_unit
     *
     * @param[in] __uncounted The \ref uncounted::trick_unit to cast
     * @return The casted \ref counted::trick_unit
     */

    counted::trick_unit count(const uncounted::trick_unit& __uncounted);

    /**
     * @brief Cast a \ref uncounted::trick to a \ref counted::trick
     *
     * @param[in] __uncounted The \ref uncounted::trick to cast
     * @return The casted \ref counted::trick
     */

    inline counted::trick count(const uncounted::trick& __uncounted)
    {
        return counted::trick {
            count(__uncounted.north),
            count(__uncounted.west),
            count(__uncounted.south),
            count(__uncounted.east)
        };
    }

    /**
     * @brief Cast a \ref boxed::trick to a \ref uncounted::trick
     *
     * If \p __boxed contains only one element, \p __center is used to affect
     * the card to the right player; otherwise, a bounding rect is used and,
     * therefore, all \ref card::boxed_card are compared each other.
     *
     * @param[in] __center The center from which \ref positioning is determined
     * @param[in] __boxed The \ref boxed::trick to cast
     *
     * @return The casted \ref uncounted::trick
     */

    uncounted::trick unbox(
        const cv::Point2f& __center,
        const boxed::trick& __boxed
    );
}

#endif // BRIDGE_ANALYZER_TYPES_RAW_HPP
