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

        metadata m; ///< The metadata of the auction
    };

    /**
     * @brief An aggregate describing a player
     */

    struct player
    {
        std::string first_name; ///< The first name of the player
        std::string last_name;  ///< The last name of the player

        metadata m; ///< The metadata of the player
    };

    /**
     * @brief An aggregate describing a game
     */

    struct game
    {
        player north; ///< The north player of the game
        player west;  ///< The west player of the game
        player south; ///< The south player of the game
        player east;  ///< The east player of the game

        auction a;                        ///< The auction of the game
        deal::deal d;                     ///< The deal of the game
        std::vector<trick::trick> tricks; ///< The tricks of the game

        metadata m; ///< The metadata of the game
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
        none   ///< The positioning is not specified
    };

    /**
     * @brief A trick as analyzed by the IA model
     */

    struct raw_trick
    {
        std::vector<card::card> north; ///< North's cards on the table
        std::vector<card::card> west;  ///< West's cards on the table
        std::vector<card::card> south; ///< South's cards on the table
        std::vector<card::card> east;  ///< East's cards on the table
    };

    /**
     * @brief Equality operator for auction
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator==(const auction& __lhs, const auction& __rhs) noexcept
    {
        return
            (__lhs.first_player == __rhs.first_player) &&
            (__lhs.bidding_cards == __rhs.bidding_cards);
    }

    /**
     * @brief Inequality operator for auction
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    inline bool operator!=(const auction& __lhs, const auction& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Equality operator for player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator==(const player& __lhs, const player& __rhs) noexcept
    {
        return
            (__lhs.first_name == __rhs.first_name) &&
            (__lhs.last_name == __rhs.last_name);
    }

    /**
     * @brief Inequality operator for player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    inline bool operator!=(const player& __lhs, const player& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Less-than operator for player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is lesser than `rhs`
     */

    inline bool operator<(const player& __lhs, const player& __rhs) noexcept
    {
        return
            (__lhs.last_name == __rhs.last_name) ?
            (__lhs.first_name < __rhs.first_name) :
            (__lhs.last_name < __rhs.last_name);
    }

    /**
     * @brief Greater-than operator for player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is greater than `rhs`
     */

    inline bool operator>(const player& __lhs, const player& __rhs) noexcept
        { return !(__lhs == __rhs) && (__rhs < __lhs); }

    /**
     * @brief Less-equal operator for player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is lesser than or equal to `rhs`
     */

    inline bool operator<=(const player& __lhs, const player& __rhs) noexcept
        { return (__lhs == __rhs) || (__rhs < __lhs); }

    /**
     * @brief Greater-equal operator for player
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is greater than or equal to `rhs`
     */

    inline bool operator>=(const player& __lhs, const player& __rhs) noexcept
        { return !(__lhs < __rhs); }

    /**
     * @brief Inserts a player to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    Ostream&& operator<<(Ostream&& __os, const player& __value);

    /**
     * @brief Equality operator for game
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
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
     * @brief Inequality operator for game
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    inline bool operator!=(const game& __lhs, const game& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a phase to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, phase __value);

    /**
     * @brief Inserts a positioning to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, positioning __value);

    /**
     * @brief Equality operator for raw_trick
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    inline bool operator==(
        const raw_trick& __lhs,
        const raw_trick& __rhs
    ) noexcept
    {
        return
            (__lhs.north == __rhs.north) &&
            (__lhs.west == __rhs.west) &&
            (__lhs.south == __rhs.south) &&
            (__lhs.east == __rhs.east);
    }

    /**
     * @brief Inequality operator for raw_trick
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    inline bool operator!=(
        const raw_trick& __lhs,
        const raw_trick& __rhs
    ) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Cast a type to std::string
     *
     * @param[in] __value The type to cast
     * @return A std::string representing the type
     */

    template <class T>
    std::string to_string(const T& __value);
}

#include "types.ipp"

#endif // BRIDGE_ANALYZER_TYPES_HPP
