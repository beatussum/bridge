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

        metadata metadata; ///< The metadata of the deal
    };
}

#endif // BRIDGE_ANALYZER_TYPES_DEAL_HPP
