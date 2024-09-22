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


#ifndef BRIDGE_ANALYZER_TYPES_TRICK_HPP
#define BRIDGE_ANALYZER_TYPES_TRICK_HPP

#include "card/playing.hpp"

#include <any>
#include <array>

namespace bridge::analyzer::types
{
    enum struct positioning;

    /**
     * @brief An aggregate describing a trick unit
     */

    struct trick_unit
    {
        card::playing::card card; ///< The card played by the associated player
        positioning positioning;  ///< The positioning of the associated player
    };

    /**
     * @brief An aggregate describing a trick
     */

    struct trick
    {
        /**
         * @brief The four units composing the trick
         *
         * These units are stored in the order in which they were played.
         */

        std::array<trick_unit, 4> units;

        std::any metadata; ///< The metadata of the trick
    };
}

#endif // BRIDGE_ANALYZER_TYPES_TRICK_HPP
