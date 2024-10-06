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


#ifndef BRIDGE_ANALYZER_TYPES_DEAL_HPP
#define BRIDGE_ANALYZER_TYPES_DEAL_HPP

#include "card/playing.hpp"
#include "metadata.hpp"

#include <vector>

/**
 * @file
 * @brief This namespace describes the deal type and its associated types
 */

namespace bridge::analyzer::types
{
    using deal_unit = std::vector<card::playing::card>; ///< A deal unit

    /**
     * @brief An aggregate describing a deal
     */

    struct deal
    {
        deal_unit north; ///< The deal unit of the north player
        deal_unit west;  ///< The deal unit of the west player
        deal_unit south; ///< The deal unit of the south player
        deal_unit east;  ///< The deal unit of the north player

        metadata m; ///< The metadata of the deal
    };

    /**
     * @brief Equality operator for deal
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator==(const deal& __lhs, const deal& __rhs) noexcept
    {
        return
            (__lhs.north == __rhs.north) &&
            (__lhs.west == __rhs.west) &&
            (__lhs.south == __rhs.south) &&
            (__lhs.east == __rhs.east);
    }

    /**
     * @brief Inequality operator for deal
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    inline bool operator!=(const deal& __lhs, const deal& __rhs) noexcept
        { return !(__lhs == __rhs); }
}

#endif // BRIDGE_ANALYZER_TYPES_DEAL_HPP
