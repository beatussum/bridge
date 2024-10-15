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

#include "types/card.hpp"
#include "types/deal.hpp"
#include "types/metadata.hpp"
#include "types/trick.hpp"

/**
 * @file
 * @brief The base header of the namespace \ref bridge::analyzer::types
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
         * @brief The \ref positioning of the first player to call
         */

        positioning first_player;

        /**
         * @brief The bidding cards of the auction
         *
         * @note The cards are described clockwise from the first player.
         */

        std::vector<card::bidding::card> bidding_cards;

        metadata::metadata m; ///< The \ref metadata of the \ref auction
    };

    /**
     * @brief An aggregate describing a player
     */

    struct player
    {
        std::string first_name; ///< The first name of the \ref player
        std::string last_name;  ///< The last name of the \ref player

        metadata::metadata m; ///< The \ref metadata of the \ref player
    };

    /**
     * @brief An aggregate describing a game
     */

    struct game
    {
        player north; ///< The north \ref player of the \ref game
        player west;  ///< The west \ref player of the \ref game
        player south; ///< The south \ref player of the \ref game
        player east;  ///< The east \ref player of the \ref game

        auction a;                        ///< The \ref auction of the \ref game
        deal::deal d;                     ///< The \ref deal of the \ref game
        std::vector<trick::trick> tricks; ///< The tricks of the \ref game

        metadata::metadata m; ///< The \ref metadata of the \ref game
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
        east,  ///< This is the eastern player
        none   ///< The \ref positioning is not specified
    };

    /**
     * @brief Equality operator for \ref auction
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const auction& __lhs, const auction& __rhs) noexcept
    {
        return
            (__lhs.first_player == __rhs.first_player) &&
            (__lhs.bidding_cards == __rhs.bidding_cards);
    }

    /**
     * @brief Inequality operator for \ref auction
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const auction& __lhs, const auction& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a \ref auction to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const auction& __value);

    /**
     * @brief Equality operator for \ref player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const player& __lhs, const player& __rhs) noexcept
    {
        return
            (__lhs.first_name == __rhs.first_name) &&
            (__lhs.last_name == __rhs.last_name);
    }

    /**
     * @brief Inequality operator for \ref player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const player& __lhs, const player& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Less-than operator for \ref player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is lesser than \p __rhs
     */

    inline bool operator<(const player& __lhs, const player& __rhs) noexcept
    {
        return
            (__lhs.last_name == __rhs.last_name) ?
            (__lhs.first_name < __rhs.first_name) :
            (__lhs.last_name < __rhs.last_name);
    }

    /**
     * @brief Greater-than operator for \ref player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is greater than \p __rhs
     */

    inline bool operator>(const player& __lhs, const player& __rhs) noexcept
        { return !(__lhs == __rhs) && (__rhs < __lhs); }

    /**
     * @brief Less-equal operator for \ref player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is lesser than or equal to \p __rhs
     */

    inline bool operator<=(const player& __lhs, const player& __rhs) noexcept
        { return (__lhs == __rhs) || (__rhs < __lhs); }

    /**
     * @brief Greater-equal operator for \ref player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is greater than or equal to \p __rhs
     */

    inline bool operator>=(const player& __lhs, const player& __rhs) noexcept
        { return !(__lhs < __rhs); }

    /**
     * @brief Inserts a \ref player to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const player& __value);

    /**
     * @brief Equality operator for \ref game
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    inline bool operator==(const game& __lhs, const game& __rhs) noexcept
    {
        return
            (__lhs.north == __rhs.north) &&
            (__lhs.west == __rhs.west) &&
            (__lhs.south == __rhs.south) &&
            (__lhs.east == __rhs.east) &&
            (__lhs.a == __rhs.a) &&
            (__lhs.d == __rhs.d) &&
            (__lhs.tricks == __rhs.tricks);
    }

    /**
     * @brief Inequality operator for \ref game
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    inline bool operator!=(const game& __lhs, const game& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a \ref game to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    Ostream&& operator<<(Ostream&& __os, const game& __value);

    /**
     * @brief Inserts a \ref phase to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, phase __value);

    /**
     * @brief Inserts a \ref positioning to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, positioning __value);
}

#include "types.ipp"

#endif // BRIDGE_ANALYZER_TYPES_HPP
