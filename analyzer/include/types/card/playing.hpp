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


#ifndef BRIDGE_ANALYZER_TYPES_CARD_PLAYING_HPP
#define BRIDGE_ANALYZER_TYPES_CARD_PLAYING_HPP

/**
 * @file
 *
 * @brief The base header of the namespace
 * bridge::analyzer::types::card::playing
 */

/**
 * @brief This namespace describes the playing card type and its associated
 * types
 */

namespace bridge::analyzer::types::card::playing
{
    /**
     * @brief The color of a playing card
     */

    enum struct color
    {
        club,    ///< A club
        diamond, ///< A diamond
        heart,   ///< A heart
        spade    ///< A spade
    };

    /**
     * @brief The rank of a playing card
     */

    enum struct rank
    {
        two = 2, ///< 2
        three,   ///< 3
        four,    ///< 4
        five,    ///< 5
        six,     ///< 6
        seven,   ///< 7
        eight,   ///< 8
        nine,    ///< 9
        ten,     ///< 10
        jack,    ///< J
        queen,   ///< Q
        king,    ///< K
        ace      ///< A
    };

    /**
     * @brief A playing card
     */

    struct card
    {
        color c; ///< The color of the playing card
        rank r;  ///< The rank of the playing card
    };
}

#endif // BRIDGE_ANALYZER_TYPES_CARD_PLAYING_HPP
