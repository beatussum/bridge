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
 * \ref bridge::analyzer::types::card::playing
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
        color c; ///< The \ref color of the playing card
        rank r;  ///< The \ref rank of the playing card
    };

    /**
     * @brief Inserts a \ref color to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, color __value);

    /**
     * @brief Inserts a \ref rank to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, rank __value);

    /**
     * @brief Equality operator for \ref card
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is equal to \p __rhs
     */

    constexpr bool operator==(const card& __lhs, const card& __rhs) noexcept
        { return (__lhs.c == __rhs.c) && (__lhs.r == __rhs.r); }

    /**
     * @brief Inequality operator for \ref card
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If \p __lhs is different from \p __rhs
     */

    constexpr bool operator!=(const card& __lhs, const card& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a \ref card to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template <class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card& __value)
        { return __os << "card { " << __value.c << __value.r << " }", __os; }
}

#include "playing.ipp"

#endif // BRIDGE_ANALYZER_TYPES_CARD_PLAYING_HPP
