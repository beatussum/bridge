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


#ifndef BRIDGE_ANALYZER_TYPES_HPP
#define BRIDGE_ANALYZER_TYPES_HPP

#include "types/card/bidding.hpp"

#include <any>
#include <string>
#include <vector>

/**
 * @file
 * @brief This header describes basic types used by the analyzer
 */

/**
 * @brief This namespace contains all types used by the analyzer
 */

namespace bridge::analyzer::types
{
    /**
     * @brief An aggregate describing an auction
     */

    struct auction
    {
        /**
         * @brief The positioning of the first player to call
         */

        positioning first_player;

        /**
         * @brief The bidding cards of the auction
         *
         * @note The cards are described clockwise from the first player.
         */

        std::vector<card::bidding::card> bidding_cards;
    };

    /**
     * @brief An aggregate describing a player
     */

    struct player
    {
        std::string first_name; ///< The first name of the player
        std::string last_name;  ///< The last name of the player
        std::any    metadata;   ///< The metadata of the player
    };

    /**
     * @brief The phase of the game
     */

    enum struct phase
    {
        bidding, ///< The bidding phase
        card     ///< The card-playing phase
    };

    /**
     * @brief A player's position on the table
     */

    enum struct positioning
    {
        north, ///< This is the northern player
        west,  ///< This is the western player
        south, ///< This is the southern player
        east   ///< This is the eastern player
    };
}

#endif // BRIDGE_ANALYZER_TYPES_HPP
