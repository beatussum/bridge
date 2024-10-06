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

    /**
     * @brief Inserts a color to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, color __value)
    {
        switch (__value) {
            case color::club:
                __os << 'C';
                break;

            case color::diamond:
                __os << 'D';
                break;

            case color::heart:
                __os << 'H';
                break;

            case color::spade:
                __os << 'S';
                break;

            default:
                __os << '?';
                break;
        }

        return __os;
    }

    /**
     * @brief Inserts a rank to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, rank __value)
    {
        switch (__value) {
            case rank::two:
            case rank::three:
            case rank::four:
            case rank::five:
            case rank::six:
            case rank::seven:
            case rank::eight:
            case rank::nine:
            case rank::ten:
                __os << std::to_string(static_cast<int>(__value));
                break;

            case rank::jack:
                __os << 'J';
                break;

            case rank::queen:
                __os << 'Q';
                break;

            case rank::king:
                __os << 'K';
                break;

            case rank::ace:
                __os << 'A';
                break;

            default:
                __os << "(undefined)";
                break;
        }

        return __os;
    }

    /**
     * @brief Equality operator for card
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is equal to `rhs`
     */

    constexpr bool operator==(const card& __lhs, const card& __rhs) noexcept
        { return (__lhs.c == __rhs.c) && (__lhs.r == __rhs.r); }

    /**
     * @brief Inequality operator for card
     *
     * @param[in] __lhs The left hand side operand
     * @param[in] __rhs The right hand side operand
     *
     * @return If `__lhs` is different from `rhs`
     */

    constexpr bool operator!=(const card& __lhs, const card& __rhs) noexcept
        { return !(__lhs == __rhs); }

    /**
     * @brief Inserts a card to an output stream
     *
     * @param[in] __os The output stream
     * @param[in] __value The value to insert
     *
     * @return The modified output stream
     */

    template<class Ostream>
    constexpr Ostream&& operator<<(Ostream&& __os, const card& __value)
    {
        __os << "card { " << __value.c << __value.r << " }";
        return __os;
    }
}

#endif // BRIDGE_ANALYZER_TYPES_CARD_PLAYING_HPP
